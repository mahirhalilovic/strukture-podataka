#pragma once
#include <iostream>
#include <stack>

bool isopenbracket(char c) {
  return c == '{' || c == '[' || c == '(' || c == '<';
}

bool isclosedbracket(char c) {
  return c == '}' || c == ']' || c == ')' || c == '>';
}

bool boltic() {
  std::stack<char> input;
  char c;

  while(std::cin >> c) {
    if(!input.size() && isopenbracket(c)) input.push(c);
    if((c == '<') ||
       (c == '(' && input.top() != '<') ||
       (c == '[' && input.top() != '<' && input.top() != '(') ||
       (c == '{' && input.top() != '<' && input.top() != '(' && input.top() != '[')) input.push(c);
    else if(isclosedbracket(c)) {
      if((input.top() == '{' && c == '}') ||
         (input.top() == '[' && c == ']') ||
         (input.top() == '(' && c == ')') ||
         (input.top() == '<' && c == '>')) input.pop();
      else
        return false;
    }
  }

  return true;
}


