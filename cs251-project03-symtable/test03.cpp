//
// A symtable unit test based on Catch framework
//
// << DANIELA CHAVEZ >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

#include <iostream>
#include "symtable.h"
#include "catch.hpp"
using namespace std;

TEST_CASE("(3) Testing..") 
{
	symtable<string, string>  table; /* Creating a new table */
	
	REQUIRE(table.size() == 0); /*Because no scope has been created, then the size should be zero*/
	REQUIRE(table.numscopes() == 0); /* No existing scopes, the total number of elements is zero*/ 

	/*This scope will store information of animals and their classification.
	 * The key would be the name of animals.
	 * The value would be their classification */
	
	table.enterScope("Animals"); /* Name of the new scope */
	table.insert("Panda Bear", "Mammal");
	table.insert("Turtle", "Reptile");
	table.insert("Spider", "Arachnid");
	table.insert("Toad", "Amphibians");
	
	REQUIRE(table.size() == 4);
	REQUIRE(table.numscopes() == 1);
	
	/*This scope will store information of a dish and their country of origin.
	 * The key would be the name of the dish.
	 * The value would be the country of origin */
	
	table.enterScope("Dishes"); /* Name of the new scope */
	table.insert("Lomo Saltado", "Peru");
	table.insert("Tacos al Pastor", "Mexico");
	table.insert("Cobbler", "England");
	table.insert("Bruschetta", "Italy");
	table.insert("Vaca Fita", "Cuba");
	table.insert("Moqueca", "Brazil");
	table.insert("Jollof Rice", "Nigeria");
	
	REQUIRE(table.size() == 11);
	REQUIRE(table.numscopes() == 2);
	
	/*This scope will store information color names and their initial.
	 * The key would be the initial letter of a color.
	 * The value would be the color name */
	
	table.enterScope("Colors"); /* Name of the new scope */
	table.insert("G", "Green");
	table.insert("P", "Pink");
	
	REQUIRE(table.size() == 13);
	REQUIRE(table.numscopes() == 3);
	
	
	/* In this part of the test, I will be testing the lookup function*/
	string symbol;
	REQUIRE(table.lookup("G", symbol, symtable<string, string>::ScopeOption::CURRENT));
	REQUIRE(table.lookup("Turtle", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(table.lookup("Moqueca", symbol, symtable<string, string>::ScopeOption::ALL));
	
	/*Exit from the current scope */
	table.exitScope();
	REQUIRE(table.lookup("Vaca Fita", symbol, symtable<string, string>::ScopeOption::CURRENT));
	REQUIRE(table.lookup("Toad", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(table.size() == 11);
	REQUIRE(table.numscopes() == 2);
	REQUIRE((!table.lookup("Panda Bear", symbol, symtable<string, string>::ScopeOption::CURRENT)));
	
	
	
	/*Going back to the current scope*/
	
	
}