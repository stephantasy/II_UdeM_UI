#ifndef CATEGORIE_NAME_H
#define CATEGORIE_NAME_H

#include "Categorie.h"

class CatName : public Categorie
{
public:
	CatName();
	~CatName();

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string)  const override;
};

#endif

