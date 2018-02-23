#ifndef CATEGORIE_NOPLAQUE_H
#define CATEGORIE_NOPLAQUE_H

#include "Categorie.h"
#include "CatLocal.h"
#include "Tools.h"
#include <memory>

class CatNoPlaque : public Categorie
{
public:
	CatNoPlaque(CatLocal&);
	~CatNoPlaque();

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string)  const override;

private:
	// On prend une référence du local afin d'en avoir le numéro
	CatLocal& _local;
};

#endif


