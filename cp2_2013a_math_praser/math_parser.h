#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cctype>

using namespace std;

typedef enum
{
    left,
    right
} direction;

class math_parser
{
private:
    struct oper
    {
        string name;
        int priority;
        direction dir;
        float(*func)(float, float);
    };

    vector<oper> ops;
    int op_count;
    bool err;

    bool IsOperator(string ch, oper *op);
    vector <string> ConvertToONP(string exp);

public:
    math_parser(void);
    ~math_parser(void);
    bool AddOperator(string name, int priority, direction dir, float(*func)(float, float));
    float Parse(string exp);
};