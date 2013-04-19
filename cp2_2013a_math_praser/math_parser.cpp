#include "math_parser.h"

       
math_parser::math_parser()
{
   err = false;
   op_count = 0;
}
      
math_parser::~math_parser()
{
}     

bool math_parser::AddOperator(string name, int priority, direction dir, float (*func)(float, float))
{
   oper op;
   op.name = name;
   op.priority = priority;
   op.dir = dir;
   op.func = func;
   ops.push_back(op);
   op_count++;

   return true;
}

bool math_parser::IsOperator(string ch, oper * op)
{
   oper tmp = {"", -1, (direction)-1, 0};
   *op = tmp;
   bool IsOperator = false;
   for(int i = 0; i < op_count; i++)
   {
      if(ops[i].name == ch)
      {
         IsOperator = true;
         *op = ops[i];
         break;
      }
   }
   return IsOperator;
}

vector<string> math_parser::ConvertToONP(string exp)
{
   vector<string> out;
   vector<string> stack;
   int length = exp.size();
   string ch;
   string ch2;
   for(int i = 0; i < length; i++)
   {
      ch = exp[i];
      if(atoi(ch.c_str()) <= 9 && (atoi(ch.c_str()) > 0 || ch == "0"))
      {
         // char is an number
         ch2 = exp[++i];
         string c = ch;
         while(atoi(ch2.c_str()) <= 9 && (atoi(ch2.c_str()) > 0 || ch2 == "0" || ch2 == "."))
         {
            c += ch2;
            ch2 = exp[++i];
            continue;
         }
         i--;
         out.push_back(c);
      }
      else if(atoi(ch.c_str()) <= 'z' && atoi(ch.c_str()) >= 'a')
      {
         // char is an variable or function
      }
      else if(ch == ",")
      {
         // char is an breaker
         while(stack[stack.size()-1] != "(")
         {
            out.push_back(stack[stack.size()-1]);
            stack.pop_back();
         }
      }
      else if(ch == "(")
      {
          stack.push_back(ch);
      }
      else if(ch == ")")
      {
         while(stack[stack.size()-1] != "(")
         {
            out.push_back(stack[stack.size()-1]);
            stack.pop_back();
         }
         stack.pop_back();
      }
      else
      {
         // char is an operator
         oper cur;
         IsOperator(ch, &cur); // geting current operator to cur variabler
          
         if(stack.size() <= 0)
         {
            // ther are no operators on stack
            stack.push_back(ch);
            continue;
         }
            
         oper op;
         // untiln stack contatinc proper operator
         while(IsOperator(stack[stack.size()-1], &op) == true)
         {
            if((cur.dir == (direction)0 && cur.priority <= op.priority) || (cur.dir == (direction)1 && cur.priority < op.priority))
            {
               out.push_back(stack[stack.size()-1]);
               stack.pop_back();
            }
            else
               break; 
            if(stack.size() <= 0)
            {
               break;
            }
         }
         stack.push_back(ch);
      }
   }
   while(stack.size() > 0)
   {
      // adding everything to the output
      out.push_back(stack[stack.size()-1]);
      stack.pop_back();
   }
                
   return out;
}

string math_parser::Parse(string exp)
{
   vector <string> symbols = ConvertToONP(exp);
   vector <string> stack;
       
   for(int i = 0; i < symbols.size(); i++)
   {
      string sym = symbols[i];
      oper op;
      if(atoi(sym.c_str()) > 0 || sym == "0")
      {
         stack.push_back(sym);
      }
      else if(IsOperator(sym, &op))
      {
         string a = stack[stack.size()-1];
         stack.pop_back();
         string b = stack[stack.size()-1];
         stack.pop_back();
         // checking for dividing by zero
         if((op.name == "/")&&(atof(a.c_str()) == 0)) return " ! error: dividing by zero";
         float ret = (*op.func)(atof(b.c_str()), atof(a.c_str()));
         char buf[10];
         gcvt(ret, 3,buf);
         stack.push_back(buf);
      }
      else
      {
      }
   }
   string ret = "";
   ret = stack[0];
   return ret;
}

