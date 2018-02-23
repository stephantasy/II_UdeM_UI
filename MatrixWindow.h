#ifndef MATRIXWINDOW_H
#define MATRIXWINDOW_H

#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>

class MatrixWindow : public wxDialog
{
protected:
    wxStaticText* m_staticTextTitle;
    wxTextCtrl* m_textCtrlMatrice;

protected:
    // Méthode pour la gestion des événements (redéfinie dans la classe fille)
    virtual void OnClose(wxCloseEvent& event) { event.Skip(); }

public:
    MatrixWindow( wxWindow* parent, 
                wxWindowID id = wxID_ANY,
                const wxString& title = _("Matrice"), 
                const wxPoint& pos = wxDefaultPosition, 
                const wxSize& size = wxSize(950,650), 
                long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER
    );
    virtual ~MatrixWindow();
};

#endif // MATRIXWINDOW_H
