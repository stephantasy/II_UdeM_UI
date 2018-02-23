#ifndef CATEGORIE_APPARTENANCE_H
#define CATEGORIE_APPARTENANCE_H

#include "Categorie.h"

class CatAppartenance : public Categorie
{
public:
	CatAppartenance();
	~CatAppartenance();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;
	
};

#endif

