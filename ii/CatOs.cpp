#include "CatOs.h"

using std::string;

const string FORMAT = "Valeur alphanumérique";
const string TAG = "OS";
const string DESC = "Système d'exploitation de l'équipement.";

// Provide Example Name Format and Category Name
CatOs::CatOs()
{	
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatOs::~CatOs()
{
}

// Return whether the name format is good
bool CatOs::isDataFormatOk(const string s) const
{
	return !(s.empty());
}

