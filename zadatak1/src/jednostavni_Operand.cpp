#include "jednostavni_Operand.h"
#include "instrukcija.hpp"


jednostavni_Operand::jednostavni_Operand(nacinAdresiranja nadr,std::string data)
{
	
	this->nAdresiranja = nadr;
	this->podatak = data;
}


jednostavni_Operand::~jednostavni_Operand()
{
}
