
#ifndef operand_h
#define operand_h


#include"operand.hpp"
#include<regex>
#include<string>
#endif
class literal : public operand
{
private:

    /* data */
public:
    literal(/* args */);
    ~literal();
	static bool is_Literal(std::string s) {
		std::smatch m1;
		if (std::regex_match(s, m1, std::regex("^([0-9]+|0x[0-9a-f]{1,4})$"))) {
			return true;
		}
		return false;
	}
	static short pretvori(std::string s) {
		short ret = 0;
		if ( s.length()> 2&&s[1] == 'x') {

			for (int i = 2;i < s.length();i++) {
				if (s[i] - '0' < 10) {
					short tmp = s[i] - '0';
					ret |= (tmp << (s.length()-1 - i)*4);
				}
				else {

					short tmp = s[i] - 'A'+10;
					ret |= (tmp << ((s.length() - 1 - i)*4));
				}
			}
		}

		else
		{
			ret= atoi(s.c_str());
		}
		return ret;
	}
};

