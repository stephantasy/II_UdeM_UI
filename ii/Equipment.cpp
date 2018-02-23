#include "Equipment.h"
#include "Tools.h"

using namespace std;

int Equipment::_equipmentNumber = 0;
const char DELIMITER = ';';


Equipment::Equipment()
{
	++_equipmentNumber;    
}

Equipment::~Equipment()
{
    --_equipmentNumber;
}


// Résultat de l'initialisation d'un équipement :
//	- < 0	: Équipement corrompu car il manque des catégories
//	- = 0	: Ok
//	- > 0	: Chaque bit à 1 correspond à l'équipement dont le nom ne respecte pas le format attendu
int Equipment::setEquipment(const string& EquipmentLine)
{
	// On mémorise la ligne
	_rawLine = EquipmentLine;

	// On place les catégories dans un vecteur
	vector<string> categories;
	if (!EquipmentLine.empty()) {
		Tools::split(EquipmentLine, DELIMITER, back_inserter(categories));
	}

	// Id 
	_id = _equipmentNumber;

	// Nombre de catégorie pas bon
	if (categories.size() < NB_CATEGORY) {
		return -1;
	}

	// On initialise les catégories en contrôlant si leur valeur est bien formée
	int cpt = 0;
	if (!_local.setValue(categories[cpt++])) _initializationResult |= 1u << 0;
	if (!_name.setValue(categories[cpt++])) _initializationResult |= 1u << 1;
	if (!_noPlaque.setValue(categories[cpt++])) _initializationResult |= 1u << 2;
	if (!_noPrise.setValue(categories[cpt++])) _initializationResult |= 1u << 3;
	if (!_colorPrise.setValue(categories[cpt++])) _initializationResult |= 1u << 4;
	if (!_switch.setValue(categories[cpt++])) _initializationResult |= 1u << 5;
	if (!_port.setValue(categories[cpt++])) _initializationResult |= 1u << 6;
	if (!_appartenance.setValue(categories[cpt++])) _initializationResult |= 1u << 7;
	if (!_architecture.setValue(categories[cpt++])) _initializationResult |= 1u << 8;
	if (!_os.setValue(categories[cpt++])) _initializationResult |= 1u << 9;
	if (!_type.setValue(categories[cpt++])) _initializationResult |= 1u << 10;
	if (!_responsable.setValue(categories[cpt++])) _initializationResult |= 1u << 11;
	if (!_sellerId.setValue(categories[cpt++])) _initializationResult |= 1u << 12;
	if (!_noSerie.setValue(categories[cpt++])) _initializationResult |= 1u << 13;
	if (!_ip.setValue(categories[cpt++])) _initializationResult |= 1u << 14;

	return _initializationResult;
}

// Set le nom de la catégorie ciblée et renvoie si cela a fonctionné
bool Equipment::setCategoryValue(category cat, string s) {
	bool res = false;
	switch (cat)
	{
		case category::Appartenance:
			res = _appartenance.setValue(s);
			break;
		case category::Architecture:
			res = _architecture.setValue(s);
			break;
		case category::CouleurPrise:
			res = _colorPrise.setValue(s);
			break;
		case category::Ip:
			res = _ip.setValue(s);
			break;
		case category::Local:
			res = _local.setValue(s);
			break;
		case category::Nom:
			res = _name.setValue(s);
			break;
		case category::NoPlaque:
			res = _noPlaque.setValue(s);
			break;
		case category::NoPrise:
			res = _noPrise.setValue(s);
			break;
		case category::NoSerie:
			res = _noSerie.setValue(s);
			break;
		case category::Os:
			res = _os.setValue(s);
			break;
		case category::Port:
			res = _port.setValue(s);
			break;
		case category::Responsable:
			res = _responsable.setValue(s);
			break;
		case category::Switch:
			res = _switch.setValue(s);
			break;
		case category::Type:
			res = _type.setValue(s);
			break;
		case category::VendeurId:
			res = _sellerId.setValue(s);
			break;
		default:
			cerr << __FUNCTION__ << ": Undefined Category Name" << endl;
			res = false;
	}
	if (res) {
		rebuildRawLine();		// On reconstruit la ligne
	}
	return res;
}

// Est-ce un format valide
bool Equipment::isValidCategoryFormat(category cat, string s) const 
{
    switch (cat)
	{
		case category::Appartenance:
			return _appartenance.isDataFormatOk(s);
		case category::Architecture:
			return _architecture.isDataFormatOk(s);
		case category::CouleurPrise:
			return _colorPrise.isDataFormatOk(s);
		case category::Ip:
			return _ip.isDataFormatOk(s);
		case category::Local:
			return _local.isDataFormatOk(s);
		case category::Nom:
			return _name.isDataFormatOk(s);
		case category::NoPlaque:
			return _noPlaque.isDataFormatOk(s);
		case category::NoPrise:
			return _noPrise.isDataFormatOk(s);
		case category::NoSerie:
			return _noSerie.isDataFormatOk(s);
		case category::Os:
			return _os.isDataFormatOk(s);
		case category::Port:
			return _port.isDataFormatOk(s);
		case category::Responsable:
			return _responsable.isDataFormatOk(s);
		case category::Switch:
			return _switch.isDataFormatOk(s);
		case category::Type:
			return _type.isDataFormatOk(s);
		case category::VendeurId:
			return _sellerId.isDataFormatOk(s);
		default:
			cerr << __FUNCTION__ << ": Undefined Category Name" << endl;
	}
	return false; 
}

string Equipment::getCategoryName(category cat) const
{
	switch (cat)
	{
		case category::Appartenance:
			return _appartenance.getTag();
		case category::Architecture:
			return _architecture.getTag();
		case category::CouleurPrise:
			return _colorPrise.getTag();
		case category::Ip:
			return _ip.getTag();
		case category::Local:
			return _local.getTag();
		case category::Nom:
			return _name.getTag();
		case category::NoPlaque:
			return _noPlaque.getTag();
		case category::NoPrise:
			return _noPrise.getTag();
		case category::NoSerie:
			return _noSerie.getTag();
		case category::Os:
			return _os.getTag();
		case category::Port:
			return _port.getTag();
		case category::Responsable:
			return _responsable.getTag();
		case category::Switch:
			return _switch.getTag();
		case category::Type:
			return _type.getTag();
		case category::VendeurId:
			return _sellerId.getTag();
		default:
			cerr << __FUNCTION__ << ": Undefined Category Name" << endl;
	}
	return "";
}

string Equipment::getCategoryDesc(category cat) const
{
	switch (cat)
	{
		case category::Appartenance:
			return _appartenance.getDesc();
		case category::Architecture:
			return _architecture.getDesc();
		case category::CouleurPrise:
			return _colorPrise.getDesc();
		case category::Ip:
			return _ip.getDesc();
		case category::Local:
			return _local.getDesc();
		case category::Nom:
			return _name.getDesc();
		case category::NoPlaque:
			return _noPlaque.getDesc();
		case category::NoPrise:
			return _noPrise.getDesc();
		case category::NoSerie:
			return _noSerie.getDesc();
		case category::Os:
			return _os.getDesc();
		case category::Port:
			return _port.getDesc();
		case category::Responsable:
			return _responsable.getDesc();
		case category::Switch:
			return _switch.getDesc();
		case category::Type:
			return _type.getDesc();
		case category::VendeurId:
			return _sellerId.getDesc();
		default:
			cerr << __FUNCTION__ << ": Undefined Category Description" << endl;
	}
	return "";
}

// Renvoie le nom de la catégorie demandée
string Equipment::getCategoryValue(category cat) const
{
	switch (cat)
	{
	case category::Appartenance:
		return _appartenance.getStringValue();
	case category::Architecture:
		return _architecture.getStringValue();
	case category::CouleurPrise:
		return _colorPrise.getStringValue();
	case category::Ip:
		return _ip.getStringValue();
	case category::Local:
		return _local.getStringValue();
	case category::Nom:
		return _name.getStringValue();
	case category::NoPlaque:
		return _noPlaque.getStringValue();
	case category::NoPrise:
		return _noPrise.getStringValue();
	case category::NoSerie:
		return _noSerie.getStringValue();
	case category::Os:
		return _os.getStringValue();
	case category::Port:
		return _port.getStringValue();
	case category::Responsable:
		return _responsable.getStringValue();
	case category::Switch:
		return _switch.getStringValue();
	case category::Type:
		return _type.getStringValue();
	case category::VendeurId:
		return _sellerId.getStringValue();
	default:
		cerr << __FUNCTION__ << ": Undefined Category Name" << endl;
	}
	return "";
}

// Renvoie l'entier de la catégorie demandée
int Equipment::getCategoryIntValue(category cat) const
{
	switch (cat)
	{
	case category::Appartenance:
		return _appartenance.getIntValue();
	case category::Architecture:
		return _architecture.getIntValue();
	case category::CouleurPrise:
		return _colorPrise.getIntValue();
	case category::Ip:
		return _ip.getIntValue();
	case category::Local:
		return _local.getIntValue();
	case category::Nom:
		return _name.getIntValue();
	case category::NoPlaque:
		return _noPlaque.getIntValue();
	case category::NoPrise:
		return _noPrise.getIntValue();
	case category::NoSerie:
		return _noSerie.getIntValue();
	case category::Os:
		return _os.getIntValue();
	case category::Port:
		return _port.getIntValue();
	case category::Responsable:
		return _responsable.getIntValue();
	case category::Switch:
		return _switch.getIntValue();
	case category::Type:
		return _type.getIntValue();
	case category::VendeurId:
		return _sellerId.getIntValue();
	default:
		cerr << __FUNCTION__ << ": Undefined Category Name" << endl;
	}
	return -1;
}

// Renvoie le nom de la catégorie demandée
string Equipment::getCategoryFormat(category cat) const
{
	switch (cat)
	{
	case category::Appartenance:
		return _appartenance.getDataFormatRule();
	case category::Architecture:
		return _architecture.getDataFormatRule();
	case category::CouleurPrise:
		return _colorPrise.getDataFormatRule();
	case category::Ip:
		return _ip.getDataFormatRule();
	case category::Local:
		return _local.getDataFormatRule();
	case category::Nom:
		return _name.getDataFormatRule();
	case category::NoPlaque:
		return _noPlaque.getDataFormatRule();
	case category::NoPrise:
		return _noPrise.getDataFormatRule();
	case category::NoSerie:
		return _noSerie.getDataFormatRule();
	case category::Os:
		return _os.getDataFormatRule();
	case category::Port:
		return _port.getDataFormatRule();
	case category::Responsable:
		return _responsable.getDataFormatRule();
	case category::Switch:
		return _switch.getDataFormatRule();
	case category::Type:
		return _type.getDataFormatRule();
	case category::VendeurId:
		return _sellerId.getDataFormatRule();
	default:
		cerr << __FUNCTION__ << ": Undefined Category Name" << endl;
	}
	return "";
}


// Renvoie le nom de la catégorie demandée
void Equipment::setCategoryModified(category cat, bool state)
{
	switch (cat)
	{
	case category::Appartenance:
		_appartenance.setIsModified(state);
	case category::Architecture:
		_architecture.setIsModified(state);
	case category::CouleurPrise:
		_colorPrise.setIsModified(state);
	case category::Ip:
		_ip.setIsModified(state);
	case category::Local:
		_local.setIsModified(state);
	case category::Nom:
		_name.setIsModified(state);
	case category::NoPlaque:
		_noPlaque.setIsModified(state);
	case category::NoPrise:
		_noPrise.setIsModified(state);
	case category::NoSerie:
		_noSerie.setIsModified(state);
	case category::Os:
		_os.setIsModified(state);
	case category::Port:
		_port.setIsModified(state);
	case category::Responsable:
		_responsable.setIsModified(state);
	case category::Switch:
		_switch.setIsModified(state);
	case category::Type:
		_type.setIsModified(state);
	case category::VendeurId:
		_sellerId.setIsModified(state);
	default:
		cerr << __FUNCTION__ << ": Undefined Category Name" << endl;
	}
}


// Renvoie le nom de la catégorie demandée
bool Equipment::isCategoryModified(category cat) const
{
	switch (cat)
	{
	case category::Appartenance:
		return _appartenance.getIsModified();
	case category::Architecture:
		return _architecture.getIsModified();
	case category::CouleurPrise:
		return _colorPrise.getIsModified();
	case category::Ip:
		return _ip.getIsModified();
	case category::Local:
		return _local.getIsModified();
	case category::Nom:
		return _name.getIsModified();
	case category::NoPlaque:
		return _noPlaque.getIsModified();
	case category::NoPrise:
		return _noPrise.getIsModified();
	case category::NoSerie:
		return _noSerie.getIsModified();
	case category::Os:
		return _os.getIsModified();
	case category::Port:
		return _port.getIsModified();
	case category::Responsable:
		return _responsable.getIsModified();
	case category::Switch:
		return _switch.getIsModified();
	case category::Type:
		return _type.getIsModified();
	case category::VendeurId:
		return _sellerId.getIsModified();
	default:
		cerr << __FUNCTION__ << ": Undefined Category Name" << endl;
	}
	return false;
}

// On reset les catégories qualifiée de "modifiée"
void Equipment::resetIsModified()
{
    for(int i = 0 ; i < NB_CATEGORY ; ++i){
        setCategoryModified(static_cast<category>(i), false);
    }
}

// Renvoie si l'équipement est modifié
bool Equipment::isModified() const
{
    for(int i = 0 ; i < NB_CATEGORY ; ++i){
        if( isCategoryModified(static_cast<category>(i)) )
            return true;
    }
    return false;
}

// Renvoie la liste des formats disponibles
std::vector<std::string> Equipment::getCategoryFormatList(category cat) const
{
    switch (cat)
	{
	case category::CouleurPrise:
		return _colorPrise.getDataFormatList();
	case category::Type:
		return _type.getDataFormatList();
	default:
		cerr << __FUNCTION__ << ": Unauthorized Category Name" << endl;
	}
	return {};  // On renvoie un vecteur vide
}

// Renvoie l'index du format choisi
int Equipment::getCategoryFormatIndex(category cat ) const
{
    switch (cat)
	{
	case category::CouleurPrise:
		return _colorPrise.getDataFormatIndex();
	case category::Type:
		return _type.getDataFormatIndex();
	default:
		cerr << __FUNCTION__ << ": Unauthorized Category Name" << endl;
	}
	return 0;
}

// Détruit l'équipement
void Equipment::destroy() {
	_isDeleted = true;
}

// Mise en forme de l'affichage
string displayCool(const Categorie& cat) {
	int nbSpace = 30 - (cat.getTag().size() + cat.getStringValue().size());
	string s;
	s += string("    - ");
	s += cat.getTag() + " : ";
	s += string(nbSpace, ' ');
	s += cat.getStringValue();
	s += "\n";

	return s;
}

// On reconstruit la ligne complète
void Equipment::rebuildRawLine() {
	_rawLine = "";
	for (int i = 0; i < NB_CATEGORY; ++i) {
		_rawLine += getCategoryValue((category)i);
		if (i < NB_CATEGORY-1) {
			_rawLine += ";";
		}
	}
}

// Renvoie l'Id de l'équipement s'il correspond à la recherche
int Equipment::getRecherche(int cat, string search) const{
	
	// Si on est pas dans le Range des catégories, on cherche dans toutes les catégories
	if(cat >= NB_CATEGORY){
		vector<string> allCat;
		for(int i = 0 ; i < NB_CATEGORY ; ++i){
			allCat.push_back(getCategoryValue((category)i));
		}
		if(Tools::researchEngine(search, allCat)){
			return _id;
		}
	}
	// On cherche dans la catégorie spécifiée
	else{
		if(Tools::researchEngine(search, getCategoryValue((category)cat))){
			return _id;
		}
	}
	return 0;
}