#include"prolaz.hpp"
class prvi_Prolaz :public prolaz
{
   
private:
     std::vector<linija*> *linije;
     std::vector<sekcija*> *sekcije;
     tabela_Simbola *tabela;
     int errcode=0;


public:
    prvi_Prolaz(std::vector<linija*>*lin);
    ~prvi_Prolaz();
    void prodji();
    int greska(){
        return errcode;
    }
	std::vector<sekcija*> * dohvati_Sekcije() {
		return sekcije;
	}
	tabela_Simbola * dohvati_Tabelu_Simbola() {
		return tabela;
	}
};

