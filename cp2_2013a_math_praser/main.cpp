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

    string exp;
    math_parser mp;
    mp.AddOperator("+", 1, (direction)0, addition);
    mp.AddOperator("-", 1, (direction)0, difference);
    mp.AddOperator("*", 2, (direction)0, product);
    mp.AddOperator("/", 2, (direction)0, quotien);

    while(true)
    {
        cout << " > write the expression " << endl;
        cout << "   (to see example type \"example\", to quit write \"quit\")" << endl;
        cout << " : "; cin >> exp;

        for (int i = 0; i < exp.length(); i++)
        {
            exp[i] = tolower(exp[i]);
        }

        if(exp == "quit") return 0;
        else if(exp == "example")
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
                    exp.erase(i, 1);
                    i = -1;
                }
            }
            if(exp.empty())
            {
                cout << " ! erro: wrong expresion" << endl;
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
    }

    return 0;
}