#pragma once

#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include "SymbolTable.hpp"

class ASTNode {



private:
  // PLACE AST NODE INFO HERE.
  std::vector<std::shared_ptr<ASTNode>> children;
  std::shared_ptr<ASTNode> parent = nullptr;
  std::string type;
  std::string value;
  
public:
  // CONSTRUCTORS, ETC HERE.
  // Constructor
  ASTNode(const std::string &type, const std::string &value)
  {
    this->parent = nullptr;
    this->type = type;
    this->value = value;
  }

  ~ASTNode(){;}
  //Add parent pointer
  void AddParent(ASTNode &node)
  {
    parent = std::make_shared<ASTNode>(node);
  }

  // CAN SPECIFY NODE TYPE AND ANY NEEDED VALUES HERE OR USING OTHER FUNCTIONS.
  // Return type of node
  std::string GetType(){return(type);}
  // Return value of node
  std::string GetValue(){return(value);}


  // CODE TO ADD CHILDREN AND SETUP AST NODE HERE.
  // Adds child to node, adds to left child then right child
  void AddChild(ASTNode &node) 
  { 
    if (children[0] == nullptr)
    {
      children[0] = std::make_shared<ASTNode>(node);
    }
    else if (children[1] == nullptr)
    {
      children[1] = std::make_shared<ASTNode>(node);
    }
    else if (type == "VAR")
    {
      std::cerr << "Node already has children" << std::endl;
    }
  }
  
  // CODE TO EXECUTE THIS NODE (AND ITS CHILDREN, AS NEEDED).
  double Run(SymbolTable & symbols) 
  {
    if (type == "VAR")
    {
      return (symbols.GetValue(GetValue()));
    }
    else if (type == "CONSTANT")
    {
      return(std::stod(value));
    }
    else if (type == "OPERATOR")
    {
      if (value == "+")
      {
        return(children[0]->Run(symbols) + children[1]->Run(symbols));
      }
      if (value == "-")
      {
        return(children[0]->Run(symbols) - children[1]->Run(symbols));
      }
      if (value == "*")
      {
        return(children[0]->Run(symbols) * children[1]->Run(symbols));
      }
      if (value == "/")
      {
        if (children[1]->Run(symbols) == 0)
        {
          std::cerr << "Division by zero error" << std::endl;
          exit;
        }
        return(children[0]->Run(symbols) / children[1]->Run(symbols));
      }
    }
  }

};
