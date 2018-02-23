#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include <memory>
#include "Equipment.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	void addEquipment(const std::string&);
	void exportToFile(std::ostream&) const;
	std::string displayMatrix() const;
	void destroyEquipment(int);
    
	bool setEquipmentValue(int equ, int cat, std::string val) { return m_equipmentList[equ]->setCategoryValue((Equipment::category)cat, val); };   // Supprime un équipement
    void setEquipmentCategoryModified(int equ, int cat, bool state) { m_equipmentList[equ]->setCategoryModified((Equipment::category)cat, state); };  // Affecte une valeur à la catégorie d'un équipement
    void resetEquipmentCategoryModified(int equ) { m_equipmentList[equ]->resetIsModified(); };
	
	int getNbEquipmentCategory() const { return Equipment::NB_CATEGORY;  }
	int getNbEquipment() const { return m_equipmentList.size(); };
	int getNbEquipmentOk() const { return m_nbEquipmentOk; };
	std::string getEquipmentCategory(int cat) const { return m_equipmentList[0]->getCategoryName((Equipment::category)cat); };
    std::string getEquipmentCategoryDesc(int cat) const { return m_equipmentList[0]->getCategoryDesc((Equipment::category)cat); };    
	std::string getEquipmentCategoryFormat(int cat) const { return m_equipmentList[0]->getCategoryFormat((Equipment::category)cat); };
	std::string getEquipmentCategoryValue(int equ, int cat) const { return m_equipmentList[equ]->getCategoryValue((Equipment::category)cat); };
    std::vector<std::string> getEquipmentCategoryFormatList(int cat) const { return m_equipmentList[0]->getCategoryFormatList((Equipment::category)cat); };
    int getEquipmentCategoryFormatIndex(int equ, int cat) const { return m_equipmentList[equ]->getCategoryFormatIndex((Equipment::category)cat); };      
    int getEquipmentId(int equ) const { return m_equipmentList[equ]->getId(); } 
	std::vector<int> getRechercheList(std::vector<int>&, int, std::string) const;
    
    bool isValidEquipmentValue(int equ, int cat, std::string s) const { return m_equipmentList[equ]->isValidCategoryFormat((Equipment::category)cat, s); };  
    bool isEquipmentModified(int equ) const { return m_equipmentList[equ]->isModified(); };
    bool isAnyEquipmentModified() const;
    bool isEquipmentDeleted(int equ) const { return m_equipmentList[equ]->isDeleted(); };

	friend std::ostream& operator<<(std::ostream&, const Inventory&);
    
private:
	std::vector<std::unique_ptr<Equipment>> m_equipmentList;		// Liste des équipements
	int m_nbEquipmentOk = 0;					                    // Nombre d'équipements Ok
};
#endif

