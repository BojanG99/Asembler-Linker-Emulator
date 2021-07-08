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

	for (podaci_O_Relokacionom_Zapisu* pod : *zapisi) {
		unsigned short size = pod->velicina()&& 0x0000ffff;
		izlaz->write((char*)(&size), sizeof(unsigned short));
		pod->popuniOfajl(izlaz);
	}
}
void relokacioni_Zapisi::ucitajIzOfajla(std::ifstream*ulaz) {

	unsigned short num = 0;
	ulaz->read((char*)(&num), sizeof(unsigned short));

	for (int i = 0;i < num;i++) {
		podaci_O_Relokacionom_Zapisu*zapis = podaci_O_Relokacionom_Zapisu::ucitajPodORZ(ulaz);
		zapisi->push_back(zapis);

	}
	
}
relokacioni_Zapisi* relokacioni_Zapisi::ucitajrelZapise(std::ifstream* ulaz) {
	relokacioni_Zapisi* ret = new relokacioni_Zapisi();
	ret->ucitajIzOfajla(ulaz);

	return ret;

}