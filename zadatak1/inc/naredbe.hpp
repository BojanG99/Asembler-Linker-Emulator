#pragma once

#include"instrukcija.hpp"
#include<vector>
class operand;
class tabela_Simbola;
class sekcija;
class naredbe
{
protected:
    mnemonik  mnem;
    operand *prvi_Operand;
    short velicina;
public:
    naredbe();
    ~naredbe();
    virtual int dohvati_ID()=0;
	virtual int dohvati_Veliciniu() = 0;
	virtual int popuniMemoriju(tabela_Simbola*tabela_Simbola, sekcija*, std::vector<sekcija*>*sekcije) = 0;

};


