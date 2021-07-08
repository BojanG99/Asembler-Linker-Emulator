#include "objektni_Fajl.h"



objektni_Fajl::objektni_Fajl(string ime)
{
	izlazniFajl = new ofstream();
	izlazniFajl->open(ime, ios::out | ios::binary);
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
