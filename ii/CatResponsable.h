#ifndef CATEGORIE_RESPONSABLE_H
#define CATEGORIE_RESPONSABLE_H

#include "Categorie.h"

class CatResponsable : public Categorie
{
public:
	CatResponsable();
	~CatResponsable();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;
};

#endif

