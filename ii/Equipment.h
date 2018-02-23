#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "CatLocal.h"
#include "CatName.h"
#include "CatNoPlaque.h"
#include "CatNoPrise.h"
#include "CatColorPrise.h"
#include "CatSwitch.h"
#include "CatPort.h"
#include "CatAppartenance.h"
#include "CatArchitecture.h"
#include "CatOs.h"
#include "CatType.h"
#include "CatResponsable.h"
#include "CatIdSeller.h"
#include "CatNoSerie.h"
#include "CatIp.h"

class Equipment
{
	
public:

	static const int NB_CATEGORY = 15;	// Nombre de catégories
	
	// Liste des catégories
	enum category {
		Local = 0,
		Nom,
		NoPlaque,
		NoPrise,
		CouleurPrise,
		Switch,
		Port,
		Appartenance,
		Architecture,
		Os,
		Type,
		Responsable,
		VendeurId,
		NoSerie,
		Ip
	};

	Equipment();
	~Equipment();

	void display() const;
	void destroy();

	int setEquipment(const std::string& EquipmentLine);
	bool setCategoryValue(category, std::string);
    void setCategoryModified(category, bool);
    void resetIsModified();    
	bool isDeleted() const { return _isDeleted; };
	bool isModified() const;
	std::string getRawEquipment() const { return _rawLine; };
    bool isValidCategoryFormat(category, std::string) const; 

	std::string getCategoryName(category) const;
	std::string getCategoryDesc(category) const;    
	std::string getCategoryValue(category) const;
	int getCategoryIntValue(category) const;
	std::string getCategoryFormat(category) const;
    std::vector<std::string> getCategoryFormatList(category) const;
    int getCategoryFormatIndex(category) const;
	int getRecherche(int, std::string) const;
    int getId() const { return _id; }
    bool isCategoryModified(category) const;
    
	friend std::ostream& operator<<(std::ostream&, const Equipment&);    

private:	

	static int _equipmentNumber;			// Nombre d'équipement créé

	int _initializationResult = 0;			// Résultat de l'initialisation d'un équipement		
	int _id = -1;							// Numéro de l'équipement
	std::string _rawLine = "";				// On mémorise la ligne
    bool _isDeleted = false;				// Si l'équipement a été supprimé

	// 15 Catégories
	CatLocal _local;
	CatName _name;
	CatNoPlaque _noPlaque = CatNoPlaque(_local);
	CatNoPrise _noPrise;
	CatColorPrise _colorPrise;
	CatSwitch _switch;
	CatPort _port;
	CatAppartenance _appartenance;
	CatArchitecture _architecture;
	CatOs _os;
	CatType _type;
	CatResponsable _responsable;
	CatIdSeller _sellerId;
	CatNoSerie _noSerie;
	CatIp _ip;

	void rebuildRawLine();
};



#endif
