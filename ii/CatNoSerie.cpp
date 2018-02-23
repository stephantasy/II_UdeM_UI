#include "CatNoSerie.h"

using std::string;

const string FORMAT = "Valeur alphanumérique";
const string TAG = "No. Série";
const string DESC = "Numéro indiqué sur l’équipement.";

// Provide Example Name Format and Category Name
CatNoSerie::CatNoSerie()
{	
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatNoSerie::~CatNoSerie()
{
}

// Return whether the name format is good
bool CatNoSerie::isDataFormatOk(const string s) const
{
	return !(s.empty());
}

