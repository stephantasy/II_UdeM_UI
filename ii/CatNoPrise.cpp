#include "CatNoPrise.h"

using std::string;

const string FORMAT = "Valeur alphanumérique";
const string TAG = "No. Prise";
const string DESC = "Le numéro correspond au numéro sur le panneau de branchement de la prise dans la salle des serveurs.";

// Provide Example Name Format and Category Name
CatNoPrise::CatNoPrise()
{
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatNoPrise::~CatNoPrise()
{
}

// Return whether the name format is good
bool CatNoPrise::isDataFormatOk(const string s) const
{
	// IMPROVEMENT: Le numéro devrait être unique...
	return !(s.empty());
}

