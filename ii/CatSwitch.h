#ifndef CATEGORIE_SWITCH_H
#define CATEGORIE_SWITCH_H

#include "Categorie.h"

class CatSwitch : public Categorie
{
public:
	CatSwitch();
	~CatSwitch();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;
};

#endif

