#include"relokacioni_Zapisi.hpp"
#include<iostream>
#include"podaci_O_Relokacionom_Zapisu.hpp"
#include<fstream>
relokacioni_Zapisi::relokacioni_Zapisi(/* args */)
{
	zapisi = new std::vector<podaci_O_Relokacionom_Zapisu *>(0);
}

relokacioni_Zapisi::~relokacioni_Zapisi()
{
}
void relokacioni_Zapisi::ubaciZapis( podaci_O_Relokacionom_Zapisu* pRel) {
	zapisi->push_back(pRel);
}

std::ostream& operator<<(std::ostream& os, const relokacioni_Zapisi& dt)
{


	for (podaci_O_Relokacionom_Zapisu* podatak : *(dt.zapisi)) {

		std::cout << *podatak << std::endl;
	}

	return os;
}

int relokacioni_Zapisi::velicina() {

	int size = 0;
	for (podaci_O_Relokacionom_Zapisu *pod : *zapisi) {

		size += pod->velicina();
	}
	return size;
}
void relokacioni_Zapisi::popuniOfajl(std::ofstream*izlaz) {
	
	unsigned short size = zapisi->size();
	izlaz->write((char*)(&size), sizeof(unsigned short));
	for (podaci_O_Relokacionom_Zapisu* pod : *zapisi) {
		
		pod->popuniOfajl(izlaz);
	}
}