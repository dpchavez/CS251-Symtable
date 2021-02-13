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

TEST_CASE("(4) Testing..") 
{
	string symbol;
	symtable<string, string>  table; /* Creating a new table */
	
	table.enterScope("Animals"); /* Name of the new scope */
	table.insert("D", "Dog");
	table.insert("C", "Cat");
	table.insert("E", "Eagle");
	
	/* Insert new value, same key */
	table.insert("C", "Camel");
	
	REQUIRE(table.size() == 3);
	REQUIRE(table.numscopes() == 1);
	
	/*Checking for the name*/
	REQUIRE(table.curScope().Name == "Animals");
	
	table.enterScope("Colleges"); /* Name of the new scope */
	table.insert("u", "UIC");
	table.insert("c", "Columbia");
	table.insert("e", "Eastern Illiois");
	table.insert("h", "Harvard");
	table.insert("o", "Oxford");
	
	REQUIRE(!table.lookup("D", symbol, symtable<string, string>::ScopeOption::CURRENT));
	REQUIRE(!table.lookup("u", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	
	/*Insert new value, same key*/
	table.insert("u", "University of Iowa");
	REQUIRE(table.size() == 8);
	REQUIRE(table.numscopes() == 2);
	REQUIRE(!table.lookup("BH Cosmetics", symbol, symtable<string, string>::ScopeOption::CURRENT));
	
	/*Checking for the name*/
	REQUIRE(table.curScope().Name == "Colleges");
	REQUIRE(table.lookup("D", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	
	table.enterScope("Names"); /* Name of the new scope */
	table.insert("G", "Gloria");
	table.insert("P", "Patricia");
	table.insert("K", "Karla");
	table.insert("R", "Raymond");
	table.insert("N", "Nico");
	/*Inserting new value, same key*/
	table.insert("G", "Greg");
	
	REQUIRE(table.size() == 13);
	REQUIRE(table.numscopes() == 3);
	
	/* In this part of the test, I will be testing the lookup function*/
	REQUIRE(table.lookup("G", symbol, symtable<string, string>::ScopeOption::CURRENT));
	REQUIRE(table.lookup("C", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	REQUIRE(table.lookup("o", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(!table.lookup("BH Cosmetics", symbol, symtable<string, string>::ScopeOption::ALL));
	
	/*Exit from the current scope */
	table.exitScope();
	
	REQUIRE(table.size() == 8);
	REQUIRE(table.numscopes() == 2);
	
	
	/*This scope will store information of some makeup brands I am familiar with.
	 * The key would be the name of the cosmetics brand.
	 * The value would be the nane of a certain product */
	
	table.enterScope("Beauty"); /* Name of the new scope */
	table.insert("Maybelline", "Mousse Foundation");
	table.insert("BH Cosmetics", "Take Me to Brazil Pallet");
	table.insert("Ofra", "Glazed Donut");
	table.insert("Bare Minerals", "Foundation with SPF");
	
	REQUIRE(table.size() == 12); /* New number of total elements */
	REQUIRE(table.numscopes() == 3); /* New number of total scopes */
	
	
	REQUIRE(table.lookup("BH Cosmetics", symbol, symtable<string, string>::ScopeOption::ALL));
	REQUIRE(!table.lookup("UIC", symbol, symtable<string, string>::ScopeOption::GLOBAL));
	
	table.exitScope();
	table.exitScope();
	
	
	REQUIRE(table.size() == 3);
	REQUIRE(table.numscopes() == 1);
	
	REQUIRE((!table.lookup("Panda ", symbol, symtable<string, string>::ScopeOption::CURRENT)));
	REQUIRE((!table.lookup("Ofra", symbol, symtable<string, string>::ScopeOption::ALL)));
	
	table.exitScope();
	REQUIRE((!table.lookup("Ofra", symbol, symtable<string, string>::ScopeOption::ALL)));
	REQUIRE_THROWS(table.exitScope());
	
	
	
	
	
	
}