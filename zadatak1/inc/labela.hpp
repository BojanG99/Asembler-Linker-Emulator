#include<string>
class labela
{
private:
    std::string naziv;
public:
    labela(std::string);
    ~labela();
    std::string dohvati_Naziv(){return naziv;}
};

