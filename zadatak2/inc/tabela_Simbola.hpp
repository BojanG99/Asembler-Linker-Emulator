#pragma once
#include <unordered_map>
#include<iostream>
#include<fstream>
#include<iostream>

class podaci_O_Simbolu;
class tabela_Simbola
{
private:
    std::unordered_map<std::string, podaci_O_Simbolu*>*tabela;
public:
    tabela_Simbola(/* args */);
    ~tabela_Simbola();
    void ubaci_Simbol(std::string, podaci_O_Simbolu*);
    podaci_O_Simbolu* dohvati_Simbol(std::string);
	friend std::ostream& operator<<(std::ostream& os, const tabela_Simbola& dt);
	int velicina();
	friend class sekcija;
	void popuniOfajl(std::ofstream*);
	static tabela_Simbola* dohvatiIzFajla(std::ifstream*,int num);
	friend class objektni_Fajl;
	std::unordered_map<std::string, podaci_O_Simbolu*>* dohvati_Tabelu() {
		return tabela;
	}
	void popuniMapu(std::unordered_map<std::string, int>*mapa);
	int procitajMapu(std::unordered_map<std::string, int>*mapa);
};
