#include "CatSwitch.h"

using std::string;

const string FORMAT = "Valeur alphanumérique";
const string TAG = "Switch";
const string DESC = "Nom du commutateur réseau où est branché l'équipement";

// Provide Example Name Format and Category Name
CatSwitch::CatSwitch()
{	
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatSwitch::~CatSwitch()
{
}

// Return whether the name format is good
bool CatSwitch::isDataFormatOk(const string s) const
{
	return !(s.empty());
}

