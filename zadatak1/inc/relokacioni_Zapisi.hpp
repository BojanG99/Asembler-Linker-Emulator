#pragma once
#include<iostream>
#include <vector>

class podaci_O_Relokacionom_Zapisu;
class relokacioni_Zapisi
{
private:
    std::vector< podaci_O_Relokacionom_Zapisu*> *zapisi;
public:
    relokacioni_Zapisi(/* args */);
    ~relokacioni_Zapisi();
	int velicina();
    void ubaciZapis(podaci_O_Relokacionom_Zapisu*);
	void popuniOfajl(std::ofstream*);
	friend std::ostream& operator<<(std::ostream& os, const relokacioni_Zapisi& dt);
};

