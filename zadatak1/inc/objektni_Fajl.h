#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"sekcija.hpp"
#include"podaci_O_Simbolu.hpp"
#include"podaci_O_Relokacionom_Zapisu.hpp"
#include"relokacioni_Zapisi.hpp"
#include"tabela_Simbola.hpp"
class objektni_Fajl
{
private:
	ofstream *izlazniFajl;
public:
	objektni_Fajl(string imeFajla);
	void serijalizuj(std::vector<sekcija*>*sekcije, tabela_Simbola*tabelaSimboa);
	~objektni_Fajl();
};

