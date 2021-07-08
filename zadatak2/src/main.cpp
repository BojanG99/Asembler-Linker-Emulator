#include<string>
#include<iostream>
#include<fstream>
#include"objektni_Fajl.h"
#include<unordered_map>
#include<vector>
#include<string.h>
#include"sekcija.hpp"
#include"tabela_Simbola.hpp"


using namespace std;
string getSection(string s) {
	int odIndex=0, doIndex = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '=')odIndex = i + 1;

		if (s[i] == '@') {
			doIndex = i -1;
			break;
		}
	}

	return s.substr(odIndex, doIndex - odIndex + 1);
}
unsigned short dohvatiPodatak(string s, vector<tabela_Simbola*>*tabeleSimbola, vector<vector<sekcija*>*>*svesekcije,int sek) {

	int i = 0;
	for (tabela_Simbola * tabela : *tabeleSimbola) {

		unordered_map<string, podaci_O_Simbolu*>*mapa = tabela->dohvati_Tabelu();
		for( auto const& pair: *mapa)


			if (pair.second->isLocal() == false && pair.second->isdefinisan() == true && s==pair.first) {
			
					std::cout << "Nasli smo simbol " <<s << std::endl;

					if (pair.second->getSekcija() == "APSOLUTAN")return pair.second->dohvati_Vrijednost();

					for (sekcija*sek : *(*svesekcije)[i]) {

						if (sek->dohvati_Naziv() == pair.second->getSekcija()) {

							return pair.second->dohvati_Vrijednost() + sek->dohvatiOffset();

						}
					}
				
				
			}
		i++;
	}
	//nije globalni znaci da je sekcija
	(*(*tabeleSimbola)[sek]);



		for (auto const& pair : *((*tabeleSimbola)[sek]->dohvati_Tabelu()))


			if ( s == pair.first) {

			
				if(pair.second->isLocal())

					for (sekcija*sek : *(*svesekcije)[sek]) {

						if (sek->dohvati_Naziv() == pair.second->getSekcija()) {

							return sek->dohvatiOffset();

						}
					}
				else {


					for (sekcija*sek : *(*svesekcije)[sek]) {

						if (sek->dohvati_Naziv() == pair.second->getSekcija()) {

							return pair.second->dohvati_Vrijednost() + sek->dohvatiOffset();

						}
					}

				}



			}

		cout << "Nije nadjen simbol "<<s;
		return -1;

}
string getOffset(string s) {
	int odIndex = 0, doIndex = 0;
	for (int i = 0; i < s.length(); i++)
	{
	

		if (s[i] == '@') {
			odIndex = i + 1;
			break;
		}
	}

	return s.substr(odIndex, s.length() - odIndex + 1);;
}

unsigned short toUS(string s) {
	short ret = 0;
	if (s.length() > 2 && s[1] == 'x') {

		for (int i = 2;i < s.length();i++) {
			if (s[i] - '0' < 10) {
				short tmp = s[i] - '0';
				ret |= (tmp << (s.length() - 1 - i) * 4);
			}
			else {

				short tmp = s[i] - 'A' + 10;
				ret |= (tmp << ((s.length() - 1 - i) * 4));
			}
		}
	}

	else
	{
		ret = atoi(s.c_str());
	}
	return (unsigned short)ret;
}
int main(int argc, char**argv) {
	string o = "-o";
	string place = "-place=";
	string nazivFajla;
	bool linkable = false, hex = false;
	
	unordered_map<string, string> mapa;
	vector<string> objektniFajlovi;
	for (int i = 1;i < argc;i++) {
		if (strcmp(o.c_str(), argv[i]) == 0) {
			if (nazivFajla != "") {
				cout<<"Vec je postavljen naziv fajla"<<endl;
				return 0;
			}
			nazivFajla = string(argv[i + 1]);i++;
		}
		else if (memcmp(place.c_str(), argv[i], 7 * sizeof(char)) == 0) {
			string placeoffset = argv[i];

			mapa[getSection(placeoffset)] = getOffset(placeoffset);
		}
		else if (strcmp("-linkable", argv[i]) == 0) {

			if (hex) {
				cout << "Vec je postavljen hex" << endl;
				return 0;
			}
			linkable = true;
		}
		else if (strcmp("-hex", argv[i]) == 0) {

			if (hex) {
				cout << "Vec je postavljen linkable" << endl;
				return 1;
			}
			hex = true;

		}
		else {
			objektniFajlovi.push_back(argv[i]);
			
		}

	}


	//ispis
	for (auto const &pair : mapa) {
		std::cout << "{" << pair.first << ": " << pair.second << "}\n";
	}
	if (hex)cout << "hex"<< nazivFajla << endl;

	if (linkable)cout << "linkable" << endl;

	for (string s : objektniFajlovi) {
		cout << s << endl;
	}
	////////////////////////

	//ucitavamo sve sekcije, tabele simbola i relokacione zapise;
	if (hex) {
		vector<vector<sekcija*>*>*svesekcije = new vector<vector<sekcija*>*>();
		vector<tabela_Simbola*>*tabeleSimbola = new vector<tabela_Simbola*>();
		for (string s : objektniFajlovi) {
			ifstream *inputFajl = new ifstream(s, ios::in | ios::binary);
			if (!inputFajl->is_open()) {
				cout << "Fajl: " << s << " ne postoji" << endl;
				system("pause");
			}
			objektni_Fajl::deserijalizuj(svesekcije, tabeleSimbola, inputFajl);


		}

		//provjera definisanosti
		unordered_map<string, int >definisani;
		//
		for (tabela_Simbola* tabela : *tabeleSimbola) {

			tabela->popuniMapu(&definisani);

		}

		for (auto const &pair : definisani) {
			if (pair.second != 1) {
				cout << "Simbol " << pair.first << " je vise puta definisan" << endl;
			}
		}
		int error = 0;
		for (tabela_Simbola* tabela : *tabeleSimbola) {

			error += tabela->procitajMapu(&definisani);

		}
		if (error > 0) {
			cout << "Visestruka definicija simbola" << endl;
			return 0;
		}


		//popraviti sve relokacione zapise

		//

	// objediniti sekcije
		unordered_map<string, vector<sekcija*>*> sekcijeObjedinjeno;

		for (vector<sekcija*>* sekcije : *svesekcije) {

			for (sekcija* sek : *sekcije) {

				if (sekcijeObjedinjeno[sek->dohvati_Naziv()] != nullptr) {
					sekcijeObjedinjeno[sek->dohvati_Naziv()]->push_back(sek);

				}
				else {
					sekcijeObjedinjeno[sek->dohvati_Naziv()] = new vector<sekcija*>();
					sekcijeObjedinjeno[sek->dohvati_Naziv()]->push_back(sek);
				}
			}

		}






		unsigned short minaddr = 0;;
		for (auto const &pair : mapa) {
			if (minaddr < (toUS(pair.second)))minaddr = toUS(pair.second);
			for (auto const &sek : sekcijeObjedinjeno) {
				if (sek.first == pair.first) {
					unsigned short pomjeraj = toUS(pair.second);
					for (sekcija *trenutnaSekcija : *(sek.second)) {
						trenutnaSekcija->postaviOffset(pomjeraj);
						pomjeraj += trenutnaSekcija->getSize();

					}
					if (minaddr < pomjeraj)minaddr = pomjeraj;
				}

			}

		}
		//provjera da li dolazi do overlapa

		////



		//ostale sekcije postavimo na adrese vece od maksimalne postavljene preko place parametra
		for (auto const &sek : sekcijeObjedinjeno) {

			for (sekcija*sekc : *(sek.second)) {


				if (sekc->postavljenoffset == false) {

					sekc->postaviOffset(minaddr);
					minaddr += sekc->getSize();

				}

			}


		}

		int i = 0;
		for (vector<sekcija*> *sekcije : *svesekcije) {

			for (sekcija* sek : *sekcije) {

				relokacioni_Zapisi* relzapisi = sek->dohvatiTabeluRZ();
				vector<podaci_O_Relokacionom_Zapisu*> *podaci = relzapisi->dohvatiZapise();

				for (podaci_O_Relokacionom_Zapisu * podatak : *podaci) {

					unsigned short prepravka = dohvatiPodatak(podatak->getSimbol(), tabeleSimbola, svesekcije, i);

					if (podatak->getTip() == R_386_32) {
						unsigned short prosli = sek->dohvatiPodatak(podatak->getOff());
						prosli += prepravka;
						sek->postaviPodatak(prosli, podatak->getOff());

					}
					else {
						unsigned short prosli = sek->dohvatiPodatak(podatak->getOff());
						prosli += prepravka;
						prosli -= podatak->getOff() + sek->dohvatiOffset();
						sek->postaviPodatak(prosli, podatak->getOff());


					}
				}
			}
			i++;
		}



		for (vector<sekcija*> *sekcije : *svesekcije) {

			for (sekcija* sek : *sekcije) {
				cout << *sek;
			}
		}
		ofstream *izlazniFajl = new ofstream();
		izlazniFajl->open(nazivFajla, ios::out | ios::binary);
		int k = 0;
		unsigned short start = 0;
		for (auto &tab : *tabeleSimbola) {

			unordered_map<string, podaci_O_Simbolu*>*mapa = tab->dohvati_Tabelu();
			for (auto const& pair : *mapa)


				if (pair.second->isdefinisan() == true && strcmp(pair.first.c_str(), "myStart") ){
					start += pair.second->dohvati_Vrijednost();
					for (sekcija* sek : *(*svesekcije)[k]) {
						if (strcmp(sek->dohvati_Naziv().c_str(), pair.second->getSekcija().c_str()) == 0) {
							start += sek->dohvatiOffset();
						}
					}
					break;
				}
			k++;
		}
		cout << "Pocetna je " << start<<endl;
		izlazniFajl->write((char*)(&start), sizeof(unsigned short));
		for (auto const &sek : sekcijeObjedinjeno) {
			unsigned short velicina = 0;
			short pocetak = (*(sek.second))[0]->dohvatiOffset();
			for (sekcija*sekc : *(sek.second)) {

				velicina += sekc->velicina();
			}

			cout << "VEL" << velicina;

			izlazniFajl->write(sek.first.c_str(), sek.first.length() + 1);
			izlazniFajl->write((char*)(&pocetak), sizeof(short));
			izlazniFajl->write((char*)(&velicina), sizeof(unsigned short));
			for (sekcija* sekc : *(sek.second)) {
				cout << *sekc << endl;
				sekc->popuniOfajl(izlazniFajl);
			}

		}

		izlazniFajl->flush();
		izlazniFajl->close();
	}
	else if (linkable) {





	vector<vector<sekcija*>*>*svesekcije = new vector<vector<sekcija*>*>();
	vector<tabela_Simbola*>*tabeleSimbola = new vector<tabela_Simbola*>();
	for (string s : objektniFajlovi) {
		ifstream *inputFajl = new ifstream(s, ios::in | ios::binary);
		if (!inputFajl->is_open()) {
			cout << "Fajl: " << s << " ne postoji" << endl;
			system("pause");
		}
		objektni_Fajl::deserijalizuj(svesekcije, tabeleSimbola, inputFajl);


	}

	//provjera definisanosti
	unordered_map<string, int >definisani;
	//
	for (tabela_Simbola* tabela : *tabeleSimbola) {

		tabela->popuniMapu(&definisani);

	}

	for (auto const &pair : definisani) {
		if (pair.second != 1) {
			cout << "Simbol " << pair.first << " je vise puta definisan" << endl;
		}
	}
	int error = 0;
	for (tabela_Simbola* tabela : *tabeleSimbola) {

		error += tabela->procitajMapu(&definisani);

	}
	if (error > 0) {
		cout << "Visestruka definicija simbola" << endl;
		return 0;
	}


	//popraviti sve relokacione zapise

	//

// objediniti sekcije
	unordered_map<string, sekcija*> sekcijeObjedinjeno;
	unordered_map<string,int> ofset;
	int j = 0;
	for (vector<sekcija*>* sekcije : *svesekcije) {

		for (sekcija* sek : *sekcije) {
			sek->postaviOffset(ofset[sek->dohvati_Naziv()]);
			


			if (sekcijeObjedinjeno[sek->dohvati_Naziv()] != nullptr) {
				sek->ispravi_RZ();
				sekcijeObjedinjeno[sek->dohvati_Naziv()]->spoji(sek);
			}
			else {
				
				sekcijeObjedinjeno[sek->dohvati_Naziv()]=sek;
			}
		
			

			//azuriraj relokacione zapise na osnovu sekcije
			
			//

			//spojiti 2 sekcije sa istim imenom
			
		}
		j++;
	}

	//spojiti tabelu simbola
	tabela_Simbola *tabsim = new tabela_Simbola();
	for (tabela_Simbola* ts : *tabeleSimbola) {

		for (auto & sim : *(ts->dohvati_Tabelu())) {
			if (sim.second->isdefinisan() == true && sim.second->isLocal() == false) {
				tabsim->ubaci_Simbol(sim.first,sim.second);
			}
		}

	}
	int k = 0;
	vector<sekcija*> sekSpojene;
	for (auto& sekObj : sekcijeObjedinjeno) {
		k++;
		tabsim->ubaci_Simbol(sekObj.first, new podaci_O_Simbolu(0, sekObj.first, true, k, true));
		sekSpojene.push_back(sekObj.second);
	}


	cout << *tabsim;




	objektni_Fajl *o = new objektni_Fajl(nazivFajla);
	o->serijalizuj(&sekSpojene, tabsim);
	delete(o);
	//o->serijalizuj()







}
	else {
	cout << "Nije postavljen tip izlaznog fajla" << endl;
}
//	system("pause");

}
