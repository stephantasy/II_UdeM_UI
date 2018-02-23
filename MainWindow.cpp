#include "MainWindow.h"

MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
    
    // Sizer principal
    wxBoxSizer* boxSizerMain = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(boxSizerMain);
        
    //*************************************
    //*            CONSTRUCTION           *
    //*************************************
    
    // Sizer secondaire : LISTE + IMAGE + RECHERCHE
    wxBoxSizer* boxSizerEquipment = new wxBoxSizer(wxVERTICAL);
    
        // Ajout de la liste des équipements
        boxSizerEquipment->Add(getEquipmentListSizer(), 1, wxALL|wxEXPAND, 0);
        
        // Ajout de l'image de séparation
        boxSizerEquipment->Add(getHorizontalImage(), 0, 0, 0);
            
        // Ajout de la liste des équipements
        boxSizerEquipment->Add(getSearchSizer(), 0, wxALL|wxEXPAND, 0);
        
    // EQUIPEMENTS + IMAGE + CATÉGORIES
    boxSizerMain->Add(boxSizerEquipment, 1, wxLEFT|wxTOP|wxBOTTOM|wxEXPAND, 0);
    boxSizerMain->Add(getVerticalImage(), 0, wxEXPAND, 5);
    boxSizerMain->Add(getCategoriesSizer(), 0, wxEXPAND, 5);

    
    //********************************************
    //*              BARRES DIVERSES             *
    //********************************************
    
    // Barre de menu
    this->SetMenuBar(getMenuBar());
    
    // Barre d'outils
    this->SetToolBar(getToolsBar());
    
    // Barre de status
    this->SetStatusBar(getStatusBar());
    
    
    //********************************************
    //*              PARAMÉTRAGE                 *
    //********************************************
    
    // Icone
    wxIconBundle app_icons;
    getProgIcon(app_icons);
    SetIcons( app_icons );
    
    // Event de fermeture de la fenêtre
    this->Bind(wxEVT_CLOSE_WINDOW, OnExit, this);
    
    // Déco
    SetBackgroundColour(wxColour(_("rgb(200,220,225)")));
    SetForegroundColour(wxColour(_("rgb(0,0,50)")));
    
    // Taille et taille minimum
    SetMinClientSize(wxSize(780,700));
    SetSize(780,700);
    
    // Centre à l'écran
    CentreOnScreen(wxBOTH);    
}

MainWindow::~MainWindow()
{
    // Events : Suppression des liens
    // Main Window
    this->Unbind(wxEVT_CLOSE_WINDOW, OnExit, this);
    // Menu
    this->Unbind(wxEVT_COMMAND_MENU_SELECTED, OnOpenFile, this, m_menuItemOpen->GetId());
    this->Unbind(wxEVT_COMMAND_MENU_SELECTED, OnSaveFile, this, m_menuItemSave->GetId());
    this->Unbind(wxEVT_COMMAND_MENU_SELECTED, OnExitAsk, this, m_menuItemExit->GetId());
    this->Unbind(wxEVT_COMMAND_MENU_SELECTED, OnAbout, this, m_menuItemAbout->GetId());
    // Toolbar
    this->Unbind(wxEVT_COMMAND_TOOL_CLICKED, OnOpenFile, this, wxID_OPEN);
    this->Unbind(wxEVT_COMMAND_TOOL_CLICKED, OnSaveFile, this, wxID_SAVE);
    this->Unbind(wxEVT_COMMAND_TOOL_CLICKED, OnDisplayMatrix, this, ID_MATRIX);
    // Liste
    m_equipmentList->Unbind(wxEVT_COMMAND_DATAVIEW_COLUMN_HEADER_CLICK, OnColumnSort, this);
    m_equipmentList->Unbind(wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, OnItemSelected, this);
    // Recherche
    m_searchCtrl->Unbind(wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN,OnSearch, this);
    m_searchCtrl->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnSearch, this);
    m_buttonClearSearch->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, OnSearchCancel, this);
    // Catégories    
    m_staticTextLocal->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlLocal->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlLocal->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlLocal->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapLocal->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextNom->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNom->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNom->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlNom->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapNom->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextNoPlaque->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoPlaque->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoPlaque->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlNoPlaque->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapNoPlaque->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextNoPrise->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoPrise->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoPrise->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlNoPrise->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapNoPrise->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextCouleurPrise->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_choiceCouleurPrise->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_choiceCouleurPrise->Unbind(wxEVT_COMMAND_CHOICE_SELECTED, OnCategoryModified, this);
    m_staticBitmapCouleurPrise->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextSwitch->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlSwitch->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlSwitch->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlSwitch->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapSwitch->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextPort->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlPort->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlPort->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlPort->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapPort->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextAppartenance->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlAppartenance->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlAppartenance->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlAppartenance->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapAppartenance->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextArchitecture->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlArchitecture->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlArchitecture->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlArchitecture->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapArchitecture->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextOS->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlOS->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlOS->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlOS->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapOS->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextType->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_choiceType->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_choiceType->Unbind(wxEVT_COMMAND_CHOICE_SELECTED, OnCategoryModified, this);
    m_staticBitmapType->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextResponsable->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlResponsable->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlResponsable->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlResponsable->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapResponsable->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextIdVendeur->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlIdVendeur->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlIdVendeur->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlIdVendeur->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapIdVendeur->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextNoSerie->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoSerie->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoSerie->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlNoSerie->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapNoSerie->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextIP->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlIP->Unbind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlIP->Unbind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlIP->Unbind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapIP->Unbind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_buttonCatDelete->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, OnEquipmentDelete, this);
    m_buttonCatModifier->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, OnEquipmentModify, this);
    m_buttonCatAnnuler->Unbind(wxEVT_COMMAND_BUTTON_CLICKED, OnEquipmentCancel, this);
}

/**
 * @brief Construction du menu
 * @return La barre de menu
 */
wxMenuBar* MainWindow::getMenuBar(){
    wxMenuBar* m_menuBar = new wxMenuBar(0);
    
    // Menu FICHIER
    wxMenu* m_menuFile = new wxMenu();
    m_menuBar->Append(m_menuFile, _(L"Fichier"));
    
        // Ouvrir
        m_menuItemOpen = new wxMenuItem(m_menuFile, wxID_OPEN, _(L"Ouvrir...\tCtrl+O"), _(L"Ouvrir un fichier"), wxITEM_NORMAL);
        m_menuFile->Append(m_menuItemOpen);
        
        m_menuFile->AppendSeparator();      // Séparation

        // Sauvagarder
        m_menuItemSave = new wxMenuItem(m_menuFile, wxID_SAVE, _(L"Enregistrer\tCtrl+S"), _(L"Sauvegarder le fichier en cours"), wxITEM_NORMAL);
        m_menuFile->Append(m_menuItemSave);
        
        m_menuFile->AppendSeparator();      // Séparation
        
        // Quitter
        m_menuItemExit = new wxMenuItem(m_menuFile, wxID_EXIT, _(L"Quitter\tCtrl+Q"), _(L"Quitter le programme"), wxITEM_NORMAL);
        m_menuFile->Append(m_menuItemExit);
    
    // Menu ACTIONS
    wxMenu* m_menuAction = new wxMenu();
    m_menuBar->Append(m_menuAction, _(L"Actions"));
    
        // Matrice
        wxMenuItem* m_menuItemMatrix = new wxMenuItem(m_menuAction, ID_MATRIX, _(L"Afficher/Cacher la matrice...\tCtrl+M"), _(L"Affiche la matrice des équipments"), wxITEM_NORMAL);
        m_menuAction->Append(m_menuItemMatrix);
        
    // Menu AIDE
    wxMenu* m_menuHelp = new wxMenu();
    m_menuBar->Append(m_menuHelp, _(L"Aide"));
    
        // About
        m_menuItemAbout = new wxMenuItem(m_menuHelp, wxID_ABOUT, _(L"À propos...\tF1"), _(L"À propos"), wxITEM_NORMAL);
        m_menuHelp->Append(m_menuItemAbout);
    
    // Events    
    this->Bind(wxEVT_COMMAND_MENU_SELECTED, OnOpenFile, this, m_menuItemOpen->GetId());
    this->Bind(wxEVT_COMMAND_MENU_SELECTED, OnSaveFile, this, m_menuItemSave->GetId());
    this->Bind(wxEVT_COMMAND_MENU_SELECTED, OnExitAsk, this, m_menuItemExit->GetId());
    this->Bind(wxEVT_COMMAND_MENU_SELECTED, OnAbout, this, m_menuItemAbout->GetId());
    
    return m_menuBar;
}

/**
 * @brief Construction de la Toolbar
 * @return La Toolbar
 */
wxToolBar* MainWindow::getToolsBar(){
    
    // Toolbar
    m_toolbar = this->CreateToolBar(wxTB_FLAT);
    m_toolbar->SetToolBitmapSize(wxSize(32,32));    // Images de 32x32
    m_toolbar->SetToolPacking(10);                  // Espace entre les images
    
    // Images
    wxBitmap m_bmpOpen = wxBitmap(_(L"../Assets/Open.png"), wxBITMAP_TYPE_PNG);
    wxBitmap m_bmpSave = wxBitmap(_(L"../Assets/Save.png"), wxBITMAP_TYPE_PNG);
    wxBitmap m_bmpSaveDisabled = wxBitmap(_(L"../Assets/SaveDisabled.png"), wxBITMAP_TYPE_PNG);
    wxBitmap m_bmpMatrix = wxBitmap(_(L"../Assets/Matrix.png"), wxBITMAP_TYPE_PNG);
    
    // Icone OUVRIR
    m_toolbar->AddTool( wxID_OPEN, 
                        _(L"Open"), 
                        m_bmpOpen, //wxXmlResource::Get()->LoadBitmap(_(L"Open")), 
                        wxNullBitmap, 
                        wxITEM_NORMAL, 
                        _(L"Ouvrir un fichier"), 
                        _(L"Ouvrir un fichier"), 
                        NULL
    );    
    m_toolbar->AddSeparator();      // Séparation
    
    // Icone SAUVEGARGER
    m_toolbar->AddTool( wxID_SAVE, 
                        _(L"Save"), 
                        m_bmpSave,
                        m_bmpSaveDisabled, 
                        wxITEM_NORMAL, 
                        _(L"Sauvegarder"), 
                        _(L"Sauvegarder"), 
                        NULL
    );    
    m_toolbar->AddSeparator();
    
    // Icone MATRICE
    m_toolbar->AddTool( ID_MATRIX, 
                        _(L"Matrix"), 
                        m_bmpMatrix, 
                        wxNullBitmap, 
                        wxITEM_NORMAL, 
                        _(L"Afficher/Cacher la matrice des équipments"), 
                        _(L"Afficher/Cacher la matrice des équipments"), 
                        NULL)
    ;
    m_toolbar->Realize();   // you must call Realize() in order to have the tools appear.    
    
    // Events
    this->Bind(wxEVT_COMMAND_TOOL_CLICKED, OnOpenFile, this, wxID_OPEN);
    this->Bind(wxEVT_COMMAND_TOOL_CLICKED, OnSaveFile, this, wxID_SAVE);
    this->Bind(wxEVT_COMMAND_TOOL_CLICKED, OnDisplayMatrix, this, ID_MATRIX);
    
    return m_toolbar;
}

/**
 * @brief Construction de la StatusBar
 * @return La StatusBar
 */
wxStatusBar* MainWindow::getStatusBar(){
    m_statusBar = new wxStatusBar(this, ID_STATUSBAR, wxSTB_DEFAULT_STYLE);
    m_statusBar->SetFieldsCount(3);
    
    return m_statusBar;
}

/**
 * @brief Construction de la zone contenant la liste des équipements
 * @return Sizer Vertical
 */
wxBoxSizer* MainWindow::getEquipmentListSizer(){
        
    // Création de la bannière
    wxBannerWindow* m_bannerEquipments = new wxBannerWindow(this, wxID_ANY, wxTOP, wxDefaultPosition, wxDefaultSize, 0);
    m_bannerEquipments->SetText(_(L"LISTE DE  ÉQUIPEMENTS"), _(L"Liste de tous les équipements disponibles"));
    m_bannerEquipments->SetGradient(wxColour(_("rgb(128,255,128)")), wxColour(_("rgb(40,170,40)")));
        
    // Création de la liste
    m_equipmentList = new wxDataViewListCtrl(this, ID_ITEM_SELECTED, wxDefaultPosition,  wxDefaultSize, wxDV_ROW_LINES|wxDV_SINGLE);
    m_equipmentList->SetBackgroundColour(wxColour(_("rgb(200,220,225)")));
    m_equipmentList->Enable(false);
    
    // Ajout des colonnes
    m_equipmentList->AppendTextColumn(_(L"Id"), wxDATAVIEW_CELL_INERT, 50, wxALIGN_CENTER);
    m_equipmentList->AppendTextColumn(_(L"Nom"), wxDATAVIEW_CELL_INERT, -2, wxALIGN_LEFT);
    m_equipmentList->AppendTextColumn(_(L"Local"), wxDATAVIEW_CELL_INERT, 60, wxALIGN_CENTER);
    m_equipmentList->AppendTextColumn(_(L"Appartenance"), wxDATAVIEW_CELL_INERT, -2, wxALIGN_LEFT);
    
    // Events
    m_equipmentList->Bind(wxEVT_COMMAND_DATAVIEW_COLUMN_HEADER_CLICK, OnColumnSort, this);
    m_equipmentList->Bind(wxEVT_COMMAND_DATAVIEW_SELECTION_CHANGED, OnItemSelected, this);
        
    // Sizer vertical pour la bannière et la liste
    wxBoxSizer* boxSizerList = new wxBoxSizer(wxVERTICAL);
    boxSizerList->Add(m_bannerEquipments, 0, wxALL|wxEXPAND, 0);    // Ajout de la bannière
    boxSizerList->Add(m_equipmentList, 1, wxALL|wxEXPAND, 0);       // Ajout de la liste
        
    return boxSizerList;
}

/**
 * @brief Construction de la zone contenant la recherche
 * @return Sizer Vertical
 */
wxBoxSizer* MainWindow::getSearchSizer(){
        
    // Création de la bannière
    wxBannerWindow* m_bannerSearch = new wxBannerWindow(this, wxID_ANY, wxTOP, wxDefaultPosition, wxDefaultSize, 0);
    m_bannerSearch->SetText(_(L"CHERCHER"), _(L"Entrer un mot et appuyez sur ENTRÉE\nNote : Utilisez * pour les caractères inconnus"));
    m_bannerSearch->SetGradient(wxColour(_("rgb(255,223,128)")), wxColour(_("rgb(170,40,40)")));
        
    // Zone de recherche    
    m_searchCtrl = new wxSearchCtrl(this, ID_SEARCH_ZONE, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    m_searchCtrl->SetForegroundColour(wxColour(_("rgb(0,80,0)")));
    wxFont m_searchCtrlFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _(L"Tahoma"));
    m_searchCtrl->SetFont(m_searchCtrlFont);
    m_searchCtrl->ShowSearchButton(true);
    m_searchCtrl->ShowCancelButton(true);
    m_searchCtrl->Enable(false);    // Désactivée par défaut
    
    // Bouton Reset
    m_buttonClearSearch = new wxButton(this, ID_SEARCH_RESET, _(L"Rétablir"), wxDefaultPosition, wxDefaultSize, 0);
    
    // Events
    m_searchCtrl->Bind(wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN,OnSearch, this);
    m_searchCtrl->Bind(wxEVT_COMMAND_TEXT_ENTER, OnSearch, this);
    m_buttonClearSearch->Bind(wxEVT_COMMAND_BUTTON_CLICKED, OnSearchCancel, this);
        
    // Sizer pour la zone de recherche et le bouton Reset
    wxBoxSizer* boxSizerSearchSecond = new wxBoxSizer(wxHORIZONTAL);
    boxSizerSearchSecond->Add(m_searchCtrl, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL, 30);
    boxSizerSearchSecond->Add(m_buttonClearSearch, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    
    // Sizer vertical pour la bannière et la liste
    wxBoxSizer* boxSizerSearch = new wxBoxSizer(wxVERTICAL);        
    boxSizerSearch->Add(m_bannerSearch, 1, wxALL|wxEXPAND, 0);    // Ajout de la bannière
    boxSizerSearch->Add(boxSizerSearchSecond, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 10);       // Ajout de la zone + bouton
        
    return boxSizerSearch;
}

/**
 * @brief Construction de la zone contenant les catégories
 * @return Sizer Vertical
 */
wxBoxSizer* MainWindow::getCategoriesSizer(){
    
    // ***********************
    // CRÉATION DES ÉLÉMENTS
    // ***********************
    
    // Création de la bannière
    wxBannerWindow* m_bannerCategories = new wxBannerWindow(this, wxID_ANY, wxTOP, wxDefaultPosition, wxDefaultSize, 0);
    m_bannerCategories->SetText(_(L"DÉTAIL ÉQUIPEMENT"), _(L"Détail de l'équipement sélectionné"));
    m_bannerCategories->SetGradient(wxColour(_("rgb(128,223,255)")), wxColour(_("rgb(40,132,170)")));
        
    // Fonts
    wxFont m_staticTextIdFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _(L"Segoe UI"));       // Id Version "Gras"
    wxFont m_staticTextIdNbFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, _(L"Segoe UI"));   // Id Version "normale"
    wxFont m_staticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);                                            // Font pour le reste...
    m_staticTextFont.SetWeight(wxFONTWEIGHT_BOLD);                                                                          // ...en gras
    
    // CATÉGORIES
    // Id
    m_staticTextId = new wxStaticText(this, wxID_ANY, _(L"Id"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextId->SetFont(m_staticTextIdFont);
    m_staticTextIdNb = new wxStaticText(this, wxID_ANY, _(L"0"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextIdNb->SetFont(m_staticTextIdNbFont);
    // Local
    m_staticTextLocal = new wxStaticText(this, ID_LOCAL, _(L"Local"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextLocal->SetFont(m_staticTextFont);
    m_textCtrlLocal = new wxTextCtrl(this, ID_LOCAL, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlLocal->Enable(false);
    // Nom
    m_staticTextNom = new wxStaticText(this, ID_NOM, _(L"Nom"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextNom->SetFont(m_staticTextFont);
    m_textCtrlNom = new wxTextCtrl(this, ID_NOM, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlNom->Enable(false);
    // NoPlaque
    m_staticTextNoPlaque = new wxStaticText(this, ID_NO_PLAQUE, _(L"No. Plaque"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextNoPlaque->SetFont(m_staticTextFont);
    m_textCtrlNoPlaque = new wxTextCtrl(this, ID_NO_PLAQUE, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlNoPlaque->Enable(false);
    // NoPrise
    m_staticTextNoPrise = new wxStaticText(this, ID_NO_PRISE, _(L"No. Prise"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextNoPrise->SetFont(m_staticTextFont);
    m_textCtrlNoPrise = new wxTextCtrl(this, ID_NO_PRISE, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlNoPrise->Enable(false);
    // CouleurPrise
    wxArrayString m_choiceCouleurPriseArr;
    m_choiceCouleurPrise = new wxChoice(this, ID_COULEUR_PRISE, wxDefaultPosition, wxDefaultSize, m_choiceCouleurPriseArr, 0);
    m_choiceCouleurPrise->Enable(false);
    m_staticTextCouleurPrise = new wxStaticText(this, ID_COULEUR_PRISE, _(L"Couleur Prise"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextCouleurPrise->SetFont(m_staticTextFont);
    // Switch
    m_staticTextSwitch = new wxStaticText(this, ID_SWITCH, _(L"Switch"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextSwitch->SetFont(m_staticTextFont);
    m_textCtrlSwitch = new wxTextCtrl(this, ID_SWITCH, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlSwitch->Enable(false);
    // Port
    m_staticTextPort = new wxStaticText(this, ID_PORT, _(L"Port"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextPort->SetFont(m_staticTextFont);
    m_textCtrlPort = new wxTextCtrl(this, ID_PORT, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlPort->Enable(false);
    // Appartenance
    m_staticTextAppartenance = new wxStaticText(this, ID_APPARTENANCE, _(L"Appartenance"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextAppartenance->SetFont(m_staticTextFont);
    m_textCtrlAppartenance = new wxTextCtrl(this, ID_APPARTENANCE, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlAppartenance->Enable(false);
    // Architecture
    m_staticTextArchitecture = new wxStaticText(this, ID_ARCHITECTURE, _(L"Architecture"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextArchitecture->SetFont(m_staticTextFont);
    m_textCtrlArchitecture = new wxTextCtrl(this, ID_ARCHITECTURE, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlArchitecture->Enable(false);
    // Os
    m_staticTextOS = new wxStaticText(this, ID_OS, _(L"OS"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextOS->SetFont(m_staticTextFont);
    m_textCtrlOS = new wxTextCtrl(this, ID_OS, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlOS->Enable(false);
    // Type
    wxArrayString m_choiceTypeArr;
    m_choiceType = new wxChoice(this, ID_TYPE, wxDefaultPosition, wxDefaultSize, m_choiceTypeArr, 0);
    m_choiceType->Enable(false);
    m_staticTextType = new wxStaticText(this, ID_TYPE, _(L"Type"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextType->SetFont(m_staticTextFont);
    // Responsable
    m_staticTextResponsable = new wxStaticText(this, ID_RESPONSABLE, _(L"Responsable"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextResponsable->SetFont(m_staticTextFont);
    m_textCtrlResponsable = new wxTextCtrl(this, ID_RESPONSABLE, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlResponsable->Enable(false);        
    // VendeurId
    m_staticTextIdVendeur = new wxStaticText(this, ID_ID_VENDEUR, _(L"Id. Vendeur"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextIdVendeur->SetFont(m_staticTextFont);
    m_textCtrlIdVendeur = new wxTextCtrl(this, ID_ID_VENDEUR, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlIdVendeur->Enable(false);
    // NoSerie
    m_staticTextNoSerie = new wxStaticText(this, ID_NO_SERIE, _(L"No. Série"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextNoSerie->SetFont(m_staticTextFont);
    m_textCtrlNoSerie = new wxTextCtrl(this, ID_NO_SERIE, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlNoSerie->Enable(false);
    // Ip
    m_staticTextIP = new wxStaticText(this, ID_IP, _(L"IP"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticTextIP->SetFont(m_staticTextFont);
    m_textCtrlIP = new wxTextCtrl(this, ID_IP, _(L""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxBORDER_NONE);
    m_textCtrlIP->Enable(false);    
    // Lignes de séparation
    wxStaticLine* m_staticLineCat0 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat3 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat4 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat5 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat6 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat7 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat8 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat9 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat10 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat11 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat12 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat13 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat14 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    wxStaticLine* m_staticLineCat15 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);

    // Image indiquant une catégorie modifiée
    wxBitmap bmp = wxBitmap(_(L"../Assets/info.png"), wxBITMAP_TYPE_PNG);
    m_staticBitmapAppartenance = new wxStaticBitmap(this, ID_APPARTENANCE, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapArchitecture = new wxStaticBitmap(this, ID_ARCHITECTURE, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapCouleurPrise = new wxStaticBitmap(this, ID_COULEUR_PRISE, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapIdVendeur = new wxStaticBitmap(this, ID_ID_VENDEUR, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapIP = new wxStaticBitmap(this, ID_IP, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapLocal = new wxStaticBitmap(this, ID_LOCAL, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapNom = new wxStaticBitmap(this, ID_NOM, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapNoPlaque = new wxStaticBitmap(this, ID_NO_PLAQUE, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapNoPrise = new wxStaticBitmap(this, ID_NO_PRISE, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapNoSerie = new wxStaticBitmap(this, ID_NO_SERIE, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapOS = new wxStaticBitmap(this, ID_OS, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapPort = new wxStaticBitmap(this, ID_PORT, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapResponsable = new wxStaticBitmap(this, ID_RESPONSABLE, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapSwitch = new wxStaticBitmap(this, ID_SWITCH, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    m_staticBitmapType = new wxStaticBitmap(this, ID_TYPE, bmp, wxDefaultPosition, wxDefaultSize, 0 );
    // Cachées par défaut
    m_staticBitmapAppartenance->Hide();
    m_staticBitmapArchitecture->Hide();
    m_staticBitmapCouleurPrise->Hide();    
    m_staticBitmapIdVendeur->Hide();
    m_staticBitmapIP->Hide();
    m_staticBitmapLocal->Hide();    
    m_staticBitmapNom->Hide();
    m_staticBitmapNoPlaque->Hide();
    m_staticBitmapNoPrise->Hide();
    m_staticBitmapNoSerie->Hide();
    m_staticBitmapOS->Hide();
    m_staticBitmapPort->Hide();
    m_staticBitmapResponsable->Hide();
    m_staticBitmapSwitch->Hide();
    m_staticBitmapType->Hide();
    
    
    // BOUTONS
    // Delete
    m_buttonCatDelete = new wxButton(this, ID_BT_CAT_SUPPRIMER, _(L"Supprimer"), wxDefaultPosition, wxDefaultSize, 0);
    m_buttonCatDelete->SetFont(m_staticTextFont);
    m_buttonCatDelete->Enable(false);
    // Modify
    m_buttonCatModifier = new wxButton(this, ID_BT_CAT_MODIFIER, _(L"Modifier"), wxDefaultPosition, wxDefaultSize, 0);
    m_buttonCatModifier->SetFont(m_staticTextFont);
    m_buttonCatModifier->Hide();    // Caché par défaut
    // Cancel
    m_buttonCatAnnuler = new wxButton(this, ID_BT_CAT_ANNULER, _(L"Annuler"), wxDefaultPosition, wxDefaultSize, 0);
    m_buttonCatAnnuler->SetFont(m_staticTextFont);
    m_buttonCatAnnuler->Hide();    // Caché par défaut
    
    
    // Zone d'information
    m_staticTextCatDesc = new wxTextCtrl(this, wxID_ANY, _(L"Cliquez sur une catégorie pour afficher sa description et son format."), wxDefaultPosition, wxDefaultSize, wxTE_WORDWRAP|wxTE_READONLY|wxTE_MULTILINE);

    
    // ***********************
    //          EVENTS
    // ***********************
    m_staticTextLocal->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlLocal->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlLocal->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlLocal->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapLocal->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextNom->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNom->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNom->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlNom->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapNom->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextNoPlaque->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoPlaque->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoPlaque->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlNoPlaque->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapNoPlaque->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextNoPrise->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoPrise->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoPrise->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlNoPrise->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapNoPrise->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextCouleurPrise->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_choiceCouleurPrise->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_choiceCouleurPrise->Bind(wxEVT_COMMAND_CHOICE_SELECTED, OnCategoryModified, this);
    m_staticBitmapCouleurPrise->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextSwitch->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlSwitch->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlSwitch->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlSwitch->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapSwitch->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextPort->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlPort->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlPort->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlPort->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapPort->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextAppartenance->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlAppartenance->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlAppartenance->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlAppartenance->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapAppartenance->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextArchitecture->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlArchitecture->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlArchitecture->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlArchitecture->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapArchitecture->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextOS->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlOS->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlOS->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlOS->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapOS->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextType->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_choiceType->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_choiceType->Bind(wxEVT_COMMAND_CHOICE_SELECTED, OnCategoryModified, this);
    m_staticBitmapType->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextResponsable->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlResponsable->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlResponsable->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlResponsable->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapResponsable->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextIdVendeur->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlIdVendeur->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlIdVendeur->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlIdVendeur->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapIdVendeur->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextNoSerie->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoSerie->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlNoSerie->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlNoSerie->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapNoSerie->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_staticTextIP->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlIP->Bind(wxEVT_LEFT_DOWN, OnCategoryClic, this);
    m_textCtrlIP->Bind(wxEVT_COMMAND_TEXT_UPDATED, OnCategoryModified, this);
    m_textCtrlIP->Bind(wxEVT_COMMAND_TEXT_ENTER, OnCategoryModified, this);
    m_staticBitmapIP->Bind(wxEVT_LEFT_DOWN, OnInfoClic, this);
    m_buttonCatDelete->Bind(wxEVT_COMMAND_BUTTON_CLICKED, OnEquipmentDelete, this);
    m_buttonCatModifier->Bind(wxEVT_COMMAND_BUTTON_CLICKED, OnEquipmentModify, this);
    m_buttonCatAnnuler->Bind(wxEVT_COMMAND_BUTTON_CLICKED, OnEquipmentCancel, this);

        
    // ***********************
    //      CONSTRUCTION
    // ***********************
    
    // Sizer de chaque catégories (Horizontal)
    // Id
    wxBoxSizer* boxSizerCatId = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatId->Add(m_staticTextId, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    boxSizerCatId->Add(m_staticTextIdNb, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5);
    // Local
    wxBoxSizer* boxSizerCatLocal = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatLocal->Add(m_staticTextLocal, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatLocal->Add(m_textCtrlLocal, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatLocal->Add(m_staticBitmapLocal, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // Nom
    wxBoxSizer* boxSizerCatNom = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatNom->Add(m_staticTextNom, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatNom->Add(m_textCtrlNom, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatNom->Add(m_staticBitmapNom, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // No Plaque
    wxBoxSizer* boxSizerCatNoPlaque = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatNoPlaque->Add(m_staticTextNoPlaque, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatNoPlaque->Add(m_textCtrlNoPlaque, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatNoPlaque->Add(m_staticBitmapNoPlaque, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // No Prise
    wxBoxSizer* boxSizerCatNoPrise = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatNoPrise->Add(m_staticTextNoPrise, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatNoPrise->Add(m_textCtrlNoPrise, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatNoPrise->Add(m_staticBitmapNoPrise, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // Couleur prise
    wxBoxSizer* boxSizerCatCouleurPrise = new wxBoxSizer(wxHORIZONTAL);   
    boxSizerCatCouleurPrise->Add(m_staticTextCouleurPrise, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0); 
    boxSizerCatCouleurPrise->Add(m_choiceCouleurPrise, 2, wxALL|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatCouleurPrise->Add(m_staticBitmapCouleurPrise, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // Switch
    wxBoxSizer* boxSizerCatSwitch = new wxBoxSizer(wxHORIZONTAL);    
    boxSizerCatSwitch->Add(m_staticTextSwitch, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatSwitch->Add(m_textCtrlSwitch, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatSwitch->Add(m_staticBitmapSwitch, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // Port
    wxBoxSizer* boxSizerCatPort = new wxBoxSizer(wxHORIZONTAL);    
    boxSizerCatPort->Add(m_staticTextPort, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatPort->Add(m_textCtrlPort, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatPort->Add(m_staticBitmapPort, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // Appartenance
    wxBoxSizer* boxSizerCatAppartenance = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatAppartenance->Add(m_staticTextAppartenance, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatAppartenance->Add(m_textCtrlAppartenance, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatAppartenance->Add(m_staticBitmapAppartenance, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // Architecture
    wxBoxSizer* boxSizerCatArchitecture = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatArchitecture->Add(m_staticTextArchitecture, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatArchitecture->Add(m_textCtrlArchitecture, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatArchitecture->Add(m_staticBitmapArchitecture, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // OS
    wxBoxSizer* boxSizerCatOS = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatOS->Add(m_staticTextOS, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatOS->Add(m_textCtrlOS, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatOS->Add(m_staticBitmapOS, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // Type
    wxBoxSizer* boxSizerCatType = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatType->Add(m_staticTextType, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatType->Add(m_choiceType, 2, wxALL|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatType->Add(m_staticBitmapType, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // Responsable
    wxBoxSizer* boxSizerCatResponsable = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatResponsable->Add(m_staticTextResponsable, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatResponsable->Add(m_textCtrlResponsable, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatResponsable->Add(m_staticBitmapResponsable, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // Id Vendeur
    wxBoxSizer* boxSizerCatIdVendeur = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatIdVendeur->Add(m_staticTextIdVendeur, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatIdVendeur->Add(m_textCtrlIdVendeur, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatIdVendeur->Add(m_staticBitmapIdVendeur, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // No Série
    wxBoxSizer* boxSizerCatNoSerie = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatNoSerie->Add(m_staticTextNoSerie, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatNoSerie->Add(m_textCtrlNoSerie, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatNoSerie->Add(m_staticBitmapNoSerie, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    // IP
    wxBoxSizer* boxSizerCatIP = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatIP->Add(m_staticTextIP, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatIP->Add(m_textCtrlIP, 2, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    boxSizerCatIP->Add(m_staticBitmapIP, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL|wxRESERVE_SPACE_EVEN_IF_HIDDEN, 5);
    
    // Sizer pour les catégories (qu'on empile)
    wxBoxSizer* boxSizerCategories = new wxBoxSizer(wxVERTICAL);
    boxSizerCategories->Add(boxSizerCatId, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 0);
    boxSizerCategories->Add(m_staticLineCat0, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatLocal, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat1, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatNom, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat2, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatNoPlaque, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat3, 0, wxALL|wxEXPAND, 0);   
    boxSizerCategories->Add(boxSizerCatNoPrise, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat4, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatCouleurPrise, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat5, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatSwitch, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat6, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatPort, 0, wxALL|wxEXPAND, 5);       
    boxSizerCategories->Add(m_staticLineCat7, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatAppartenance, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat8, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatArchitecture, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat9, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatOS, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat10, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatType, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat11, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatResponsable, 0, wxALL|wxEXPAND, 5);  
    boxSizerCategories->Add(m_staticLineCat12, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatIdVendeur, 0, wxALL|wxEXPAND, 5);  
    boxSizerCategories->Add(m_staticLineCat13, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatNoSerie, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat14, 0, wxALL|wxEXPAND, 0);
    boxSizerCategories->Add(boxSizerCatIP, 0, wxALL|wxEXPAND, 5);
    boxSizerCategories->Add(m_staticLineCat15, 0, wxALL|wxEXPAND, 0);
    
    // Sizer pour les boutons Modify et Cancel
    wxBoxSizer* boxSizerCatButtons = new wxBoxSizer(wxHORIZONTAL);
    boxSizerCatButtons->Add(m_buttonCatModifier, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL, 10);
    boxSizerCatButtons->Add(m_buttonCatAnnuler, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL, 10);
    
    // Sizer de la zine d'info
    wxStaticBoxSizer* staticBoxSizerCatDesc = new wxStaticBoxSizer( new wxStaticBox(this, wxID_ANY, _(L"Description")), wxVERTICAL);
    staticBoxSizerCatDesc->Add(m_staticTextCatDesc, 1, wxALL|wxEXPAND, 5);
    
    // Sizer vertical pour la bannière, les catégories, les boutons et la zone de texte
    wxBoxSizer* boxSizerEquipDetail = new wxBoxSizer(wxVERTICAL);
    boxSizerEquipDetail->SetMinSize(320,-1);       
    boxSizerEquipDetail->Add(m_bannerCategories, 1, wxALL|wxEXPAND, 0);     // Ajout de la bannière
    boxSizerEquipDetail->Add(boxSizerCategories, 0, wxALL|wxEXPAND, 5);     // Ajout des catégories
    boxSizerEquipDetail->Add(m_buttonCatDelete, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);   // Ajout du bouton Delete
    boxSizerEquipDetail->Add(boxSizerCatButtons, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);           // Ajout des boutons Modify et Cancel
    boxSizerEquipDetail->Add(staticBoxSizerCatDesc, 1, wxALL|wxEXPAND, 5);        // Ajout de la zone d'info
    
    // Taille mini de 300
    boxSizerEquipDetail->SetMinSize(wxSize(320,-1));
    
    return boxSizerEquipDetail;
}


/**
 * @brief Image de séparation horizontale
 * @return Renvoie l'image
 */
wxStaticBitmap* MainWindow::getHorizontalImage(){
    wxBitmap m_bmp = wxBitmap(_(L"../Assets/BarreH.png"), wxBITMAP_TYPE_PNG);    // Image
    return new wxStaticBitmap(this, wxID_ANY, m_bmp, wxDefaultPosition, wxDefaultSize, 0 );
}

/**
 * @brief Image de séparation verticale
 * @return Renvoie l'image
 */
wxStaticBitmap* MainWindow::getVerticalImage(){    
    wxBitmap m_bmp = wxBitmap(_(L"../Assets/BarreV.png"), wxBITMAP_TYPE_PNG);    // Image
    return new wxStaticBitmap(this, wxID_ANY, m_bmp, wxDefaultPosition, wxDefaultSize, 0 );
}

/**
 * @brief Icone du programme
 * @return Renvoie l'icone
 */
void MainWindow::getProgIcon(wxIconBundle& icon){
    
    // On charge les différentes tailles des icones
    wxBitmap iconBmp16 = wxBitmap(_(L"../Assets/Icon_16x16.png"), wxBITMAP_TYPE_PNG);
    wxBitmap iconBmp24 = wxBitmap(_(L"../Assets/Icon_24x24.png"), wxBITMAP_TYPE_PNG);
    wxBitmap iconBmp32 = wxBitmap(_(L"../Assets/Icon_32x32.png"), wxBITMAP_TYPE_PNG);
    wxBitmap iconBmp48 = wxBitmap(_(L"../Assets/Icon_48x48.png"), wxBITMAP_TYPE_PNG);
    wxBitmap iconBmp64 = wxBitmap(_(L"../Assets/Icon_64x64.png"), wxBITMAP_TYPE_PNG);
    wxBitmap iconBmp96 = wxBitmap(_(L"../Assets/Icon_96x96.png"), wxBITMAP_TYPE_PNG);
    wxBitmap iconBmp128 = wxBitmap(_(L"../Assets/Icon_128x128.png"), wxBITMAP_TYPE_PNG);
    wxBitmap iconBmp256 = wxBitmap(_(L"../Assets/Icon_256x256.png"), wxBITMAP_TYPE_PNG);
    
    // On les applique
    wxIcon icn;
    icn.CopyFromBitmap(iconBmp16);
    icon.AddIcon( icn );
    icn.CopyFromBitmap(iconBmp24);
    icon.AddIcon( icn );
    icn.CopyFromBitmap(iconBmp32);
    icon.AddIcon( icn );
    icn.CopyFromBitmap(iconBmp48);
    icon.AddIcon( icn );
    icn.CopyFromBitmap(iconBmp64);
    icon.AddIcon( icn );
    icn.CopyFromBitmap(iconBmp96);
    icon.AddIcon( icn );
    icn.CopyFromBitmap(iconBmp128);
    icon.AddIcon( icn );
    icn.CopyFromBitmap(iconBmp256);
    icon.AddIcon( icn );    
}
