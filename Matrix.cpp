#include "Matrix.h"

Matrix::Matrix(wxWindow* parent) : MatrixWindow(parent)
{
}

Matrix::~Matrix()
{
}

// On vide le texte courant
void Matrix::clearText()
{
    m_textCtrlMatrice->Clear();
}

// On ajoute du texte à celui existant
void Matrix::appendText(wxString s)
{
    m_textCtrlMatrice->AppendText(s);
}

// Enregistrement des fonctions à appeler
void Matrix::CallbackInscription(stdf v){
    stdf f = std::bind(v);
	callbacks.push_back(f);
}

// Lorsqu'on ferme la fenêtre, on ne fait que la cacher
void Matrix::OnClose(wxCloseEvent& event)
{
    wxUnusedVar(event);
    
    // On prévient toutes les fonctions enregistrées
	for(auto& f : callbacks) {
		f();
	}
    
    // On cache la fenêtre
    this->Show(false);      // NE PAS DÉTRUIRE !
}
