#ifndef CATEGORIE_IDSELLER_H
#define CATEGORIE_IDSELLER_H

#include "Categorie.h"

class CatIdSeller : public Categorie
{
public:
	CatIdSeller();
	~CatIdSeller();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;
};

#endif

