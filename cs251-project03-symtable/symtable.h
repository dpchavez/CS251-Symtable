/*symtable.h*/

// 
// << Daniela Chavez >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #03: symtable
//
// Symbol Table: a symbol table is a stack of scopes, typically used by a
// compiler to keep track of symbols in a program (functions, variables,
// types, etc.).  In most programming languages, you "enter scope" when you 
// see {, and "exit scope" when you see the corresponding }.  Example:
//
// int main()
// {              <-- enterScope()
//    int i;      <-- enter "i" into symbol table as type "int"
//    .
//    .
//    while (true)
//    {              <-- enterScope()
//       char i;     <-- enter "i" into symbol table as type "char"
//
// Notice there are two variables named "i", which is legal because
// they are in different scopes.
//

#pragma once

#include <iostream>
#include <deque>
#include <map>

using namespace std;

template<typename KeyT, typename SymbolT>
class symtable
{
public:
  //
  // A symbol table is a stack of scopes.  Every scope has a name, and 
  // we use a map to hold the symbols in that scope.  You can *add* to
  // this class, but you must use the Name and Symbols as given to store
  // the scope name, and scope symbols, respectively.
  //
  class Scope
  {
  public:
    string              Name;
    map<KeyT, SymbolT>  Symbols;

    // constructors:
    Scope()
    {
      // default empty string and an empty map:
    }

    Scope(string name)
    {
      this->Name = name;
      // empty map created by map's constructor:
    }
  };

private:
  int counter = 0;
  deque<Scope>myScopes;

public:
  enum class ScopeOption
  {
    ALL, 
    CURRENT,
    GLOBAL
  };

  //
  // default constructor:
  //
  // Creates a new, empty symbol table.  No scope is open.
  //
  symtable()
  {
    // TODO: note that member variables will have their default constructor 
    // called automatically, so there may be nothing to do here.
  }

  // size()
  // Returns total # of symbols in the symbol table.
  // Complexity: O(1)
  int size() const
  {
    return counter; 
  }

  
  // numscopes
  // Returns the # of open scopes.
  // Complexity: O(1) ---> no loops
  //
  int numscopes() const
  { 
  //Returns the number of scopes
    return myScopes.size();
  }

  //
  // enterScope
  //
  // Enters a new, open scope in the symbol table, effectively "pushing" on
  // a new scope.  You must provide a name for the new scope, although
  // the name is currently used only for debugging purposes.
  //
  // NOTE: the first scope you enter is known as the GLOBAL scope, since this
  // is typically where GLOBAL symbols are stored.  
  //
  // Complexity: O(1) ---> no loops
  //
  void enterScope(string name)
  {
	Scope newScope; //creating a new scope
	newScope.Name = name; //assigning the name of the new scope to the string parameter
    myScopes.push_front(newScope); //pushing the new scope inside of myScopes

  }

  //
  // exitScope
  //
  // Exits the current open scope, discarding all symbols in this scope.
  // This effectively "pops" the symbol table so that it returns to the 
  // previously open scope.  A runtime_error is thrown if no scope is 
  // currently open.  
  //
  // Complexity: O(1)
  //
  void exitScope()
  {
  
   if(myScopes.size() == 0){ //If the deque is empty, then throw invalid argument
	   throw invalid_argument("Symtable::exitScope: Currently empty");
	   }
   else{ //if the deque isnt empty, then decrease the counter and pop the head of the deque
	   counter -= myScopes.front().Symbols.size();
	   myScopes.pop_front();
	   }	   
  }

  //
  // curScope 
  //
  // Returns a copy of the current scope.  A runtime_error is thrown if
  // no scope is currently open.
  // Complexity: O(N) where N is the # of symbols in the current scope
  //
  Scope curScope() const
  {
    if (myScopes.empty()){ //if the scope is empty, then trhow an invalid argument
		throw invalid_argument("Symtable::exitScope: Currently empty");
	}
	else{ //if the scope isnt empty, then return the first scope 
		return myScopes.front(); 
	}
  }

  //
  // insert
  //
  // Inserts the (key, symbol) pair in the *current* scope.  If the key
  // already exists in the current scope, the associated symbol is replaced
  // by this new symbol.
  // Complexity: O(lgN) where N is the # of symbols in current scope
  //
  void insert(KeyT key, SymbolT symbol)
  {
   if (myScopes.front().Symbols.count(key) == 1){ //if the key exists within the scope,
	   myScopes.front().Symbols.at(key) = symbol; //then update its current symbol
	   }
	   
   else{
	   myScopes.front().Symbols.emplace(key, symbol); //If the key doesnt exist in the scope
	   counter++;                                     //then create the new key and symbol as you increase the counter
	   }
	   
  }

  //
  // lookup
  //
  // Searches the symbol table for the first (key, symbol) pair that 
  // matches the given key.  The search starts in the current scope, and 
  // proceeds "outward" to the GLOBAL scope.  If a matching (key, symbol)
  // pair is found, true is returned along with a copy of the symbol (via 
  // "symbol" reference parameter).  If not found, false is returned and
  // the "symbol" parameter is left unchanged.
  //
  // NOTE: the search can be controlled by the "option" parameter.  By 
  // default, the entire symbol table is searched as described above.
  // However, the search can also be limited to just the current scope, 
  // or just the GLOBAL scope, via the "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   string                   symbol;
  //   bool                     found;
  //   ...
  //   found = table.lookup("i", 
  //                        symbol, 
  //                        symtable<string,string>::ScopeOption::CURRENT);
  //
  // Complexity: O(SlgN) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  bool lookup(KeyT key, 
              SymbolT& symbol, 
              ScopeOption option = ScopeOption::ALL) const
  {
	  if (option == ScopeOption::CURRENT){  //Checking at the current scope at the front
		  if (myScopes.front().Symbols.count(key) == 1){ //If the key that we want to find exists in the scope
			  symbol = myScopes.front().Symbols.at(key); //We assign symbol with the value at that key
			  return true;
		   }
	    }
	  
	  else if(option == ScopeOption::GLOBAL){ //Checking at the last scope at the tail
		  if (myScopes.back().Symbols.count(key) == 1){ //If the key that we want to find exists in the scope
			  symbol = myScopes.back().Symbols.at(key); //We assign symbol with the value at that key
			  return true;
		  }
	   }
      
	  else{
		  for (int i = 0; i < myScopes.size(); i++){
			  if (myScopes[i].Symbols.count(key) == 1){ //If the key that we want to find exists in the scope
			  symbol = myScopes[i].Symbols.at(key); //We assign symbol with the value at that key
			  return true;
			  }
		  }
	  }
	  
    return false; //default if nothing has been found
  }

  //
  // dump
  // 
  // Dumps the contents of the symbol table to the output stream, 
  // starting with the current scope and working "outward" to the GLOBAL
  // scope.  You can dump the entire symbol table (the default), or dump
  // just the current scope or global scope; this is controlled by the 
  // "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   ...
  //   table.dump(std::cout, symtable<string,string>::ScopeOption::GLOBAL);
  //
  // Complexity: O(S*N) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  void dump(ostream& output, ScopeOption option = ScopeOption::ALL) const
  {
    output << "**************************************************" << endl;

    if (option == ScopeOption::ALL){
	  output << "*************** SYMBOL TABLE (ALL) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
	  
	  for (int i = 0; i < myScopes.size(); i++){
	  	  output << "** "<<myScopes[i].Name<< " **" << endl;
		  for (pair<KeyT, SymbolT>newScopes: myScopes[i].Symbols){
			output << newScopes.first << ": " << newScopes.second << endl;
		  }
		}
	
	}
      
		
    else if (option == ScopeOption::CURRENT){
	  output << "*************** SYMBOL TABLE (CUR) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
	  output << "** "<<myScopes.front().Name<< " **" << endl;
	  for (pair<KeyT, SymbolT>newScopes: myScopes.front().Symbols){
			output << newScopes.first << ": " << newScopes.second << endl;
	  }
	}
      
		  
    else {
	  output << "*************** SYMBOL TABLE (GBL) ***************" << endl;
      output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
	  output << "** "<<myScopes.back().Name<< " **" << endl;
	  for (pair<KeyT, SymbolT>newScopes: myScopes.back().Symbols){
		  output << newScopes.first << ": " << newScopes.second << endl;
	  }
	
	
	}// global:
      

    //
    // output format per scope:
    //
    // ** scopename **
    // key: symbol
    // key: symbol
    // ...
    //

    output << "**************************************************" << endl;
  }

};
