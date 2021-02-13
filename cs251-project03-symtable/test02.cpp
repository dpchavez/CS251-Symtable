//
// A symtable unit test based on Catjavascript:void(0)ch framework
//
// << YOUR NAME >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable
//

#include <iostream>
#include "symtable.h"
#include "catch.hpp"
using namespace std;

TEST_CASE("(2) Testing size() and numscopes() functions") 
{
	symtable<string, string>  table; /* Creating a new table */
	
	REQUIRE(table.size() == 0); /*Because no scope has been created, then the size should be zero*/
	REQUIRE(table.numscopes() == 0); /* No existing scopes, the total number of elements is zero*/ 

	/*This scope will store information of some makeup brands I am familiar with.
	 * The key would be the name of the cosmetics brand.
	 * The value would be the nane of a certain product */
	
	table.enterScope("Makeup Brands and Products"); /* Name of the new scope */
	table.insert("KVD Beauty", "Tattoo Liner");
	table.insert("Jefree Star Cosmetics", "Royal Blue Pallet");
	table.insert("Too Faced", "Pretty As a Peach");
	table.insert("Anastasia Beverly Hills", "The Norvina Pallet");
	table.insert("ColorPop Cosmetics", "Blush Crush Pallet");
	
	REQUIRE(table.size() == 5); /* New number of total elements */
	REQUIRE(table.numscopes() == 1); /* New number of total scopes */
	
	
	/*This is a new scope. This will store name of some countries as their key.
	 * As a value, it will be storing the name of a city*/
	
	table.enterScope("Countries and Cities"); /* Name of the new scope */
	table.insert("Italy", "Venice");
	table.insert("USA", "New York");
	table.insert("Peru", "Lima");
	
	REQUIRE(table.size() == 8); /* New number of total elements */
	REQUIRE(table.numscopes() == 2); /* New number of total scopes */
	
	/* This will be the part where we delete the current scope we are currently at.
	 * The size and number of scopes should decrease */
	table.exitScope();
	REQUIRE(table.size()== 5);
	REQUIRE(table.numscopes() == 1);
}