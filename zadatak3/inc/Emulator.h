#pragma once
#include<iostream>
#include<ctime>
#include<string>
class Emulator
{
	short r[8], psw;
	//r7 pc
	//r6 sp
//psw 15-I 14-Tl  13-Tr    0 omogucen 1 maskiran   3-N 2-C 1-O 0-Z

unsigned char memorija[1 << 16];
bool kraj = false;
std::ifstream* input;
std::clock_t c_start;
std::clock_t c_end;
double ukupno;
long timePerioda = 500;
public:
	Emulator();
	~Emulator();

	void ucitaj_U_Memoriju(std::string s);//ucitava iz fajla u memoriju
	
	void saberi(char kod);
	void oduzmi(char kod);
	void pomnozi(char kod);
	void podjeli(char kod);
	void uporedi(char kod);
	void notuj(char kod);
	void xoruj(char kod);
	void anduj(char kod);
	void oruj(char kod);
	void test(char kod);
	void lshift(char kod);
	void rshift(char kod);
	void push(short kod);
	void pop(short kod);
	void xchg(char kod);
	void halt();
	void iret();
	void ret();
	void ldr(int kod);
	void str(int kod);
	void interrupt(char kod);
	void call(int kod);
	void jmp(int kod);
	void jeq(int kod);
	void jne(int kod);
	void jgt(int kod);
	void izvrsi();
	void provjeri_prekid();
};

