#include"tabela_Simbola.hpp"
#include"podaci_O_Simbolu.hpp"
#include<string>

tabela_Simbola::tabela_Simbola(/* args */)
{
	tabela = new std::unordered_map<std::string, podaci_O_Simbolu*>(0);
}

tabela_Simbola::~tabela_Simbola()
{
}


void tabela_Simbola::ubaci_Simbol(std::string s, podaci_O_Simbolu* ps){
	(*tabela)[s] = ps;
}
podaci_O_Simbolu* tabela_Simbola::dohvati_Simbol(std::string s) {
	if(tabela->find(s)!=tabela->end())
	return tabela->find(s)->second;
	return nullptr;
}
int tabela_Simbola::velicina() {
	int size = 0;
	for ( auto element : *tabela) {
		size += element.first.length() + 1 + element.second->velicina();
	}
	return size;
}

void tabela_Simbola::popuniOfajl(std::ofstream* izlaz) {
	for (auto element : *tabela) {
	
		izlaz->write(element.first.c_str(), element.first.length() + 1);
		element.second->popuniOfajl(izlaz);
	}

}
tabela_Simbola* tabela_Simbola::dohvatiIzFajla(std::ifstream *ulaz,int num) {
	tabela_Simbola *ret = new tabela_Simbola();
//	int num = 0;
//	ulaz->read((char*)(&num), sizeof(int));
	std::string s = "";
	for (int i = 0;i < num;i++) {
		while (true) {
			char c;
			ulaz->read(&c, 1);
			if (c == '\0')break;
			s += c;
		}
		podaci_O_Simbolu *pod = podaci_O_Simbolu::dohvatiIzFajla(ulaz);
		(*(ret->tabela))[s] = pod;
		s = "";
	}
	return ret;
}

std::ostream& operator<<(std::ostream& os, const tabela_Simbola& dt)
{
	std::unordered_map<std::string, podaci_O_Simbolu*>::iterator it;

	for (it = dt.tabela->begin(); it != dt.tabela->end(); it++)
	{
		os << it->first<< ':'<< it->second->dohvati_Vrijednost()<< std::endl;
	}
	return os;
}
void tabela_Simbola::popuniMapu(std::unordered_map<std::string, int>*mapa) {
	for (auto const& pair : *tabela) {
		
		if (pair.second->isLocal() == false && pair.second->isdefinisan()==true) {
			(*mapa)[pair.first]++;
		}
	}

}
int tabela_Simbola::procitajMapu(std::unordered_map<std::string, int>*mapa) {
	int ret = 0;
	for (auto const& pair : *tabela) {

		if (pair.second->isLocal() == false && pair.second->isdefinisan() == false) {
			if ((*mapa)[pair.first] == 0) {
				std::cout << "Simbol " <<pair.first <<" nije definisan" << std::endl;
				ret = 1;
			}
		}
	}
	return ret;
}
