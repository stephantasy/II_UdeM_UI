#include "CatName.h"

using std::string;

const string FORMAT = "Valeur alphanumérique";
const string TAG = "Nom";
const string DESC = "Nom de l’équipement.";

// Provide Example Name Format and Category Name
CatName::CatName()
{
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatName::~CatName()
{
}

// Return whether the name format is good
bool CatName::isDataFormatOk(const string s) const
{
	return !(s.empty());
}

