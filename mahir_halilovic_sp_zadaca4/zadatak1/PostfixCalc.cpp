#pragma once

#include <sstream>
#include "PostfixCalc.hpp"

int PostfixCalc::parse(std::string &s) {
  std::istringstream ss(s);
  std::string op;

  while(ss >> op) {
    if(isnumber(op)) rpn.push(std::stoi(op));
    else if(isoperator(op)) calculate(op);
  }

  int temp = rpn.top();
  rpn.pop();
  return temp;
}

bool PostfixCalc::isnumber(const std::string &s) {
  if(s[0] == '-') 
    return isnumber(s.substr(1, s.length() - 1));
  for(const char &c : s)
    if(!isdigit(c)) return false;

  return true;
}

bool PostfixCalc::isoperator(const std::string &s) {
  return s == "+" || s == "-" || s == "*" || s == "/";
}

void PostfixCalc::calculate(const std::string &s) {
  if(rpn.size() < 2) throw std::out_of_range{"Not enough operands!"};

  int rOp = rpn.top();
  rpn.pop();
  int lOp = rpn.top();
  rpn.pop();
  
  switch(s[0]) {
    case '+':
      rpn.push(lOp + rOp);
      break;
    case '-':
      rpn.push(lOp - rOp);
      break;
    case '*':
      rpn.push(lOp * rOp);
      break;
    case '/':
      if(rOp == 0) throw std::out_of_range{"Division by zero is not allowed."};
      rpn.push(lOp / rOp);
      break;
    default:
      throw std::out_of_range{"Invalid operand!"};
  }
}
