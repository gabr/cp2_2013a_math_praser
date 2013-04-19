#include "math_parser.h"

float addition(float a, float b)
{
    return a + b;
}

float difference(float a, float b)
{
    return a - b;
}

float product(float a, float b)
{
    return a * b;
}

float quotien(float a, float b)
{
    return a / b;
}

int main(int argc, char *argv[])
{

    bool parameter = false;

    string exp;
    if(argc == 2)
    {
        parameter = true;
        exp = string(argv[1]);
    }

    if(exp == "-h" || exp == "--help")
    {
        cout << "math parser" << endl;
        cout << "Arkadiusz Gabrys" << endl;
        cout << "Macrocourse Sem 2 Group 2" << endl;
        cout << endl;
        cout << "\tStart program without parameters to see" << endl;
        cout << "\tuser prompt or type expression as a parameter" << endl;
        cout << "\tto see the result without others program outputs." << endl;
        cout << endl;
        return 0;
    }

    math_parser mp;
    mp.AddOperator("+", 1, (direction)0, addition);
    mp.AddOperator("-", 1, (direction)0, difference);
    mp.AddOperator("*", 2, (direction)0, product);
    mp.AddOperator("/", 2, (direction)0, quotien);

    while(true)
    {
        if(!parameter)
        {
            cout << " > write the expression " << endl;
            cout << "   (to see example type \"example\", to quit write \"quit\")" << endl;
            cout << " : "; cin >> exp;
        }

        for (int i = 0; i < exp.length(); i++)
        {
            exp[i] = tolower(exp[i]);
        }

        if(exp == "quit" && !parameter) return 0;
        else if(exp == "example" && !parameter)
        {
            cout << "(2*(19-3)+1)/2 = " << mp.Parse("(2*(19-3)+1)/2") << endl;
            continue;
        }
        else
        {
        // cuting off all inappropriate chars
            for (int i = 0; i < exp.length(); i++)
            {
                if(!(exp[i] == '+' ||
                     exp[i] == '-' ||
                     exp[i] == '*' ||
                     exp[i] == '/' ||
                     exp[i] == '(' ||
                     exp[i] == ')' ||
                    (exp[i] >= '0'  && exp[i] <= '9')))
                {
                    if(!(i > 1 && i+1 < exp.length() &&
                        (exp[i-1] >= '0'  && exp[i-1] <= '9') &&
                        (exp[i+1] >= '0'  && exp[i+1] <= '9') &&
                        exp[i] == '.'))
                    {
                        exp.erase(i, 1);
                        i = -1;
                    }
                }
            }
            if(exp.empty())
            {
                cout << " ! error: wrong expression" << endl;
                if(parameter) return 1;
                continue;
            }
            else{
                // counting parentheses
                int left, right;
                left = right = 0;
                for (int i = 0; i < exp.length(); i++)
                {
                    if(exp[i] == '(') ++left;
                    if(exp[i] == ')') ++right;
                }
                if(left != right)
                {
                    cout <<" ! error: something wrong with parentheses" << endl;
                    if(parameter) return 1;
                    continue;
                }

                // looking for leading '-'
                if(exp[0] == '-') exp = "0"+exp;
                for (int i = 1; i < exp.length(); i++)
                {
                    if(exp[i] == '-'
                        && (exp[i-1] < '0' || exp[i-1] > '9')
                        && (exp[i-1] != '(' && exp[i-1] != ')'))
                        exp.insert(i-1, "0");
                }

                cout << exp << "=" << mp.Parse(exp) << endl;
            }
        }
        if(parameter) break;
    }

    return 0;
}