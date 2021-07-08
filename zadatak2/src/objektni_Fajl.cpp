#include "objektni_Fajl.h"



objektni_Fajl::objektni_Fajl(string ime)
{
	izlazniFajl = new ofstream();
	izlazniFajl->open(ime, ios::out | ios::binary);
}
objektni_Fajl::objektni_Fajl()
{
	
}

objektni_Fajl::~objektni_Fajl()
{
	izlazniFajl->flush();
	izlazniFajl->close();
}

void objektni_Fajl::serijalizuj(std::vector<sekcija*>*sekcije, tabela_Simbola*tabelaSimboa) {

	short brojSekcija = sekcije->size();
	short brojSimbola = tabelaSimboa->tabela->size();
			
		izlazniFajl->write((char*)(&brojSekcija), sizeof(short));
		izlazniFajl->write((char*)(&brojSimbola), sizeof(short));
	
		tabelaSimboa->popuniOfajl(izlazniFajl);

		for (sekcija* sek : *sekcije)
		{
			sek->popuniOfajl(izlazniFajl);
		}
		for (sekcija* sek : *sekcije)
		{

			sek->dohvatiTabeluRZ()->popuniOfajl(izlazniFajl);

		}


}


void objektni_Fajl::deserijalizuj(std::vector<std::vector<sekcija*>*>*svesekcije, std::vector<tabela_Simbola*>*tabeleSimbola,std::ifstream *ulaz) {
	short brojSekcija ;
	short brojSimbola ;

	ulaz->read((char*)(&brojSekcija), sizeof(short));
	ulaz->read((char*)(&brojSimbola), sizeof(short));

	tabeleSimbola->push_back(tabela_Simbola::dohvatiIzFajla(ulaz,brojSimbola));
	std::vector<sekcija*>*sekcije = new std::vector<sekcija*>();
	for (int i = 0;i < brojSekcija;i++) {

		sekcije->push_back(sekcija::ucitajSekciju(ulaz));
	}

	for (int i = 0;i < brojSekcija;i++) {

		(*sekcije)[i]->postavi_Tabelu_Rel_Zapisa(relokacioni_Zapisi::ucitajrelZapise(ulaz));
	}
	svesekcije->push_back(sekcije);
}