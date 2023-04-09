// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char symbol) {
  switch (symbol) {
  case '(':
    return 1;
  case ')':
    return 1;
  case '+':
    return 2;
  case '-':
    return 2;
  case '*':
    return 3;
  case '/':
    return 3;
  case ' ':
    return -100;
  }
  return -1;
}

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack;
  std::string output = "";
  int pr = 0;
  int prOnHeight = -1;
  for (auto& op : inf) {
    pr = prior(op);
    prOnHeight = prior(stack.get());
    if (op == '\n') { 
      while (getPrior(stack.get()) > 1) {
        output += stack.pop();
        output += " ";
      }
      stack.pop();
    }
    if (pr == -1) { /* 2. chislo*/
      output += op;
      output += " ";
    } else if (pr == 0) { /* 3. skobka ( */
      stack.push(op);
    } else if (pr == 1) {
      while (prior(stack.get()) > 0) {
       output += stack.pop();
       output += " ";
      }
      stack.pop();
    } else if (pr > prOnHeight || stack.isEmpty()) {
      stack.push(op);
    } else if (pr <= prOnHeight && pr > 1) {
      while (prior(stack.get()) > 1) {
        output += stack.pop();
        output += " ";
      }
      stack.push(op);
    }
  }
  while (prior(stack.get()) > 1) {
      output += stack.pop();
      output += " ";
  }
  std::string out = "";
  for (int i = 0; i < output.length()-1; ++i) {
    out += output[i];
  }
  return out;
}
int znachOpertat(int a, int b, char operat) {
  switch (operat) {
  case '+':
    return a+b;
  case '-':
    return a-b;
  case '*':
    return a*b;
  case '/':
    return a/b;
  }
  return 0;
}
int eval(std::string pref) {
  TStack<int, 100> stack1;
  int per = 0;
  int pr = 0;
  for (auto& operat : pref) {
    pr = prior(operat);
    if (pr == -100) { //space
      continue;
    }
    if (pr == -1) { //number
      stack1.push(operat-48);
    } else {
      int phu = 0;
      while (!(stack1.isEmpty()+phu)) {
          phu += 1;
      int a = stack1.pop();
      int b = stack1.pop();
      per = znachOpertat(b, a, operat);
      stack1.push(per);
      }
    }
  }
  return stack1.pop();
}
