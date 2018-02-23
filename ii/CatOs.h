#ifndef CATEGORIE_OS_H
#define CATEGORIE_OS_H

#include "Categorie.h"

class CatOs : public Categorie
{
public:
	CatOs();
	~CatOs();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;
};

#endif

