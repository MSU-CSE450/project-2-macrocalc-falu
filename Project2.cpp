#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Below are some suggestions on how you might want to divide up your project.
// You may delete this and divide it up however you like.
#include "ASTNode.hpp"
#include "lexer.hpp"
#include "SymbolTable.hpp"


int main(int argc, char * argv[])
{
  if (argc != 2) {
    std::cout << "Format: " << argv[0] << " [filename]" << std::endl;
    exit(1);
  }

  std::string filename = argv[1];
  
  std::ifstream in_file(filename);              // Load the input file
  if (in_file.fail()) {
    std::cout << "ERROR: Unable to open file '" << filename << "'." << std::endl;
    exit(1);
  }

  // TO DO:  
  // PARSE input file to create Abstract Syntax Tree (AST).
  // EXECUTE the AST to run your program.

  emplex::Lexer lexer;
  std::unordered_map<std::string, float> symbolTable;
  std::vector<emplex::Token> out_tokens = lexer.Tokenize(in_file);
  int i = 0;
  for(auto token: out_tokens)
  {
      i++;
      if (lexer.TokenName(token.id) == "VAR" && symbolTable.count(token.lexeme) == 0)
      {
          symbolTable.insert(std::make_pair(token.lexeme, std::numeric_limits<double>::quiet_NaN()));
      }
  }

  // Main AST Node
  ASTNode parent = ASTNode("STATEMENT_BLOCK", "ROOT");
  int token_id = 0;
  while (token_id < out_tokens.size())
  {
    
    if (out_tokens[token_id] == emplex::Lexer::ID_VAR)
    {
      ASTNode var_branch = ASTNode("VAR", out_tokens[token_id].lexeme);
      var_branch.AddParent(parent);
      parent.AddChild(var_branch);

    }
    token_id++;
  }
  //SymbolTable tab = SymbolTable();
  //parent.Run(tab);
  
}
