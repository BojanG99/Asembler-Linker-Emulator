#include"sekcija.hpp"
#include"relokacioni_Zapisi.hpp"
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
    pozicija=0;
	
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


	os << dt.ime << " : " << dt.vel << std::endl;

	return os;
}

void sekcija::popuniOfajl(std::ofstream *izlaz) {

	izlaz->write(ime.c_str(), ime.length() + 1);

	(*izlaz).write((char*)(&pozicija), sizeof(unsigned short));

	for (int i = 0; i < pozicija; i++)
	{
		(*izlaz) << niz[i];
	}
}