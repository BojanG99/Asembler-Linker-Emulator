#include"drugi_Prolaz.hpp"
#include"relokacioni_Zapisi.hpp"
#include"naredbe_Podaci.hpp"
#include"naredbe_Skoka.hpp"
#include"linija.hpp"
#include"direktiva.hpp"

drugi_Prolaz::drugi_Prolaz( tabela_Simbola *tabela, std::vector<linija*> *linije, std::vector<sekcija*>*sekcije)
{
    this->tabela=tabela;
    this->linije=linije;
    this->sekcije=sekcije;
   
}

drugi_Prolaz::~drugi_Prolaz()
{
}

void drugi_Prolaz::prodji(){
	int i = -1;
	sekcija*sek = nullptr;
	for (linija* lin : *linije)
	{
		if (lin->dohvati_Naredbu() != nullptr) {
			naredbe *nar = lin->dohvati_Naredbu();
			if (nar->popuniMemoriju(tabela, sek, sekcije) != 1) {
				errcode = POSTOJINEDEFINISANSIMBOL;
				//greska nije definisan simbol
			}

		}
		else if (lin->dohvati_Direktivu() != nullptr)
		{
			if (lin->dohvati_Direktivu()->da_Li_Je_(SECTION)) {
				sek = (*sekcije)[++i];
			}
			else if (
				lin->dohvati_Direktivu()->popuniMemoriju(tabela, sek, sekcije) != 1) {

				//greska nije definisan simbol
				errcode = POSTOJINEDEFINISANSIMBOL;
			}
		}
    }
}
