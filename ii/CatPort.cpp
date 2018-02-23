#include "CatPort.h"
#include "Tools.h"

using std::string;

const string FORMAT = "Un nombre entre 0 et 255";
const string TAG = "Port";
const string DESC = "Numéro de port du commutateur sur lequel l'équipement est branché.";

// Provide Example Name Format and Category Name
CatPort::CatPort()
{	
	// Le nom est aussi un nombre
	_isNameIntable = true;
	_isNameConstraint = true;
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatPort::~CatPort()
{
}

// Return whether the name format is good
bool CatPort::isDataFormatOk(const string s) const
{	
	if (s.empty()) 
        return false;
        
	if (Tools::isAllDigits(s)) {
		if (std::stoi(s.c_str()) >= 0 && std::stoi(s.c_str()) < 256) {
			return true;
		}
	}
	return false;
}

