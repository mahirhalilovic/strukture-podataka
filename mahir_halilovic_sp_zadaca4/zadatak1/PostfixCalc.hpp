#include <iostream>
#include <stack>

class PostfixCalc{
  public:
    int parse(std::string&);

  private:
    std::stack<int> rpn;
    void calculate(const std::string&);
    bool isnumber(const std::string&);
    bool isoperator(const std::string&);
};
