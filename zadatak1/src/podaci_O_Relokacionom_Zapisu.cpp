#include"podaci_O_Relokacionom_Zapisu.hpp"
#include<iostream>
#include<fstream>
#include<string>
podaci_O_Relokacionom_Zapisu::podaci_O_Relokacionom_Zapisu(tipRelZapisa trz, short offset, std::string simol)
{
	this->ofset = offset;
	this->trz = trz;
	this->simbol = simol;
}

podaci_O_Relokacionom_Zapisu::~podaci_O_Relokacionom_Zapisu()
{
}
std::ostream& operator<<(std::ostream& os, const podaci_O_Relokacionom_Zapisu& dt)
{



		std::cout << dt.simbol << "  -- "<< dt.ofset<<"  -- "<<dt.trz<<std::endl;
	

	return os;
}
void podaci_O_Relokacionom_Zapisu::popuniOfajl(std::ofstream* izlaz) {

	izlaz->write(simbol.c_str(), simbol.length() + 1);
	izlaz->write((char*)(&ofset), sizeof(short));
	izlaz->write((char*)(&trz), sizeof(tipRelZapisa));

}