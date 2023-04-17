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
#include "parser.h"

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
	//	VARS
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	/*
    User::Tokenizer cl_my_instance;
	std::cout << cl_my_instance.get_error();

    cl_my_instance.parse( "4Y=3X" );

	std::cout << "Create a Binary Operator token\n";
    User::Token *pcl_token = new User::Binary_operator();


	std::cout << "Destroy a Binary Operator token\n";
	//This only calls the Token Destructor
	//delete pcl_token;
	//This calls also the destructor of Binary Operator
    delete (User::Binary_operator *)pcl_token;


    User::Equation cl_my_equation;
    cl_my_equation.gpcl_root = pcl_token;
    */

    //unit test the token array parser
	int n_fail = unit_test_parse_token_array();
	DPRINT("Failed test patterns: %d\n", n_fail );
	std::cout << "Unit Test: parser token array |:" << n_fail << "\n";

	//User::Equation_parser cl_equation;

	//Empty equation
	//cl_equation.parse( "" );
	//Unbalanced Open
	//cl_equation.parse( "((1)" );
	//Unbalanced Close
	//cl_equation.parse( "(1))" );
	//redundant priority token
	//cl_equation.parse( "(1)" );
	//cl_equation.parse( "(((((1)))))" );
	//Equation
	//cl_equation.parse( "1=1" );
	//Equation
	//cl_equation.parse( "5=2+3" );
	//Equation
	//cl_equation.parse( "1+4=2+3" );
	//Equation Simple (OK)
	//cl_equation.parse( "x*1.000=y*2" );
	//Equation Harder (OK)
	//cl_equation.parse( "x*1.000=((pippo+1.2)+(y+.233)*2)*0.001" );
	//Test unary operators
	//cl_equation.parse( "x*(-1.000)=(-y+.233)*2" );
    //harder with unary and diff
	//cl_equation.parse( "((-x)*(-1.000))=((-pippo-1.2)+(y-.233)*2)*(-0.001)" );
	//Function are just symbols with arguments! Already work with current parser
	//cl_equation.parse( "y=sin(x)" );
	//Tree operation: merge sum operation.
	//cl_equation.parse( "y=8+8+8" );
	//Tree operation: merge sum operation. Preserve tree
	//cl_equation.parse( "y=8+(9+10+23*2)+(x*y)" );
	//Tree operation: merge sum operation, turn all diffs into sums.
	//cl_equation.parse( "y=(-1+2+3+4-5-6-7+8)" );

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN();
	return false; //OK
}	//end function: Dummy | bool

/****************************************************************************
**	@brief Function
**	f | bool
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

	User::Equation_parser cl_equation_parser;

	//----------------------------------------------------------------
	//	INIT
	//----------------------------------------------------------------

	//count the test patterns that failed the check
	int n_cnt_fail = 0;
	struct St_test_pattern
	{
	    const char *s_equation;
	    bool x_fail;
	    std::vector<std::string> as_token_vector;
	};
    //Create the test patterns with validation patterns
	St_test_pattern ast_test_pattern[] =
	{
	    //Empty string
	    St_test_pattern{ "", false, std::vector<std::string>() },
	    //Unbalanced brackets
	    St_test_pattern{ "(1", true, std::vector<std::string>() },
	    St_test_pattern{ "((1)", true, std::vector<std::string>() },
	    St_test_pattern{ "(1))", true, std::vector<std::string>() },
	    //Balanced bracket
	    St_test_pattern{ "((((((1))))))", false, std::vector<std::string>( { std::string("1") } ) },
	    //Sum, Equations equation
        St_test_pattern{ "1=1", false, std::vector<std::string>( { std::string("1"), std::string("="), std::string("1") } ) },
        St_test_pattern{ "5=2+3", false, std::vector<std::string>( { std::string("5"), std::string("="), std::string("2"), std::string("+"), std::string("3") } ) },
        St_test_pattern{ "1+4=2+3", false, std::vector<std::string>( { std::string("1"), std::string("+"), std::string("4"), std::string("="), std::string("2"), std::string("+"), std::string("3") } ) },
	};
    //
	size_t n_num_test_equations = sizeof( ast_test_pattern )/ sizeof(St_test_pattern);
	std::cout << "Test patterns: " << n_num_test_equations << "\n";
	DPRINT("Number of test patterns %d\n", int(n_num_test_equations) );

	//----------------------------------------------------------------
	//	BODY
	//----------------------------------------------------------------
	//! @details algorithm:

	//For all test patterns
	for (size_t n_test_pattern_index = 0; n_test_pattern_index < n_num_test_equations;n_test_pattern_index++)
	{
	    DPRINT("PATTERN%d\n", int(n_test_pattern_index) );
		//Feed the test pattern
		bool x_fail = cl_equation_parser.parse( ast_test_pattern[n_test_pattern_index].s_equation );
		//If expected fail state
		if (x_fail == ast_test_pattern[n_test_pattern_index].x_fail)
		{
			//Get the array of string tokens
			std::vector<std::string> ras_array_token = cl_equation_parser.get_array_of_token();

			size_t n_num_tokens = ras_array_token.size();
			//if not
			if (n_num_tokens == ast_test_pattern[n_test_pattern_index].as_token_vector.size())
			{
				for (size_t n_array_token_index = 0;n_array_token_index < n_num_tokens;n_array_token_index++)
				{
				    DPRINT("TOKEN%d\n", int(n_array_token_index) );
                    if (ast_test_pattern[n_test_pattern_index].as_token_vector[n_array_token_index] != ras_array_token[n_array_token_index])
                    {
                        DPRINT("ERR: Pattern: %d | Token %d | WRONG TOKEN expected >%s< got >%s<\n", int(n_test_pattern_index), int(n_array_token_index), ast_test_pattern[n_test_pattern_index].as_token_vector[n_array_token_index].c_str(), ras_array_token[n_array_token_index].c_str() );
                        n_cnt_fail++;
                        //Stop
                        n_array_token_index = n_num_tokens;
                    }

				}
			}
			else
			{

				std::cout << "ERR Pattern " << n_test_pattern_index << " FAIL: Inconsistent token count\n";
				DPRINT("ERR: Pattern: %d | TOKEN COUNT expected %d | measured %d\n", n_test_pattern_index, as_token_vector[n_test_pattern_index].size(), n_num_tokens );
				n_cnt_fail++;
			}
		}
		//if expected fail state
		else
		{
			std::cout << "ERR Pattern " << n_test_pattern_index << " FAIL | Inconsistent fail\n";
			DPRINT("ERR: FAIL test pattern: %d\n", n_test_pattern_index );
			n_cnt_fail++;
		}
	}   //For all test patterns

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN_ARG("Failed test patterns: %d", n_cnt_fail);
	return n_cnt_fail; //OK
}	//end function: Dummy | bool
