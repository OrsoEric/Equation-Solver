/**********************************************************************************
BSD 3-Clause License

Copyright (c) 2022, Orso Eric
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********************************************************************************/

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	INCLUDES
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

//--------------------------------------------------------------------------
//	DEBUGGER
//--------------------------------------------------------------------------

//Enable the file trace debugger
#define ENABLE_DEBUG
//file trace debugger
#ifdef ENABLE_DEBUG
    #include <cstdio>
    #include "debug.h"
#endif
//If DEBUG is not needed, blank out the implementations
#ifndef DEBUG_H_
    #define DEBUG_VARS_PROTOTYPES()
    #define DEBUG_VARS()
    #define DSHOW( ... )
    #define DSTART( ... )
    #define DSTOP()
    #define DTAB( ... )
    #define DPRINT( ... )
    #define DPRINT_NOTAB( ... )
    #define DENTER( ... )
    #define DRETURN( ... )
    #define DENTER_ARG( ... )
    #define DRETURN_ARG( ... )
#endif

//--------------------------------------------------------------------------
//	INCLUDES
//--------------------------------------------------------------------------

//Standard C Libraries
#include <cstdio>
//#include <cstdlib>

//Standard C++ libraries
#include <iostream>
//#include <array>
//#include <vector>
//#include <queue>
#include <string>
//#include <fstream>
//#include <chrono>
//#include <thread>

//OS Libraries
//#define _WIN32_WINNT 0x0500	//Enable GetConsoleWindow
//#include <windows.h>

//User Libraries

//Class Header
#include "parser.h"

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	NAMESPACE
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

//! @namespace custom namespace
namespace User
{

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	CONSTRUCTORS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Constructor: Equation_parser | void
/***************************************************************************/
// @param
//! @return no return
//! @details
//! \n Empty constructor
/***************************************************************************/

Equation_parser::Equation_parser( void )
{
    DENTER_ARG("This: %p", this);   //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //Initialize class vars
    this->init_class_vars();

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN();  //Trace Return
    return;
}   //Constructor: Equation_parser | void

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	DESTRUCTORS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//!	@brief Destructor: Equation_parser | void
/***************************************************************************/
// @param
//! @return no return
//! @details
//! \n Empty destructor
/***************************************************************************/

Equation_parser::~Equation_parser( void )
{
    DENTER_ARG("This: %p", this);   //Trace Enter
    //--------------------------------------------------------------------------
    //	INIT
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN();      //Trace Return
    return;         //OK
}   //Destructor: Equation_parser | void

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	PUBLIC OPERATORS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Public Operator | operator<< | const Lesson_operator_overloading &icl_rhs
/***************************************************************************/
//! @param icl_stream | reference to stream
//! @param irst_rhs | reference to structure to be streamed
//! @return std::ostream&
//! @details
//! \n Stream Token
/***************************************************************************/

std::ostream& operator<<( std::ostream& icl_stream, const Equation_parser::Token &irst_rhs )
{
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    DPRINT("Token: %c%s | Type: %d | Priority: %d\n", (irst_rhs.u1_negative)?('-'):(' '), irst_rhs.cl_str.c_str(), irst_rhs.e_type, irst_rhs.s32_open_close_priority );
    //Stream payload
    icl_stream << "Token: " << ((irst_rhs.u1_negative)?('-'):(' ')) << irst_rhs.cl_str.c_str() << " | Type: " << irst_rhs.e_type << " | Priority: " << irst_rhs.s32_open_close_priority;

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    return icl_stream;	//OK
}   //End: Public Operator |  operator<< | const Lesson_operator_overloading::Error_code ie_error_code

/***************************************************************************/
//! @brief Public Operator | operator<< | const Lesson_operator_overloading &icl_rhs
/***************************************************************************/
//! @param icl_stream | reference to stream
//! @param irclast_tokens | array of tokens
//! @return std::ostream&
//! @details
//! \n Overloads the std stream operator to print out Arrays of Tokens
/***************************************************************************/

std::ostream& operator<<( std::ostream& icl_stream, std::vector<Equation_parser::Token> &irclast_tokens )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

	//Header
    icl_stream << "Tokens ";
    DPRINT("Tokens   ");
	//Scan all tokens
    for (std::vector<Equation_parser::Token>::iterator cl_token_iterator = irclast_tokens.begin(); cl_token_iterator != irclast_tokens.end(); cl_token_iterator++ )
    {
		//Valid token
		if (cl_token_iterator->cl_str.size() > 0)
		{
			icl_stream << "|" << cl_token_iterator->cl_str.c_str();
			DPRINT_NOTAB("|%c%s", (cl_token_iterator->u1_negative)?('-'):(' '),cl_token_iterator->cl_str.c_str() );
		}
		//Empty token
		else
		{
			icl_stream << "<" << cl_token_iterator->e_type;
			DPRINT_NOTAB("<%d", cl_token_iterator->e_type );
		}
    }
    DPRINT_NOTAB("\n");
    //Show the priority in the line below
    DPRINT("Priority ");
	//Scan all tokens
    for (std::vector<Equation_parser::Token>::iterator cl_token_iterator = irclast_tokens.begin(); cl_token_iterator != irclast_tokens.end(); cl_token_iterator++ )
    {
		DPRINT_NOTAB("| %d", cl_token_iterator->s32_open_close_priority );
		//Valid token
		if (cl_token_iterator->cl_str.size() > 1)
		{

			for (unsigned int u32_cnt = 0;u32_cnt < cl_token_iterator->cl_str.size()-1;u32_cnt++)
			{
				DPRINT_NOTAB(" ");
			}
		}
    }
	DPRINT_NOTAB("\n");

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return icl_stream;	//OK
}   //End: Public Operator |  operator<< | const Lesson_operator_overloading::Error_code ie_error_code

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	PUBLIC SETTER
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Public Setter: parse | std::string |
/***************************************************************************/
//! @param icl_equation_string | string containing the equation to be parsed into a vector of string tokens
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Parse a string into a vector of string tokens. Basically slice the string into individual tokens.
//! \n Unary operators (+ and (- are tokenized at this stage, by deleting them and applying negation to the following token if needed
/***************************************************************************/

bool Equation_parser::parse( std::string is_equation )
{
    DENTER_ARG("Parse: %s | Size: %d", is_equation.c_str(), is_equation.size() ); //Trace Enter
    //--------------------------------------------------------------------------
    //	LINEAR PARSER
    //--------------------------------------------------------------------------
    //	The first pass translates a string into a vector of tokens with base token types

    //Allocate a vector for the array of token structure
    std::vector<Token> clast_tokens;
    //Try to translate an equation into an array of string tokens, and an array of token structure
    bool x_fail = this->equation_to_token_array( is_equation, this->gclacl_tokens, clast_tokens );
	if (x_fail == true)
	{
		DRETURN_ARG("ERR%d | failed to parse an equation into an array of string tokens...\n" );
		return true;
	}


	//Link the decorator for the tree to print out the token
	std::string (*f_my_decorator)(Token ist_token) = [](Token ist_token){ return ist_token.cl_str; };
	//Link the provided decorator to replace the default decorator
	this->gcl_token_tree.link_decorator( f_my_decorator );
	//Tree must be empty before conversion of token array to token tree
	if (this->gcl_token_tree.size() > 1)
	{
		DPRINT("Tree wasn't empty: %d | FLUSH\n", this->gcl_token_tree.size() );
		this->gcl_token_tree.flush();
	}
	//Recursively translate an array of token into a tree of tokens, starting from the root
	bool u1_ret = this->token_array_to_tree( clast_tokens, this->gcl_token_tree, 0 );
	if (u1_ret == true)
	{
		DRETURN_ARG("ERR:%d | Could not convert from token array to tree...", __LINE__ );
		return true;
	}
	std::cout << "Array->Tree\n";
	this->gcl_token_tree.print();
	std::cout << "--------------------------------------\n";

	//Recursively
	int s32_ret = this->aggregate_tree_token_sum_diff( this->gcl_token_tree );
	if (s32_ret < 0)
	{
		DRETURN_ARG("ERR:%d | Could not aggregate sum/diff operators into wide sum operators...", __LINE__ );
		return true;
	}
	std::cout << "Aggregate\n";
	this->gcl_token_tree.print();
	std::cout << "--------------------------------------\n";

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG( "Token array size: %d | Token tree size: %d", this->gclacl_tokens.size(), this->gcl_token_tree.size() ); //Trace Return
    return false; //OK
} //Public Setter: parse | const char * |

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	PUBLIC GETTERS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Public Getter: tree_to_equation | void |
/***************************************************************************/
//! @return std::string | string containing the literal equation reverse transated from a tree, if any
//! @details
//! \n Reverse translation of a tree of tokens back to an equation is string form
/***************************************************************************/

std::string Equation_parser::tree_to_equation( void )
{
    DENTER(); //Trace Enter
    std::string cl_str;

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------



    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG( "<%s> | %d", cl_str.c_str(), cl_str.size() ); //Trace Return
    return cl_str; //OK
}   //Public Getter: tree_to_equation | void |

/***************************************************************************/
//! @brief Public Getter: get_error | void |
/***************************************************************************/
//! @return Error_code
//! @details
//! \n Get current error state of the library
//! \n Try to recover from errors
/***************************************************************************/

const char *Equation_parser::get_error( void )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //Fetch error
    const char *err_code = this->gps8_error_code;
    //Try to recover from error
    bool f_ret = this -> error_recovery();
    //If: failed to recover
    if (f_ret == true)
    {
        //Do nothing
    }

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return err_code; //OK
}   //Public Getter: get_error | void |

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**  PUBLIC METHODS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Public method: my_public_method | void
/***************************************************************************/
// @param
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Method
/***************************************************************************/

bool Equation_parser::my_public_method( void )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	INIT
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return false;	//OK
}   //Public method: my_public_method | void

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	PRIVATE INIT
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Private Method: init_class_vars | void
/***************************************************************************/
// @param
//! @return no return
//! @details
//! \n Initialize class vars
/***************************************************************************/

bool Equation_parser::init_class_vars( void )
{
    DENTER();		//Trace Enter
    //--------------------------------------------------------------------------
    //	INIT
    //--------------------------------------------------------------------------

    this->gps8_error_code = Error_code::CPS8_OK;

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN();      //Trace Return
    return false;   //OK
}   //Private Method: init_class_vars | void

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	PRIVATE TESTER
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Private Tester: is_operator | char
/***************************************************************************/
//! @param is8_digit | digit to be tested
//! @return bool | true = digit is an operator |
//! @details
//! \n returns true if the digit is an operator token
/***************************************************************************/

bool Equation_parser::is_operator( char is8_digit )
{
    DENTER_ARG("Digit: >>%c<<", (is8_digit!='\0')?(is8_digit):(' ')  ); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------

    //Temp return
	bool u1_ret;
    switch (is8_digit)
    {
		case Token_legend::CS8_OPERATOR_EQUAL:
		case Token_legend::CS8_OPERATOR_SUM:
		case Token_legend::CS8_OPERATOR_DIFF:
		case Token_legend::CS8_OPERATOR_MUL:
		case Token_legend::CS8_OPERATOR_DIV:
		//case Token_legend::CS8_PRIORITY_OPEN:
		//case Token_legend::CS8_PRIORITY_CLOSE:
			//Operator
			u1_ret = true;
			break;
		default:
			//Not an operator
			u1_ret = false;
			break;
    }

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("%c",(u1_ret==true?'Y':'N')); //Trace Return
    return u1_ret;	//Propagate
}   //Private Tester: is_operator | char

/***************************************************************************/
//! @brief Private Tester: is_symbol | char
/***************************************************************************/
//! @param is8_digit | digit to be tested
//! @return bool | true = the digit is a symbol digit |
//! @details
//! \n returns true if the digit is a symbol digit
/***************************************************************************/

bool Equation_parser::is_symbol( char is8_digit )
{
    DENTER_ARG("Digit: >>%c<<", (is8_digit!='\0')?(is8_digit):(' ') ); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------
	//Temp return
	bool u1_ret;
    if (Equation_parser::is_letter(is8_digit) == true)
    {
		//Symbol digit
		u1_ret = true;
    }
    else
    {
		switch (is8_digit)
		{
			case Token_legend::CS8_SYMBOL_DIGIT_UNDERSCORE:
				//Symbol digit
				u1_ret = true;
				break;
			default:
				//Not a Symbol digit
				u1_ret = false;
				break;
		}
	}

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("%c",(u1_ret==true?'Y':'N')); //Trace Return
    return u1_ret;	//Propagate
}   //Private Tester: is_symbol | char

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	PRIVATE STATIC METHODS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Private Static Method: compute_token_array_priority | std::vector<Token> & | std::vector<Token>::iterator & |
/***************************************************************************/
//! @param irclacl_token_array | array of Tokens for which open/close priority must be computed
//! @param orclacl_highest_priority_token | iterator pointing to the highest priority tokens nested at the lowest open/close priority
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n	Takes a vector of tokens, and compute priority
//! \n	Priority is meant to account ONLY for "priority" tokens like "(" and ")"
//! \n	Search the highest priority tokens at the lowest open/close priority
//! \n		Feature: Redundant Open/Close Token Deletion "(" ")"
//! \n	This module is the first module that has the information to do redundant priority token deletion
//! \n		EXAMPLES
//! \n	-------------------------------------------------------------------
//! \n		e.g. lowest = 0, all tokens without "priority" tokens
//! \n	Tokens:		x+y+3*2
//! \n	Priority:	0000000
//! \n	-------------------------------------------------------------------
//! \n		e.g. lowest = 0 there are "Priority" tokens
//! \n	(((((1)))))+1
//! \n	1234555432100
//! \n	-------------------------------------------------------------------
//! \n		e.g. lowest = 1 "redundant priority token deletion" kicks in deleting all "priority" tokens of priority 1 or lower
//! \n	Tokens:		(1+1)	"redundant priority token deletion" -> 1+1
//! \n	Priority: 	11111	                                    -> 000
//! \n	-------------------------------------------------------------------
//! \n		e.g. lowest = 1 "redundant priority token deletion" kicks in deleting all "priority" tokens of priority 1 or lower
//! \n	Tokens:		(((((1)))))	"redundant priority token deletion" -> 1
//! \n	Priority: 	12345554321	                                    -> 0
/***************************************************************************/

bool Equation_parser::compute_token_array_priority( std::vector<Token> &irclacl_token_array, std::vector<Token>::iterator &orclacl_highest_priority_token )
{
    DENTER_ARG("Tokens: %d", irclacl_token_array.size() ); //Trace Enter
    //--------------------------------------------------------------------------
    //	INIT
    //--------------------------------------------------------------------------

    if ((Config::CU1_INTERNAL_CHECKS == true) && (irclacl_token_array.size() <= 0))
    {
		DRETURN_ARG("Empty Array of tokens");
		return true;
    }

    //--------------------------------------------------------------------------
    //	COMPUTE PRIORITY OPEN/CLOSE
    //--------------------------------------------------------------------------
    //	priority dominated by priority operators parenthesis open/close

    std::vector<Token>::iterator cl_token_iterator;
	//Priority Operator, if priority operators don't return to zero, it's an unbalanced bracket error
	int s32_open_close_priority = 0;
	//Remember the minimum priority of the first "non priority" token. Start uninitialized
	int s32_min_priority = -1;
	//Number of non priority tokens
	int u32_num_non_priority = 0;
	//Scan the given array of token and compute the open/clsoe priority
	for (cl_token_iterator = irclacl_token_array.begin(); cl_token_iterator != irclacl_token_array.end(); cl_token_iterator++ )
	{
		//Compute symbol priority
		Equation_parser::compute_token_symbol_priority( *cl_token_iterator );
		//"Priority" open
		if (cl_token_iterator->e_type == Token_type::BASE_OPEN)
		{
			//Open, increase priority of what comes after
			s32_open_close_priority++;
			cl_token_iterator->s32_open_close_priority = s32_open_close_priority;
			DPRINT("Open | Priority: %d\n", s32_open_close_priority );
		}
		//"Priority" close
		else if (cl_token_iterator->e_type == Token_type::BASE_CLOSE)
		{
			//If: I have more close tokens than open tokens
			if (s32_open_close_priority <= 0)
			{
				DRETURN_ARG("ERR:%d | Unbalanced Brackets, extra close at Token: %d", __LINE__, (cl_token_iterator -irclacl_token_array.begin()) );
				return true;
			}
			//Open, decrease priority of what comes after
			cl_token_iterator->s32_open_close_priority = s32_open_close_priority;
			DPRINT("Close| Priority: %d\n", s32_open_close_priority );
			s32_open_close_priority--;
		}
		//"Non Priority"
		else
		{
			//Count the non priority symbols
			u32_num_non_priority++;
			//Set Token priority
			cl_token_iterator->s32_open_close_priority = s32_open_close_priority;
			//If "non priority" token priority is uninitialized
			if (s32_min_priority == -1)
			{
				//This is the new minimum priority
				s32_min_priority = s32_open_close_priority;
			}
			//if priority of token is the new lowest
			else if (s32_open_close_priority < s32_min_priority)
			{
				//This is the new minimum priority
				s32_min_priority = s32_open_close_priority;
			}
			//if priority is higher than lowest
			else
			{
				//Do nothing
			}
			DPRINT("Token: %s | Priority: %d\n", cl_token_iterator->cl_str.c_str() , s32_open_close_priority );
		}
	}	//Scan the given array of token and compute the open/clsoe priority
	//DEBUG
	std::cout << irclacl_token_array << "\n";

	//--------------------------------------------------------------------------
    //	SANITY CHECK
    //--------------------------------------------------------------------------
    //	Catch syntax error from input equation that are evident here

	//If: I have more open tokens than close tokens
	if (s32_open_close_priority > 0)
	{
		DRETURN_ARG("ERR:%d | Unbalanced Brackets, extra open", __LINE__ );
		return true;
	}
	//If I have no non priority token the equation is sintaxically invalid
	if (u32_num_non_priority <= 0)
	{
		DRETURN_ARG("ERR:%d | Equation Syntax Error, No non priority tokens", __LINE__ );
		return true;
	}

	//--------------------------------------------------------------------------
    //	REMOVE REDUNDANT PRIORITY TOKENS
    //--------------------------------------------------------------------------
	//	Remove extra parenthesis that are not needed
	//	Update the priority of what remains to avoid recomputing the priority

	//If: I have redundant priority tokens
	if (s32_min_priority > 0)
	{
		//Initialize scan
		cl_token_iterator = irclacl_token_array.begin();
		//While: scan is not complete
		while (cl_token_iterator != irclacl_token_array.end())
		{
			//Redundant "Priority" open token
			if ((cl_token_iterator->e_type == Token_type::BASE_OPEN) && (cl_token_iterator->s32_open_close_priority <= s32_min_priority))
			{
				DPRINT("Delete Open %d | Priority: %d | Min Priority: %d \n", (cl_token_iterator-irclacl_token_array.begin()), cl_token_iterator->s32_open_close_priority, s32_min_priority );
				//Remove this element from the array
				irclacl_token_array.erase( cl_token_iterator );
				//Do not advance scan
			}
			//"Priority" close
			else if ((cl_token_iterator->e_type == Token_type::BASE_CLOSE) && (cl_token_iterator->s32_open_close_priority <= s32_min_priority))
			{
				DPRINT("Delete Close %d | Priority: %d | Min Priority: %d \n", (cl_token_iterator-irclacl_token_array.begin()), cl_token_iterator->s32_open_close_priority, s32_min_priority );
				//Remove this element from the array
				irclacl_token_array.erase( cl_token_iterator );
				//Do not advance scan
			}
			//"Non Priority"
			else
			{
				//Update its priority
				cl_token_iterator->s32_open_close_priority -= s32_min_priority;
				//Next Token
				cl_token_iterator++;
				if ((Config::CU1_INTERNAL_CHECKS == true) && (cl_token_iterator->s32_open_close_priority < 0))
				{
					DRETURN_ARG("ERR:%d | Algrithmic error, bracket elision token priority negative...", cl_token_iterator->s32_open_close_priority );
				}
			}
		}	//While: scan is not complete
		DPRINT("Deleted redundant priority tokens | Tokens: %d\n", irclacl_token_array.size() );
		//DEBUG
		std::cout << irclacl_token_array << "\n";
	}	//If: I have redundant priority tokens

	//--------------------------------------------------------------------------
    //	SEEK HIGHEST PRIORITY "NON PRIORITY" TOKEN
    //--------------------------------------------------------------------------
    //	From the tokens remaining, find the token that would be at the top of a tree translation
    //	It must be a token with the lowest priority from open/close, but highest priority from operator types

    //Initialize seek
    std::vector<Token>::iterator cl_best_iterator;
    int s32_best_priority = -1;
    //Reset open close priority
    s32_open_close_priority = 0;
	//Scan all tokens
    for (cl_token_iterator = irclacl_token_array.begin(); cl_token_iterator != irclacl_token_array.end(); cl_token_iterator++ )
    {
			//Check forbracket balance
		//!@todo I can do better than repeating this code. Look to make a lambda or split hierarch and add incapsulate priority computation
		//"Priority" open
		if (cl_token_iterator->e_type == Token_type::BASE_OPEN)
		{
			//Open, increase priority of what comes after
			s32_open_close_priority++;
			cl_token_iterator->s32_open_close_priority = s32_open_close_priority;
		}
		//"Priority" close
		else if (cl_token_iterator->e_type == Token_type::BASE_CLOSE)
		{
			//If: I have more close tokens than open tokens
			if (s32_open_close_priority <= 0)
			{
				DRETURN_ARG("ERR:%d | Unbalanced Brackets, extra close at Token: %d", __LINE__, (cl_token_iterator -irclacl_token_array.begin()) );
				return true;
			}
			//Open, decrease priority of what comes after
			cl_token_iterator->s32_open_close_priority = s32_open_close_priority;
			s32_open_close_priority--;
		}
		//If the token has the lowest open/close priority
		else if (cl_token_iterator->s32_open_close_priority <= s32_min_priority)
		{
			//There is an algorithmic error, symbol priority is uninitialized
			if ((Config::CU1_INTERNAL_CHECKS == true) && (cl_token_iterator->s32_symbol_priority == -1))
			{
				DRETURN_ARG("ERR:%d | Symbol has uninitialized priority... | Index: %d ", __LINE__, (cl_token_iterator -irclacl_token_array.begin()) );
				return true;
			}
			//No best token has been found yet
			else if (s32_best_priority == -1)
			{
				//New best
				cl_best_iterator = cl_token_iterator;
				s32_best_priority = cl_token_iterator->s32_symbol_priority;
			}
			//Current symbol has stronger priority then best symbol
			else if (s32_best_priority > cl_token_iterator->s32_symbol_priority)
			{
				//New best
				cl_best_iterator = cl_token_iterator;
				s32_best_priority = cl_token_iterator->s32_symbol_priority;
			}
			//Current symbol has weaker priority then best symbol
			else
			{
				//Ignore it
			}
		}
		//If token has higher open/close priority
		else
		{
			//Ignore it
		}
    }	//Scan all tokens
    //If search couldn't find the best token
    if (s32_best_priority == -1)
    {
		DRETURN_ARG("ERR:%d | Could not find the strongest priority token...", __LINE__ );
		return true;
    }
    //If: I have more open tokens than close tokens
	if (s32_open_close_priority > 0)
	{
		DRETURN_ARG("ERR:%d | Unbalanced Brackets, extra open", __LINE__ );
		return true;
	}
	//Return highest priority token
	orclacl_highest_priority_token = cl_best_iterator;

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Tokens: %d | Highest Priority Token: <%s> | %d %d", irclacl_token_array.size(), cl_best_iterator->cl_str.c_str(), cl_best_iterator->s32_open_close_priority, cl_best_iterator->s32_symbol_priority ); //Trace Return
    return false;	//OK
}   //Private Static Method: compute_token_array_priority | std::vector<Token> & | std::vector<Token>::iterator & |

/***************************************************************************/
//! @brief Private Static Method | compute_token_symbol_priority | Token & |
/***************************************************************************/
//! @param irst_token | token for which priority is to be computed
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Compute the priority of a token removed from the open/close priority. Used to decide precedence between operators
/***************************************************************************/

bool Equation_parser::compute_token_symbol_priority( Token &irst_token )
{
    DENTER_ARG_CONDITIONAL(Config::CU1_DEBUG_COMPUTE_SYMBOL_PRIORITY, "Token type: %d | Token size: %d", irst_token.e_type, irst_token.cl_str.size() ); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------

    if (irst_token.cl_str.size() <= 0)
    {
		irst_token.s32_symbol_priority = -1;
		DRETURN_ARG_CONDITIONAL(Config::CU1_DEBUG_COMPUTE_SYMBOL_PRIORITY, "ERR:%d | Empty symbol...", __LINE__ );
		return true;
    }

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

	int s32_symbol_priority = -1;
	//If: token is an operator
	if (irst_token.e_type == Token_type::BASE_OPERATOR)
	{
		//Operators
		switch(irst_token.cl_str[0])
		{
			case Token_legend::CS8_OPERATOR_EQUAL:
				//Highest priority
				s32_symbol_priority = 0;
				break;
			case Token_legend::CS8_OPERATOR_MUL:
				//Highest priority
				s32_symbol_priority = 1;
				break;
			case Token_legend::CS8_OPERATOR_DIV:
				//Highest priority
				s32_symbol_priority = 2;
				break;
			case Token_legend::CS8_OPERATOR_SUM:
				//Highest priority
				s32_symbol_priority = 3;
				break;
			case Token_legend::CS8_OPERATOR_DIFF:
				//Highest priority
				s32_symbol_priority = 3;
				break;
		}
	}
	else if (irst_token.e_type == Token_type::BASE_SYMBOL)
	{
		s32_symbol_priority = 4;
	}
	else if (irst_token.e_type == Token_type::BASE_NUMBER)
	{
		s32_symbol_priority = 5;
	}
	else if ((irst_token.e_type == Token_type::BASE_OPEN) || (irst_token.e_type == Token_type::BASE_CLOSE))
	{
		//Low priority, open and close are handled by the second dimension of priority
		s32_symbol_priority = 10;
	}
	else
	{
		irst_token.s32_symbol_priority = -1;
		DRETURN_ARG_CONDITIONAL(Config::CU1_DEBUG_COMPUTE_SYMBOL_PRIORITY, "ERR:%d | Unknown Symbol >%s<", __LINE__, irst_token.cl_str.c_str() );
		return true;
	}

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    //Save symbol priority
	irst_token.s32_symbol_priority = s32_symbol_priority;
    DRETURN_ARG_CONDITIONAL(Config::CU1_DEBUG_COMPUTE_SYMBOL_PRIORITY, "Symbol Priority: %d", s32_symbol_priority ); //Trace Return
    return false;	//OK
} 	//Private Static Method | compute_token_symbol_priority | Token & |

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	PRIVATE METHODS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Private Method: equation_to_token_array | std::string, std::vector<std::string> &, std::vector<Equation_parser::Token> &
/***************************************************************************/
//! @return return false = OK | true = fail
//! @details
//! \n Equation Tokenizer. Translates an equation in string form to an array of string tokens.
/***************************************************************************/

bool Equation_parser::equation_to_token_array( std::string is_equation, std::vector<std::string> &oras_token_array, std::vector<Equation_parser::Token> &orast_token_array )
{
	DENTER_ARG("Parse: %s | Size: %d", is_equation.c_str(), is_equation.size() ); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------

    if (is_equation.size() <= 0)
    {
		DRETURN_ARG("ERR:%d | Bad input string",__LINE__);
		return true;
    }

    //Flush arrays
	oras_token_array = std::vector<std::string>();
	orast_token_array = std::vector<Equation_parser::Token>();

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //Temp storage of token being decoded
    Token cl_token;
    //Lambda to reset the token, I use it as a private local function
	auto reset_token = [](Token &irst_token)
	{
		//Clean up the temp string
		irst_token.cl_str.clear();
		//Initialize token type to unknown
		irst_token.e_type = Token_type::UNKNOWN;
		//Initialize priority to uninitialized
		irst_token.s32_open_close_priority = -1;
		irst_token.s32_symbol_priority = -1;
		irst_token.u1_negative = false;
		return false;
	};
	//Initialize the token
	reset_token( cl_token );
    //The FSM creates a vector holding one string for each token decoded in sequence.
    //Another algorithm is responsible for translating a sequence of token into a tree
    std::vector<Token> clast_token;

	//Start by searching the next token
    Fsm_state e_fsm_state = Fsm_state::SEEK_NEXT_TOKEN;
    //Start scan from first digit f the equation
    std::string::iterator clst_item = is_equation.begin();
    //true = a full token has been decoded by the FSM
    bool u1_token_decoded = false;
    //true = the FSM needs to reprocess a digit, so skip advancing to next token
    bool u1_reprocess_digit = false;
    //keep looping
    bool u1_continue = true;
	//Detect if a unary operator has been detected and if negation has to be applied to the next token
	bool u1_unary_operator = false;
    bool u1_unary_negation = false;
    //Detect if the previous token was an OPEN
    bool u1_unary_previous_open = false;
	//Count open and close brackets
    int s32_cnt_open = 0, s32_cnt_close = 0;
    //While: Iterate until all characters inside the string object have been scanned
    while (u1_continue == true)
    {
		//--------------------------------------------------------------------------
		//	PROCESSS DIGIT
		//--------------------------------------------------------------------------

		//Decode the digit
		char s8_digit = *clst_item;
		//FSM
		switch( e_fsm_state )
		{
			//--------------------------------------------------------------------------
			//	SEEK_NEXT_TOKEN
			//--------------------------------------------------------------------------
			//No open token. Seek beginning of next token
			case Fsm_state::SEEK_NEXT_TOKEN:
				DPRINT_CONDITIONAL( ((Config::CU1_PARSER_EXTENDED_DEBUG==true) && (clst_item != is_equation.end())) , "SEEK_NEXT_TOKEN | Decode: >>%c<<\n",s8_digit);
				//Detect a number digit
                if (Equation_parser::is_number(s8_digit) == true)
                {
					//Append digit to the token
					cl_token.cl_str.push_back( s8_digit );
					e_fsm_state = Fsm_state::TOKEN_NUMBER;
                }
                //Detect decimal separator
                else if (s8_digit == Token_legend::CS8_DECIMAL_SEPARATOR)
                {
					//Append 0 before the digit and the digit to the token
					cl_token.cl_str.push_back( '0' );
					cl_token.cl_str.push_back( s8_digit );
					e_fsm_state = Fsm_state::TOKEN_NUMBER;
                }
                //Detect a symbol digit. Symbols must start with a symbol digit. Symbols are things like constants or variable names
                else if (Equation_parser::is_symbol(s8_digit) == true)
                {
					//Append digit to the token
					cl_token.cl_str.push_back( s8_digit );
					e_fsm_state = Fsm_state::TOKEN_SYMBOL;
                }
                //Detect Operator
                else if (Equation_parser::is_operator(s8_digit))
                {
					//Special Unary Positive Detection. "(+"
					if ((u1_unary_previous_open == true) && (s8_digit == Token_legend::CS8_OPERATOR_SUM))
					{
						//Detected a + unary operator, It has no effect other than deleting the token
						u1_unary_operator = true;
                        u1_unary_negation = false;
                        DPRINT("Unary + detected\n");
					}
					//Special Unary Negative Detection "(-"
					else if ((u1_unary_previous_open == true) && (s8_digit == Token_legend::CS8_OPERATOR_DIFF))
					{
						//Detected an unary operator. It has the effect of setting the negate flag of the next token
						u1_unary_operator = true;
                        u1_unary_negation = true;
                        DPRINT("Unary - detected\n");
					}
					//Not an unary operator
					else
					{
						//Append digit to the token
						cl_token.cl_str.push_back( s8_digit );
						//Single digit operator decoded
						u1_token_decoded = true;
						cl_token.e_type = Token_type::BASE_OPERATOR;
						DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Operator detected: >>%c<< | Token: %s\n",s8_digit, cl_token.cl_str.c_str() );
					}
                }
                //Detect Open
                else if (s8_digit == Token_legend::CS8_PRIORITY_OPEN)
                {
					//Append digit to the token
					cl_token.cl_str.push_back( s8_digit );
					//Single digit operator decoded
					u1_token_decoded = true;
					cl_token.e_type = Token_type::BASE_OPEN;
					s32_cnt_open++;
					DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Open detected: >>%c<< | Token: %s\n",s8_digit, cl_token.cl_str.c_str() );
                }
                //Detect Open
                else if (s8_digit == Token_legend::CS8_PRIORITY_CLOSE)
                {
					//Append digit to the token
					cl_token.cl_str.push_back( s8_digit );
					//Single digit operator decoded
					u1_token_decoded = true;
					cl_token.e_type = Token_type::BASE_CLOSE;
					s32_cnt_close++;
					DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Close detected: >>%c<< | Token: %s\n",s8_digit, cl_token.cl_str.c_str() );
                }
                //Unknown digit
                else
                {
					DPRINT("ERR%d: Invalid Digit >>%c<<\n", __LINE__, (s8_digit!='\0')?(s8_digit):(' ') );
                }

				break;
			//Parsing a number token
			case Fsm_state::TOKEN_NUMBER:
				DPRINT_CONDITIONAL( ((Config::CU1_PARSER_EXTENDED_DEBUG==true) && (clst_item != is_equation.end())) , "TOKEN_NUMBER | Decode: >>%c<<\n",s8_digit);
				//Last digit
				if (clst_item == is_equation.end())
				{
					//Do not append digit, it's a terminator
					//Symbol fully decoded
					u1_token_decoded = true;
					cl_token.e_type = Token_type::BASE_NUMBER;
				}
				//Ignore thousand separator
				else if (s8_digit == Token_legend::CS8_THOUSAND_SEPARATOR)
				{
					//!@todo Parser should check that the thousand separator token is in the right place
					//Do nothing
				}
				//More numbers or decimal separators
				else if ((Equation_parser::is_number(s8_digit)) || (s8_digit == Token_legend::CS8_DECIMAL_SEPARATOR))
				{
					//!@todo Parser should check that the decimal separator token is in the right place
					//Append digit to the token, not done yet
					cl_token.cl_str.push_back( s8_digit );
				}
				//Non number digit
				else
				{
					//Do not append digit, it belongs to another token
					//Reprocess the digit as it might be the beginning of a new token
					u1_reprocess_digit = true;
					//Symbol fully decoded
					u1_token_decoded = true;
					cl_token.e_type = Token_type::BASE_NUMBER;
				}
				break;

			//Parsing a symbol token. End when I'm parsing a non symbol non number or when string ends
			case Fsm_state::TOKEN_SYMBOL:
				DPRINT_CONDITIONAL( ((Config::CU1_PARSER_EXTENDED_DEBUG==true) && (clst_item != is_equation.end())) , "TOKEN_SYMBOL | Decode: >>%c<<\n",(s8_digit!='\0')?(s8_digit):(' '));
				//Last digit
				if (clst_item == is_equation.end())
				{
					//Do not append digit, it's a terminator
					//Symbol fully decoded
					u1_token_decoded = true;
					cl_token.e_type = Token_type::BASE_SYMBOL;
				}
				//Detect a symbol digit or a number digit
				else if ((Equation_parser::is_symbol(s8_digit) == true) || (Equation_parser::is_number(s8_digit) == true))
                {
					//Append digit to the token
					cl_token.cl_str.push_back( s8_digit );
                }
                //Detect a non symbol not number digit
                else
                {
					//Do not append digit, it belongs to another token
					//Reprocess the digit as it might be the beginning of a new token
					u1_reprocess_digit = true;
					//Symbol fully decoded
					u1_token_decoded = true;
					cl_token.e_type = Token_type::BASE_SYMBOL;
                }

				break;

			//Unknown state
			default:
				DPRINT("ERR%d: Unknown FSM state >>%d<<... Reset FSM\n", e_fsm_state );
				//Reset FSM State
				e_fsm_state = Fsm_state::SEEK_NEXT_TOKEN;
				//Initialize the token
				reset_token( cl_token );
				break;
		}
		//If FSM has fully decoded a token
		if (u1_token_decoded == true)
		{
			//Clear flag
			u1_token_decoded = false;
			//If: unary detection was tripped
			if (u1_unary_operator == true)
			{
				//acknoweldge
				u1_unary_operator = false;
				//Propagate negation to token
				cl_token.u1_negative = u1_unary_negation;
				DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Unary Operator: %c\n", (u1_unary_negation)?('-'):('+') );
				//Clear negation (can be skipped for performance)
				u1_unary_negation = false;
			}
			//Special detection of previous OPEN, used for Unary detection
			u1_unary_previous_open = (cl_token.e_type == Token_type::BASE_OPEN);
			//If: decoding resulted in an empty token
			if (cl_token.cl_str.size() <= 0)
			{
				//Algorithmic error
				DPRINT("ERR%d: An empty token was decoded\n" ,__LINE__);
			}
			else
			{
				//Append the decoded string to the string token vector
				oras_token_array.push_back( cl_token.cl_str );
				//Append the decoded string to the token vector (structure)
				orast_token_array.push_back( cl_token );
				DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Token fully decoded: %c%s | type: %d | size: %d\n", (cl_token.u1_negative)?('-'):(' '),cl_token.cl_str.c_str(), cl_token.e_type, cl_token.cl_str.size() );
				DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Tokens decoded: %d\n", orast_token_array.size() );
				//Initialize the token
				reset_token( cl_token );
			}
            //FSM is now IDLE
            e_fsm_state = Fsm_state::SEEK_NEXT_TOKEN;
		}

		//--------------------------------------------------------------------------
		//	NEXT
		//--------------------------------------------------------------------------
		//If: this is the last digit ('\0')
		if (clst_item == is_equation.end())
		{
			//Done
			u1_continue = false;
		}
		//If FSM asked to reprocess a digit
		else if (u1_reprocess_digit == true)
		{
			//Clear flag
			u1_reprocess_digit = false;
		}
		//If: FSM didn't say anything, advance to next digit to avoid stalling FSM
		else
		{
			//Scan next digit
			clst_item++;
		}
	}	//While: Iterate until all characters inside the string object have been scanned
	//Check bracket balance
	if (s32_cnt_close != s32_cnt_open)
	{
		DRETURN_ARG("ERR%d | Unbalanced brackets | Open %d | Close %d", __LINE__, s32_cnt_open, s32_cnt_close );
		return true;
	}

	//--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
	//
	DPRINT("Equations decoded into %d tokens\n", orast_token_array.size() );
	for (std::vector<Token>::iterator cl_token_iter = orast_token_array.begin();cl_token_iter != orast_token_array.end();cl_token_iter++)
	{
		DPRINT("Token: >>%s<< | Type: %d | Size: %d\n", cl_token_iter->cl_str.c_str(), cl_token_iter->e_type, cl_token_iter->cl_str.size() );
	}

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Decoded %d tokens", oras_token_array.size() );
    return false;
}   //Private Method: equation_to_token_array | std::string, std::vector<std::string> &, std::vector<Equation_parser::Token> &

/***************************************************************************/
//! @brief Static Private Method | token_array_to_tree | std::vector<Token> & | Tree<Token> & |
/***************************************************************************/
//! @param irclacl_token_array | array of Tokens
//! @param orclacl_token_array | tree of tokens. This function will fill up the tree
//! @param in_index_father | index of the father where the token should be spawned
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Recursive function that finds the highest priority token, and push that into the tree. Recursively push more tokens.
//! \n The tokenizer wants to use only sum and negation, with large number of leaves if possible
/***************************************************************************/

bool Equation_parser::token_array_to_tree( std::vector<Token> &irclacl_token_array, Tree<Token> &orcl_token_tree, size_t in_index_father )
{
    DENTER_ARG("Token Array Size: %d | Father %d", irclacl_token_array.size(), in_index_father ); //Trace Enter
    //--------------------------------------------------------------------------
    //	Search CORE token
    //--------------------------------------------------------------------------
    //	The treezation of an array of tokens require finding a core token to become the branch
    //	All tokens to its left are to be added to the LHS leaves recursively
    //	All tokens to its right are to be added to the RHS leaves recursively
    //	Open and Close token help enforce Priority
	//	priority is encoded in tree structure (that's the point of treezation)

    //Token that will become the branch
    std::vector<Token>::iterator cl_core_iterator;
	//Compute priorities and search for the strongest symbol
    bool u1_ret = Equation_parser::compute_token_array_priority( irclacl_token_array, cl_core_iterator );
	if (u1_ret == true)
	{
		DRETURN_ARG("ERR:%d | Priority computation failed", __LINE__);
		return true;
    }
    DPRINT("Core Token: >%s< | Size: %d | Open/Close Priority: %d | Symbol Priority: %d\n", cl_core_iterator->cl_str.c_str(), cl_core_iterator->cl_str.size(), cl_core_iterator->s32_open_close_priority, cl_core_iterator->s32_symbol_priority );

	//--------------------------------------------------------------------------
    //	LHS | CORE | RHS
    //--------------------------------------------------------------------------
    //	Having found a core token
    //	The core token become the content of the leaf
    //	Up to two branches are created, tiling all tokens left of core LHS, and all tokens right of the core RHS

    //Aid vectors. Tiled left and right around an operator.
    std::vector<Token> clast_lhs;
    std::vector<Token> clast_rhs;
	//Start from first token
	std::vector<Token>::iterator cl_token_iterator = irclacl_token_array.begin();
	//Scan the given array of token until a core token is found or until the array is over
	for (cl_token_iterator = irclacl_token_array.begin(); cl_token_iterator != irclacl_token_array.end(); cl_token_iterator++ )
	{
		//if: LHS token
		if (cl_token_iterator < cl_core_iterator)
		{
			clast_lhs.emplace_back( *cl_token_iterator );
			DPRINT("LHS: >%s<\n", cl_token_iterator->cl_str.c_str() );
		}
		//If: RHS token
		else if (cl_token_iterator > cl_core_iterator)
		{
			clast_rhs.emplace_back( *cl_token_iterator );
			DPRINT("RHS: >%s<\n", cl_token_iterator->cl_str.c_str() );
		}
		//Core or End
		else
		{
			//Do nothing
		}
	}
	DPRINT("LHS Tokens: %d | RHS Tokens: %d\n", clast_lhs.size(), clast_rhs.size() );

	//--------------------------------------------------------------------------
    //	Sanity Check
    //--------------------------------------------------------------------------

    //Father under which the tokens are tiled
    size_t n_next_father = 0;
	//Binary Operators must have both RHS and LHS
	if ((cl_core_iterator->e_type == Token_type::BASE_OPERATOR) && ( (clast_lhs.size() == 0) || (clast_rhs.size() == 0) ))
	{
		DRETURN_ARG("ERR:%d | Operator without RHS and LHS", __LINE__);
		return true;
	}
	//Equal is special, it's the first simbol that becomes the root of the tree
	if ((cl_core_iterator->cl_str[0] == Token_legend::CS8_OPERATOR_EQUAL) && (in_index_father == 0))
	{
		DPRINT("ROOT: >%s<\n", cl_core_iterator->cl_str.c_str() );
		//Write the payload on the root
		orcl_token_tree[0] = *cl_core_iterator;
		//Show the tree
		orcl_token_tree.print();

		n_next_father = in_index_father;
		DPRINT("LHS: >%s<\n", cl_core_iterator->cl_str.c_str() );
	}
	else
	{
		//Add a child to the current branch holding the Payload of the core token found
		size_t n_child_index = orcl_token_tree.create_child( in_index_father, *cl_core_iterator );
		if (n_child_index >= orcl_token_tree.size() )
		{
			DRETURN_ARG("ERR:%d | Failed to add branch to tree | index: %d", __LINE__, n_child_index);
			return true;
		}
		n_next_father = n_child_index;
		//Show the tree
		orcl_token_tree.print();
		std::cout << "--------------------------------------\n";
	}

	//Execute the search on the LHS and RHS sides of the equation
	if (clast_lhs.size() > 0)
	{
		token_array_to_tree( clast_lhs, orcl_token_tree, n_next_father );
		DPRINT("LHS of size %d under father %d\n", clast_lhs.size(), n_next_father );
	}
	if (clast_rhs.size() > 0)
	{
		token_array_to_tree( clast_rhs, orcl_token_tree, n_next_father );
		DPRINT("RHS of size %d under father %d\n", clast_rhs.size(), n_next_father );
	}

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return false;	//OK
}   //Static Private Method | token_array_to_tree | std::vector<Token> & | Tree<Token> & |

/***************************************************************************/
//! @brief Static Private Method | token_array_to_tree | std::vector<Token> & | Tree<Token> & |
/***************************************************************************/
//! @param ircl_tree_root | tree of tokens
//! @param orast_token_array | array of Tokens filled by method
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Reverse translation from a tree of tokens to a vector of token. Will add open and close tokens where needed
/***************************************************************************/

bool Equation_parser::token_tree_to_array( Tree<Token> &ircl_tree_root, std::vector<Token> &orast_token_array )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return false;	//OK
}   //Static Private Method | token_array_to_tree | std::vector<Token> & | Tree<Token> & |

/***************************************************************************/
//! @brief Static Private Method | aggregate_tree_token_sum_diff | Tree<Token> & |
/***************************************************************************/
//! @param ircl_token_tree | tree of tokens
//! @return int | -1 fail | return number of tokens merged
//! @details
//! \n Within a tree of tokens, search for sum and diff operators, aggregate them in sum operators with a greater number of leaves
//! \n Navigate the tree
//! \n if the root is a sum operator
//! \n search for sum operators in the leaves. That leaf's leaves are added to the root and the leaf is destroyed
//! \n	e.g.
//! \n	Before					After
//! \n	=						=
//! \n		y						y
//! \n		+						+
//! \n			2						2
//! \n			+						-1
//! \n				-1					x
//! \n				x
//! \n	e.g.
//! \n	Before					After
//! \n	=						=
//! \n		y						y
//! \n		+						+
//! \n			+						1
//! \n				1					2
//! \n				2					-3
//! \n			-						-4
//! \n				3
//! \n				4
/***************************************************************************/

int Equation_parser::aggregate_tree_token_sum_diff( Tree<Token> &ircl_tree_root )
{
	/*
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------


    bool u1_ret;
    int s32_cnt_destroyed = 0;
    int s32_cnt_moved = 0;

    unsigned int u32_ret;
	//Root token
    Token &rst_token_root = ircl_tree_root[0];
	//If the token is a SUM and there is at least one leaf
    if ((rst_token_root.e_type == Token_type::BASE_OPERATOR) && (rst_token_root.cl_str[0] == Token_legend::CS8_OPERATOR_SUM))
    {
		//An operator MUST have at least two operands under it
		if (ircl_tree_root.size() < 2)
		{
			DRETURN_ARG("ERR:%d | Root Operator %c has %d leaves. It should have at least 2 leaves...", __LINE__, rst_token_root.cl_str[0], ircl_tree_root.size() );
			return -1;
		}
		//Save the number of leaves to search for. the leaves might increase in number after merging
		unsigned int u32_num_leaves = ircl_tree_root.size();
		//For each leaf already there before starting, the number may reduce when deleting a leaf
		unsigned int u32_index = 0;
		while (u32_index < u32_num_leaves)
        {
			//Fetch Token
			Token &rst_token_leaf = rst_tree_leaf.payload();
			//If leaf is a SUM/DIFF operator
			if ((rst_token_leaf.e_type == Token_type::BASE_OPERATOR) && (rst_token_leaf.cl_str[0] == Token_legend::CS8_OPERATOR_SUM))
			{
				//An operator MUST have at least two operands under it
				if (ircl_tree_root.get_children(u32_index) < 2)
				{
					DRETURN_ARG("ERR:%d | Leaf Operator %c has %d leaves. It should have at least 2 leaves...", __LINE__, rst_token_leaf.cl_str[0], ircl_tree_root.get_children(u32_index) );
					return -1;
				}
				//For there are leaflets remaining under the leaf
				while (rst_tree_leaf.get_num_leaves() > 0)
				{
					//move the leaflet
					u1_ret = rst_tree_leaf.move_leaf( 0, ircl_tree_root, u32_ret );
					if (u1_ret == true)
					{
						DRETURN_ARG("ERR:%d | failed to move leaflet %d of leaf %p %d to root %p...\n", __LINE__, 0, rst_tree_leaf, ircl_tree_root );
						return -1;
					}
                    DPRINT("%d | Added leaf %d to root with now %d leaves\n", __LINE__, u32_ret, ircl_tree_root);
                    //Count the moved leaves
					s32_cnt_destroyed++;
				}
				//I now need to remove the leaf
				u1_ret = ircl_tree_root.destroy_leaf( u32_index );
				if (u1_ret == true)
				{
					DRETURN_ARG("ERR:%d | Failed to destroy leaf %d...\n", __LINE__, u32_index );
					return -1;
				}
				//Count the destroyed leaves
				s32_cnt_destroyed++;
				DPRINT("%d | Destroyed leaf %d\n", __LINE__, u32_index);
				//This now requires updating the indexes, I have one fewer leaves to search for
				if (u32_num_leaves <= 0)
				{
					DRETURN_ARG("ERR:%d | Not enough maximum leaves remaining %d...\n", __LINE__, u32_num_leaves );
					return -1;
				}
				u32_num_leaves--;
			}
			//If: not a SUM/DIFF
			else
			{
				//Advance
				u32_index++;
			}
        }	//For each leaf

    }
    if (ircl_tree_root.size() > 0)
    {

		//For each leaf after the merge, I now have to call recursively the merge process
		for (unsigned int u32_index = 0;u32_index < ircl_tree_root.get_num_leaves();u32_index++)
		{
			u32_ret = aggregate_tree_token_sum_diff( ircl_tree_root[u32_index] );
			if (u32_ret < 0)
			{
				DRETURN_ARG("ERR:%d | failed to recursively aggregate...\n", __LINE__ );
				return -1;
			}
		}
	}



    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Destroyed: %d | Moved: %d", s32_cnt_destroyed, s32_cnt_moved ); //Trace Return
    */
    return 0;	//OK
}   //Static Private Method | aggregate_tree_token_sum_diff | Tree<Token> & |

/***************************************************************************/
//! @brief Private Method | flush | void
/***************************************************************************/
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n flush the token array and the token tree
/***************************************************************************/

bool Equation_parser::flush( void )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //Clear the array of tokens
    this->gclacl_tokens.clear();
    if (this->gclacl_tokens.size() != 0)
    {
		DRETURN_ARG("ERR%d | CRITICAL ERROR!!! COULD NOT CLEAR VECTOR %d", this->gclacl_tokens.size() );
		return true;
    }

    //Clear the array of tokens
    this->gcl_token_tree.flush();
    if (this->gcl_token_tree.size() != 1)
    {
		DRETURN_ARG("ERR%d | CRITICAL ERROR!!! COULD NOT FLUSH TREE %d", this->gclacl_tokens.size() );
		return true;
    }

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return false;	//OK
} 	//Private Method: flush | void

/***************************************************************************/
//! @brief Private Method | report_error | Error_code
/***************************************************************************/
//! @param ips8_error_code | error string to be reported. Error strings can be stored in Error_code
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Report an error. return false: OK | true: Unknown error code
/***************************************************************************/

bool Equation_parser::report_error( const char *ips8_error_code )
{
    DENTER_ARG("ERR: %p", ips8_error_code ); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //If class is OK
    if (ips8_error_code != Error_code::CPS8_OK)
    {
		//Report current error
		this->gps8_error_code = ips8_error_code;
    }
    else
    {
		//Class was already in error. Could not
		DRETURN_ARG("ERR: Class is already in error: %p | culd not report error: %p", this->gps8_error_code, ips8_error_code );
		return true;
    }

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return false;	//OK
} 	//Private Method: report_error | Error_code

/***************************************************************************/
//! @brief Private Method: error_recovery | void |
/***************************************************************************/
//! @return return false = OK | true = fail
//! @details
//! \n Tries to recover from an error
//! \n Automatically called by get_error.
/***************************************************************************/

bool Equation_parser::error_recovery( void )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN();      //Trace Return
    return true;    //FAIL
}   //Private Method: error_recovery | void |

/***************************************************************************/
//! @brief Private Method: my_private_method | void
/***************************************************************************/
// @param
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Method
/***************************************************************************/

bool Equation_parser::my_private_method( void )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	INIT
    //--------------------------------------------------------------------------

    if (Config::CU1_EXTERNAL_CHECKS == true)
    {
		return true;
    }

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return false;	//OK
}   //Private Method: my_private_method | void

/**********************************************************************************
**	NAMESPACE
**********************************************************************************/

} //End Namespace: User
