#pragma once
#include"operand.hpp"

class slozeni_Operand :public operand
{
private:
	std::string podatak2;
public:
	slozeni_Operand( nacinAdresiranja nadr, std::string data1, std::string data2);
    ~slozeni_Operand();
	std::string dohvati_prvi() {
		return podatak;
	}
	std::string dohvati_drugi() {
		return podatak2;
	}
	int dohvati_ID() { return 2; };
};

