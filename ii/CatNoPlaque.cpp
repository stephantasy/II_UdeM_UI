#include "CatNoPlaque.h"

using std::string;

const string FORMAT = "Le format doit être : Numéro du local / numero de la plaque (nombre entier)";
const string TAG = "No. Plaque";
const string DESC = "Numéro de la plaque murale où est branché l'équipement.";

// Provide Example Name Format and Category Name
CatNoPlaque::CatNoPlaque(CatLocal &local) : _local(local)
{	
	_isNameConstraint = true;
	_formatRule = FORMAT;
	_tag = TAG;	
	_desc = DESC;
}


CatNoPlaque::~CatNoPlaque()
{
}

// Return whether the name format is good
bool CatNoPlaque::isDataFormatOk(const string s) const
{
	if (s.empty()) 
        return false;
        
	// On cherche le nom du local dans le nom de la plaque et on respecte le format x/y    
    string reg = "^(" + _local.getStringValue() + "\\/[0-9]*)$";
	return Tools::matchRegex(s, reg);
}

