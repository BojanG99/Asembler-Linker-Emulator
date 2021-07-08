


#include"naredbe.hpp"


class naredbe_Skoka : public naredbe
{
private:
 
public:
    naredbe_Skoka(mnemonik mnem, operand* oper);
    ~naredbe_Skoka();
    int dohvati_ID(){return 2;}
	int dohvati_Veliciniu();
	int popuniMemoriju(tabela_Simbola*tabela_Simbola, sekcija*, std::vector<sekcija*>*sekcije);
};

