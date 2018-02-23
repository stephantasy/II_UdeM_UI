#include "CatResponsable.h"

using std::string;

const string FORMAT = "Valeur alphanumérique";
const string TAG = "Responsable";
const string DESC = "Nom du professeur ou du département, si c’est une utilisation globale, qui possède l'équipement.";

// Provide Example Name Format and Category Name
CatResponsable::CatResponsable()
{	
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatResponsable::~CatResponsable()
{
}

// Return whether the name format is good
bool CatResponsable::isDataFormatOk(const string s) const
{
	return !(s.empty());
}

