#pragma once
#include<string>
#include"instrukcija.hpp"

class operand
{
protected:
 
  nacinAdresiranja nAdresiranja;
  std::string podatak;
public:
    operand();
    ~operand();
	std::string dohvatiOperand() { return podatak; }
	nacinAdresiranja dohvatiNacinA() { return nAdresiranja; }
	virtual int dohvati_ID() = 0;
};

