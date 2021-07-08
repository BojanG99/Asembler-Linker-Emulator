
#ifndef naredbe_podaci_h
#define naredbe_podaci_h


#include"naredbe.hpp"
#endif
class operand;

class naredbe_Podaci : public naredbe
{
private:
    operand* drugiOperand;
public:
	naredbe_Podaci(mnemonik mnem, operand* oper1=nullptr, operand* oper2 = nullptr);
    ~naredbe_Podaci();
	int dohvati_Veliciniu();
    int dohvati_ID(){return 1;}
	int popuniMemoriju(tabela_Simbola*tabela_Simbola, sekcija*, std::vector<sekcija*>*sekcije);
};

