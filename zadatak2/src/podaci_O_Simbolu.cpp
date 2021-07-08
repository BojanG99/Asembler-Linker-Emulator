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
podaci_O_Simbolu::podaci_O_Simbolu() {

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
void podaci_O_Simbolu::ucitajIzFajla(std::ifstream* ulaz) {
	ulaz->read((char*)(&lokalan), sizeof(bool));
	std::string s = "";
	while (true) {
		char c;
		ulaz->read(&c, 1);
		if (c == '\0')break;
		s += c;
	}
	sekcija = s;
	ulaz->read((char*)(&vrijednost), sizeof(short));
	ulaz->read((char*)(&brojsekcije), sizeof(short));
	ulaz->read((char*)(&definisan), sizeof(bool));
}

podaci_O_Simbolu* podaci_O_Simbolu::dohvatiIzFajla(std::ifstream* ulaz) {
	podaci_O_Simbolu* ret = new podaci_O_Simbolu();
	ret->ucitajIzFajla(ulaz);

	return ret;

}