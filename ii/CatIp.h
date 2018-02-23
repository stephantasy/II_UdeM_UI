#ifndef CATEGORIE_IP_H
#define CATEGORIE_IP_H

#include "Categorie.h"

class CatIp : public Categorie
{
public:
	CatIp();
	~CatIp();	

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;
};

#endif

