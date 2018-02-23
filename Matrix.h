#ifndef MATRIX_H
#define MATRIX_H

#include "MatrixWindow.h"
#include <functional>
#include <vector>

using stdf = std::function<void()>;

class Matrix : public MatrixWindow
{
public:
    Matrix(wxWindow* parent);
    virtual ~Matrix();
    
    void clearText();
    void appendText(wxString);
    
    void CallbackInscription (stdf);
    
private:
    std::vector<stdf> callbacks;    // Vector contenant les fonctions enregistrées pour le Callback

protected:
    virtual void OnClose(wxCloseEvent& event);
};
#endif // MATRIX_H
