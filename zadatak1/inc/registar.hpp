#include"operand.hpp"
#include<string>
class registar : public operand
{
private:
    /* data */
public:
    registar(/* args */);
    ~registar();
	static bool is_registar(std::string) {
		
		return true;
	}
	static int dohvatiRegistar(std::string str){
		if (str == "r0")return 0;
		else if (str == "r1")return 1;
		else if (str == "r2")return 2;
		else if (str == "r3")return 3;
		else if (str == "r4")return 4;
		else if (str == "r5")return 5;
		else if (str == "r6")return 6;
		else if (str == "r7")return 7;
		return 8;
	}
};


