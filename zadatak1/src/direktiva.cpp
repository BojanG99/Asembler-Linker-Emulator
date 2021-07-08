#include"direktiva.hpp"
#include"operand.hpp"
#include"literal.hpp"
#include"sekcija.hpp"
#include"tabela_Simbola.hpp"
#include"podaci_O_Relokacionom_Zapisu.hpp"
#include"podaci_O_Simbolu.hpp"
#include"relokacioni_Zapisi.hpp"
#include<string>;
asemblerskaDirektiva::asemblerskaDirektiva(direktiva dire)
{
	velicina = 0;
	dir = dire;
	

}
void asemblerskaDirektiva::dodaj_Argumente(std::string s) {
	lista_Argumenata.push_back(s);
}

asemblerskaDirektiva::~asemblerskaDirektiva()
{
}
void asemblerskaDirektiva::postavi_Velicinu() {

	if (dir == WORD) {
		velicina = 2 * lista_Argumenata.size();
	}

	if (dir == SKIP) {
		velicina = 0;// atoi(lista_Argumenata[0].c_str());
		for (int i = 0; i < lista_Argumenata.size(); i++)
		{
			velicina += literal::pretvori(lista_Argumenata[i]);
		}
	}
}
std::string asemblerskaDirektiva::dohvati_Argument(int id) {

	return lista_Argumenata[id];
}

int asemblerskaDirektiva::popuniMemoriju(tabela_Simbola*tabela_Smb, sekcija* trenutnaSekcija, std::vector<sekcija*>*sekcije) { 
	
	switch (dir)
	{
	case EQU:
	case END:
	case SECTION:
		break;
	case SKIP:
		for (int i = 0;i < velicina;i++) {
			trenutnaSekcija->popuni(0);
	}
		break;
	case WORD:
		for (std::string str : lista_Argumenata) {
			short data = 0;
			if (literal::is_Literal(str)) {
				data=literal::pretvori(str);
			}
			else {
			podaci_O_Simbolu* pod = tabela_Smb->dohvati_Simbol(str);
			string simb;
			if (pod == nullptr)return-1;
			if (pod->sekcija != "APSOLUTAN") {
				
				if (pod->lokalan) {
					simb = pod->sekcija;
					data = pod->dohvati_Vrijednost();
				}
				else {
					simb = str;
					data = 0;
				}

				podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutnaSekcija->getOffset(), simb);
				trenutnaSekcija->dohvatiTabeluRZ()->ubaciZapis(relpod);
			
			}
			else {
				data = pod->dohvati_Vrijednost();

			}

			}

			char dataL = data & 0x00FF;
			char dataH = (data >> 8);
			
			trenutnaSekcija->popuni(dataH);
			trenutnaSekcija->popuni(dataL);
		}
		break;
	case EXTERN:
		break;
	case GLOBAL:
		for (int i = 0;i < lista_Argumenata.size();i++) {
			if (tabela_Smb->dohvati_Simbol(lista_Argumenata[i]) == nullptr)return -1;

			podaci_O_Simbolu* podatak = tabela_Smb->dohvati_Simbol(lista_Argumenata[i]);
			podatak->lokalan = false;
		
		}
		//updatuje tabelu simbola
		break;
	default:
		break;
	}
	
	
	return 1; }
