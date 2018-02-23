#include <sstream>
#include <iterator>
#include <map>
#include "Inventory.h"
#include "Tools.h"

using namespace std;

const int INIT_SIZE = 10000;

// Constructor
Inventory::Inventory()
{
	// On réserve la place en mémoire pour le nombre maximum de salles prévues
	m_equipmentList.reserve(INIT_SIZE);
}

// Destructor
Inventory::~Inventory()
{
}

// Enregistrement des équipements fournis par le fichier d'entrée
void Inventory::addEquipment(const string& EquipmentLine)
{
	// On contrôle que la ligne ne soit pas vide
	if (EquipmentLine.empty()) return;

	// On crée un équipement avec un pointeur pour en garder la référence 
	unique_ptr<Equipment> equipment(new Equipment);
	int result = equipment->setEquipment(EquipmentLine);

	// Equipement corrompu
	if (result < 0) {
		// On ne le mémorise pas
	}
	// Equipement OK
	else
	{
        // On mémorise notre inventaire
        m_equipmentList.push_back(move(equipment));
        m_nbEquipmentOk++;
	}
}


// On renvoie les équipement au format du fichier de sortie
void Inventory::exportToFile(ostream& is) const
{
	for (auto& it : m_equipmentList) {
		// On met l'équipement dans le fichier de sortie
        is << it->getRawEquipment() << endl;
	}
}

// Affichage du tableau croisé
string Inventory::displayMatrix() const
{
    string result;
	const int nbCharApp = 32;	// Nb espace pour appartenances
	const int nbCharNo = 5;		// Nb espace pour les nombres
	int rowSum = 0;				// Somme des lignes
	int colSum[7] = { 0 };		// Somme des colonnes
	int nbSpace = 0;			// Nombre d'espaces
	int nbHyphen = nbCharApp + 7 * nbCharNo + 8 * 3 + 5 + 3;	// Nb tirets par ligne de séparation

	// ***** On crée d'abord la matrice *****

    // Map de Type par défaut et son itérateur
	map<string, int> typ = {
		{ CatType::getChoixName(CatType::choix::Cluster), 0 },
		{ CatType::getChoixName(CatType::choix::Station_accueil), 0 },
		{ CatType::getChoixName(CatType::choix::Imprimante), 0 },
		{ CatType::getChoixName(CatType::choix::Laptop), 0 },
		{ CatType::getChoixName(CatType::choix::Routeur), 0 },
		{ CatType::getChoixName(CatType::choix::Serveur), 0 },
		{ CatType::getChoixName(CatType::choix::Station), 0 },
	};
	map<string, int>::iterator it_typ;

	// Map des apparences/type et son itérateur
	map<string, map<string, int>> pivotTable;
	map<string, map<string, int>>::iterator it_app;

	// On parcourt les équipements (par référence pour ne pas créer de copie de "e" !)
	for (auto& it : m_equipmentList) {
        if(!it->isDeleted()){
            // Est-ce que l'appartenance est déjà dans la Map ?
            it_app = pivotTable.find(it->getCategoryValue(Equipment::category::Appartenance));

            // Nouvelle appartenance et Type par défaut
            if (it_app == pivotTable.end()) {
                pivotTable[it->getCategoryValue(Equipment::category::Appartenance)] = typ;

                // On replace l'itérateur au bon endroit
                it_app = pivotTable.find(it->getCategoryValue(Equipment::category::Appartenance));
            }

            // On incrémente le Type (s'il existe !)
            map<string, int> *actualType = &(it_app->second);
            it_typ = actualType->find(it->getCategoryValue(Equipment::category::Type));
            if (it_typ != actualType->end()) {
                (*actualType)[it->getCategoryValue(Equipment::category::Type)] = it_typ->second + 1;
            }
        }
	}

    // ***** On construit la matrice avec les éléments récupérés *****

	// Légende
	string clu("Clu"), s_a("S_A"), imp("Imp"), lap("Lap"), rou("Rou"), ser("Ser"), sta("Sta");

	result += ("\nLégende :\n");
	result += ("---------\n\n");
	result += (clu + " = " + CatType::getChoixName(CatType::choix::Cluster) + "\n");
	result += (imp + " = " + CatType::getChoixName(CatType::choix::Imprimante) + "\n");
	result += (lap + " = " + CatType::getChoixName(CatType::choix::Laptop) + "\n");
	result += (rou + " = " + CatType::getChoixName(CatType::choix::Routeur) + "\n");
	result += (ser + " = " + CatType::getChoixName(CatType::choix::Serveur) + "\n");
	result += (sta + " = " + CatType::getChoixName(CatType::choix::Station) + "\n");
	result += (s_a + " = " + CatType::getChoixName(CatType::choix::Station_accueil) + "\n\n");

	// Entête
	// " " | a | b | c | d | Total
    string title("APPARTENANCE / TYPE"); // Titre colonne / ligne qu'on centre
    nbSpace = (nbCharApp > title.size()) ? nbCharApp - title.size() : 0;
    int nbSpaceBefore = nbSpace / 2;
    int nbSpaceAfter = nbSpace - nbSpaceBefore;
	result += (string(nbHyphen, '-') + "\n");
	result += (string(nbSpaceBefore, ' ') + title + string(nbSpaceAfter, ' ') + string(" |  "));
	result += (clu + "  |  ");
	result += (imp + "  |  ");
	result += (lap + "  |  ");
	result += (rou + "  |  ");
	result += (ser + "  |  ");
	result += (sta + "  |  ");
	result += (s_a + "  |  ");
	result += ("Total" + string(" | "));
	result += ("\n");
	result += (string(nbHyphen, '-') + "\n");

	// Lignes
	// Nom | 0 | 0 | 0 | 0 | 0
	for (auto& pt : pivotTable) {
		// On compte les espaces a ajouter en s'assurant que ce soit positif
		nbSpace = (nbCharApp > pt.first.size()) ? nbCharApp - pt.first.size() : 0;
		// Appartenance
		result += (pt.first + string(nbSpace, ' ') + " | ");
		rowSum = 0;
		int cpt = 0;
		// Nombre d'équipement
		for (auto& pts : pt.second) {						
			// On compte les espaces a ajouter pour remplir la case		
			nbSpace = pts.second > 9999 ? 0 : pts.second > 999 ? 1 : pts.second > 99 ? 2 : pts.second > 9999 ? 3 : 4;
			//nbSpace = pts.second > 9 ? 1 : pts.second > 99 ? 0 : 2;			
			result += (string(nbSpace, ' ') + to_string(pts.second) + " | ");
			// On totalise les éléments de la ligne
			rowSum += pts.second;
			// On totalise les éléments de la colonne
			colSum[cpt++] += pts.second;
		}
		// Total de la ligne
		nbSpace = rowSum > 9999 ? 1 : rowSum > 999 ? 2 : rowSum > 99 ? 3 : rowSum > 9 ? 4 : 5;
		result += (string(nbSpace, ' ') + to_string(rowSum) + " | ");
		result += ("\n");
		result += (string(nbHyphen, '-') + "\n");
	}
	
	// Total
	// Total | 0 | 0 | 0 | 0 | 0 |	
	result += ("Total" + string(nbCharApp-5, ' ') + " | ");
	rowSum = 0;
	for (int t : colSum) {
		nbSpace = t > 9999 ? 0 : t > 999 ? 1 : t > 99 ? 2 : t > 9 ? 3 : 4;
		result += (string(nbSpace, ' ') + to_string(t) + " | ");
		rowSum += t;
	}
	// Total de la ligne
    nbSpace = rowSum > 9999 ? 1 : rowSum > 999 ? 2 : rowSum > 99 ? 3 : rowSum > 9 ? 4 : 5;
	result += (string(nbSpace, ' ') + to_string(rowSum) + " |\n");
	result += (string(nbHyphen, '-') + "\n");
    
    return result;
}


// On recherche la string passée en paramètre dans la liste des équipements passée en paramètre.
// Si elle est vide, on cherche dans tous les équipements.
vector<int> Inventory::getRechercheList(vector<int>& previouslist, int cat, string toSearch) const {
	vector<int> list;

	// Si c'est une 1ère recherche, on parcours tous les équipements
	if (previouslist.empty()) {
		for (auto& e : m_equipmentList) {
            if (!e->isDeleted()) {
                int res = e->getRecherche(cat, toSearch);
                if (res > 0) {
                    list.push_back(res);
                }
            }
		}
	}
	// Sinon, on cherche dans le résultat de la précédente recherche
	else {
		for (auto& e : previouslist) {
			int res = m_equipmentList[e-1]->getRecherche(cat, toSearch);
			if (res > 0) {
				list.push_back(res);
			}
		}
	}

	return list;
}

// Renvoie si un équipement a été modifié
bool Inventory::isAnyEquipmentModified() const{
    for(auto& e : m_equipmentList){
        if(e->isModified())
            return true;
    }
    return false;
}

// Supprime un équipement
void Inventory::destroyEquipment(int pos)
{
	m_equipmentList[pos]->destroy();
    m_nbEquipmentOk--;
}

