/****************************************************************
**	OrangeBot Project
*****************************************************************
**        /
**       /
**      /
** ______ \
**         \
**          \
*****************************************************************
**	Symbolic Equation Solver
*****************************************************************
**  Tokenizer: Transform a string into an equation
****************************************************************/

/****************************************************************
**	DESCRIPTION
****************************************************************
**
****************************************************************/

/****************************************************************
**	HISTORY VERSION
****************************************************************
**
****************************************************************/

/****************************************************************
**	KNOWN BUGS
****************************************************************
**
****************************************************************/

/****************************************************************
**	TODO
****************************************************************
**
****************************************************************/

/****************************************************************
**	INCLUDES
****************************************************************/

//Standard C Libraries
#include <cstdio>
//#include <cstdlib>

//Standard C++ libraries
#include <iostream>
//#include <array>
//#include <vector>
//#include <queue>
//#include <string>
//#include <fstream>
//#include <chrono>
//#include <thread>

//OS Libraries
//#define _WIN32_WINNT 0x0500	//Enable GetConsoleWindow
//#include <windows.h>

//User Libraries
//Include user log trace
#define ENABLE_DEBUG
#include "debug.h"

//#include "tokenizer.h"
#include "equation.h"
//Header with the test pattern arrays to be fed to the unit tests
#include "st_test_pattern.hpp"

/****************************************************************
**	NAMESPACES
****************************************************************/

//Never use a whole namespace. Use only what you need from it.
using std::cout;
using std::endl;

/****************************************************************
**	DEFINES
****************************************************************/

/****************************************************************
**	MACROS
****************************************************************/

/****************************************************************
**	PROTOTYPES
****************************************************************/

extern bool test_bench( void );

extern int unit_test_parse_token_array( void );

extern bool unit_test_equation_solver( void );

/****************************************************************
**	GLOBAL VARIABILES
****************************************************************/

//User::Dummy my_class;

/****************************************************************
**	FUNCTIONS
****************************************************************/

/****************************************************************************
**	@brief main
**	main |
****************************************************************************/
//! @return int |
//! @details Entry point of program
/***************************************************************************/

int main()
{
	//Start Debugging. Show function nesting level 0 and above
	DSTART( 0 );
	//Trace Enter main
	DENTER();

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------

	cout << "OrangeBot Projects\n";
	//print in the 'debug.log' file. works just like a fully featured printf
	DPRINT("OrangeBot Projects\n");

	test_bench();

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return from main
	DRETURN();
	//Stop Debugging
	DSTOP();

    return 0;
}	//end function: main

/****************************************************************************
**	@brief Function
**	test_bench | bool
****************************************************************************/
//! @return bool |
//! @details test_bench for the code
/***************************************************************************/

bool test_bench( void )
{
	//Trace Enter with arguments
	DENTER();
	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	//Convert a test pattern array into a .csv file, test St_test_pattern::save and St_test_pattern::load
	if (false)
	{
		/*
		std::vector<St_test_pattern> vst_test_pattern;
		for (size_t n_index = 0; n_index < sizeof( ast_test_pattern )/ sizeof(St_test_pattern);n_index++)
		{
			vst_test_pattern.push_back( ast_test_pattern[n_index] );
		}
		std::cout <<  "Test patterns: " << vst_test_pattern.size() << "\n";
		St_test_pattern::save( vst_test_pattern, "xxx.csv" );

		std::vector<St_test_pattern> ast_loaded_test_pattern;
		ast_loaded_test_pattern = St_test_pattern::load( std::string("xxx.csv") );

		St_test_pattern::save( ast_loaded_test_pattern, "yyy.csv" );
		*/
	}

	//Single Equation. Parse it, reverse translate it, and write it on a .csv file
	if (true)
	{
		//Virgin vector of test patterns
		std::vector<User::St_test_pattern> ast_test_pattern;
		//Append a note and an equation to the vector of test patterns
		std::string s_user_note			= "Mix operators of different priority";
		//std::string s_equation 			= "Y=1+(3*X)+2-(5*sephiroth -100 +101)+4";
		//std::string s_equation_reverse	= "Y=(1+((3*X)+(2-((5*(sephiroth-(100+101)))+4))))";
		//std::string s_equation 			= "Y=3*4-5+6";
		//std::string s_equation_reverse	= "Y=(3*(4-(5+6)))";
		//std::string s_equation_expected	= "Y=(((3*4)-5)+6)";
		std::string s_equation 			= "4=1-2+3-4+5-6+7";
		std::string s_equation_reverse	= "Y=(3*(4-(5+6)))";
		std::string s_equation_expected	= "Y=(((3*4)-5)+6)";


		//If I have operators of different priority, I have to resolve first LOWER priority operators, so that higher priority gets at the bottom in tree reconstruction
		User::St_test_pattern::append_string_equation( ast_test_pattern, s_user_note, s_equation );


		//It got wrong the priority of operator *
		//Save all patterns on file
		User::St_test_pattern::save( ast_test_pattern, std::string("equation.csv") );
	}

	if (false)
	{
		//unit test the token array parser
		int n_fail = unit_test_parse_token_array();
		DPRINT("Failed test patterns: %d\n", n_fail );
		std::cout << "----------------------------------------------------------------\n";
		std::cout << "Unit Test: Failed patterns:" << n_fail << "\n";
		std::cout << "----------------------------------------------------------------\n";
	}

	//Develop the equation solver
	if (false)
	{
		unit_test_equation_solver();
	}

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN();
	return false; //OK
}	//end function: Dummy | bool

/****************************************************************************
**	@brief unit_test_parse_token_array | void
****************************************************************************/
//! @param f bool
//! @return bool |
//! @details
//! runs a number of unit tests on the equation solver
//! feed a string, manually create a token array, and checks that the two are the same.
/***************************************************************************/

int unit_test_parse_token_array( void )
{
	//Trace Enter with arguments
	DENTER_ARG("in: %d\n", 0);

	//----------------------------------------------------------------
	//	VARS
	//----------------------------------------------------------------

	User::Equation cl_equation_parser;

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//count the test patterns that failed the check
	int n_cnt_fail_tokenizer = 0;
	int n_cnt_fail_treeificator = 0;
	int n_cnt_fail = 0;
	//Remember which pattern failed
	std::vector<int> an_index_failed_tokenizer;
	std::vector<int> an_index_failed_treeificator;
	std::vector<int> an_index_failed_pattern;

	//Load the test patterns
	std::vector<User::St_test_pattern> ast_test_pattern;
	ast_test_pattern = User::St_test_pattern::load( "test_patterns_parser.csv" );
	size_t n_num_test_equations = ast_test_pattern.size();
	std::cout << "Test patterns: " << n_num_test_equations << "\n";
	DPRINT("Number of test patterns %d\n", int(n_num_test_equations) );

	//OBSOLETE: Number of test patterns. when I was defining the test patterns in a .h file. Now the test pattern structures loads from a .csv
	//size_t n_num_test_equations = sizeof( ast_test_pattern )/ sizeof(St_test_pattern);

	//Result test patterns, save the result in another test pattern structure to later save them to file
	std::vector<User::St_test_pattern> ast_test_pattern_result;

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	//For all test patterns
	for (size_t n_test_pattern_index = 0; n_test_pattern_index < n_num_test_equations;n_test_pattern_index++)
	{
		std::cout << "----------------------------------------------------------------\n";
		std::cout << "PATTERN: " << int(n_test_pattern_index) << " | " << ast_test_pattern[n_test_pattern_index].s_user_note << "\n";
		std::cout << "Equation: "<< ast_test_pattern[n_test_pattern_index].s_equation << "\n";
	    DPRINT("PATTERN%d >%s<\n", int(n_test_pattern_index), ast_test_pattern[n_test_pattern_index].s_equation.c_str() );
		//Array of string tokens resulting from the parsing
	    std::vector<std::string> as_string_token;
		//Array of tokens resulting from parsing. A token is the parsed version of the string that build a token, and can be manipulated inside a tree.
		std::vector<User::Equation::Token> ast_token;
		//Feed the test pattern
		bool x_fail = cl_equation_parser.parse( ast_test_pattern[n_test_pattern_index].s_equation, as_string_token, ast_token );
		//If expected fail state
		if (x_fail == ast_test_pattern[n_test_pattern_index].x_fail)
		{
			//Allocate the result
			User::St_test_pattern st_pattern_result;
			//Number of string tokens decoded by parse
			size_t n_num_tokens = as_string_token.size();
			//if good tokenizer size
			if (n_num_tokens == ast_test_pattern[n_test_pattern_index].as_string_token.size())
			{
				//Scan string tokens
				for (size_t n_array_token_index = 0;n_array_token_index < n_num_tokens;n_array_token_index++)
				{
				    DPRINT("TOKEN%d - %s\n", int(n_array_token_index), as_string_token[n_array_token_index].c_str() );
                    if (ast_test_pattern[n_test_pattern_index].as_string_token[n_array_token_index] != as_string_token[n_array_token_index])
                    {
						std::cout << "ERR Pattern " << n_test_pattern_index << " FAIL: Wrong token | expected: " << ast_test_pattern[n_test_pattern_index].as_string_token[n_array_token_index].c_str() << " | got: " << as_string_token[n_array_token_index].c_str() << "\n";
                        DPRINT("ERR: Pattern: %d | Token %d | WRONG TOKEN expected >%s< got >%s<\n", int(n_test_pattern_index), int(n_array_token_index), ast_test_pattern[n_test_pattern_index].as_string_token[n_array_token_index].c_str(), as_string_token[n_array_token_index].c_str() );
                        n_cnt_fail++;
                        n_cnt_fail_tokenizer++;
                        an_index_failed_tokenizer.push_back( n_test_pattern_index );
                        an_index_failed_pattern.push_back(n_test_pattern_index );
                        //Stop
                        n_array_token_index = n_num_tokens;
                    }
				}
			}
			//if tokenizer failure
			else
			{
				std::cout << "ERR Pattern " << n_test_pattern_index << " FAIL: Inconsistent token count | expected: " << ast_test_pattern[n_test_pattern_index].as_string_token.size() << " | got: " << n_num_tokens << "\n";
				DPRINT("ERR%d: Pattern: %d | TOKEN COUNT expected %d | measured %d\n", __LINE__, n_test_pattern_index, ast_test_pattern[n_test_pattern_index].as_string_token.size(), n_num_tokens );
				n_cnt_fail++;
				n_cnt_fail_tokenizer++;
				an_index_failed_tokenizer.push_back( n_test_pattern_index );
				an_index_failed_pattern.push_back(n_test_pattern_index );

				//Show the expected and the got tokenizer side by side
				DPRINT_TAB();
				DPRINT_NOTAB("Parsed   | ");
				for (auto an_iterator_parsed = as_string_token.begin();an_iterator_parsed != as_string_token.end();an_iterator_parsed++)
				{
					DPRINT_NOTAB("\t>%s<", (*an_iterator_parsed).c_str() );
				}
				DPRINT_NOTAB("\n");
				DPRINT_TAB();
				DPRINT_NOTAB("Expected | ");
				for (auto an_iterator_expected = ast_test_pattern[n_test_pattern_index].as_string_token.begin();an_iterator_expected != ast_test_pattern[n_test_pattern_index].as_string_token.end();an_iterator_expected++)
				{
					DPRINT_NOTAB("\t>%s<", (*an_iterator_expected).c_str() );
				}
				DPRINT_NOTAB("\n");
			}
			//Get the tree representation of the equation
			User::Tree<User::Equation::Token> cl_tree_from_equation = cl_equation_parser.get_tree_of_token();
			//if the parser passed, I should have a tree
			if (x_fail == false)
			{

				std::cout << "parsed equation in tree form:\n";
				cl_tree_from_equation.show(0);
				//Construct a tree from the test pattern
				std::cout << "tree constructed from test pattern:\n";
				User::Tree<User::Equation::Token> cl_tree_from_test_pattern = User::Tree<User::Equation::Token>( ast_test_pattern[n_test_pattern_index].ast_minimal_node );
				cl_tree_from_test_pattern.link_decorator( cl_tree_from_equation.get_decorator() );
				cl_tree_from_test_pattern.show(0);
				//tree from parsing is the same as tree from test pattern
				if (cl_tree_from_equation == cl_tree_from_test_pattern)
				{
					//Do a reverse translation from tree to string, it can be slighly different to input equation due to open/close operators or rounding
					std::string s_tree_reverse_translation = cl_equation_parser.to_string();
					//Reverse translation is the same as the test pattern expected reverse translation
                    if (ast_test_pattern[n_test_pattern_index].s_equation_decoded == s_tree_reverse_translation)
                    {
						std::cout << "PASS pattern: "  << n_test_pattern_index << "\n";
						DPRINT("PASS pattern: %d\n", n_test_pattern_index );
                    }
                    else
                    {
						//Bad reverse translation
						std::string s_message = "ERR: " +std::to_string( __LINE__ )+ " | Pattern: " + std::to_string(n_test_pattern_index);
						std::cerr << s_message << "\n";
						DPRINT("%s\n", s_message.c_str() );
					}



				}
				else
				{
					std::cout << "ERR Pattern " << n_test_pattern_index << " FAIL | Tree from parsing is not the same as tree from test pattern\n";
					DPRINT("ERR%d: FAIL TREE | Test pattern: %d\n", __LINE__, n_test_pattern_index );
					n_cnt_fail++;
					n_cnt_fail_treeificator++;
					an_index_failed_treeificator.push_back( n_test_pattern_index );
					an_index_failed_pattern.push_back(n_test_pattern_index );

					//Parsed tree of tokens
					std::vector<User::Equation::Token> ast_tree_token_parsed;
					for (auto an_iterator_parsed = cl_tree_from_equation.begin();an_iterator_parsed != cl_tree_from_equation.end();an_iterator_parsed++)
					{
						ast_tree_token_parsed.push_back( (*an_iterator_parsed).t_payload );
					}
					//Expected tree of tokens
					std::vector<User::Equation::Token> ast_tree_token_expected;
					for (auto an_iterator_expected = cl_tree_from_test_pattern.begin();an_iterator_expected != cl_tree_from_test_pattern.end();an_iterator_expected++)
					{
						ast_tree_token_expected.push_back( (*an_iterator_expected).t_payload );
					}

					DPRINT_TAB();
					DPRINT_NOTAB("Tree Parsed   | ");
					for (auto an_iterator = ast_tree_token_parsed.begin();an_iterator != ast_tree_token_parsed.end();an_iterator++)
					{
						DPRINT_NOTAB("\t>%s<", (*an_iterator).to_string() );
					}
					DPRINT_NOTAB("\n");
					DPRINT_TAB();
					DPRINT_NOTAB("Tree Expected | ");
					for (auto an_iterator = ast_tree_token_expected.begin();an_iterator != ast_tree_token_expected.end();an_iterator++)
					{

						DPRINT_NOTAB("\t>%s<", (*an_iterator).to_string() );
					}
					DPRINT_NOTAB("\n");
				}
			}
			//if parser failed and I have a tree
			else
			{
				if (cl_tree_from_equation.size() <= 1)
				{
					std::cout << "PASS pattern: "  << n_test_pattern_index << "\n";
					DPRINT("PASS pattern: %d\n", n_test_pattern_index );
				}
				else
				{
					std::cout << "ERR Pattern " << n_test_pattern_index << " FAIL | A failed parsing has a tree\n";
					DPRINT("ERR: FAIL test pattern: %d\n", n_test_pattern_index );
					n_cnt_fail++;
					an_index_failed_pattern.push_back(n_test_pattern_index );
				}
			}
		}	//If expected fail state
		//if expected fail state
		else
		{
			std::cout << "ERR Pattern " << n_test_pattern_index << " FAIL | Inconsistent fail\n";
			DPRINT("ERR: FAIL test pattern: %d\n", n_test_pattern_index );
			n_cnt_fail++;
			an_index_failed_pattern.push_back(n_test_pattern_index );
		}
	}   //For all test patterns

	User::St_test_pattern::save( ast_test_pattern, "output.csv" );

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	std::cout << "Number of Patterns: " << n_num_test_equations << "\n";
	for (size_t n_test_pattern_index = 0; n_test_pattern_index < n_num_test_equations;n_test_pattern_index++)
	{
		std::cout << "PATTERN" << int(n_test_pattern_index) << " | " << ast_test_pattern[n_test_pattern_index].s_equation<< "\n";
	}

	std::cout << "Failed Tokenizations: " << n_cnt_fail_tokenizer << "\n";
	for (auto cl_iterator = an_index_failed_tokenizer.begin();cl_iterator!=an_index_failed_tokenizer.end();cl_iterator++)
	{
		std::cout << *cl_iterator << " | ";
	}
	std::cout << "\n\n";

	std::cout << "Failed Treeifications: " << n_cnt_fail_treeificator << "\n";
	for (auto cl_iterator = an_index_failed_treeificator.begin();cl_iterator!=an_index_failed_treeificator.end();cl_iterator++)
	{
		std::cout << *cl_iterator << " | ";
	}
	std::cout << "\n\n";

	std::cout << "Failed Patterns: " << n_cnt_fail << "\n";
	for (auto cl_iterator = an_index_failed_pattern.begin();cl_iterator!=an_index_failed_pattern.end();cl_iterator++)
	{
		std::cout << *cl_iterator << " | ";
	}
	std::cout << "\n\n";
	//Trace Return vith return value
	DRETURN_ARG("Failed test patterns: %d", n_cnt_fail);
	return n_cnt_fail; //OK
}	//unit_test_parse_token_array | void

#include "equation_solver.h"

bool unit_test_equation_solver( void )
{
	User::Equation_solver cl_equation;

	cl_equation.load( "1=1" );

	cl_equation.preprocess_tree();

}
