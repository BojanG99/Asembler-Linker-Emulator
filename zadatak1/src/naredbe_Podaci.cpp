#include"naredbe_Podaci.hpp"
#include"instrukcija.hpp"
#include"sekcija.hpp"
#include"operand.hpp"
#include"slozeni_Operand.hpp"
#include"literal.hpp"
#include"registar.hpp"
#include"simbol.hpp"
#include"tabela_Simbola.hpp"
#include"podaci_O_Simbolu.hpp"
#include"podaci_O_Relokacionom_Zapisu.hpp"
#include"relokacioni_Zapisi.hpp"
naredbe_Podaci::naredbe_Podaci(mnemonik mnem, operand* oper1, operand* oper2)
{
	this->mnem = mnem;
	drugiOperand = oper2;
	prvi_Operand = oper1;
}

naredbe_Podaci::~naredbe_Podaci()
{
}

int naredbe_Podaci::dohvati_Veliciniu() {

	if (mnem == RET || mnem == IRET || mnem == HALT) { return 1; }

	
	if(mnem==ADD|| mnem == SUB|| mnem == MUL || mnem == DIV || mnem == SHR)	return 2;

	if (mnem == XCHG || mnem == XOR || mnem == TEST ||
		mnem == SHL)return 2;

	if (mnem == OR || mnem == NOT )return 2;

	
	if (mnem == AND)return 2;
	if (mnem == TEST)return 2;

	if (mnem == CMP)return 2;
	else if (mnem == POP || mnem == PUSH||drugiOperand->dohvatiNacinA()==REGDIR|| prvi_Operand->dohvatiNacinA() == REGINDIR )return 3;

	return 5;
}
int naredbe_Podaci::popuniMemoriju(tabela_Simbola*tabela_Sim, sekcija* trenutanSekcija, std::vector<sekcija*>*sekcije) {
	int reg, reg1, reg2;
	char pod;
	char dataH = 0, dataL = 0;
	short dataHL;
	char addrmode;
	nacinAdresiranja na;
	switch (mnem)
	{
	case POP:
		trenutanSekcija->popuni(0xA0);
		reg = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		pod = 0x06 | (reg<<4);
		trenutanSekcija->popuni(pod);
		trenutanSekcija->popuni(0x42);
		break;
	case PUSH:
		trenutanSekcija->popuni(0xB0);
		reg = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		pod = 0x06 | (reg<<4);
		trenutanSekcija->popuni(pod);
		trenutanSekcija->popuni(0x12);
		break;
	case RET:
		trenutanSekcija->popuni(0x40);
		break;
	case IRET:
		trenutanSekcija->popuni(0x20);
		break;
	case HALT:
		trenutanSekcija->popuni(0x00);
		break;
	case ADD:
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod = (reg1 << 4) | reg2;
		trenutanSekcija->popuni(0x70);
		trenutanSekcija->popuni(pod);
		break;
	case SUB:
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod = (reg1 << 4) | reg2;
		trenutanSekcija->popuni(0x71);
		trenutanSekcija->popuni(pod);

		break;
	case MUL:
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod =( reg1 << 4) | reg2;
		trenutanSekcija->popuni(0x72);
		trenutanSekcija->popuni(pod);

		break;
	case DIV:
		trenutanSekcija->popuni(0x73);
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod = (reg1 << 4 )| reg2;
		trenutanSekcija->popuni(pod);
		break;
	case XOR:
		trenutanSekcija->popuni(0x83);

		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod = (reg1 << 4) | reg2;
		trenutanSekcija->popuni(pod);
		break;
	case OR:
		trenutanSekcija->popuni(0x82);
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod =( reg1 << 4) | reg2;
		trenutanSekcija->popuni(pod);
		break;
	case TEST:

		trenutanSekcija->popuni(0x84);
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod = (reg1 << 4) | reg2;
		trenutanSekcija->popuni(pod);
		break;
	case XCHG:
		trenutanSekcija->popuni(0x60);
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod = (reg1 << 4) | reg2;
		trenutanSekcija->popuni(pod);
		break;
	case LDR:
		//dohvatiti drugi operand

		trenutanSekcija->popuni(0xA0);
		na = drugiOperand->dohvatiNacinA();
		reg = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		pod = reg << 4;
		addrmode = 0;
		dataH = 0, dataL = 0;
		if (na == NEPOSREDNO) {
			addrmode = 0x00;
			if (literal::is_Literal(drugiOperand->dohvatiOperand())) {
				dataHL = literal::pretvori(drugiOperand->dohvatiOperand());

			}
			else {
				podaci_O_Simbolu* pod = tabela_Sim->dohvati_Simbol(drugiOperand->dohvatiOperand());
				string simb;
				if (pod == nullptr)return-1;
				if (pod->sekcija != "APSOLUTAN") {

					if (pod->lokalan) {
						simb = pod->sekcija;
						dataHL = pod->dohvati_Vrijednost();
					}
					else {
						simb = drugiOperand->dohvatiOperand();
						dataHL = 0;
					}

					podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutanSekcija->getOffset() + 2, simb);
					trenutanSekcija->dohvatiTabeluRZ()->ubaciZapis(relpod);

				}
				else {
					dataHL = pod->dohvati_Vrijednost();

				}

			}
			dataH = dataHL >> 8;
			dataL = dataHL & 0x00ff;
			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);
			
			
			trenutanSekcija->popuni(dataH);
			trenutanSekcija->popuni(dataL);
		}
		else if (na == REGDIR) {
			pod |= registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
			addrmode = 0x01;
			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);

		}
		else if (na == REGINDIR) {
			 pod|= registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
			addrmode = 0x02;
			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);

		}
		else if (na == PCREL) {

			addrmode = 0x05;//NISAM SIGURAN ZA OVO
			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);


			podaci_O_Simbolu* pod = tabela_Sim->dohvati_Simbol(drugiOperand->dohvatiOperand());
			string simb;
			if (pod == nullptr)return-1;
			if (pod->sekcija != "APSOLUTAN") {

				if (pod->lokalan) {
					simb = pod->sekcija;
					dataHL = pod->dohvati_Vrijednost() - 2;
				}
				else {
					simb = drugiOperand->dohvatiOperand();
					dataHL = -2;
				}

				podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_PC32, trenutanSekcija->getOffset(), simb);
				trenutanSekcija->dohvatiTabeluRZ()->ubaciZapis(relpod);

			}
			else {
				dataHL = pod->dohvati_Vrijednost();

			}

			dataH = dataHL >> 8;
			dataL = dataHL & 0x00ff;
			trenutanSekcija->popuni(dataH);
			trenutanSekcija->popuni(dataL);
			
			


		}
		else if (na == MEMORIJSKO) {
			addrmode = 0x04;
			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);

			if (literal::is_Literal(drugiOperand->dohvatiOperand())) {
				dataHL = literal::pretvori(drugiOperand->dohvatiOperand());
			}
			else {
				podaci_O_Simbolu* pod = tabela_Sim->dohvati_Simbol(drugiOperand->dohvatiOperand());
				string simb;
				if (pod == nullptr)return-1;
				if (pod->sekcija != "APSOLUTAN") {

					if (pod->lokalan) {
						simb = pod->sekcija;
						dataHL = pod->dohvati_Vrijednost();
					}
					else {
						simb = drugiOperand->dohvatiOperand();
						dataHL = 0;
					}

					podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutanSekcija->getOffset(), simb);
					trenutanSekcija->dohvatiTabeluRZ()->ubaciZapis(relpod);

				}
				else {
					dataHL = pod->dohvati_Vrijednost();

				}

			}

			dataH = dataHL >> 8;
			dataL = dataHL & 0x00ff;
		
			
			trenutanSekcija->popuni(dataH);
			trenutanSekcija->popuni(dataL);
		}

		else {//slozeni operand
			addrmode = 0x03;
			slozeni_Operand *sloOper = (slozeni_Operand*)drugiOperand;

			int regslozeni = registar::dohvatiRegistar(sloOper->dohvati_prvi());
			pod |= regslozeni;

			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);


			if (literal::is_Literal(drugiOperand->dohvatiOperand())) {
				dataHL = literal::pretvori(drugiOperand->dohvatiOperand());
			}
			else {
				podaci_O_Simbolu* pod = tabela_Sim->dohvati_Simbol(drugiOperand->dohvatiOperand());
				string simb;
				if (pod == nullptr)return-1;
				if (pod->sekcija != "APSOLUTAN") {

					if (pod->lokalan) {
						simb = pod->sekcija;
						dataHL = pod->dohvati_Vrijednost();
					}
					else {
						simb =sloOper->dohvati_drugi();
						dataHL = 0;
					}

					podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutanSekcija->getOffset(), simb);
					trenutanSekcija->dohvatiTabeluRZ()->ubaciZapis(relpod);

				}
				else {
					dataHL = pod->dohvati_Vrijednost();

				}


			}
			dataH = dataHL >> 8;
			dataL = dataHL & 0x00FF;
			
			trenutanSekcija->popuni(dataH);
			trenutanSekcija->popuni(dataL);
		
		}
	
		break;
	case SHL:
		
		trenutanSekcija->popuni(0x90);
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod = (reg1 << 4) | reg2;
		trenutanSekcija->popuni(pod);
		break;
	case SHR:
		trenutanSekcija->popuni(0x91);
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod = (reg1 << 4) | reg2;
		trenutanSekcija->popuni(pod);
		break;
	case STR:
		
		trenutanSekcija->popuni(0xB0);
		na = drugiOperand->dohvatiNacinA();
		reg = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		pod = reg << 4;
		addrmode = 0;
		dataH = 0, dataL = 0;
		if (na == NEPOSREDNO) {
			addrmode = 0x00;
			if (literal::is_Literal(drugiOperand->dohvatiOperand())) {
				dataHL = literal::pretvori(drugiOperand->dohvatiOperand());

			}
			else {
				podaci_O_Simbolu* pod = tabela_Sim->dohvati_Simbol(drugiOperand->dohvatiOperand());
				string simb;
				if (pod == nullptr)return-1;
				if (pod->sekcija != "APSOLUTAN") {

					if (pod->lokalan) {
						simb = pod->sekcija;
						dataHL = pod->dohvati_Vrijednost();
					}
					else {
						simb = drugiOperand->dohvatiOperand();
						dataHL = 0;
					}

					podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutanSekcija->getOffset() + 2, simb);
					trenutanSekcija->dohvatiTabeluRZ()->ubaciZapis(relpod);

				}
				else {
					dataHL = pod->dohvati_Vrijednost();

				}

			}
			dataH = dataHL >> 8;
			dataL = dataHL & 0x00ff;
			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);
			trenutanSekcija->popuni(dataH);
			trenutanSekcija->popuni(dataL);
			
		}
		else if (na == REGDIR) {
			pod |= registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
			addrmode = 0x01;
			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);

		}
		else if (na == REGINDIR) {
			pod |= registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
			addrmode = 0x02;
			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);

		}
		else if (na == PCREL) {

			addrmode = 0x05;
			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);


			podaci_O_Simbolu* pod = tabela_Sim->dohvati_Simbol(drugiOperand->dohvatiOperand());
			string simb;
			if (pod == nullptr)return-1;
			if (pod->sekcija != "APSOLUTAN") {

				if (pod->lokalan) {
					simb = pod->sekcija;
					dataHL = pod->dohvati_Vrijednost() - 2;
				}
				else {
					simb = prvi_Operand->dohvatiOperand();
					dataHL = -2;
				}

				podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_PC32, trenutanSekcija->getOffset(), simb);
				trenutanSekcija->dohvatiTabeluRZ()->ubaciZapis(relpod);

			}
			else {
				dataHL = pod->dohvati_Vrijednost();

			}

			dataH = dataHL >> 8;
			dataL = dataHL & 0x00ff;
			trenutanSekcija->popuni(dataH);
			trenutanSekcija->popuni(dataL);
			


		}
		else if (na == MEMORIJSKO) {
			addrmode = 0x04;
			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);

			if (literal::is_Literal(drugiOperand->dohvatiOperand())) {
				dataHL = literal::pretvori(drugiOperand->dohvatiOperand());
			}
			else {
				podaci_O_Simbolu* pod = tabela_Sim->dohvati_Simbol(drugiOperand->dohvatiOperand());
				string simb;
				if (pod == nullptr)return-1;
				if (pod->sekcija != "APSOLUTAN") {

					if (pod->lokalan) {
						simb = pod->sekcija;
						dataHL = pod->dohvati_Vrijednost();
					}
					else {
						simb = drugiOperand->dohvatiOperand();
						dataHL = 0;
					}

					podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutanSekcija->getOffset(), simb);
					trenutanSekcija->dohvatiTabeluRZ()->ubaciZapis(relpod);

				}
				else {
					dataHL = pod->dohvati_Vrijednost();

				}

			}

			dataH = dataHL >> 8;
			dataL = dataHL & 0x00ff;
			trenutanSekcija->popuni(dataH);
			trenutanSekcija->popuni(dataL);
		

		}

		else {//sa pomjerajem
				//dodatna 2 bajta
			addrmode = 0x03;
			slozeni_Operand *sloOper = (slozeni_Operand*)drugiOperand;

			int regslozeni = registar::dohvatiRegistar(sloOper->dohvati_prvi());
			pod |= regslozeni;

			trenutanSekcija->popuni(pod);
			trenutanSekcija->popuni(addrmode);

				if (literal::is_Literal(drugiOperand->dohvatiOperand())) {
					dataHL = literal::pretvori(sloOper->dohvati_drugi());
				}
				else {
					podaci_O_Simbolu* pod = tabela_Sim->dohvati_Simbol(drugiOperand->dohvatiOperand());
					string simb;
					if (pod == nullptr)return-1;
					if (pod->sekcija != "APSOLUTAN") {

						if (pod->lokalan) {
							simb = pod->sekcija;
							dataHL = pod->dohvati_Vrijednost();
						}
						else {
							simb = sloOper->dohvati_drugi();
							dataHL = 0;
						}

						podaci_O_Relokacionom_Zapisu* relpod = new podaci_O_Relokacionom_Zapisu(R_386_32, trenutanSekcija->getOffset(), simb);
						trenutanSekcija->dohvatiTabeluRZ()->ubaciZapis(relpod);

					}
					else {
						dataHL = pod->dohvati_Vrijednost();

					}
				}
			
				dataH = dataHL >> 8;
				dataL = dataHL & 0x00FF;
				trenutanSekcija->popuni(dataH);
			trenutanSekcija->popuni(dataL);
			
		}
		break;
	case NOT:
		trenutanSekcija->popuni(0x80);
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
	
		pod = reg1 <<4;
		trenutanSekcija->popuni(pod);
		break;
	case AND:
		trenutanSekcija->popuni(0x81);
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod = (reg1 << 4) | reg2;
		trenutanSekcija->popuni(pod);
		break;
	case CMP:
		trenutanSekcija->popuni(0x74);
		reg1 = registar::dohvatiRegistar(prvi_Operand->dohvatiOperand());
		reg2 = registar::dohvatiRegistar(drugiOperand->dohvatiOperand());
		pod = (reg1 << 4) | reg2;
		trenutanSekcija->popuni(pod);
		break;
	}

	return 1;
}

