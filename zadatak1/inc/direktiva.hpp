#include<vector>
#include<string>
class sekcija;
typedef enum{GLOBAL=1,EXTERN=2,SECTION=3,WORD=4,SKIP=5,EQU=6,END=7} direktiva;
class tabela_Simbola;
class operand;
class asemblerskaDirektiva
{
private:
    direktiva dir;
    std::vector<std::string> lista_Argumenata;
    short velicina;
public:
    asemblerskaDirektiva(direktiva dire);
    ~asemblerskaDirektiva();
    short dohvati_Velicinu(){return velicina;}
	bool da_Li_Je_Sekcija() {
		return dir == SECTION;
	}
	int dohvati_Broj_Elemenata() {
		return lista_Argumenata.size();
	}
	void dodaj_Argumente(std::string s);
	void postavi_Velicinu();
	std::string dohvati_Argument(int);
	bool da_Li_Je_Kraj() {
		return dir == END;
	}
	bool da_Li_Je_(direktiva d){
		return d== dir;
	}
	int popuniMemoriju(tabela_Simbola*tabela_Simbola, sekcija*, std::vector<sekcija*>*sekcije) ;
};

