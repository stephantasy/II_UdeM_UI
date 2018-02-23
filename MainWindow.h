#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/frame.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/bannerwindow.h>
#include <wx/dataview.h>
#include <wx/statbmp.h>
#include <wx/srchctrl.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/statbox.h>
#include <wx/statusbr.h>
#include <wx/dialog.h>

class MainWindow : public wxFrame
{
public:
    MainWindow( wxWindow* parent, 
                wxWindowID id = wxID_ANY, 
                const wxString& title = _(L"Inventaire Informatique UdeM"), 
                const wxPoint& pos = wxDefaultPosition, 
                const wxSize& size = wxSize(780, 700), 
                long style = wxCAPTION|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLOSE_BOX
    );
    virtual ~MainWindow();
    
    // Enum des ID
    enum{
        // Liste des équipements
        ID_ITEM_SELECTED,
        ID_SEARCH_ZONE,
        ID_SEARCH_RESET,
        
        // Catégories
        ID_LOCAL,
        ID_NOM,
        ID_NO_PLAQUE,
        ID_NO_PRISE,
        ID_COULEUR_PRISE,
        ID_SWITCH,
        ID_PORT,
        ID_APPARTENANCE,
        ID_ARCHITECTURE,
        ID_OS,
        ID_TYPE,
        ID_RESPONSABLE,
        ID_ID_VENDEUR,
        ID_NO_SERIE,
        ID_IP,
        
        // Boutons
        ID_BT_CAT_SUPPRIMER,
        ID_BT_CAT_MODIFIER,
        ID_BT_CAT_ANNULER,
        
        // Matrice
        ID_MATRIX,
        
        // Barres        
        ID_STATUSBAR,
    };
    
protected:    
    /* ******************
     *      VARIABLES
     * ******************/
     
    // List
    wxDataViewListCtrl* m_equipmentList;    
   
    // Search
    wxSearchCtrl* m_searchCtrl;
    wxButton* m_buttonClearSearch;
    
    // Categories
    wxStaticText* m_staticTextId;       // Les wxStaticText sont globales à cause des Bind
    wxStaticText* m_staticTextIdNb;
    wxStaticText* m_staticTextLocal;
    wxTextCtrl* m_textCtrlLocal;
    wxStaticBitmap* m_staticBitmapLocal;
    wxStaticText* m_staticTextNom;
    wxTextCtrl* m_textCtrlNom;
    wxStaticBitmap* m_staticBitmapNom;
    wxStaticText* m_staticTextNoPlaque;
    wxTextCtrl* m_textCtrlNoPlaque;
    wxStaticBitmap* m_staticBitmapNoPlaque;
    wxStaticText* m_staticTextNoPrise;
    wxTextCtrl* m_textCtrlNoPrise;
    wxStaticBitmap* m_staticBitmapNoPrise;
    wxStaticText* m_staticTextCouleurPrise;
    wxChoice* m_choiceCouleurPrise;
    wxStaticBitmap* m_staticBitmapCouleurPrise;
    wxStaticText* m_staticTextSwitch;
    wxTextCtrl* m_textCtrlSwitch;
    wxStaticBitmap* m_staticBitmapSwitch;
    wxStaticText* m_staticTextPort;
    wxTextCtrl* m_textCtrlPort;
    wxStaticBitmap* m_staticBitmapPort;
    wxStaticText* m_staticTextAppartenance;
    wxTextCtrl* m_textCtrlAppartenance;
    wxStaticBitmap* m_staticBitmapAppartenance;
    wxStaticText* m_staticTextArchitecture;
    wxTextCtrl* m_textCtrlArchitecture;
    wxStaticBitmap* m_staticBitmapArchitecture;
    wxStaticText* m_staticTextOS;
    wxTextCtrl* m_textCtrlOS;
    wxStaticBitmap* m_staticBitmapOS;
    wxStaticText* m_staticTextType;
    wxChoice* m_choiceType;
    wxStaticBitmap* m_staticBitmapType;
    wxStaticText* m_staticTextResponsable;
    wxTextCtrl* m_textCtrlResponsable;
    wxStaticBitmap* m_staticBitmapResponsable;
    wxStaticText* m_staticTextIdVendeur;
    wxTextCtrl* m_textCtrlIdVendeur;
    wxStaticBitmap* m_staticBitmapIdVendeur;
    wxStaticText* m_staticTextNoSerie;
    wxTextCtrl* m_textCtrlNoSerie;
    wxStaticBitmap* m_staticBitmapNoSerie;
    wxStaticText* m_staticTextIP;
    wxTextCtrl* m_textCtrlIP;
    wxStaticBitmap* m_staticBitmapIP;
    
    // Boutons
    wxButton* m_buttonCatDelete;
    wxButton* m_buttonCatModifier;
    wxButton* m_buttonCatAnnuler;
    
    // Description
    wxTextCtrl* m_staticTextCatDesc;

    // Barres
    wxMenuItem* m_menuItemOpen;
    wxMenuItem* m_menuItemSave;
    wxMenuItem* m_menuItemExit;
    wxMenuItem* m_menuItemAbout;
    wxToolBar* m_toolbar;
    wxStatusBar* m_statusBar;
    
    /* ******************
     *      FONCTIONS
     * ******************/
     
    // Méthodes pour la gestion des événements (redéfinies dans la classe fille)
    // Main Window    
    virtual void OnExit(wxCloseEvent& event) { event.Skip(); }                  // On quitte le programme
    // Menus    
    virtual void OnOpenFile(wxCommandEvent& event) { event.Skip(); }            // Ouvrir un fichier
    virtual void OnSaveFile(wxCommandEvent& event) { event.Skip(); }            // Sauvegarde
    virtual void OnExitAsk(wxCommandEvent& event) { event.Skip(); }             // On demande à quitter le programme
    virtual void OnAbout(wxCommandEvent& event) { event.Skip(); }               // À propos
    virtual void OnDisplayMatrix(wxCommandEvent& event) { event.Skip(); }       // Affichage de la matrice
    // List
    virtual void OnColumnSort(wxDataViewEvent& event) { event.Skip(); }         // Tir des colonnes
    virtual void OnItemSelected(wxDataViewEvent& event) { event.Skip(); }       // Sélection d'un équipement
    // Search
    virtual void OnSearch(wxCommandEvent& event) { event.Skip(); }              // Recherche
    virtual void OnSearchCancel(wxCommandEvent& event) { event.Skip(); }        // Clear de la recherche
    // Categories    
    virtual void OnCategoryClic(wxMouseEvent& event) { event.Skip(); }          // Info
    virtual void OnCategoryModified(wxCommandEvent& event) { event.Skip(); }    // Modification
    virtual void OnInfoClic(wxMouseEvent& event) { event.Skip(); }              // Clic sur l'image
    virtual void OnEquipmentDelete(wxCommandEvent& event) { event.Skip(); }     // Suppression
    virtual void OnEquipmentModify(wxCommandEvent& event) { event.Skip(); }     // Validation 
    virtual void OnEquipmentCancel(wxCommandEvent& event) { event.Skip(); }     // Annulation
    
private:
    /* ******************
     *      FONCTIONS
     * ******************/
    wxMenuBar* getMenuBar();
    wxToolBar* getToolsBar();
    wxStatusBar* getStatusBar();
    wxBoxSizer* getEquipmentListSizer();
    wxBoxSizer* getSearchSizer();
    wxBoxSizer* getCategoriesSizer();
    wxStaticBitmap* getHorizontalImage();
    wxStaticBitmap* getVerticalImage();
    void getProgIcon(wxIconBundle&);    
};

#endif // MAINWINDOW_H
