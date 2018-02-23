#include "CatColorPrise.h"

using std::string;
using std::map;
using std::vector;

const string FORMAT = "Choisir une couleur dans la liste";
const string TAG = "Couleur Prise";
const string DESC = "La prise où est branché l'équipement peut avoir une des 4 couleurs.";

map<CatColorPrise::choix, string> CatColorPrise::_choixMap = {
	{ choix::Jaune, "Jaune" },
	{ choix::Vert, "Vert" },
	{ choix::Rose, "Rose" },
	{ choix::Bleu, "Bleu" }
};

// Provide Example Name Format and Category Name
CatColorPrise::CatColorPrise()
{
	_isNameConstraint = true;
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatColorPrise::~CatColorPrise()
{
}

// Return whether the name format is good
bool CatColorPrise::isDataFormatOk(const string s) const
{
	bool res = false;
	for (auto& m : _choixMap) {
		if (s == m.second) {
			return true;
		}
	}
	return res;
}

// Renvoie la liste de choix
vector<string> CatColorPrise::getDataFormatList() const
{
    vector<string> data;
    for (auto& m : _choixMap) {
		data.push_back(m.second);
	}
    return data;
}

// Renvoie l'index du choix
int CatColorPrise::getDataFormatIndex() const
{
    int res = 0;
	for (auto& m : _choixMap) {
		if (_value == m.second) {
			return res;
		}
        res++;
	}
	return res;
}
