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

std::ostream& operator<<(std::ostream& os, const tabela_Simbola& dt)
{
	std::unordered_map<std::string, podaci_O_Simbolu*>::iterator it;

	for (it = dt.tabela->begin(); it != dt.tabela->end(); it++)
	{
		os << it->first<< ':'<< it->second->dohvati_Vrijednost()<< std::endl;
	}
	return os;
}