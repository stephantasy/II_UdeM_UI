#include "CatIp.h"
#include "Tools.h"

using std::string;

const string FORMAT = "a.b.c.d où a, b, c, et d sont des nombres entre 0 et 255";
const string TAG = "IP";
const string DESC = "Adresse de l'équipement. Elle est unique sur le réseau, exemple 10.10.20.30.";

// Provide Example Name Format and Category Name
CatIp::CatIp()
{	
	_isNameConstraint = true;
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatIp::~CatIp()
{
}

// Return whether the name format is good
bool CatIp::isDataFormatOk(const string s) const
{    
	if (s.empty()) 
        return false;
    
	// On contrôle si le format est bon avec une expression régulière
	string reg = "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$";
	return Tools::matchRegex(s, reg);
}

