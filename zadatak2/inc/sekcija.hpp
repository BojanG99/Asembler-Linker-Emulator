#pragma once
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
class relokacioni_Zapisi;
class sekcija
{
private:
    unsigned short offset;
    std::string ime;
    unsigned short vel;
    char *niz;
    unsigned char pozicija;
	relokacioni_Zapisi *tabela_Relokacionih_zapisa;

public:
	bool postavljenoffset;
	string nazivSekcije() {
		return ime;
	}
    void postavi_velicinu(unsigned short);
	void postavi_ID_Sekcije(short);
	unsigned short getSize() {
		return vel;
	}
	char * dohvati_Niz() {
		return niz;
	}
	int velicina() {
		return vel;
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
	sekcija();
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
	void ucitajizOfajla(std::ifstream*);
	static sekcija* ucitajSekciju(std::ifstream*);
	void postavi_Tabelu_Rel_Zapisa(relokacioni_Zapisi *tabela_Relokacionih_zapisa) {
		this->tabela_Relokacionih_zapisa = tabela_Relokacionih_zapisa;
	}
	void postaviOffset(unsigned short offset) {
		this->offset = offset;
		postavljenoffset = true;
	}
	unsigned short dohvatiOffset() {
		return offset;
	}
	unsigned short dohvatiPodatak(unsigned short poz) {
		unsigned short ret = niz[poz] << 8;
		ret |= niz[poz+1 ];
		return ret;
	}
	void postaviPodatak(unsigned short podatak, unsigned short poz) {
		niz[poz] = (podatak & 0xff00) >> 8;
		niz[poz+1] = podatak & 0x00ff;
	}
	void spoji(sekcija*sek);
	void ispravi_RZ();
};

