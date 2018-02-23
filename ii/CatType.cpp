#include "CatType.h"

using std::string;
using std::vector;

const string FORMAT = "Choisir un élément dans la liste";
const string TAG = "Type";
const string DESC = "Type d'équipement.";

std::map<CatType::choix, std::string> CatType::_choixMap = {
	{ choix::Cluster, "Cluster" },
	{ choix::Station_accueil, "Station d\'accueil" },
	{ choix::Imprimante, "Imprimante" },
	{ choix::Laptop, "Laptop" },
	{ choix::Routeur, "Routeur" },
	{ choix::Serveur, "Serveur" },
	{ choix::Station, "Station" }
};


// Provide Example Name Format and Category Name
CatType::CatType()
{	
	_isNameConstraint = true;
	_formatRule = FORMAT;
	_tag = TAG;
	_desc = DESC;
}

CatType::~CatType()
{
}

std::string CatType::getChoixName(choix c)
{
	std::string res("Undefined Type");
	auto it = _choixMap.find(c);
	if (it != _choixMap.end()) {
		res = it->second;
	}
	return res;
}

// Return whether the name format is good
bool CatType::isDataFormatOk(const string s) const
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
vector<string> CatType::getDataFormatList() const
{
    vector<string> data;
    for (auto& m : _choixMap) {
		data.push_back(m.second);
	}
    return data;
}

// Renvoie l'index du choix
int CatType::getDataFormatIndex() const
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