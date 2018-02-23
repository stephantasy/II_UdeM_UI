#include <cctype>
#include "CatLocal.h"
#include "Tools.h"

using std::string;

const string FORMAT = "La valeur doit être un chiffre entre 0 et 1000";
const string TAG = "Local";
const string DESC = "Numéro du local où est installé l’équipement.";

// Provide Example Name Format and Category Name
CatLocal::CatLocal()
{	
	// Le nom est aussi un nombre
	_isNameIntable = true;
	_isNameConstraint = true;
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatLocal::~CatLocal()
{
}

// Return whether the name format is good
bool CatLocal::isDataFormatOk(const string s) const
{
	if (s.empty()) 
        return false;
        
	if (!_isNameEmpty) {
		// Est-ce un nombre ?
		if (Tools::isAllDigits(s)) {
			// Est-il comnpris entre 0 et 1000 ?
			int number = atoi(s.c_str());
			if (number >= 0 && number <= 1000) {
				return true;
			}
		}
		return false;
	}
	return true;
}

