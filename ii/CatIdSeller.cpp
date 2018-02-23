#include "CatIdSeller.h"

using std::string;

const string FORMAT = "Valeur alphanumérique";
const string TAG = "Id Vendeur";
const string DESC = "Numéro de l’inventaire du vendeur de l'équipement.";

// Provide Example Name Format and Category Name
CatIdSeller::CatIdSeller()
{
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatIdSeller::~CatIdSeller()
{
}

// Return whether the name format is good
bool CatIdSeller::isDataFormatOk(const string s) const
{
	return !(s.empty());
}

