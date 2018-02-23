#ifndef CATEGORIE_LOCAL_H
#define CATEGORIE_LOCAL_H

#include "Categorie.h"

class CatLocal : public Categorie
{
public:
	CatLocal();
	~CatLocal();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string)  const override;
};

#endif

