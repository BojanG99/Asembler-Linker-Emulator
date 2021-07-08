#pragma once
#include"operand.hpp"
class jednostavni_Operand :public operand
{
public:
	jednostavni_Operand(nacinAdresiranja nadr,std::string);
	~jednostavni_Operand();
	int dohvati_ID() { return 1; };
};

