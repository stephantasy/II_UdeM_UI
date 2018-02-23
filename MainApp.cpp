#include "MainApp.h"
#include <wx/aboutdlg.h>


MainApp::MainApp(wxWindow* parent) : MainWindow(parent)
{
    // Initialisation
    m_data.resize(4);
    m_defaultCatFormat = m_staticTextCatDesc->GetValue();
    updateStatusBar(Statusbar_Init);
    
    // Création de la matrice et enregistrement pour recevoir ses messages
    matrix = new Matrix(this);        
    matrix->CallbackInscription([this](){ MatrixHasBeenClosed(); });
}

MainApp::~MainApp()
{
}


// =======================================
// ========== EVENTS  FUNCTIONS ==========
// =======================================


// On demande à quitter le programme
void MainApp::OnExitAsk(wxCommandEvent& event)
{
    wxUnusedVar(event);    
    Close();
}

// On quitte le programme
void MainApp::OnExit(wxCloseEvent& event)
{
    wxUnusedVar(event);  
    
    // Avant de quitter, on s'assure que c'est voulu        
    if (wxMessageBox(_(L"Voulez-vous quitter le programme ?"), _("Quitter"), wxICON_QUESTION | wxYES_NO, this) == wxNO )
            return; 
            
    // Contrôle des sauvegardes
    if ( !isAllDataSafe() ) return;
        
    // On détruit la matrice
    if(matrix)
        matrix->Destroy();
    
    // Fin
    this->Destroy();
}

// About
void MainApp::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.SetName(Text::APP_NAME_FULL);
    info.SetVersion(Text::APP_VERSION);
    info.SetCopyright(Text::APP_COPYRIGHT);
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(Text::APP_DESCRIPTION);    
    info.AddArtist(Text::MY_NAME);
    info.AddDeveloper(Text::MY_NAME);
    info.AddDocWriter(Text::MY_NAME);
    info.AddTranslator(Text::MY_NAME);
    ::wxAboutBox(info);
}

// Ouverture d'un fichier
void MainApp::OnOpenFile(wxCommandEvent& event)
{    
    wxUnusedVar(event);
            
    // Contrôle des sauvegardes
    if ( !isAllDataSafe() ) return;
    
    // Boite de dialogue
    wxFileDialog *openFileDialog = new wxFileDialog(this, _("Ouvrir..."), ".", "Data.csv", "Fichiers CSV (*.csv)|*.csv", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog->ShowModal() == wxID_OK){    
        // On lit le fichier
        ReadFile(openFileDialog->GetPath());
    }
    openFileDialog->Destroy();   
        
    // Mise à jour de la Toolbar
    updateSaveItems();
    
    // Si la matrice est affichée, on la refraichi
    if(m_isMatrixDisplayed)
        refreshMatrix();
}

// On sauvegarde le fichier
void MainApp::OnSaveFile(wxCommandEvent& event)
{
    wxUnusedVar(event);
        
    std::ofstream fs;
	fs.open(m_fileName, std::ios_base::binary);
	inventory->exportToFile(fs);
	fs.close();
    m_isNeedToSaveFile = false;
    updateSaveItems();
    updateStatusBar(Statusbar_NeedSave);
}

// Affichage de la matrice
void MainApp::OnDisplayMatrix(wxCommandEvent& event)
{
    wxUnusedVar(event);
    
    // Si aucun fichier n'est chargé, on quitte
    if( ! m_fileLoaded ) {
        wxMessageBox(_(L"Vous devez ouvrir un fichier avant d'afficher la matrice."), _(L"Information"));
        return;
    }
                 
    // Si la matrice est cachée
    if(!m_isMatrixDisplayed){
        // On affiche la fenêtre au 1er plan
        matrix->Iconize(false);   // restore the window if minimized
        matrix->SetFocus();       // focus on my window
        matrix->Raise();          // bring window to front
        matrix->Show(true);       // show the window
        m_isMatrixDisplayed = true;
        
        // On rempli la matrice
        refreshMatrix();
    }
    // Sinon on la cache
    else{
        matrix->Show(false);    // Hide the window 
        m_isMatrixDisplayed = false;
    }
}

// Comparateur pour le tri des colonnes (car on doit passer l'index de la colonne !)
class ListComparator
{
public:
    explicit ListComparator(int column) : m_column(column) {}    
    bool operator()(const wxVector<wxVariant>& a, const wxVector<wxVariant>& b)
    {
        switch(m_column){
            // Les colonnes contenant des entiers
            case 0:
            case 2:
            {
                wxLongLong c = a[m_column];
                wxLongLong d = b[m_column];
                return (c < d);
            }  
            // Colonnes contenants des String
            default:
            {
                wxString c = a[m_column];
                wxString d = b[m_column];
                if(c.ToStdString() == d.ToStdString()){
                    // Si les String sont égales, on compare les Id
                    wxLongLong e = a[0];
                    wxLongLong f = b[0];
                    return (e < f);
                }
                return (c < d);
            }            
        }
    }
private:
    int m_column;    
};

// Lorsqu'on clique sur l'entête d'une colonne, on la tri
void MainApp::OnColumnSort(wxDataViewEvent& event)
{
    int column = event.GetColumn();
    wxDataViewColumn * const col = m_equipmentList->GetColumn(column);
    if ( !col->IsSortable() ){        
        std::sort(m_data.begin(), m_data.end(), ListComparator (column));
    }
    setDataAfterSort();
}

// Lorsqu'on clique sur un équipement, on affiche le détail
void MainApp::OnItemSelected(wxDataViewEvent& event)
{        
    wxUnusedVar(event);
    
    // Ligne sélectionnée
    int row = m_equipmentList->GetSelectedRow();        // Ligne sélectionnée
    if(row < 0) { return; }                             // Clic dans la DataView mais pas sur un élément        
    
    // Y-a-t'il une modification en cours
    if( isModifInProgress() )
        return;
    
    // On récupère l'Id de la ligne sélectionnée
    wxVariant rowData;    
    m_equipmentList->GetValue(rowData, row, 0);
    wxLongLong index;
    rowData.Convert(&index);
        
    // On remplie la fenêtre de l'équipement
    fillEquipmentDetail((int)index.ToLong()-1);
    
    // On cache les icones
    setCategoryIcon((Equipment::category)-1, false);
    
    m_currentSelectedRow = row;
}

// Recherche
void MainApp::OnSearch(wxCommandEvent& event)
{    
    // Y-at-il des data ?
    if(inventory->getNbEquipment() <= 0)
        return;
        
    // Y-a-t'il une modification en cours
    if( isModifInProgress() )
        return;
    
    // Texte recherché
    wxString laString = event.GetString();
    if(laString.IsEmpty()) return;
    
    m_isRSearchActive = true;
    
    // Renvoie la liste des Id correspondants à la recherche
    idEquipmentListFound = inventory->getRechercheList(idEquipmentListFound, 16, laString.ToStdString());
    
    // On affiche le résultat
    setDataAfterSearch(true);
}

// On rétabli la liste complète des équipements
void MainApp::OnSearchCancel(wxCommandEvent& event)
{
    wxUnusedVar(event);
    
    // Y-a-t'il une modification en cours
    if( isModifInProgress() )
        return;
        
    doSearchCancel();
}

// On affiche la description et le format de données dans la fenêtre "Description"
void MainApp::OnCategoryClic(wxMouseEvent& event)
{
    event.Skip();
    
    if(inventory->getNbEquipment() <= 0)
        return;
    
    wxString desc;
    Equipment::category catName = getCategorieIndex(event.GetId());     // Catégorie
    
    // Texte a afficher
    desc = "";
    desc += inventory->getEquipmentCategoryDesc(catName);
    desc += "\n\nFormat :\n\n";
    desc += inventory->getEquipmentCategoryFormat(catName);
       
    // Convertion de la string pour gérer les caractères spéciaux
    const char* chars = desc.c_str();
    wxString goodStr(chars, wxConvUTF8);
    m_staticTextCatDesc->ChangeValue(goodStr);
}

// Clic sur l'icône "!"
void MainApp::OnInfoClic(wxMouseEvent& event)
{
    event.Skip();
    m_staticTextCatDesc->ChangeValue(L"Cette catégorie a été mofifiée !");
}

// On a modifié une catégorie
void MainApp::OnCategoryModified(wxCommandEvent& event)
{       
    if(m_currentEquipmentIndex < 0) { return; }   // Out of bound Protection
    
    Equipment::category catName = getCategorieIndex(event.GetId());     // Catégorie
    wxString newValue = event.GetString();                              // Nouvelle valeur entrée
    wxString oldValue = m_equipmentMem.at(catName);                     // Ancienne valeur
    bool isOk = inventory->isValidEquipmentValue(m_currentEquipmentIndex, catName, newValue.ToStdString());   // Format Ok ?

    // On affecte la nouvelle valeur
    inventory->setEquipmentValue(m_currentEquipmentIndex, catName, newValue.ToStdString());
        
    // On colorie le fond de l'EditText en fonction du résultat    
    wxTextCtrl *bgd = (wxTextCtrl*)event.GetEventObject();
    if(isOk){        
        // En blanc si la valeur est bonne
        bgd->SetBackgroundColour(wxColour(_("rgb(255,255,255)")));
    }
    else{
        // en rouge si la valeur ne respecte pas le format
        bgd->SetBackgroundColour(wxColour(_("rgb(255,128,128)")));
    }
    // On rafraichi l'affichage
    bgd->Refresh();
    
    // On indique si l'équipement a été modifié en comparant l'ancienne et la nouvelle valeur
    if(newValue.ToStdString() != oldValue.ToStdString()){
        inventory->setEquipmentCategoryModified(m_currentEquipmentIndex, catName, true);    
        // On ajoute une icone si la valeur a été modifiée
        setCategoryIcon(catName, true);    
    }else{        
        inventory->setEquipmentCategoryModified(m_currentEquipmentIndex, catName, false); 
        // On ôte l'icone si la valeur est la même que l'originale
        setCategoryIcon(catName, false);  
    }

    // Si une catégorie est modifié, on cache le bouton "supprimer" et on affiche ceux de la modification
    if(inventory->isEquipmentModified(m_currentEquipmentIndex)){
        setCatagoryModifyButtons(true);
        m_isNeedToSaveEquipment = true;
    }else{        
        setCatagoryModifyButtons(false);
        m_isNeedToSaveEquipment = false;
    }
        
    // On met à jour l'erreur de la catégorie
    setCategoryError(catName, isOk);
    
    // Dans le cas du local, on contrôle aussi le No.Plaque en provoquant un Event
    if(catName == Equipment::Local){
        //On lui réapplique sa valeur, ce qui provoque un Event
        m_textCtrlNoPlaque->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, Equipment::NoPlaque));
    }
}

// On applique la modification apportée à l'équipement
void MainApp::OnEquipmentModify(wxCommandEvent& event)
{      
    wxUnusedVar(event);
    
    if(m_isCategoryError){
        wxMessageBox(L"Veuillez corriger les erreurs avant d'appliquer les modifications.");
    }else{
        
        m_isNeedToSaveEquipment = false;     // Équipement sauvé
        m_isNeedToSaveFile = true;           // Fichier doit être sauvé

        // On copie les valeurs en suppirmant les espaces superflues (avant et après)
        std::string newValue = m_textCtrlLocal->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::Local, Tools::trim(newValue));
                
        newValue = m_textCtrlNom->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::Nom, Tools::trim(newValue));
        
        newValue = m_textCtrlNoPlaque->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::NoPlaque, Tools::trim(newValue));
        
        newValue = m_textCtrlNoPrise->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::NoPrise, Tools::trim(newValue));
        
        // Inutile ici, car c'est une liste de choix
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::CouleurPrise, m_choiceCouleurPrise->GetString(m_choiceCouleurPrise->GetSelection()).ToStdString());
        
        newValue = m_textCtrlSwitch->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::Switch, Tools::trim(newValue));
        
        newValue = m_textCtrlPort->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::Port, Tools::trim(newValue));
        
        newValue = m_textCtrlAppartenance->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::Appartenance, Tools::trim(newValue));
        
        newValue = m_textCtrlArchitecture->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::Architecture, Tools::trim(newValue));
        
        newValue = m_textCtrlOS->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::Os, Tools::trim(newValue));
        
        // Inutile ici, car c'est une liste de choix
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::Type, m_choiceType->GetString(m_choiceType->GetSelection()).ToStdString());
        
        newValue = m_textCtrlResponsable->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::Responsable, Tools::trim(newValue));
        
        newValue = m_textCtrlIdVendeur->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::VendeurId, Tools::trim(newValue));
        
        newValue = m_textCtrlNoSerie->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::NoSerie, Tools::trim(newValue));
        
        newValue = m_textCtrlIP->GetValue().ToStdString();
        inventory->setEquipmentValue(m_currentEquipmentIndex, Equipment::Ip, Tools::trim(newValue));
        
        // On reset les "Modify"
        inventory->resetEquipmentCategoryModified(m_currentEquipmentIndex);
        
        // On cache les icones
        setCategoryIcon((Equipment::category)-1, false);
        
        // On reset l'affichage des boutons
        setCatagoryModifyButtons(false);
        
        // Rafraichi la liste (à cause des modifs) et le détail (à cause du Trim)
        m_isRSearchActive ? setDataAfterSearch(false) :  fillEquipmentsList(false);      // On rafraichi tout ou seulement la recherhe
        fillEquipmentDetail(m_currentEquipmentIndex);
        refreshMatrix();
    }
}

// On annule la modification apportée à l'équipement
void MainApp::OnEquipmentCancel(wxCommandEvent& event)
{
    wxUnusedVar(event);
    
    // On annule
    cancelModification();
    
    // On recharge le détail de l'équipement
    fillEquipmentDetail(m_currentEquipmentIndex);
    
    // On cache les icones
    setCategoryIcon((Equipment::category)-1, false);
}

// On supprime l'équipement
void MainApp::OnEquipmentDelete(wxCommandEvent& event)
{
    wxUnusedVar(event);
    
    // Avant de supprimer, on s'assure que c'est voulu
    if (wxMessageBox(_(L"Êtes-vous sûr de vouloir supprimer cet équipement ?"), _("Supprimer"), wxICON_WARNING | wxYES_NO, this) == wxNO )
            return;
    
    // On le supprime
    inventory->destroyEquipment(m_currentEquipmentIndex);
    
    // Fichier doit être sauvé
    m_isNeedToSaveFile = true;
    
    // On rafraichi la liste
    fillEquipmentsList(true);

    // Annulation de la recherche
    doSearchCancel();   
}


// =======================================
// ========== PUBLIC  FUNCTIONS ==========
// =======================================

// Renvoie si le fichier existe
bool MainApp::IsFileExists(const wxString& fileName) const{
    // On utilise std, car wxFileInputStream génére automatiquement un message d'erreur et on en veut pas.
    std::ifstream f(fileName.ToStdString().c_str());
    return f.good();
}

// On lit le fichier passé en paramètre
void MainApp::ReadFile(const wxString& fileName){
    // Initialisation
    m_fileLoaded = false;    
    m_equipmentList->Enable(false);     // On desactive la DataView
    m_searchCtrl->Enable(false);        // On desactive la recherche
    m_buttonClearSearch->Enable(false); // Bouton Reset
    
    // Si le fichier n'est pas vide
    if(!fileName.IsEmpty()){
        m_fileName = fileName;
        wxFileInputStream input_stream(fileName);
        // Si le fichier est bon (sinon wxFileInputStream génére automatiquement le message d'erreur)
        if (!input_stream.IsOk())
        {
            return;
        }
        else
        {            
            // On (re)crée notre inventaire
            inventory.reset(new Inventory());
        
            // On lit le fichier d'entrée
            wxTextInputStream text(input_stream, _("\x09"), wxConvAuto() );
            while(input_stream.IsOk() && !input_stream.Eof() )
            {            
                inventory->addEquipment(text.ReadLine().ToStdString());
            }
            
            // On rempli la liste
            fillEquipmentsList(true);            
            
            // Init
            m_fileLoaded = true;
            m_isNeedToSaveFile = false;
            m_isRSearchActive = false;
            
            if(inventory->getNbEquipment() > 0){
                m_equipmentList->Enable(true);     // On active la DataView
                m_searchCtrl->Enable(true);        // On active la recherche
                m_buttonClearSearch->Enable(true); // Bouton Reset
            }
        }
    }
}

// Fonction appelé par la fenêtre de la matrice lorsqu'elle se ferme
void MainApp::MatrixHasBeenClosed(){
    // On remonte le bouton
    //m_toolbar->EnableTool(3, false);        // Je voulais faire un Toogle, mais l'option "EnableTool" NE FONCTIONNE PAS ! (peut-être à cause du "wxTB_FLAT" ??)
    m_isMatrixDisplayed = false;
}

// =======================================
// ========== PRIVATE FUNCTIONS ==========
// =======================================

// Affectation des équipement à la DataView après un tri des colonnes
void MainApp::setDataAfterSort(){
    m_equipmentList->DeleteAllItems();
    for(auto& d : m_data){
        m_equipmentList->AppendItem( d );  
    }
    
    // On vide le détail d'un équipement
    fillEquipmentDetail(-1);
}

// Affectation des données après une recherche
void MainApp::setDataAfterSearch(bool resetCatagories){
    
    // Clear
    m_equipmentList->DeleteAllItems();    
    m_data.resize(idEquipmentListFound.size());
    
    // On rempli les lignes
    for(size_t i = 0 ; i < idEquipmentListFound.size() ; ++i){
        m_data[i].clear();
        m_data[i].push_back( wxVariant( wxLongLong(inventory->getEquipmentId(idEquipmentListFound.at(i)-1)).ToString() ));
        m_data[i].push_back( wxVariant(inventory->getEquipmentCategoryValue(idEquipmentListFound.at(i)-1, Equipment::category::Nom)) );
        m_data[i].push_back( wxVariant(inventory->getEquipmentCategoryValue(idEquipmentListFound.at(i)-1, Equipment::category::Local)) );
        m_data[i].push_back( wxVariant(inventory->getEquipmentCategoryValue(idEquipmentListFound.at(i)-1, Equipment::category::Appartenance)) );        
    }
    
    // On rempli le Dataview
    for(auto& d : m_data){
        m_equipmentList->AppendItem( d );
    }
        
    // On vide le détail d'un équipement
    if(resetCatagories){
        fillEquipmentDetail(-1);        
    }
    
    // Mise à jour de la Statubar
    updateStatusBar(Statusbar_NbElementsSearch);
}

// Remplissage de la liste d'équipements
void MainApp::fillEquipmentsList(bool resetCatagories){
    
    // On vide la DataView
    m_equipmentList->DeleteAllItems();
    
    // On redimmensionne le vecteur et on le rempli avec les données de l'inventaire
    m_data.resize(inventory->getNbEquipmentOk());
    
    // On récupère les équipements
    int index = 0;
    for(int i = 0 ; i < inventory->getNbEquipment() ; ++i)
    {
        if(!inventory->isEquipmentDeleted(i)){
            m_data[index].clear();
            m_data[index].push_back( wxVariant( (wxLongLong(inventory->getEquipmentId(i)).ToString() )) );
            m_data[index].push_back( wxVariant(inventory->getEquipmentCategoryValue(i, Equipment::category::Nom)) );
            m_data[index].push_back( wxVariant(inventory->getEquipmentCategoryValue(i, Equipment::category::Local)) );
            m_data[index].push_back( wxVariant(inventory->getEquipmentCategoryValue(i, Equipment::category::Appartenance)) );  
            index++;      
        }
    }
   
    // On rempli la DataView
    for(auto& d : m_data){
        m_equipmentList->AppendItem( d );
    }
    
    if(resetCatagories){
        // On vide le détail d'un équipement
        fillEquipmentDetail(-1);    
    }
    
    // Mise à jour de la Statubar
    updateStatusBar(Statusbar_NbElements);
    updateStatusBar(Statusbar_NeedSave);    
}

// Remplissage du détail d'un équipement
void MainApp::fillEquipmentDetail(int index){
    
    m_currentEquipmentIndex = index;       // Id de l'équipement
    
    // Si l'index est positif, on rempli les champs... (avec SetValue pour provoquer l'Event et aisni contrôler les valeurs)
    if(m_currentEquipmentIndex >= 0){
                      
        int cat = 0;     // Index de la catégorie
        
        //On mémorise les valeurs avant modifications
        m_equipmentMem.clear();
        for(int i = 0 ; i < Equipment::NB_CATEGORY ; ++i){
            m_equipmentMem.push_back( inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, i) );        
        }
        
        // On les place dans les champs 
        // (À noter qu'on utilise "SetValue" (au lieu de "ChangeValue") pour forcer la génération de l'Event et donc le contrôle du contenu)
        m_staticTextIdNb->SetLabel(wxLongLong(index+1).ToString());
        m_textCtrlLocal->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        m_textCtrlNom->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        m_textCtrlNoPlaque->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        m_textCtrlNoPrise->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        
        // On commence par remplir la liste de choix
        int catTmp = cat++;
        std::vector<std::string> vsl = inventory->getEquipmentCategoryFormatList(catTmp);
        wxArrayString as;
        for(auto& l : vsl){
            as.Add(l);
        }
        m_choiceCouleurPrise->Set(as);    // Liste de choix
        m_choiceCouleurPrise->SetSelection(inventory->getEquipmentCategoryFormatIndex(m_currentEquipmentIndex, catTmp));    // Puis on active le choix de cet équipement
        
        m_textCtrlSwitch->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        m_textCtrlPort->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        m_textCtrlAppartenance->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        m_textCtrlArchitecture->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        m_textCtrlOS->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
            
        catTmp = cat++;
        vsl.clear();
        vsl = inventory->getEquipmentCategoryFormatList(catTmp);
        as.clear();
        for(auto& l : vsl){
            as.Add(l);
        }
        m_choiceType->Set(as);    // Liste de choix
        m_choiceType->SetSelection(inventory->getEquipmentCategoryFormatIndex(m_currentEquipmentIndex, catTmp));
        
        m_textCtrlResponsable->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        m_textCtrlIdVendeur->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        m_textCtrlNoSerie->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
        m_textCtrlIP->SetValue(inventory->getEquipmentCategoryValue(m_currentEquipmentIndex, cat++));
                  
        // On active les contrôles
        setTextCrtlEnable(true);
        
        // On affiche le contenu de la desctiption
        m_staticTextCatDesc->SetValue(m_defaultCatFormat);        
    }
    // ...sinon on les vide
    else{
        m_staticTextIdNb->SetLabel("");
        m_textCtrlLocal->ChangeValue("");
        m_textCtrlNom->ChangeValue("");
        m_textCtrlNoPlaque->ChangeValue("");
        m_textCtrlNoPrise->ChangeValue("");
        wxArrayString as;
        m_choiceCouleurPrise->Set(as);        
        m_textCtrlSwitch->ChangeValue("");
        m_textCtrlPort->ChangeValue("");
        m_textCtrlAppartenance->ChangeValue("");
        m_textCtrlArchitecture->ChangeValue("");
        m_textCtrlOS->ChangeValue("");            
        m_choiceType->Set(as);  
        m_textCtrlResponsable->ChangeValue("");
        m_textCtrlIdVendeur->ChangeValue("");
        m_textCtrlNoSerie->ChangeValue("");
        m_textCtrlIP->ChangeValue("");
        
        // Et on desactive les TextCtrl et les icones
        setTextCrtlEnable(false);
        setCategoryIcon((Equipment::category)-1, false);
        
        // On vide la descritpion
        m_staticTextCatDesc->ChangeValue("");
    }
}

// On active ou desactive l'édition des catégories
void MainApp::setTextCrtlEnable(bool state){
    m_textCtrlLocal->Enable(state);
    m_textCtrlNom->Enable(state);
    m_textCtrlNoPlaque->Enable(state);
    m_textCtrlNoPrise->Enable(state);
    m_choiceCouleurPrise->Enable(state);
    m_textCtrlSwitch->Enable(state);
    m_textCtrlPort->Enable(state);
    m_textCtrlAppartenance->Enable(state);
    m_textCtrlArchitecture->Enable(state);
    m_textCtrlOS->Enable(state);
    m_choiceType->Enable(state);;
    m_textCtrlResponsable->Enable(state);
    m_textCtrlIdVendeur->Enable(state);
    m_textCtrlNoSerie->Enable(state);
    m_textCtrlIP->Enable(state);
    m_buttonCatDelete->Enable(state);
}

// On affiche le boutton "supprimer" ou "modifier et annuler"
void MainApp::setCatagoryModifyButtons(bool state){

    // Si l'état est le même que le précédent, on ne fait rien
    if(m_isModifying == state) return; 
        
    // Supprimer...
    m_buttonCatDelete->Show(!state);
    // ...ou Modifier et Annuler
    m_buttonCatModifier->Show(state);
    m_buttonCatAnnuler->Show(state);
    
    // L'état correspond également à celui d'un équipement modifié
    m_isModifying = state;
    
    // On rafraichi l'affichage
    Layout();
}

// Affiche ou cache l'icone indiquant qu'une valeur a été modifiée
void MainApp::setCategoryIcon(Equipment::category cat, bool state){
    // Si une catégorie est spécifiée, on traite celle-là
    if((int)cat >= 0){
        switch (cat){
            case Equipment::Appartenance:
                m_staticBitmapAppartenance->Show(state);
                break;
            case Equipment::Architecture:
                m_staticBitmapArchitecture->Show(state);
                break;
            case Equipment::CouleurPrise:
                m_staticBitmapCouleurPrise->Show(state);
                break;
            case Equipment::Ip:
                m_staticBitmapIP->Show(state);
                break;
            case Equipment::Local:
                m_staticBitmapLocal->Show(state);
                break;
            case Equipment::Nom:
                m_staticBitmapNom->Show(state);
                break;
            case Equipment::NoPlaque:
                m_staticBitmapNoPlaque->Show(state);
                break;
            case Equipment::NoPrise:
                m_staticBitmapNoPrise->Show(state);
                break;
            case Equipment::NoSerie:
                m_staticBitmapNoSerie->Show(state);
                break;
            case Equipment::Os:
                m_staticBitmapOS->Show(state);
                break;
            case Equipment::Port:
                m_staticBitmapPort->Show(state);
                break;
            case Equipment::Responsable:
                m_staticBitmapResponsable->Show(state);
                break;
            case Equipment::Switch:
                m_staticBitmapSwitch->Show(state);
                break;
            case Equipment::Type:
                m_staticBitmapType->Show(state);
                break;
            case Equipment::VendeurId:
                m_staticBitmapIdVendeur->Show(state);
                break;
            default:
                std::cerr << __FUNCTION__ << ": Undefined Category Name" << std::endl;
        }
    }
    // Sinon toutes
    else{
        m_staticBitmapLocal->Show(state);
        m_staticBitmapNom->Show(state);
        m_staticBitmapNoPlaque->Show(state);
        m_staticBitmapNoPrise->Show(state);
        m_staticBitmapCouleurPrise->Show(state);
        m_staticBitmapSwitch->Show(state);
        m_staticBitmapPort->Show(state);
        m_staticBitmapAppartenance->Show(state);
        m_staticBitmapArchitecture->Show(state);
        m_staticBitmapOS->Show(state);
        m_staticBitmapType->Show(state);
        m_staticBitmapResponsable->Show(state);
        m_staticBitmapIdVendeur->Show(state);
        m_staticBitmapNoSerie->Show(state);
        m_staticBitmapIP->Show(state);
    }
}

// On active ou non le bit de la catégorie en fonction de son état
void MainApp::setCategoryError(Equipment::category cat, bool isOk){
    // &= pour forcer la valeur 1
    // |= pour force la valeur 0
    switch (cat){            
        case Equipment::Local:
            isOk ? m_isCategoryError &= 0xFFFE : m_isCategoryError |= 1; 
            break;
        case Equipment::Nom:
            isOk ? m_isCategoryError &= 0xFFFD : m_isCategoryError |= 2;
            break;
        case Equipment::NoPlaque:
            isOk ? m_isCategoryError &= 0xFFFB : m_isCategoryError |= 4;
            break;
        case Equipment::NoPrise:
            isOk ? m_isCategoryError &= 0xFFF7 : m_isCategoryError |= 8;
            break;
        case Equipment::CouleurPrise:
            isOk ? m_isCategoryError &= 0xFFEF : m_isCategoryError |= 16;
            break;
        case Equipment::Switch:
            isOk ? m_isCategoryError &= 0xFFDF : m_isCategoryError |= 32;
            break;
        case Equipment::Port:
            isOk ? m_isCategoryError &= 0xFFBF : m_isCategoryError |= 64;
            break;
        case Equipment::Appartenance:
            isOk ? m_isCategoryError &= 0xFF7F : m_isCategoryError |= 128;
            break;
        case Equipment::Architecture:
            isOk ? m_isCategoryError &= 0xFEFF : m_isCategoryError |= 256;
            break;
        case Equipment::Os:
            isOk ? m_isCategoryError &= 0xFDFF : m_isCategoryError |= 512;
            break;
        case Equipment::Type:
            isOk ? m_isCategoryError &= 0xFBFF : m_isCategoryError |= 1024;
            break;
        case Equipment::Responsable:
            isOk ? m_isCategoryError &= 0xF7FF : m_isCategoryError |= 2048;
            break;
        case Equipment::VendeurId:
            isOk ? m_isCategoryError &= 0xEFFF : m_isCategoryError |= 4096;
            break;            
        case Equipment::NoSerie:
            isOk ? m_isCategoryError &= 0xDFFF : m_isCategoryError |= 8192;
            break;
        case Equipment::Ip:
            isOk ? m_isCategoryError &= 0xBFFF : m_isCategoryError |= 16384;
            break;
            
        default:
            std::cerr << __FUNCTION__ << ": Undefined Category Name" << std::endl;
    }
}


// Renvoie l'enumérateur de la catégorie en fonction de l'ID
Equipment::category MainApp::getCategorieIndex(int id) const{
    switch(id){
        case ID_LOCAL:
            return Equipment::Local;
        case ID_NOM:
            return Equipment::Nom;
        case ID_NO_PLAQUE:
            return Equipment::NoPlaque;
        case ID_NO_PRISE:
            return Equipment::NoPrise;
        case ID_COULEUR_PRISE:
            return Equipment::CouleurPrise;
        case ID_SWITCH:
            return Equipment::Switch;
        case ID_PORT:
            return Equipment::Port;
        case ID_APPARTENANCE:
            return Equipment::Appartenance;
        case ID_ARCHITECTURE:
            return Equipment::Architecture;
        case ID_OS:
            return Equipment::Os;
        case ID_TYPE:
            return Equipment::Type;
        case ID_RESPONSABLE:
            return Equipment::Responsable;
        case ID_ID_VENDEUR:
            return Equipment::VendeurId;
        case ID_NO_SERIE:
            return Equipment::NoSerie;
        case ID_IP:
            return Equipment::Ip;
        default:
            return (Equipment::category)-1;
    }
}

// Renvoie si on continue la modification en cours
bool MainApp::isModifInProgress(){
    // Y-a-t'il une modification en cours
    if(m_isModifying){
        wxMessageDialog dlg(this,
                L"Un équipement est en cours de modification.\nVoulez-vous abandonner la modification ?", 
                L"Attention !", 
                wxYES_NO | wxCENTRE | wxICON_WARNING,
                wxDefaultPosition);
        if(dlg.ShowModal() == wxID_NO){
            m_equipmentList->SelectRow(m_currentSelectedRow);    // On remet la sélection courante
            return true;
        }else{
            cancelModification();
        }
    }
    return false;
}

// On s'assure que tout est sauvegardé
bool MainApp::isAllDataSafe(){
    
    // Avant de quitter, on s'assure qu'il n'y a pas de fichier non sauvé
    if (m_isNeedToSaveFile)
    {
        int msg = wxMessageBox(_(L"L'inventaire n'a pas été sauvegarder.\nVoulez-vous sauvegarder avant de quitter ?"), _("Attention !"), wxICON_WARNING | wxYES_NO | wxCANCEL, this);
        // Annule quitter
        if (msg == wxCANCEL){
            return false;
        }
        // Sauve avant de quitter
        else if(msg == wxYES){
            wxCommandEvent event(wxEVT_NULL);
            OnSaveFile(event);
            return true;    // Pas utile, mais facilite la lecture du code (on peut ignorer le reste)
        }
    }
    
    // Avant de quitter, on s'assure qu'il n'y a pas de d'équipement non sauvé
    // (Si on a pas voulu sauvé le fichier, c'est qu'on se moque de la modification de l'équipment (d'où le "else if"))
    else if (m_isNeedToSaveEquipment)
    {
        if (wxMessageBox(_(L"L'équipement affiché n'a pas été sauvegarder.\n(Cliquez sur [Modifier] pour valider les données)\n\nÊtes-vous certain de vouloir quitter ?"), _("Attention !"), wxICON_WARNING | wxYES_NO, this) == wxNO )
            return true;
    }
    
    return true;
}

// On annule la modification en cours
void MainApp::cancelModification()
{
    //On restore les valeurs initiales
    for(int i = 0 ; i < Equipment::NB_CATEGORY ; ++i){
        inventory->setEquipmentValue(m_currentEquipmentIndex, i, m_equipmentMem.at(i));        
    }
        
    // On reset l'affichage des boutons
    setCatagoryModifyButtons(false);
}

// Mise à jour de la ToolBar
void MainApp::updateSaveItems(){
    m_menuItemSave->Enable(m_isNeedToSaveFile);
    m_toolbar->EnableTool(wxID_SAVE, m_isNeedToSaveFile);
}

// Mise à jour de la StatusBar
void MainApp::updateStatusBar(StatusBar action){
    
    switch(action){
        case Statusbar_Init:        
            // Taille des cellules
            int widths[Field_Max];
            widths[Field_State] = -1;
            widths[Field_Info] = -1;
            widths[Field_Version] = 150;
            m_statusBar->SetStatusWidths(Field_Max, widths);            
            // Contenu
            m_statusBar->SetStatusText(L"Version : " + Text::APP_VERSION, Field_Version);            
            break;
            
        case Statusbar_NbElements:
            m_statusBar->SetStatusText(L"Nombre d'équipement : " + wxLongLong(m_equipmentList->GetItemCount()).ToString(), Field_Info);
            break;        
        
        case Statusbar_NbElementsSearch:
            m_statusBar->SetStatusText(L"Nombre d'équipement : " + wxLongLong(m_equipmentList->GetItemCount()).ToString() + " (Recherche en cours...)", Field_Info);
            break;        
                
        case Statusbar_NeedSave:
            if(m_isNeedToSaveFile){
                m_statusBar->SetStatusText(L"Fichier non sauvegardé !", Field_State);                
            }else{
                m_statusBar->SetStatusText(L"Fichier sauvegardé", Field_State);
            }
            break;
            
        default:
            // Don't care... (mais utile pour éviter le Warning des options manquantes)
            break;
    }
    
    // Mise à jour de la Toolbar
    updateSaveItems();
}

// On affiche le texte dans la matrice
void MainApp::refreshMatrix(){
            
    // On vide le texte
    matrix->clearText();
    
    // Convertion de la string pour gérer les caractères spéciaux
    wxString popo(inventory->displayMatrix());
    const char* chars = popo;
    wxString goodStr(chars, wxConvUTF8);
    
    // On affecte le nouveau texte
    matrix->appendText(goodStr);
}

// Annule la recherche en cours
void MainApp::doSearchCancel(){
    if(m_isRSearchActive){
        idEquipmentListFound.clear();
        fillEquipmentsList(true);
        m_isRSearchActive = false;
    }  
}