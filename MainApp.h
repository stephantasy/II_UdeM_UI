#ifndef MAINAPP_H
#define MAINAPP_H

//#include "wxcrafter.h"

#include "MainWindow.h"
#include "Matrix.h"
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/file.h>
#include <wx/msgdlg.h>
#include <Texts.h>
#include <ii/Tools.h>
#include <ii/Inventory.h>
#include <fstream>
#include <memory>

class MainApp : public MainWindow
{
public:
    MainApp(wxWindow*);
    virtual ~MainApp();
    
    bool IsFileExists(const wxString&) const;
    void ReadFile(const wxString&);
    
protected:
    // Menu et Toolbar
    virtual void OnOpenFile(wxCommandEvent& event);
    virtual void OnSaveFile(wxCommandEvent& event);
    virtual void OnAbout(wxCommandEvent& event);   
    virtual void OnExitAsk(wxCommandEvent& event);
    // Liste
    virtual void OnColumnSort(wxDataViewEvent& event);
    virtual void OnItemSelected(wxDataViewEvent& event);
    virtual void OnSearch(wxCommandEvent& event);
    virtual void OnSearchCancel(wxCommandEvent& event);
    // Catégories
    virtual void OnInfoClic(wxMouseEvent& event);
    virtual void OnCategoryClic(wxMouseEvent& event);
    virtual void OnCategoryModified(wxCommandEvent& event);
    // Bouton Catégories
    virtual void OnEquipmentCancel(wxCommandEvent& event);
    virtual void OnEquipmentDelete(wxCommandEvent& event);
    virtual void OnEquipmentModify(wxCommandEvent& event);
    // Matrice
    virtual void OnDisplayMatrix(wxCommandEvent& event);    
    // Fermeture du programme
    virtual void OnExit(wxCloseEvent& event);
        
private:
    Matrix* matrix;                             // Fenêtre contenant la matrice

    std::unique_ptr<Inventory> inventory;       // Inventaire des équipments
    std::vector<std::string> m_equipmentMem;    // Valeur de l'équipement temporaire
    bool m_isNeedToSaveFile = false;            // Au moins un équipement a été modifié, donc il faut sauver le fichier
    bool m_isNeedToSaveEquipment = false;       // Au moins une catégorie a été modifiée, donc il faut appliquer la modification
    wxString m_fileName;                        // Chemin du fichier en cours de lecture
    bool m_fileLoaded = false;                  // Si un fichier a été chargé
    bool m_isRSearchActive = false;             // Indique si une recherche est en cours
    wxVector<wxVector<wxVariant>> m_data;       // Liste des équipements affichés ; 4 = nombre de colonnes dans le DataView
    std::vector<int> idEquipmentListFound;      // Liste des équipements dans la dernière recherche
    wxString m_defaultCatFormat;                // Message par défaut dans la description du format de données
    int m_currentEquipmentIndex = -1;           // Index de l'équipement actuellement affiché
    int m_currentSelectedRow = -1;              // Ligne sélectionnée
    bool m_isModifying = false;                 // Si un équipement est en cours de modification
    int m_isCategoryError = 0;                  // Indique les erreurs dans les catégories
    bool m_isMatrixDisplayed = false;           // Indique si la matrice est visible
    
    Equipment::category getCategorieIndex(int) const;
    
    void setDataAfterSort();
    void setDataAfterSearch(bool);
    void setTextCrtlEnable(bool);
    void setCategoryIcon(Equipment::category, bool);
    void setCatagoryModifyButtons(bool);
    void setCategoryError(Equipment::category, bool);
    
    bool isAllDataSafe();
    bool isModifInProgress();
    void cancelModification();
    void doSearchCancel();
    
    void fillEquipmentsList(bool);
    void fillEquipmentDetail(int);
    
    void MatrixHasBeenClosed();
    void refreshMatrix();
    
    enum StatusBar
    {
        // Cellules
        Field_State,
        Field_Info,
        Field_Version,
        Field_Max,
        // Actions
        Statusbar_Init,
        Statusbar_NbElements,
        Statusbar_NbElementsSearch,
        Statusbar_NeedSave,
    };
    void updateStatusBar(StatusBar);
    void updateSaveItems();
    
};
#endif // MAINAPP_H
