#include "Emulator.h"
#include<iostream>
#include<fstream>
#include <ctime>
#include"Conio.h"

Emulator::Emulator()
{
	psw = 0x00;
	r[6] = 0x7f00;
}


Emulator::~Emulator()
{
}


void Emulator::anduj(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f);
	r[src] &= r[dest];
}
void Emulator::pomnozi(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f);
	r[src] *= r[dest];
}
void Emulator::oruj(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f);
	r[src] |= r[dest];
}

void Emulator::podjeli(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f);

	r[src] /= r[dest];
}
void Emulator::xchg(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f);
		short tmp = r[src];
		r[src] = r[dest];
		r[dest] = tmp;
}
void Emulator::xoruj(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f);
		r[src] ^= r[dest];

}

void Emulator::lshift(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f);
	r[dest] <<= r[src];

	if(r[dest]==0){
		psw|=0x0001;
		psw&=0xfff1;
	}
	else {
		
		psw&=0xfff0;
	}
}

void Emulator::saberi(char ret) {
	int dest = (ret & 0xf0) >>4 ;
	int src = (ret & 0x0f);

	r[dest] += r[src];
	//postavi flegove
}
void Emulator::oduzmi(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f);
	r[dest] -= r[src];
	//postavi flegove
}
void Emulator::notuj(char ret) {
	int dest = (ret & 0xf0) >> 4;
	
	r[dest] = ~r[dest];
}

void Emulator::rshift(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f);
	r[dest] >>= r[src];
	if(r[dest]==0){
		psw|=0x0001;
		psw&=0xfff1;
	}
	else psw&=0xfff0;
}


void Emulator::test(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f);

	short temp = r[dest] & r[src];
	if(temp==0){psw|=0x0001; psw&=0xfff7;}
	else if(temp<0){psw|=0x0008;psw&=0xfffe;}
	//postavi flegove
}



void Emulator:: uporedi(char ret) {
	int dest = (ret & 0xf0) >> 4;
	int src = (ret & 0x0f) ;

	int tmp = r[dest] - r[src];
	
	if (tmp == 0) {
		psw |= 0x0001;
		psw&=0xfff1;
	}
	else if(tmp<0){
		if(r[dest]>=0&& r[src]>0){
			psw|=0x0008;
			psw&=0xfff8;
		}else if(r[dest]>0&&r[src]<0){
			psw|=0x000e;
			psw&=0xfffe;
		}
	}else{
			if(r[dest]>0&& r[src]>=0){
			
			psw&=0xfff0;
		}else if(r[dest]<0&&r[src]<0){
			psw|=0x0006;
			psw&=0xfff6;
		}
	}
}


void Emulator::halt() {
	kraj = true;
}

void Emulator::interrupt(char kod) {
	r[6] -= 2;
	memorija[r[6] + 1] = ((r[7] & 0xff00) >> 8);
	memorija[r[6]] = ((r[7] & 0x00ff));

	r[6] -= 2;
	memorija[r[6] + 1] =(( psw & 0xff00) >> 8);
	memorija[r[6]] = ((psw & 0x00ff));

	psw |= 0x7000;
	int dest = kod >>4;
	int pom =dest;
	pom *= 2;

	r[7] =( memorija[pom]<<8);
	r[7] |= (memorija[pom + 1]);
}

void Emulator::iret() {
	psw = (memorija[r[6]]);
	psw |= (memorija[r[6] + 1] << 8);
	r[6] += 2;

	r[7] = (memorija[r[6]]);
	r[7] |= (memorija[r[6] + 1] << 8);
	r[6] += 2;

}

void Emulator::ret() {
	r[7] = (memorija[r[6]]);
	r[7] |= (memorija[r[6] + 1] << 8);
	r[6] += 2;
}

void Emulator::jmp(int kod){
	int nacinADDR = (kod & 0x00ff0000) >> 16;
	unsigned short operand = 0;
	switch (nacinADDR)
	{
	case 0:
		operand = kod & 0x0000ffff;
		break;

	case 1:
		operand = r[(kod >> 28)];
		break;
	case 2:
		operand = r[(kod >> 28)];
		operand = memorija[operand];
		break;
	case 3:
		operand = r[(kod >> 28)];
		operand += kod & 0x0000ffff;
		operand = memorija[operand];
		break;

	case 4:
		operand += kod & 0x0000ffff;
		operand = memorija[operand];
		break;
	case 5:
		operand = r[(kod >> 28)];
		operand += kod & 0x0000ffff;
		break;
	}
	r[7] = operand;

}

void Emulator::call(int kod) {
	int nacinADDR = (kod & 0x00ff0000) >> 16;
	short operand = 0;
	switch (nacinADDR)
	{
		case 0:
			operand = kod & 0x0000ffff;
		break;

		case 1:
			operand = r[(kod >> 28)];
		break;
		case 2:
			operand = r[(kod >> 28)];
			operand = memorija[operand];
		break;
		case 3:
			operand = r[(kod >> 28)];
			operand+= kod & 0x0000ffff;
			operand = memorija[operand];
		break;

		case 4:
			operand += kod & 0x0000ffff;
			operand = memorija[operand];
		break;
		case 5:
			operand = r[(kod >> 28)];
			operand += kod & 0x0000ffff;
		break;
	}
	r[6] -= 2;
	memorija[r[6] + 1] = ((r[7] & 0xff00) >> 8);
	memorija[r[6]] = ((r[7] & 0x00ff));

	r[7] = operand;
}

void Emulator::jeq(int kod) {

	if (psw & 1)jmp(kod);
}
void Emulator::jne(int kod) {
	if ((psw & 1)==0)jmp(kod);
}

void Emulator::jgt(int kod) {

	if ((psw&0x000f)==0)jmp(kod);//smisliti sulov
}

void Emulator::ldr(int kod) {
	int nacinADDR = (kod & 0x00ff0000) >> 16;
	unsigned short operand = 0;
	switch (nacinADDR)
	{
	case 0:
		operand = kod & 0x0000ffff;
		break;

	case 1:
		operand = r[((kod >> 24)&0x0f)];
		break;
	case 2:
		operand = r[((kod >> 24) & 0x0f)];
		//if (operand == 0xff02){std::cout << memorija[0xff02]<<std::endl;
	//	std::cout.flush();}
		operand = memorija[operand];
		break;
	case 3:
		operand = r[((kod >> 24) & 0x0f)];
		operand += kod & 0x0000ffff;
	//	if (operand == 0xff02){std::cout << memorija[0xff02]<<std::endl;
	//	std::cout.flush();}
		operand = memorija[operand];
		break;

	case 4:
		operand += kod & 0x0000ffff;
	//	if (operand == 0xff02){std::cout << memorija[0xff02]<<std::endl;
	//	std::cout.flush();}
		operand = memorija[operand];
		break;
	case 5:
	//	operand = r[(kod >> 28)];
		operand = r[7];
		operand += kod & 0x0000ffff;
	//	if (operand == 0xff02){std::cout << memorija[0xff02]<<std::endl;
	//	std::cout.flush();}
		operand = memorija[operand];
		break;
	}

	int dest = (kod & 0xf0000000) >> 28;

	r[dest] = operand;

}

//str

void Emulator::str(int kod) {
	int nacinADDR = (kod & 0x00ff0000) >> 16;
	unsigned short operand = 0;
	int dest = (kod & 0xf0000000) >> 28;


	switch (nacinADDR)
	{
	case 0:
		std::cout << "Ne moze neposredan podatak" << std::endl;
		break;

	case 1:
		 r[((kod >> 24) & 0x0f)]= r[dest];
		break;
	case 2:
		operand = r[((kod >> 24) & 0x0f)];
		//if (r[dest] == 0xff00)std::cout << (char*)memorija[0xff00];
		memorija[operand]= r[dest];
		if (operand == 0xff00){std::cout << memorija[0xff00]<<std::endl;
		std::cout.flush();}
		break;
	case 3:
		operand = r[((kod >> 24) & 0x0f)];
		operand += kod & 0x0000ffff;
	//	if (r[dest] == 0xff00)std::cout << (char*)memorija[0xff00];
		memorija[operand]= r[dest];
		if (operand == 0xff00){std::cout << memorija[0xff00]<<std::endl;
		std::cout.flush();
		}
		break;

	case 4:
		operand += kod & 0x0000ffff;
		
		 memorija[operand]= r[dest];
		 if (operand == 0xff00){std::cout << memorija[0xff00];
		std::cout.flush();
		}
		break;
	case 5:
	//	operand = r[(kod >> 28)];
	//	operand += kod & 0x0000ffff;
		std::cout << "NE moze" << std::endl;
		break;
	}



}

void Emulator::push(short kod) {
	int dest = (kod & 0xff00) >> 6;

	r[dest] = memorija[r[6]];
	r[dest] |= memorija[r[6] + 1] << 8;
	r[6] += 2;
}
void Emulator::pop(short kod) {
	int dest = (kod & 0xff00) >> 6;
	r[6] -= 2;
	memorija[r[6] + 1] = (r[dest] & 0xff00) >> 8;
	memorija[r[6]] = r[dest] & 0x00ff;
}

void Emulator::ucitaj_U_Memoriju(std::string s) {
	input = new std::ifstream(s, std::ios::in | std::ios::binary);
	r[7] = 78;
	short start;
	input->read((char*)(&start), sizeof(short));
	r[7] = start;
	while (!input->eof()) {
		char c = 'a';
		while (c != '\0') {
			input->read(&c, sizeof(char));
			if (input->eof())return;
		}
			

		unsigned short pozicija, velicina;
		input->read((char*)(&pozicija), sizeof(short));
		input->read((char*)(&velicina), sizeof(short));
		for (int i = pozicija; i < pozicija + velicina; i++)
		{
			input->read((char*)(&memorija[i]), sizeof(char));
		}
	}
	//ucitaj

}

void Emulator::izvrsi() {
	c_start = std::clock();
	while (!kraj) {
		
		unsigned char c = memorija[r[7]];

		if (c == 0x00) {
			halt();
			r[7]++;
		}
		else if (c == 0x10) {
			r[7] += 2;
			interrupt(memorija[r[7] - 1]);
		}
		else if (c == 0x20) {
			r[7]++;
			iret();
		}
		else if (c == 0x30) {

			if ((memorija[r[7] + 2] & 0x0f) != 0x01 && (memorija[r[7] + 2] & 0x0f) != 0x02) {
				int kod = ((memorija[r[7] + 1]<<24) | (memorija[r[7] + 2]<<16) | (memorija[r[7] + 3]<<8) | (memorija[r[7]+4]));
				r[7] += 5;
				call(kod);
			}
			else {
				short kod = ((memorija[r[7] + 1] << 8) | (memorija[r[7] + 2]));
				r[7] += 3;
				call(kod);

			}


		}
		else if (c == 0x40) {
		r[7]++;
		ret();
		}
		else if ((c & 0xf0) == 0x50) {
		if ((memorija[r[7] + 2] & 0x0f) != 0x01 && (memorija[r[7] + 2] & 0x0f) != 0x02) {
			int kod = ((memorija[r[7] + 1] << 24) | (memorija[r[7] + 2] << 16) | (memorija[r[7] + 3] << 8) | (memorija[r[7] + 4]));
			r[7] += 5;
			if ((c & 0x0f) == 0x0) {
				jmp(kod);
			}
			else if ((c & 0x0f) == 0x3) {
				jgt(kod);
			}
			else if ((c & 0x0f) == 0x1) {
				jeq(kod);
			}
			else if ((c & 0x0f) == 0x2) {
				jne(kod);
			}
		}
		else {
			short kod = ((memorija[r[7] + 1] << 8) | (memorija[r[7] + 2]));
			r[7] += 3;
			if ((c & 0x0f) == 0x0) {
				jmp(kod);
			}
			else if ((c & 0x0f) == 0x3) {
				jgt(kod);
			}
			else if ((c & 0x0f) == 0x1) {
				jeq(kod);
			}
			else if ((c & 0x0f) == 0x2) {
				jne(kod);
			}

		}

		}
		else if (c == 0x60) {
		char kod = memorija[r[7] + 1] << 8;
		r[7] += 2;
		xchg(kod);
		}
		else if ((c & 0xf0) == 0x70) {
		char kod = memorija[r[7] + 1];
		r[7] += 2;
		if ((c & 0x0f) == 0x00) {
			saberi(kod);
		}
		else if ((c & 0x0f) == 0x01) {
			oduzmi(kod);
		}
		else if ((c & 0x0f) == 0x02) {
			pomnozi(kod);
		}
		else if ((c & 0x0f) == 0x03) {
			podjeli(kod);
		}
		else if ((c & 0x0f) == 0x04) {
			uporedi(kod);
		}

		}
		else if ((c & 0xf0) == 0x80) {
		char kod = (memorija[r[7] + 1]);
		r[7] += 2;
		if ((c & 0x0f) == 0x00) {
			not(kod);
		}
		else if ((c & 0x0f) == 0x01) {
			anduj(kod);
		}
		else if ((c & 0x0f) == 0x02) {
			oruj(kod);
		}
		else if ((c & 0x0f) == 0x03) {
			xoruj(kod);
		}
		else if ((c & 0x0f) == 0x04) {
			test(kod);
		}
		}
		else if ((c & 0xf0) == 0x90) {
		char kod = (memorija[r[7] + 1] );
		r[7] += 2;
		if ((c & 0x0f) == 0x00) {
			lshift(kod);
		}
		else if ((c & 0x0f) == 0x01) {
			rshift(kod);
		}
		}
		else if (c == 0xa0) {
		//std::cout << "ldr";
		if (memorija[r[7] + 2] == 0x42) {
			//pop
			int dest = (memorija[r[7] + 1] & 0xf0) >> 4;
			r[dest] = memorija[r[6]];
			r[dest] |= (memorija[r[6] + 1] << 8);

			r[6] += 2;
			r[7] += 3;
		}
		
		else if ((memorija[r[7] + 2] & 0x0f) != 0x01 && (memorija[r[7] + 2] & 0x0f) != 0x02) {

			int kod = ((memorija[r[7] + 1] << 24) | (memorija[r[7] + 2] << 16) | (memorija[r[7] + 3] << 8) | (memorija[r[7] + 4]));
			r[7] += 5;
			ldr(kod);
		}
		else {
			short kod = ((memorija[r[7] + 1] << 8) | (memorija[r[7] + 2]));
			r[7] += 3;
			ldr(kod);

		}

		}
		else if(c == 0xb0){
	//	std::cout << "str";
		if (memorija[r[7] + 2] == 0x12) {
			//push
			int dest = (memorija[r[7] + 1] & 0xf0) >> 4;
			memorija[r[6] - 1] = r[dest] >> 4;
			memorija[r[6] - 2] = r[dest] & 0x0f;

			r[6] -= 2;
			r[7] += 3;
		}
		else if ((memorija[r[7] + 2] & 0x0f) != 0x01 && (memorija[r[7] + 2] & 0x0f) != 0x02) {
			int kod = ((memorija[r[7] + 1] << 24) | (memorija[r[7] + 2] << 16) | (memorija[r[7] + 3] << 8) | (memorija[r[7] + 4]));
			r[7] += 5;
			str(kod);
		}
		else {
			short kod = ((memorija[r[7] + 1] << 8) | (memorija[r[7] + 2]));
			r[7] += 3;
			str(kod);

		}
		}

		//provjeri za prekid
		provjeri_prekid();

	}
}

void Emulator::provjeri_prekid() {

	if ((psw & 0x4000)==0) {
		int a;
		if (kbhit())
		{
			a = getch();
			memorija[0xff02] = a;
		//	psw |= 0x4000;
			interrupt(0x30);
			
		
		}
	}
		 c_end = std::clock();
		ukupno = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
		
	if ((psw & 0x2000)==0 && ukupno>=timePerioda ) {
		
		// your_algorithm

		unsigned char time = memorija[0xff10];
		//std::cout << ukupno;
		if (time == 0x0)timePerioda = 500;
		else if (time == 0x1)timePerioda = 1000;
		else if (time == 0x2)timePerioda = 1500;
		else if (time == 0x3)timePerioda = 2000;
		else if (time == 0x4)timePerioda = 5000;
		else if (time == 0x5)timePerioda = 10000;
		else if (time == 0x6)timePerioda = 30000;
		else if (time == 0x7)timePerioda = 60000;
		
		ukupno = 0;
		c_start=std::clock();
		interrupt(0x20);
	//	psw &= 0xbfff;
	}
}
