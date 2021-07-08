#include"naredbe_Skoka.hpp"
#include"jednostavni_Operand.h"
#include"registar.hpp"
#include"slozeni_Operand.hpp"
#include"tabela_Simbola.hpp"
#include"podaci_O_Relokacionom_Zapisu.hpp"
#include"podaci_O_Simbolu.hpp"
#include"literal.hpp"
#include"sekcija.hpp"
#include"relokacioni_Zapisi.hpp"
naredbe_Skoka::naredbe_Skoka(mnemonik mnem, operand* oper)
{
	prvi_Operand = oper;
	this->mnem = mnem;
}

naredbe_Skoka::~naredbe_Skoka()
{
}
int naredbe_Skoka::dohvati_Veliciniu() {

	if (prvi_Operand->dohvatiNacinA() == REGDIR || prvi_Operand->dohvatiNacinA() == REGINDIR)
		return 3;

	return 5;
}

int naredbe_Skoka::popuniMemoriju(tabela_Simbola*tabela_Simbola, sekcija* trenutnaSek, std::vector<sekcija*>*sekcije) {

	nacinAdresiranja na = prvi_Operand->dohvatiNacinA();
	char descriptor = 0x50;
	char addrmode = 0;
	char pod = 0xF0;
	bool is5 = true;
	addrmode = 0;
	int dataH = 0, dataL = 0,dataHL;
	if (na == NEPOSREDNO) {
		addrmode = 0x00;
		if (literal::is_Literal(prvi_Operand->dohvatiOperand())) {
			dataHL = literal::pretvori(prvi_Operand->dohvatiOperand());

		}
		else {
			podaci_O_Simbolu* pod = tabela_Simbola->dohvati_Simbol(prvi_Operand->dohvatiOperand());
			string simb;
			if (pod == nullptr)return-1;
			if (pod->sekcija != "APSOLUTAN") {

				if (pod->lokalan) {
					simb = pod->sekcija;
					dataHL = pod->dohvati_Vrijednost();
				}
				else {
					simb = prvi_Operand->dohvatiOperand();
					dataHL = 0;
				}

				podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutnaSek->getOffset()+3, simb);
				trenutnaSek->dohvatiTabeluRZ()->ubaciZapis(relpod);

			}
			else {
				dataHL = pod->dohvati_Vrijednost();

			}

	/*		if (podaci == nullptr)return -1;
			if (podaci->isLocal()) {
				dataHL = podaci->dohvati_Vrijednost();

				podaci_O_Relokacionom_Zapisu *pod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutnaSek->getOffset(), podaci->getSekcija());



				trenutnaSek->dohvatiTabeluRZ()->ubaciZapis(pod);

			}
			else {
				dataHL = 0;
				podaci_O_Relokacionom_Zapisu *pod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutnaSek->getOffset(), prvi_Operand->dohvatiOperand());

				trenutnaSek->dohvatiTabeluRZ()->ubaciZapis(pod);
			}
			/*/
		}
		dataH = dataHL >> 8;
		dataL = dataHL & 0x00ff;
	
	}
	else if (na == REGDIR) {
		pod |= registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		addrmode = 0x01;
		is5 = false;

	}
	else if (na == REGINDIR) {
		pod |= registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		addrmode = 0x02;
		is5 = false;

	}
	else if (na == PCREL) {

		addrmode = 0x05;


		podaci_O_Simbolu* pod = tabela_Simbola->dohvati_Simbol(prvi_Operand->dohvatiOperand());
		string simb;
		if (pod == nullptr)return-1;
		if (pod->sekcija != "APSOLUTAN") {

			if (pod->lokalan) {
				simb = pod->sekcija;
				dataHL = pod->dohvati_Vrijednost();
			}
			else {
				simb = prvi_Operand->dohvatiOperand();
				dataHL = 0;
			}

			podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_PC32, trenutnaSek->getOffset() + 3, simb);
			trenutnaSek->dohvatiTabeluRZ()->ubaciZapis(relpod);

		}
		else {
			dataHL = pod->dohvati_Vrijednost();

		}

		dataH = dataHL >> 8;
		dataL = dataHL & 0x00ff;




	}
	else if (na == MEMORIJSKO) {
		addrmode = 0x04;
		
		if (literal::is_Literal(prvi_Operand->dohvatiOperand())) {
			dataHL = literal::pretvori(prvi_Operand->dohvatiOperand());
		}
		else {
			podaci_O_Simbolu* pod = tabela_Simbola->dohvati_Simbol(prvi_Operand->dohvatiOperand());
			string simb;
			if (pod == nullptr)return-1;
			if (pod->sekcija != "APSOLUTAN") {

				if (pod->lokalan) {
					simb = pod->sekcija;
					dataHL = pod->dohvati_Vrijednost();
				}
				else {
					simb = prvi_Operand->dohvatiOperand();
					dataHL = 0;
				}

				podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutnaSek->getOffset() + 3, simb);
				trenutnaSek->dohvatiTabeluRZ()->ubaciZapis(relpod);

			}
			else {
				dataHL = pod->dohvati_Vrijednost();

			}

		}

		dataH = dataHL >> 8;
		dataL = dataHL & 0x00ff;


	}

	else {
	//sa pomjerajem
			//dodatna 2 bajta
		addrmode = 0x03;
		slozeni_Operand *sloOper = (slozeni_Operand*)prvi_Operand;

		int regslozeni = registar::dohvatiRegistar(sloOper->dohvati_prvi());
		pod |= regslozeni;

		
		if (literal::is_Literal) {

			dataHL = literal::pretvori(sloOper->dohvati_drugi());
			dataH = dataHL >> 8;
			dataL = dataHL & 0x00FF;
		}
		else {
			podaci_O_Simbolu* pod = tabela_Simbola->dohvati_Simbol(prvi_Operand->dohvatiOperand());
			string simb;
			if (pod == nullptr)return-1;
			if (pod->sekcija != "APSOLUTAN") {

				if (pod->lokalan) {
					simb = pod->sekcija;
					dataHL = pod->dohvati_Vrijednost();
				}
				else {
					simb = prvi_Operand->dohvatiOperand();
					dataHL = 0;
				}

				podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutnaSek->getOffset() + 3, simb);
				trenutnaSek->dohvatiTabeluRZ()->ubaciZapis(relpod);

			}
			else {
				dataHL = pod->dohvati_Vrijednost();

			}

		}
	
	}

	switch (mnem)
	{
	case CALL:

		break;
	case JMP:
		descriptor |= 0;
		break;
	case JEQ:
		descriptor |= 1;
		break;
	case JNE:
		descriptor |= 2;
		break;
	case JGT:
		descriptor |= 3;
		break;
	default:
		descriptor = 0x30;
		break;
	}
	trenutnaSek->popuni(descriptor);
	trenutnaSek->popuni(pod);
	trenutnaSek->popuni(addrmode);

	if (is5) {
		trenutnaSek->popuni(dataH);
		trenutnaSek->popuni(dataL);
		
		
	}

	return 1;
}