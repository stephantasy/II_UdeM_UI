#ifndef CATEGORIE_PORT_H
#define CATEGORIE_PORT_H

#include "Categorie.h"

class CatPort : public Categorie
{
public:
	CatPort();
	~CatPort();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;
};

#endif

