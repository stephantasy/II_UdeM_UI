#ifndef CATEGORIE_COLORPRISE_H
#define CATEGORIE_COLORPRISE_H

#include <map>
#include <vector>
#include "Categorie.h"

class CatColorPrise : public Categorie
{
public:

	enum choix {
		Jaune, Vert, Rose, Bleu
	};

	CatColorPrise();
	~CatColorPrise();	
        
    std::vector<std::string> getDataFormatList() const;
    int getDataFormatIndex() const;

	// Inherited via Categorie
	virtual bool isDataFormatOk(const std::string) const override;

private:
	static std::map<choix, std::string> _choixMap;

};

#endif

