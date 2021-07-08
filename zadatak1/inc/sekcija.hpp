#pragma once
#include<string>
#include<iostream>
using namespace std;
class relokacioni_Zapisi;
class sekcija
{
private:
    short offset;
    std::string ime;
    unsigned short vel;
    char *niz;
    unsigned char pozicija;
	relokacioni_Zapisi *tabela_Relokacionih_zapisa;
public:
	
    void postavi_velicinu(unsigned short);
	void postavi_ID_Sekcije(short);
	unsigned short getOffset() {
		return pozicija;
	}
	char * dohvati_Niz() {
		return niz;
	}
	int velicina() {
		return ime.length() + 1 + sizeof(short) + sizeof(unsigned short);
	}
	void ispisi_Niz() {
		for (int i = 0; i < vel; i++)
		{
			printf("%.2x ", (unsigned char)niz[i]);
			if ((i % 10) == 9) {
				std::cout << std::endl;
			}
		}
	}
    sekcija(std::string);
	std::string dohvati_Naziv() {
		return ime;
	}
    void popuni(char c);
	relokacioni_Zapisi* dohvatiTabeluRZ() {
		return tabela_Relokacionih_zapisa;
	}
    ~sekcija();
	friend std::ostream& operator<<(std::ostream& os, const sekcija& dt);
	void popuniOfajl(std::ofstream *);
};

