#include "CatArchitecture.h"


using std::string;

const string FORMAT = "Valeur alphanumérique";
const string TAG = "Architecture";
const string DESC = "Type de l’équipement. Exemple pour un PC (sans nom) : HP, Lenovo, Mac ou VM.";

// Provide Example Name Format and Category Name
CatArchitecture::CatArchitecture()
{
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatArchitecture::~CatArchitecture()
{
}

// Return whether the name format is good
bool CatArchitecture::isDataFormatOk(const string s) const
{
	return !(s.empty());
}

