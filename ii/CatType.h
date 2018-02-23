#ifndef CATEGORIE_TYPE_H
#define CATEGORIE_TYPE_H

#include <map>
#include <vector>
#include "Categorie.h"

class CatType : public Categorie
{
public:

	enum choix {
		Cluster, Station_accueil, Imprimante, Laptop, Routeur, Serveur, Station
	};

	static std::string getChoixName(choix);

	CatType();
	~CatType();	
        
    std::vector<std::string> getDataFormatList() const;
    int getDataFormatIndex() const;

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;

private:

	static std::map<choix, std::string> _choixMap;	// Pour l'enum

};

#endif

