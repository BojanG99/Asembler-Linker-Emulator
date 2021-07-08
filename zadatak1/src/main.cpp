#include<iostream>
#include<fstream>
#include<string>
#include"prvi_Prolaz.hpp"
#include"linija.hpp"
//#include"simbol.hpp"
//#include"literal.hpp"
#include"naredbe_Podaci.hpp"
#include"naredbe_Skoka.hpp"
#include"registar.hpp"
#include"direktiva.hpp"
#include"labela.hpp"
#include<regex>
#include"jednostavni_Operand.h"
#include"slozeni_Operand.hpp"
#include"tabela_Simbola.hpp"
#include"drugi_Prolaz.hpp"
#include"sekcija.hpp"
#include"relokacioni_Zapisi.hpp"
#include"objektni_Fajl.h"

using namespace std;

string skini_Komentar(string str) {
	int j = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '#') {
			return str.substr(j, i-j);
		}
		else if (str[i] == ' ' && i == j)j++;
	}
	return str.substr(j,str.length()-j);

}
string skini_blanko(string str) {
	int i;
	for ( i = str.length() - 1;i >= 0;i--) {
		if (str[i] != ' ' && str[i] != '\t')break;
	}
	return str.substr(0, i + 1);
}
string skini_dvotacku(string str) {
	return str.substr(0, str.length() - 1);
}
string trim(string str) {
	int poc = 0;
	int kraj = 0;
	int i = 0;
	while (str[i] == ' ')i++;
	poc = i;
	while (i<str.length() && str[i] != ' ' && str[i] != ',') {
		i++;
	}
	return str.substr(poc, i - poc);
}

int main(int argc, char ** argv) {

	ifstream readFile(argv[3]);
	string liter = "([0-9]+|0x[0-9ABCDEF]{1,4})";
	string lab = "^([a-zA-Z_]+:){0,1} *";
	string myText;
	// Use a while loop together with the getline() function to read the file line by line
	string regeksi[] = {
		"^([a-zA-Z_]+:)$",//hvata samo labelu  0
		lab+"\\.(global|extern) (([a-zA-Z_]+, )*)([a-zA-Z_]+)$",  //hvata direktviu .qlobal ili .extern  1
		lab + "\\.(section) ([a-zA-Z]+)$",//hvata direktivu .section   2
		lab + "\\.(end)$",//hvata direktivu .end   3
		lab + "\\.(word)( 0x[0-9ABCDEF]{1,4},| [0-9]+,| [a-zA-Z_]+,)* (0x[0-9ABCDEF]{1,4}|[0-9]+|[a-zA-Z_]+)$",//hvata word direktivu   4  ,
		lab+ "\\.(equ) ([a-zA-Z_]+), ([0-9]+|0x[0-9ABCDEF]{1,4})$",//.equ   5
		lab + "\\.skip " + liter + "$",//hvata skip direktivu 6
		lab + "halt$",//   7
		lab + "iret$",//8
		lab + "ret$",//  9
		lab + "(xcgh|add|sub|mul|div|cmp|and|or|xor|test|shl|shr) (r[0-7]|sp|pc|psw), (r[0-7]|sp|pc|psw)$",//10
		lab + "(pop|push|not|int) (r[0-7]|sp|pc|psw)$",//11
		lab + "(call|jmp|jeq|jne|jgt) (\\*?[0-9]+|\\*?0x[0-9ABCDEF]{1,4}|[%\\*]?[a-zA-Z_]+|\\*r[0-7]|\\*pc|\\*psw|\\*sp|\\*\\[r[0-7]\\]|\\*\\[pc\\]|\\*\\[psw\\]|\\*\\[sp\\])$",//12
		lab + "(call|jmp|jeq|jne|jgt) \\*\\[(r[0-7]|sp|pc|psw) \\+ (0x[0-9ABCDEF]{1,4}|[0-9]+|[a-zA-Z_]+)\\]$",//13
		lab + "(ldr|str) (r[0-7]|pc|psw|sp), (\\$?[0-9]+|\\$?0x[0-9ABCDEF]{1,4}|[\\%\\$]?[a-zA-Z_]+|r[0-7]|pc|psw|sp|\\[r[0-7]\\]|\\[pc\\]|\\[psw\\]|\\[sp\\])$",//14
		lab + "(ldr|str) (r[0-7]|pc|psw|sp), \\[(r[0-7]|sp|pc|psw) \\+ (0x[0-9ABCDEF]{1,4}|[0-9]+|[a-zA-Z_]+)\\]$",//15
		
		
	};
	vector<linija*>* linije = new vector<linija*>(0);
	while (std::getline(readFile,myText)) {
		 myText=myText.substr(0,myText.length()-1);
		myText = skini_Komentar(myText);
		
		myText = skini_blanko(myText);
			cout << myText <<endl;
		if (myText == "")continue;

		
		
		for (int i = 0;i < 16;i++) {
			smatch m;
			if (regex_match(myText,m, regex(regeksi[i]))) {
				linija* l = new linija();
				if (m[1] != "") {
					l->postavi_Labelu(new labela(skini_dvotacku(m[1])));
				}
				if (i == 0) {
				
				}
				else if (i == 1) {
					asemblerskaDirektiva * dir = nullptr;
					if (m[2] == "global")
					{
						 dir = new asemblerskaDirektiva(GLOBAL);

					}
					else {
						dir = new asemblerskaDirektiva(EXTERN);
					}
					cout << "Extern or global";
				/*	for (int j = 3;j < m.size();j++) {


						if (m[j] != "") {
							dir->dodaj_Argumente(m[j]);
							cout << m[j]<<"|";
						}

					}*/
					if (m[3] != "") {
						int pos = 0;
						for (int i = 0;i < m[3].length();i++) {
							if (m[3].str()[i] == ',') {
								dir->dodaj_Argumente(trim(m[3].str().substr(pos, pos - i )));
								cout << m[3].str().substr(pos, pos-1 )<<"|";
								pos = i + 1;
							}
						}
					}

					dir->dodaj_Argumente(m[5]);
					cout << m[5];
					cout << endl;
					dir->postavi_Velicinu();
					l->postavi_Direktivu(dir);
					cout << "Uhvacena .g .e" << endl;

				}//.global .extern
				else if (i == 2) {
					asemblerskaDirektiva *dir = new asemblerskaDirektiva(SECTION);
					dir->dodaj_Argumente(m[3]);
					l->postavi_Direktivu(dir);
					cout << "Uhvacena .s" << endl;
				}
				else if (i == 3) {
					asemblerskaDirektiva *dir = new asemblerskaDirektiva(END);
					l->postavi_Direktivu(dir);
					cout << "Uhvacena .end" << endl;
				}
				else if (i == 4) {
					asemblerskaDirektiva *dir = new asemblerskaDirektiva(WORD);
					for (int i = 3;i < m.size();i++)
					{
						if(m[i]!="")
						dir->dodaj_Argumente(m[i]);//nije zavrseno
					}
					l->postavi_Direktivu(dir);
					dir->postavi_Velicinu();
					cout << "Uhvacena .w" << endl;
				}
				else if (i == 5) {
					asemblerskaDirektiva *dir = new asemblerskaDirektiva(EQU);
					dir->dodaj_Argumente(m[3]);
					
					dir->dodaj_Argumente(m[4]);
					l->postavi_Direktivu(dir);
					cout << "Uhvacena .equ" << endl;
				}
				else if (i == 6) {
					asemblerskaDirektiva *dir = new asemblerskaDirektiva(SKIP);
					dir->dodaj_Argumente(m[2]);
					dir->postavi_Velicinu();

					l->postavi_Direktivu(dir);
					cout << "Uhvacena .skip" << endl;
				}
				else if (i == 7) {
					naredbe_Podaci* nar = new naredbe_Podaci(HALT);
					l->postavi_Naredbu(nar);
					cout << "Uhvacen halt" << endl;
				}
				else if (i == 8) {
					naredbe_Podaci* nar = new naredbe_Podaci(IRET);
					l->postavi_Naredbu(nar);
					cout << "Uhvacen iret" << endl;
				}
				else if (i == 9) {
					naredbe_Podaci* nar = new naredbe_Podaci(RET);
					l->postavi_Naredbu(nar);
					cout << "Uhvacen ret" << endl;
				}
				else if (i == 10) {
					naredbe_Podaci* nar = nullptr;
					if (m[2] == "add") {

						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(ADD, o1, o2);

						l->postavi_Naredbu(nar);
					}
					else if (m[2] == "xchg") {
						
						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(XCHG,o1,o2);

						l->postavi_Naredbu(nar);
					}
					else if (m[2] == "sub") {

						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(SUB, o1, o2);

						l->postavi_Naredbu(nar);
					}
					else if (m[2] == "mul") {

						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(MUL, o1, o2);

						l->postavi_Naredbu(nar);
					}
					else if (m[2] == "div") {

						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(DIV, o1, o2);

						l->postavi_Naredbu(nar);

					}
					else if (m[2] == "cmp") {

						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(CMP, o1, o2);

						l->postavi_Naredbu(nar);

					}
					else if (m[2] == "and") {


						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(AND, o1, o2);

						l->postavi_Naredbu(nar);
					}
					else if (m[2] == "or") {


						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(OR, o1, o2);

						l->postavi_Naredbu(nar);
					}
					else if (m[2] == "xor") {


						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(XOR, o1, o2);

						l->postavi_Naredbu(nar);
					}
					else if (m[2] == "test") {


						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(TEST, o1, o2);

						l->postavi_Naredbu(nar);
					}
					else if (m[2] == "shl") {


						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(SHL, o1, o2);

						l->postavi_Naredbu(nar);
					}
					else if (m[2] == "shr") {

						operand *o1 = new jednostavni_Operand(REGDIR, m[3]);
						operand *o2 = new jednostavni_Operand(REGDIR, m[4]);
						nar = new naredbe_Podaci(SHR, o1, o2);

						l->postavi_Naredbu(nar);

					}




				}
				else if (i == 11) {
				naredbe_Podaci *nar = nullptr;
				if (m[2] == "pop") {
					operand *o = new jednostavni_Operand(REGDIR, m[3]);
					nar = new naredbe_Podaci(POP,o);
					}
				else if(m[2]=="push"){
					operand *o = new jednostavni_Operand(REGDIR, m[3]);
					nar = new naredbe_Podaci(PUSH, o);
				}
				else if (m[2] == "not") {
					operand *o = new jednostavni_Operand(REGDIR, m[3]);
					nar = new naredbe_Podaci(RET, o);
				}
				else {
					operand *o = new jednostavni_Operand(REGDIR, m[3]);
					nar = new naredbe_Podaci(INT, o);
				}

				l->postavi_Naredbu(nar);
				}
				else if (i == 12) {
					cout << "skok jednostavni operand" << endl;
					naredbe_Skoka* nar = nullptr;
					string s = m[3];
					string op = "";
					nacinAdresiranja nadr;
					smatch m1;
					if (regex_match(s, m1, regex("^\\*(r[0-7]|pc|psw|sp)$"))) {
						nadr = REGDIR;
						op = m1[1];
					}
					else if (regex_match(s, m1, regex("^\\*(.*)$"))) {
						nadr = MEMORIJSKO;
						op = m1[1];
					}
					else if (regex_match(s, m1, regex("^%(.*)$"))) {
						nadr = PCREL;//
						op = m1[1];
					}
					else {
						op = m[3];
						nadr = NEPOSREDNO;
					}
					operand* o = new jednostavni_Operand(nadr, op);


					if (m[2] == "jgt") {
						nar = new naredbe_Skoka(JGT, o);
					}
					else if (m[2] == "jeq") { nar = new naredbe_Skoka(JEQ, o); }
					else if (m[2] == "jne") { nar = new naredbe_Skoka(JNE, o); }
					else if (m[2] == "jmp") { nar = new naredbe_Skoka(JMP, o); }
					else if (m[2] == "call") { nar = new naredbe_Skoka(CALL, o); }

					l->postavi_Naredbu(nar);
				
				}
				else if (i == 13) {
				
				slozeni_Operand *o = new slozeni_Operand(MEMORIJSKO, m[3], m[4]);

				naredbe_Skoka *nar = nullptr;

				if (m[2] == "jgt") {
					nar = new naredbe_Skoka(JGT, o);
				}
				else if (m[2] == "jeq") { nar = new naredbe_Skoka(JEQ, o); }
				else if (m[2] == "jne") { nar = new naredbe_Skoka(JNE, o); }
				else if (m[2] == "jmp") { nar = new naredbe_Skoka(JMP, o); }
				else if (m[2] == "call") { nar = new naredbe_Skoka(CALL, o); }

				l->postavi_Naredbu(nar);

				cout << "skok slozeni operand" << endl;
				}
				else if (i == 14) {
					cout << "data jednostavni operand" << endl;
					naredbe_Podaci* nar = nullptr;
					string s = m[4];
					string s1 = m[3];
					string op = "";
					nacinAdresiranja nadr;
					smatch m1;
					if (regex_match(s, m1, regex("^\\[(r[0-7]|pc|psw|sp)\\]$"))) {
						nadr = REGINDIR;
						op = m1[1];
					}
					else if (regex_match(s, m1, regex("^\\$(.*)$"))) {
						nadr = NEPOSREDNO;
						op = m1[1];
					}
					else if (regex_match(s, m1, regex("^\\%(.*)$"))) {
						nadr = PCREL;
						op = m1[1];
					}
					else if (regex_match(s, m1, regex("^(r[0-7]|pc|psw|sp)$"))) {
						nadr = REGDIR;
						op = m[4];
					}
					else {
						op = m[4];
						nadr = MEMORIJSKO;
					}
					operand* o = new jednostavni_Operand(nadr, op);
					operand* jo = new jednostavni_Operand(REGDIR, s1);

					if (m[2] == "ldr") {
						nar = new naredbe_Podaci(LDR, jo,o);
					}
					else if (m[2] == "str") { nar = new naredbe_Podaci(STR,jo, o); }
					

					l->postavi_Naredbu(nar);


				}
				else if (i == 15) {
				slozeni_Operand *o = new slozeni_Operand(MEMORIJSKO, m[4], m[5]);

				naredbe_Podaci *nar = nullptr;
				jednostavni_Operand *jo = new jednostavni_Operand(REGDIR, m[3]);
				if (m[2] == "ldr") {
					nar = new naredbe_Podaci(LDR,jo, o);
				}
				else if (m[2] == "str") { nar = new naredbe_Podaci(STR,jo, o); }
		

				l->postavi_Naredbu(nar);

					cout << "data slozeni operand" << endl;
				}
				else {
					cout << "NE POSTOJI OPERACIJA";
				}
			
			

				linije->push_back(l);
				break;
			}

		}
	}
		
		


	// Close the file
	readFile.close();


	

	prvi_Prolaz *prolaz1 = new prvi_Prolaz(linije);

	prolaz1->prodji();

	tabela_Simbola *ts = prolaz1->dohvati_Tabelu_Simbola();
	vector<sekcija*> *s = prolaz1->dohvati_Sekcije();
	
	cout << *ts;
	cout << "sekcije" << endl;
	for (sekcija* sek : *s) {
		cout << *sek;
	}

	drugi_Prolaz *prolaz2 = new drugi_Prolaz(ts, linije, s);
	prolaz2->prodji();
	//cout << prolaz2->getErr();
	vector<sekcija*> *ms=prolaz2->dohvatiSekcije();

	for (sekcija* sek : *ms) {
		sek->ispisi_Niz();
		cout << "sekcijeSAdrzaj" << endl;
	
		cout << "------------------" <<sek->getOffset()<<"------------------------------"<< endl;
		cout << "Rel --------" << endl;
		cout << *(sek->dohvatiTabeluRZ()) << endl;
		cout << " --------" << endl;
	}

	objektni_Fajl *ofajl = new objektni_Fajl(argv[2]);
	ofajl->serijalizuj(ms,ts );
	delete(ofajl);
//	system("pause");

	return 0;
}
