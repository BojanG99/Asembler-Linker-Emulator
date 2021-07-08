#include<unordered_map>
typedef enum tipRelZapisa { R_386_PC32, R_386_32 };
class podaci_O_Relokacionom_Zapisu
{
private:
    short ofset;
	tipRelZapisa trz;
    std::string simbol;
public:
    podaci_O_Relokacionom_Zapisu(tipRelZapisa trz, short offset, std::string simol);
    ~podaci_O_Relokacionom_Zapisu();
	int velicina() {
		return sizeof(short) + sizeof(tipRelZapisa) + simbol.length()+1;
	}
	friend std::ostream& operator<<(std::ostream& os, const podaci_O_Relokacionom_Zapisu& dt);
	void popuniOfajl(std::ofstream*);
};

