#ifndef CATEGORIE_NOSERIE_H
#define CATEGORIE_NOSERIE_H

#include "Categorie.h"

class CatNoSerie : public Categorie
{
public:
	CatNoSerie();
	~CatNoSerie();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;
};

#endif

