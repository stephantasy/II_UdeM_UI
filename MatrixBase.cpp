#include "MatrixWindow.h"

MatrixBase::MatrixBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
    
    /* ************************************
     *  CRÉATION DES OBJETS DE LA FENÊTRE
     * ************************************ */
     
    // Titre
    m_staticTextTitle = new wxStaticText(this, wxID_ANY, _(L"Tableau des équipements"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), 0);
    m_staticTextTitle->SetForegroundColour(wxColour(_("rgb(220,220,255)")));
    wxFont m_staticTextTitleFont(16, wxFONTFAMILY_ROMAN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, _(L"Lucida Bright"));
    m_staticTextTitle->SetFont(m_staticTextTitleFont);
        
    // Zone de texte
    m_textCtrlMatrice = new wxTextCtrl(this, wxID_ANY, _(L""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1,-1)), wxTE_READONLY|wxTE_MULTILINE|wxBORDER_STATIC|wxHSCROLL|wxVSCROLL);
    m_textCtrlMatrice->SetBackgroundColour(wxColour(_("rgb(200,220,225)")));
    m_textCtrlMatrice->SetForegroundColour(wxColour(_("rgb(0,0,50)")));
    wxFont m_textCtrlMatriceFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _(L"Lucida Console"));
    m_textCtrlMatrice->SetFont(m_textCtrlMatriceFont);
    
    
    /* ************************************
     *          DÉTAILS DE LA FENÊTRE
     * ************************************ */

    // Binds the given function, functor or method dynamically with the event. (cf. documentation : http://docs.wxwidgets.org/3.1/classwx_evt_handler.html#a0f30c8fa5583b4a5f661897d63de3b62)
    this->Bind(wxEVT_CLOSE_WINDOW, OnClose, this);

    // Ajout du Main Sizer et des éléments qu'il contient
    wxBoxSizer* boxSizerMain = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(boxSizerMain);    
    boxSizerMain->Add(m_staticTextTitle, 0, wxALL|wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL, 5);     // Ajout du titre
    boxSizerMain->Add(m_textCtrlMatrice, 1, wxALL|wxEXPAND, 0);                                     // Ajout de la zone de texte
            
    // Couleur de fond et du texte
    SetBackgroundColour(wxColour(_("rgb(40,70,80)")));
    SetForegroundColour(wxColour(_("rgb(220,220,255)")));
    
    // Taille et centrage à l'écran
    SetMinClientSize(wxSize(500,300));
    SetSize(950,650);
    CentreOnParent(wxBOTH);
}

MatrixBase::~MatrixBase()
{
    this->Unbind(wxEVT_CLOSE_WINDOW, OnClose, this);
}
