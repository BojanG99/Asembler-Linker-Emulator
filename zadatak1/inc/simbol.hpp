#ifndef operand_h
#define operand_h


#include"operand.hpp"
#endif
#include<string>
#include<regex>
class simbol : public operand
{
private:
    /* data */
public:
    simbol(/* args */);
    ~simbol();
	static bool is_Simbol(std::string s) {
		std::smatch m1;
		if (std::regex_match(s, m1, std::regex("^(r[0-7]|pc|psw|sp)$"))) {
			return true;
		}
		return false;
	}

	

};

simbol::simbol(/* args */)
{
}

simbol::~simbol()
{
}
