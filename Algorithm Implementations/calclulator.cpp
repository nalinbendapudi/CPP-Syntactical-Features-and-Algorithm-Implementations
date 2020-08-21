// run with C++11

#include <iostream>
#include<string>
#include<cstring>

using namespace std;

double eval(string xxx)
{

    string tok = ""; // Do parantheses first
    for (int i = 0; i < xxx.length(); i++)
    {
        if (xxx[i] == '(')
        {
            int iter = 1;
            string token;
            i++;
            while (true)
            {
                if (xxx[i] == '(')
                {
                    iter++;
                } else if (xxx[i] == ')')
                {
                    iter--;
                    if (iter == 0)
                    {
                        i++;
                        break;
                    }
                }
                token += xxx[i];
                i++;
            }
            cout << "(" << token << ")" << " == " << to_string(eval(token)) <<  endl;
            tok += to_string(eval(token));
        }
        tok += xxx[i];
    }

    for (int i = 0; i < tok.length(); i++)
    {
        if (tok[i] == '+')
        {
			cout << tok.substr(i+1, tok.length()-(i+1)-1) + " + " +  tok.substr(tok.length()-(i+1)-1,tok.length()) << " = " << eval(tok.substr(i+1, tok.length()-(i+1)-1)) +  eval(tok.substr(tok.length()-(i+1)-1,tok.length())) << endl;
            return eval(tok.substr(i+1, tok.length()-(i+1)-1)) + eval(tok.substr(tok.length()-1,tok.length()));
        } else if (tok[i] == '-')
        {
            //cout << tok.substr(0, i) + " - " +  tok.substr(i+1, tok.length()-i-1) << " == " << eval(tok.substr(0, i)) - eval(tok.substr(i+1, tok.length()-i-1)) << endl;
            return eval(tok.substr(0, i)) - eval(tok.substr(i+1, tok.length()-i-1));
        }
    }

    for (int i = 0; i < tok.length(); i++)
    {
        if (tok[i] == '*')
        {
            //cout << tok.substr(0, i) + " * " +  tok.substr(i+1, tok.length()-i-1) << " == " << eval(tok.substr(0, i)) * eval(tok.substr(i+1, tok.length()-i-1)) << endl;
            return eval(tok.substr(0, i)) * eval(tok.substr(i+1, tok.length()-i-1));
        } else if (tok[i] == '/')
        {
            //cout << tok.substr(0, i) + " / " +  tok.substr(i+1, tok.length()-i-1) << " == " << eval(tok.substr(0, i)) / eval(tok.substr(i+1, tok.length()-i-1)) << endl;
            return eval(tok.substr(0, i)) / eval(tok.substr(i+1, tok.length()-i-1));
        }
    }

    //cout << stod(tok.c_str()) << endl;
    return stod(tok.c_str()); // Return the value...
}



int main() {
	string inputString;
	cin>>inputString;
	
	string s; // Get Rid of Spaces
    for (int i = 0; i < inputString.length(); i++)
    {
        if (inputString[i] != ' ')
        {
            s += inputString[i];
        }
    }
	
	cout<<eval(s)<<endl;
	
	
	
	
	
	return 0;
}