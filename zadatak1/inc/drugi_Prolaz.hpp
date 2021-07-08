#include"prolaz.hpp"

class drugi_Prolaz : public prolaz
{
private:
   std::vector<linija*> *linije;
   std::vector<sekcija*>*sekcije;
     tabela_Simbola *tabela;
 
     int errcode=0;
public:
    drugi_Prolaz( tabela_Simbola *tabela, std::vector<linija*> *linije, std::vector<sekcija*>*sekcije);
    ~drugi_Prolaz();
	std::vector<sekcija*>* dohvatiSekcije() {
		return sekcije;
	}
    void prodji();
	int getErr() {
		return errcode;
	}
};

