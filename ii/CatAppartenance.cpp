#include "CatAppartenance.h"

using std::string;

const string FORMAT = "Valeur alphanumérique";
const string TAG = "Appartenance";
const string DESC = "Nom du laboratoire, de l'administration, de l'enseignement ou de l'infrastructure auquel appartient l'équipement.";

// Provide Example Name Format and Category Name
CatAppartenance::CatAppartenance()
{
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatAppartenance::~CatAppartenance()
{
}

// Return whether the name format is good
bool CatAppartenance::isDataFormatOk(const string s) const
{
	return !(s.empty());
}

