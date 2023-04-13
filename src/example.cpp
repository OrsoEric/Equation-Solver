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

	User::Equation_parser cl_equation;

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
	cl_equation.parse( "1=1" );
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
//! dummy method to copy the code
/***************************************************************************/

bool f( bool f )
{
	//Trace Enter with arguments
	DENTER_ARG("in: %d\n", 0);

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

	//----------------------------------------------------------------
	//	RETURN
	//----------------------------------------------------------------

	//Trace Return vith return value
	DRETURN_ARG("out: %d\n", 0);
	return false; //OK
}	//end function: Dummy | bool
