#include"sekcija.hpp"
#include"relokacioni_Zapisi.hpp"
#include"podaci_O_Relokacionom_Zapisu.hpp"
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
sekcija::sekcija(std::string s)
{
    ime=s;
	tabela_Relokacionih_zapisa = new relokacioni_Zapisi();
	pozicija = 0;
}
void sekcija::postavi_velicinu(unsigned short vel){

	this->vel = vel;
    niz=(char*)malloc(vel*sizeof(char));
    pozicija=vel;
	
}
sekcija::~sekcija()
{
}
void sekcija::popuni(char c){
    niz[pozicija++]=c;
}

void sekcija::postavi_ID_Sekcije(short idsek) {
	
}


std::ostream& operator<<(std::ostream& os, const sekcija& dt)
{


	os << dt.ime << " : " << dt.vel <<":"<<dt.offset<< std::endl;

	return os;
}

void sekcija::popuniOfajl(std::ofstream *izlaz) {

//	(*izlaz).write((char*)(&pozicija), sizeof(unsigned short));

	for (int i = 0; i < pozicija; i++)
	{
		(*izlaz) << niz[i];
	}
}
void sekcija::ucitajizOfajla(std::ifstream*ulaz) {

	while (true) {
		char c;
		ulaz->read(&c, 1);
		if (c == '\0')break;
		ime += c;
	}

	(*ulaz).read((char*)(&pozicija), sizeof(unsigned short));
	postavi_velicinu(pozicija);
	for (int i = 0; i < vel; i++)
	{
	
		(ulaz)->read(niz+i,sizeof(char));
	}
}
sekcija* sekcija::ucitajSekciju(std::ifstream* ulaz) {
	sekcija *ret = new sekcija();

	ret->ucitajizOfajla(ulaz);

	return ret;
}

sekcija::sekcija() {
	tabela_Relokacionih_zapisa = new relokacioni_Zapisi();
	pozicija = 0;
	ime = "";
	postavljenoffset = false;
}

void sekcija::spoji(sekcija* sek) {

	sek->tabela_Relokacionih_zapisa->dohvatiZapise();

	int novaVel = vel + sek->vel;
	niz = (char*)realloc(niz, novaVel * sizeof(char));
	for (int i = vel;i < novaVel;i++) {
		niz[i] = sek->niz[i - vel];
	}

	for (podaci_O_Relokacionom_Zapisu *pod : *(sek->tabela_Relokacionih_zapisa->dohvatiZapise())) {
		tabela_Relokacionih_zapisa->ubaciZapis(pod);
	}
}

void sekcija::ispravi_RZ() {
	
	for (podaci_O_Relokacionom_Zapisu* pod : *(tabela_Relokacionih_zapisa->dohvatiZapise())) {
		if (strcmp(ime.c_str(), pod->simbol.c_str()) == 0) {
			short off = offset;
			off+=(niz[pod->ofset]<<8)|niz[pod->ofset + 1] ;
			niz[pod->ofset] = (off & 0xff00) >> 8;
			niz[pod->ofset+1] = (off & 0x00ff);
		}
	}

}
