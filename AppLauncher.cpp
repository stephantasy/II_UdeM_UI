#include <wx/app.h>
#include <wx/event.h>
#include "MainApp.h"
#include <wx/image.h>

// Démarrage du programme
class AppLauncher : public wxApp
{
public:
    AppLauncher() {}
    virtual ~AppLauncher() {}

    virtual bool OnInit() {
        
        // Gestion des images
        wxImage::AddHandler( new wxPNGHandler );
        wxImage::AddHandler( new wxJPEGHandler );

        // Fenêtre à afficher
        MainApp *mainApp = new MainApp(NULL);
        
        // On tente d'ouvrir le fichier par défaut
        wxString defaultFile("../Data/Data.csv");
        if(mainApp->IsFileExists(defaultFile))
            mainApp->ReadFile(defaultFile);
        
        // Affichage
        SetTopWindow(mainApp);
        return GetTopWindow()->Show();
    }
};

DECLARE_APP(AppLauncher)
IMPLEMENT_APP(AppLauncher)
