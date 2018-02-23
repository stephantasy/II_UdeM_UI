#ifndef CATEGORIE_H
#define CATEGORIE_H

#include <iostream>
#include <string>

class Categorie
{
public:

	Categorie();
	// Virtuel car c'est une classe de base qui sert à être instanciée
	// ET elle contient une méthode virtuelle
	virtual ~Categorie();

	std::string getStringValue() const;
	int getIntValue() const;
	std::string getDataFormatRule() const;
	bool setValue(std::string);
	std::string getTag() const { return _tag; }
    std::string getDesc() const { return _desc; }
    bool getIsModified() const { return _isModified; }
    void setIsModified(bool state) { _isModified = state; }
	
	virtual bool isDataFormatOk(const std::string) const = 0;

	friend std::ostream& operator<<(std::ostream&, const Categorie&);
	
protected:
	std::string _value = "";			// Valeur de la catégorie
	bool _isNameIntable = false;		// Le nom est aussi un Integer
	bool _isNameEmpty = false;			// Le nom est vide
	bool _isNameWellFormed = false;		// Le nom est au format attendu
	bool _isNameConstraint = false;		// Si le nom est restraint par une forme ou une liste
    bool _isModified = false;			// Si la catégorie a été modifiée
	std::string _formatRule = "";		// Format du nom (si applicable)
	std::string _tag = "";				// Tag de la catégorie
	std::string _desc = "";				// Description de la catégorie

};

#endif