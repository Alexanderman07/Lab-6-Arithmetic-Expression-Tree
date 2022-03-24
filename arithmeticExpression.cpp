#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <fstream>
#include "arithmeticExpression.h"
using namespace std;

arithmeticExpression::arithmeticExpression(const string & m)
{
//TreeNode* root = NULL;
infixExpression = m;
}

void arithmeticExpression::buildTree()
{
  stack<TreeNode*> list;
  char key = 'a';
  string postfixExpression = infix_to_postfix();
  char c;
  for(unsigned int i = 0; i < postfixExpression.length(); i++)
  {
    c = postfixExpression.at(i);
    if(c != '(' && c != '*' && c != '/' && c != '+' && c != '-' && c != ')')
    {
      struct TreeNode* Addtostack = new TreeNode(c, key++);
      list.push(Addtostack);
    }
    else 
    {
      struct TreeNode* Addtostack = new TreeNode(c, key++);
      Addtostack -> right = list.top();
      list.pop();
      Addtostack -> left = list.top();
      list.pop();
      list.push(Addtostack);
    }
  }
  root = list.top();
}

void arithmeticExpression::infix()
{
  infix(root);
}

void arithmeticExpression::prefix()
{
  prefix(root);
}

void arithmeticExpression::postfix()
{
  postfix(root);
}

int arithmeticExpression::evaluate()
{
  if(!isValidIntegerExpression(root))
  {
    throw invalid_argument("expression not valid");
  }
  return evaluateIntegerExpression(root);
}

void arithmeticExpression::infix(TreeNode *n)
{
    if(n)
    {
      if(n->left)
      {
        cout << "(";
      }
      infix(n -> left);
      cout << n -> data;
      infix(n -> right);
      if(n->right)
      {
        cout << ")";
      }
    }
}

void arithmeticExpression::prefix(TreeNode *n)
{
  if(n)
  {
    cout << n -> data;
    prefix(n -> left);
    prefix(n -> right);
  }
}

void arithmeticExpression::postfix(TreeNode *n)
{
  if(n)
  {
    postfix(n -> left);
    postfix(n -> right);
    cout << n -> data;
  }
}

bool arithmeticExpression::isValidIntegerExpression(TreeNode *n)
{
if(n== nullptr)
  {
    return false;
  }
  if(n -> data >= '0' && n -> data <= '9') //if n is an integer
  {
    return true;
  }
  if(n->data == '*' || n->data == '/' || n->data == '+' || n->data == '-')
  {
    bool left = isValidIntegerExpression(n->left);
  bool right = isValidIntegerExpression(n->right);
  if(left == true && right == true)
  {
    return true;
  }
  else
  {
    return false;
  }
 }
  return false;
}

int arithmeticExpression::evaluateIntegerExpression(TreeNode *n)
{
  int left_val, right_val;

  if(n->data >= '0' && n->data <= '9')
  {
    return n->data - 48;
  }
  left_val = evaluateIntegerExpression(n->left);
  right_val = evaluateIntegerExpression(n->right);
  if(n->data == '*')
  {
    return left_val * right_val;
  }
  if(n->data == '/')
  {
    return left_val / right_val;
  }
  if(n->data == '+')
  {
    return left_val + right_val;
  }
  if(n->data == '-')
  {
    return left_val - right_val;
  }
  return 0;
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){
 if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
else{
 oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}
