#ifndef CATEGORIE_NOPRISE_H
#define CATEGORIE_NOPRISE_H

#include "Categorie.h"

class CatNoPrise : public Categorie
{
public:
	CatNoPrise();
	~CatNoPrise();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;
};

#endif

