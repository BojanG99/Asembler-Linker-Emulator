#include"slozeni_Operand.hpp"

slozeni_Operand::slozeni_Operand(nacinAdresiranja nadr, std::string data1, std::string data2)
{

	this->nAdresiranja = nadr;
	this->podatak = data1;
	this->podatak2 = data2;
}

slozeni_Operand::~slozeni_Operand()
{
}
