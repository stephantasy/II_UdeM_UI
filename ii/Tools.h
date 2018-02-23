#pragma once

#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <regex>

namespace Tools
{
    // Return whether all element are digit in a string
    inline bool isAllDigits(const std::string &str)
    {
        return all_of(str.begin(), str.end(), ::isdigit); // C++11
    }

    // Split a string in a vector with a specific delimiter
    template<typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (getline(ss, item, delim)) {
            *(result++) = item;
        }
        // Si on a tous les éléments sauf le dernier (qui est vide), alors il est ignoré et on retourne un élément de moins
        // Donc, si le dernier élément est vide, on ajoute 1
        if(item.empty()){
            *(result++) = item;
        }
    }

    // Renvoie une chaine de catactères en majuscule (http://en.cppreference.com/w/cpp/string/byte/toupper)
    inline std::string str_toupper(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),
            // static_cast<int(*)(int)>(toupper)         // wrong
            // [](int c){ return toupper(c); }           // wrong
            // [](char c){ return toupper(c); }          // wrong
            [](unsigned char c) { return std::toupper(c); } // correct
        );
        return s;
    }

    // Convertie une string en RegEx
    inline std::regex getRegEx(std::string s){
        // On remplace simplement les * par de ".+" et on ne tient pas compte de la casse
        std::string f("*"), r(".+");	
        for (std::string::size_type i = 0; (i = s.find(f, i)) != std::string::npos;)
        {
            s.replace(i, f.length(), r);
            i += r.length();
        }	
        std::regex res(s, std::regex_constants::icase);
        return res;
    }

    // On utilise une RegEx trouver une string dans une autre
    // Renvoie si la recherche est positive
    inline bool searchRegEx(const std::string& s1, const std::regex& myregex) {
        return std::regex_search(s1, myregex);
    }

    // On utilise une RegEx pour rechercher une string dans une autre (match exact)
    // Renvoie si la recherche est positive
    inline bool searchRegExExact(const std::string& s1, const std::regex& myregex) {
        return std::regex_match(s1, myregex);
    }

    // Renvoie si la 1ere string est dans la deuxième
    inline bool researchEngine(const std::string& s1, const std::string& s2) {
        return searchRegExExact(s2, getRegEx(s1));
    }

    // Renvoie si la 1ere string est dans le vecteur
    inline bool researchEngine(const std::string& s1, const std::vector<std::string>& s2) {
        for (const auto& v : s2) {
            // Une seule correspondance suffit
            if (searchRegExExact(v, getRegEx(s1))) return true;
        }
        return false;
    }

    // Renvoie si la Regex correspond à la 1ère std::string
    inline bool matchRegex(const std::string& s1, const std::string& sreg) {
        std::regex reg(sreg);
        return std::regex_match(s1, reg);
    }

    // Suppression des espaces avant et après la chaine de caractères
    // Provient de https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
    // trim au début
    inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {
            return !std::isspace(c);
        }));
    }
    // trim à la fin
    inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {
            return !std::isspace(c);
        }).base(), s.end());
    }
    // trim des 2 côtés de la String
    inline std::string& trim(std::string &s) {
        ltrim(s);
        rtrim(s);
        return s;
    }
}