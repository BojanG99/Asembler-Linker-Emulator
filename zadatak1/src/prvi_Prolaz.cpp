#include"prvi_Prolaz.hpp"
#include"linija.hpp"
#include"labela.hpp"
#include"tabela_Simbola.hpp"
#include"podaci_O_Simbolu.hpp"
#include"naredbe.hpp"
#include"direktiva.hpp"
#include<string>
#include"sekcija.hpp"
#include"literal.hpp"
prvi_Prolaz::prvi_Prolaz(std::vector<linija*>*lin)
{
    linije=lin;
    tabela=new tabela_Simbola();
	sekcije = new std::vector<sekcija*>(0);
}

prvi_Prolaz::~prvi_Prolaz()
{
}
void prvi_Prolaz::prodji(){
    short brojac=0;
	std::string nazivSek;
	sekcija *sek = nullptr;
	int brojsekcije = 0;
    unsigned char numsekcije=0;
    for (linija* lin:*linije)
    {
        if(lin->dohvati_Labelu()!=nullptr){//ako postoji labela ubacujemo je u tabelu simbola

           if( tabela->dohvati_Simbol(lin->dohvati_Labelu()->dohvati_Naziv())!=nullptr){

               errcode=VISESTRUKO_DEFINISAN_SIMBOL;//ako je ranije definisana
               return;
           }
           else{
               tabela->ubaci_Simbol(lin->dohvati_Labelu()->dohvati_Naziv(),new podaci_O_Simbolu(brojac, nazivSek,true,numsekcije,true));
           }
         
        }
          if(lin->dohvati_Naredbu()!=nullptr){//ako je linija naredba;
               brojac+=lin->dohvati_Naredbu()->dohvati_Veliciniu();//uvecavamo brojac za velicinu naredbe
           }else{
			  if (lin->dohvati_Direktivu() != nullptr) {
				  asemblerskaDirektiva *dir = lin->dohvati_Direktivu();

				  brojac += dir->dohvati_Velicinu();

				  if (dir->da_Li_Je_Sekcija()) {//sacuvamo prethodnu sekciju
					  if (sek != nullptr) {
						  sek->postavi_velicinu(brojac);
						  sek->postavi_ID_Sekcije(numsekcije);
						  sekcije->push_back(sek);

					  }
					  numsekcije++;
					  nazivSek = dir->dohvati_Argument(0);
					  brojac = 0;

					  sek = new sekcija(dir->dohvati_Argument(0));
					  tabela->ubaci_Simbol(dir->dohvati_Argument(0), new podaci_O_Simbolu(0, nazivSek, true,numsekcije,true));
				  }
				  else if (dir->da_Li_Je_Kraj()) {
					  sek->postavi_velicinu(brojac);
					  sek->postavi_ID_Sekcije(numsekcije);
					  sekcije->push_back(sek);
					  return;

				  }
				  else if (dir->da_Li_Je_(EQU)) {
					  tabela->ubaci_Simbol(dir->dohvati_Argument(0), new podaci_O_Simbolu(literal::pretvori(dir->dohvati_Argument(1)), "APSOLUTAN", true,255,true));
				  }
				  else if (dir->da_Li_Je_(EXTERN)) {
					  for(int i=0;i<dir->dohvati_Broj_Elemenata();i++)
					  tabela->ubaci_Simbol(dir->dohvati_Argument(i), new podaci_O_Simbolu(0, "UNDEF", false,0,false));
				  }
				 
			  }
                 
               
           }

       
        
    }
    
}

