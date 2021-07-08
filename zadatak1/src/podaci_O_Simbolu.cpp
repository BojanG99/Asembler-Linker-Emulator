#include"podaci_O_Simbolu.hpp"
#include<iostream>
#include<fstream>
podaci_O_Simbolu::podaci_O_Simbolu(short vrijednost, std::string sekcija, bool lokalan, short brojsekcije, bool definisan)
{
	this->lokalan = lokalan;
	this->sekcija = sekcija;
	this->vrijednost = vrijednost;
	this->brojsekcije = brojsekcije;
	this->definisan = definisan;
}

podaci_O_Simbolu::~podaci_O_Simbolu()
{
}

void podaci_O_Simbolu::popuniOfajl(std::ofstream *izlaz) {

	izlaz->write((char*)(&lokalan),sizeof(bool));
	izlaz->write((char*)(sekcija.c_str()),sekcija.length()+1 );
	izlaz->write((char*)(&vrijednost),sizeof(short) );
	izlaz->write((char*)(&brojsekcije), sizeof(short));
	izlaz->write((char*)(&definisan),sizeof(bool));
	
	
}
