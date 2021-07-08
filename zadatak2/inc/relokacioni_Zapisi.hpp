#pragma once
#include <vector>
#include<fstream>
class podaci_O_Relokacionom_Zapisu;
class relokacioni_Zapisi
{
private:
    std::vector< podaci_O_Relokacionom_Zapisu*> *zapisi;
public:
    relokacioni_Zapisi(/* args */);
    ~relokacioni_Zapisi();
	int velicina();
    void ubaciZapis(podaci_O_Relokacionom_Zapisu*);
	void popuniOfajl(std::ofstream*);
	void ucitajIzOfajla(std::ifstream*);
	static relokacioni_Zapisi* ucitajrelZapise(std::ifstream*);
	friend std::ostream& operator<<(std::ostream& os, const relokacioni_Zapisi& dt);
	std::vector< podaci_O_Relokacionom_Zapisu*> * dohvatiZapise() {
		return zapisi;
	}

};

