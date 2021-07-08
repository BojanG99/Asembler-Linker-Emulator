#include<unordered_map>
#include<fstream>
typedef enum tipRelZapisa { R_386_PC32, R_386_32 };
class podaci_O_Relokacionom_Zapisu
{
private:
    short ofset;
	tipRelZapisa trz;
    std::string simbol;
public:
    podaci_O_Relokacionom_Zapisu(tipRelZapisa trz, short offset, std::string simol);
	podaci_O_Relokacionom_Zapisu();
    ~podaci_O_Relokacionom_Zapisu();
	int velicina() {
		return sizeof(short) + sizeof(char) + simbol.length()+1;
	}
	friend std::ostream& operator<<(std::ostream& os, const podaci_O_Relokacionom_Zapisu& dt);
	friend class sekcija;
	void popuniOfajl(std::ofstream*);
	void ucitajIzOfajla(std::ifstream*);
	static podaci_O_Relokacionom_Zapisu* ucitajPodORZ(std::ifstream*);
	unsigned short getOff() {
		return ofset;
	}
	std::string getSimbol() {
		return simbol;
	}
	tipRelZapisa getTip() {
		return trz;
	}

};

