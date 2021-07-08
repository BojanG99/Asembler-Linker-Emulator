#include<iostream>
#include"Emulator.h"
#include"Conio.h"
//#include"Conio.h"
using namespace std;



//struct termios orig_termios;



int main(int argc,char**argv)
{
enableRawMode();
	/*while (1)
	{
		int a  ;
		if (_kbhit())
		{
			a = _getch();
			std::cout << a;
		}
	}*/


	Emulator e;

	e.ucitaj_U_Memoriju(argv[1]);

	e.izvrsi();

	
//	system("pause");
	return 0;
}
