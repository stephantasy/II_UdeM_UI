#ifndef CATEGORIE_ARCHITECTURE_H
#define CATEGORIE_ARCHITECTURE_H

#include "Categorie.h"

class CatArchitecture : public Categorie
{
public:
	CatArchitecture();
	~CatArchitecture();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;
};

#endif

