#include<string>
#include<fstream>
class podaci_O_Simbolu
{
private:
   short vrijednost;
   std::string sekcija;
   bool lokalan;
   short brojsekcije;
   bool definisan;
public:
    podaci_O_Simbolu(short vrijednost,std::string sekcija,bool lokalan , short brojsekcije,bool definisan);
	podaci_O_Simbolu();
    ~podaci_O_Simbolu();
	short dohvati_Vrijednost() { return vrijednost; }
	bool isLocal() { return lokalan;}
	bool isdefinisan() { return definisan; }
	void postavi_Vrijednost(short s) {
		vrijednost = s;
	}
	std::string getSekcija() {
		return sekcija;
	}
	int velicina() {
		int size = 0;
		size += sizeof(short) + sizeof(bool) + sizeof(int) + sizeof(short) + sizeof(bool) + this->sekcija.length()+1;
		return size;
	}
	void popuniOfajl(std::ofstream *izlaz);
	void ucitajIzFajla(std::ifstream*);
	static podaci_O_Simbolu* dohvatiIzFajla(std::ifstream*);
	friend class asemblerskaDirektiva;
	friend class naredbe_Skoka;
	friend class naredbe_Podaci;
};
