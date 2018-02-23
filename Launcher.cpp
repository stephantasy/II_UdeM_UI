#include <wx/app.h>
#include <wx/event.h>
#include "MainFrame.h"
#include <wx/image.h>


// Define the MainApp
class AppLauncher : public wxApp
{
public:
    Launcher() {}
    virtual ~Launcher() {}

    virtual bool OnInit() {
        
        // Gestion des images
        wxImage::AddHandler( new wxPNGHandler );
        wxImage::AddHandler( new wxJPEGHandler );

        // Fenêtre à afficher
        MainFrame *mainFrame = new MainFrame(NULL);
        
        // On tente d'ouvrir le fichier par défaut
        wxString defaultFile("Data.csv");
        if(mainFrame->IsFileExists(defaultFile))
            mainFrame->ReadFile(defaultFile);
        
        // Affichage
        SetTopWindow(mainFrame);
        return GetTopWindow()->Show();
    }
};

DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)
