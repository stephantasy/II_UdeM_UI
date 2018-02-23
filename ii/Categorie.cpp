#include "Categorie.h"

using std::string;
using std::ostream;

Categorie::Categorie()
{
}

Categorie::~Categorie()
{
}

// Return the name
string Categorie::getStringValue() const
{
	return _value;
}

// Return the int format of the name
int Categorie::getIntValue() const
{
	if (!_isNameIntable) return -1;
	return stoi(_value);
}

// Format to respect
string Categorie::getDataFormatRule() const
{
	return _formatRule;
}


ostream& operator<<(ostream& os, const Categorie& i)
{
	os << i.getStringValue();
	return os;
}


bool Categorie::setValue(string s)
{
	// Init
	_isNameEmpty = false;

	// Si c'est vide
	if (s.empty()) {
		_isNameEmpty = true;
		return false;
	}

	// On controle s'il est bon
	_isNameWellFormed = isDataFormatOk(s);

	// On affecte le nom
	//if (_isNameWellFormed) { // On interdit pas un mauvais format, c'est le UI qui s'en charge
		_value = s;
	//}

	return _isNameWellFormed;
}