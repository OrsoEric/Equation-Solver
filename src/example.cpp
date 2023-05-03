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
	std::cout << "----------------------------------------------------------------\n";
	std::cout << "Unit Test: Failed patterns:" << n_fail << "\n";
	std::cout << "----------------------------------------------------------------\n";

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
		//User adds a note to the test pattern explaining what it's testing
		const char *s_user_note;
		//Equation fed to the parser
	    const char *s_equation;
	    //Expected result of the parser. true=FAIL | false=PASS
	    bool x_fail;
	    //Expected string tokens after a successful parse
	    std::vector<std::string> as_token_vector;
	    //Expected tree structure after a successful parse
	    std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node> ast_minimal_node;
	};
	// conversion from 'User::Tree<User::Equation_parser::Token>::St_minimal_node' to non-scalar type 'std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node, std::allocator<User::Tree<User::Equation_parser::Token>::St_minimal_node> >' requested|
	const User::Tree<User::Equation_parser::Token>::St_minimal_node cst_default_equal =
	{
		User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("="), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
	};

    //Create the test patterns alongside the expected result of the pattern. Can detect a misbehaviour of the parser
	St_test_pattern ast_test_pattern[] =
	{
	    St_test_pattern{ "Empty String (FAIL)", "", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>( { cst_default_equal, } ) },
	    St_test_pattern{ "Lack of equal sign (FAIL)", "1", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>( { cst_default_equal, } ) },
	    St_test_pattern{ "Unbalanced brackets L (FAIL)", "(1", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>( { cst_default_equal, } ) },
	    St_test_pattern{ "Unbalanced brackets R (FAIL)", "1(", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>( { cst_default_equal, } ) },
	    St_test_pattern{ "Unbalanced brackets L (FAIL)", "((1)", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>( { cst_default_equal, } ) },
	    St_test_pattern{ "Two equal signs (FAIL)", "1=1=1", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>( { cst_default_equal, } ) },
	    St_test_pattern
	    {
			"Balanced bracket (PASS)",
			"1=((((((1))))))",
			false,
			std::vector<std::string>
			(
				{
					std::string("1"),
					std::string("="),
					std::string("("),
					std::string("("),
					std::string("("),
					std::string("("),
					std::string("("),
					std::string("("),
					std::string("1"),
					std::string(")"),
					std::string(")"),
					std::string(")"),
					std::string(")"),
					std::string(")"),
					std::string(")")
				}
			),
			std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>
			(
				{
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("="), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("1"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("1"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				}
			),

		},
        St_test_pattern
        {
			"Two Number Equation (PASS)",
			"1=1",
			false,
			std::vector<std::string>
			(
				{
					std::string("1"),
					std::string("="),
					std::string("1")
				}
			),
			std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>
			(
				{
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("="), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("1"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("1"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				}
			),
		},
		St_test_pattern
        {
			"Three Number Equation (PASS)",
			"5=2+3",
			false,
			std::vector<std::string>
			(
				{
					std::string("5"),
					std::string("="),
					std::string("2"),
					std::string("+"),
					std::string("3"),
				}
			),
			std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>
			(
				{
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("="), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("5"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("+"), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("2"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("3"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				}
			),
		},

		St_test_pattern
        {
			"Four Number Equation (PASS)",
			//Source equation string to be fed
			"1+4=2+3",
			//Expected failure state
			false,
			//Expected output of the tokenizer
			std::vector<std::string>
			(
				{
					std::string("1"),
					std::string("+"),
					std::string("4"),
					std::string("="),
					std::string("2"),
					std::string("+"),
					std::string("3"),
				}
			),
			//Expected output of the treeficator
			std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>
			(
				{
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("="), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("+"), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("+"), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("1"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 1, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("4"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 1, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("2"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("3"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				}
			),
		},
		//Add symbols to equation
		St_test_pattern
        {
			"One Symbol Equation (PASS)",
			//Source equation string to be fed
			"X=1",
			//Expected failure state
			false,
			//Expected output of the tokenizer
			std::vector<std::string>
			(
				{
					std::string("X"),
					std::string("="),
					std::string("1"),
				}
			),
			//Expected output of the treeficator
			std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>
			(
				{
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("="), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("X"), User::Equation_parser::Token_type::BASE_SYMBOL, 0, 0, false, }, 00, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("1"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				}
			),
		},
		//! @todo * is higher priority than +, but is parsed in wrong order without brackets
		//Add more symbols to equation
		St_test_pattern
        {
			"Three Symbol Equation (PASS)",
			//Source equation string to be fed
			"3*X=(5*Y)+C",
			//Expected failure state
			false,
			//Expected output of the tokenizer
			std::vector<std::string>
			(
				{
					std::string("3"),
					std::string("*"),
					std::string("X"),
					std::string("="),
					std::string("("),
					std::string("5"),
					std::string("*"),
					std::string("Y"),
					std::string(")"),
					std::string("+"),
					std::string("C"),
				}
			),
			//Expected output of the treeficator
			std::vector<User::Tree<User::Equation_parser::Token>::St_minimal_node>
			(
				{
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("="), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("*"), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("+"), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("3"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 1, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("X"), User::Equation_parser::Token_type::BASE_SYMBOL, 0, 0, false, }, 1, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("*"), User::Equation_parser::Token_type::BASE_OPERATOR, 0, 0, false, }, 2, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("C"), User::Equation_parser::Token_type::BASE_SYMBOL, 0, 0, false, }, 2, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("5"), User::Equation_parser::Token_type::BASE_NUMBER, 0, 0, false, }, 5, },
					User::Tree<User::Equation_parser::Token>::St_minimal_node{ User::Equation_parser::Token{ std::string("Y"), User::Equation_parser::Token_type::BASE_SYMBOL, 0, 0, false, }, 5, },

				}
			),
		},
	};	//Test pattern array
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
		std::cout << "----------------------------------------------------------------\n";
		std::cout << "PATTERN: " << int(n_test_pattern_index) << " | " << ast_test_pattern[n_test_pattern_index].s_user_note << "\n";
		std::cout << "Equation: "<< ast_test_pattern[n_test_pattern_index].s_equation << "\n";
	    DPRINT("PATTERN%d >%s<\n", int(n_test_pattern_index), ast_test_pattern[n_test_pattern_index].s_equation );
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
						std::cout << "ERR Pattern " << n_test_pattern_index << " FAIL: Wrong token | expected: " << ast_test_pattern[n_test_pattern_index].as_token_vector[n_array_token_index].c_str() << " | got: " << ras_array_token[n_array_token_index].c_str() << "\n";
                        DPRINT("ERR: Pattern: %d | Token %d | WRONG TOKEN expected >%s< got >%s<\n", int(n_test_pattern_index), int(n_array_token_index), ast_test_pattern[n_test_pattern_index].as_token_vector[n_array_token_index].c_str(), ras_array_token[n_array_token_index].c_str() );
                        n_cnt_fail++;
                        //Stop
                        n_array_token_index = n_num_tokens;
                    }
				}
			}
			else
			{
				std::cout << "ERR Pattern " << n_test_pattern_index << " FAIL: Inconsistent token count | expected: " << ast_test_pattern[n_test_pattern_index].as_token_vector.size() << " | got: " << n_num_tokens << "\n";
				DPRINT("ERR: Pattern: %d | TOKEN COUNT expected %d | measured %d\n", n_test_pattern_index, ast_test_pattern[n_test_pattern_index].as_token_vector.size(), n_num_tokens );
				n_cnt_fail++;
			}
			//Get the tree representation of the equation
			User::Tree<User::Equation_parser::Token> cl_tree_from_equation = cl_equation_parser.get_tree_of_token();
			//if the parser passed, I should have a tree
			if (x_fail == false)
			{

				std::cout << "parsed equation in tree form:\n";
				cl_tree_from_equation.show(0);
				//Construct a tree from the test pattern
				std::cout << "tree constructed from test pattern:\n";
				User::Tree<User::Equation_parser::Token> cl_tree_from_test_pattern = User::Tree<User::Equation_parser::Token>( ast_test_pattern[n_test_pattern_index].ast_minimal_node );
				cl_tree_from_test_pattern.link_decorator( cl_tree_from_equation.get_decorator() );
				cl_tree_from_test_pattern.show(0);
				//tree from parsing is the same as tree from test pattern
				if (cl_tree_from_equation == cl_tree_from_test_pattern)
				{
					//Do nothing
					std::cout << "PASS pattern: "  << n_test_pattern_index << "\n";
					DPRINT("PASS pattern: %d\n", n_test_pattern_index );
				}
				else
				{
					std::cout << "ERR Pattern " << n_test_pattern_index << " FAIL | Tree from parsing is not the same as tree from test pattern\n";
					DPRINT("ERR: FAIL test pattern: %d\n", n_test_pattern_index );
					n_cnt_fail++;
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
				}
			}
		}	//If expected fail state
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
