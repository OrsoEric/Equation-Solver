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
    this -> init_class_vars();

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
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    DPRINT("Token: %s | Type: %d | Priority: %d\n",irst_rhs.cl_str.c_str(), irst_rhs.e_type, irst_rhs.s32_open_close_priority );
    //Stream payload
    icl_stream << "Token: " << irst_rhs.cl_str.c_str() << " | Type: " << irst_rhs.e_type << " | Priority: " << irst_rhs.s32_open_close_priority << "\n";

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
/***************************************************************************/

bool Equation_parser::parse( std::string icl_equation_string )
{
    DENTER_ARG("Parse: %s | Size: %d", icl_equation_string.c_str(), icl_equation_string.size() ); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------

    if (icl_equation_string.size() <= 0)
    {
		DRETURN_ARG("ERR:%d | Bad input string",__LINE__);
		return true;
    }

    //--------------------------------------------------------------------------
    //	LINEAR PARSER
    //--------------------------------------------------------------------------
    //	The first pass translates a string into a vector of tokens with base token types

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
		return false;
	};
	//Initialize the token
	reset_token( cl_token );
    //The FSM creates a vector holding one string for each token decoded in sequence.
    //Another algorithm is responsible for translating a sequence of token into a tree
    std::vector<Token> clast_tokens;
	//Start by searching the next token
    Fsm_state e_fsm_state = Fsm_state::SEEK_NEXT_TOKEN;
    //Start scan from first digit f the equation
    std::string::iterator clst_item = icl_equation_string.begin();
    //true = a full token has been decoded by the FSM
    bool u1_token_decoded = false;
    //true = the FSM needs to reprocess a digit, so skip advancing to next token
    bool u1_reprocess_digit = false;
    //keep looping
    bool u1_continue = true;
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
				DPRINT_CONDITIONAL( ((Config::CU1_PARSER_EXTENDED_DEBUG==true) && (clst_item != icl_equation_string.end())) , "SEEK_NEXT_TOKEN | Decode: >>%c<<\n",s8_digit);
				//Detect a number digit
                if (this->is_number(s8_digit) == true)
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
                else if (this->is_symbol(s8_digit) == true)
                {
					//Append digit to the token
					cl_token.cl_str.push_back( s8_digit );
					e_fsm_state = Fsm_state::TOKEN_SYMBOL;
                }
                //Detect Operator
                else if (this->is_operator(s8_digit))
                {
					//Append digit to the token
					cl_token.cl_str.push_back( s8_digit );
					//Single digit operator decoded
					u1_token_decoded = true;
					cl_token.e_type = Token_type::BASE_OPERATOR;
					DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Operator detected: >>%c<< | Token: %s\n",s8_digit, cl_token.cl_str.c_str() );
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
					//The equation contains invalid digits
					this->report_error(Error_code::CPS8_ERR_USER_DIGIT);
					DPRINT("ERR%d: Invalid Digit >>%c<<\n", __LINE__, (s8_digit!='\0')?(s8_digit):(' ') );
                }

				break;
			//Parsing a number token
			case Fsm_state::TOKEN_NUMBER:
				DPRINT_CONDITIONAL( ((Config::CU1_PARSER_EXTENDED_DEBUG==true) && (clst_item != icl_equation_string.end())) , "TOKEN_NUMBER | Decode: >>%c<<\n",s8_digit);
				//Last digit
				if (clst_item == icl_equation_string.end())
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
				else if ((this->is_number(s8_digit)) || (s8_digit == Token_legend::CS8_DECIMAL_SEPARATOR))
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
				DPRINT_CONDITIONAL( ((Config::CU1_PARSER_EXTENDED_DEBUG==true) && (clst_item != icl_equation_string.end())) , "TOKEN_SYMBOL | Decode: >>%c<<\n",(s8_digit!='\0')?(s8_digit):(' '));
				//Last digit
				if (clst_item == icl_equation_string.end())
				{
					//Do not append digit, it's a terminator
					//Symbol fully decoded
					u1_token_decoded = true;
					cl_token.e_type = Token_type::BASE_SYMBOL;
				}
				//Detect a symbol digit or a number digit
				else if ((this->is_symbol(s8_digit) == true) || (this->is_number(s8_digit) == true))
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
				//FSM error
				this->report_error(Error_code::CPS8_ERR_FSM);
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
			//If: decoding resulted in an empty token
			if (cl_token.cl_str.size() <= 0)
			{
				//Algorithmic error
				DPRINT("ERR%d: An empty token was decoded\n" ,__LINE__);
			}
			else
			{
				//Append the decoded string to the token vector
				clast_tokens.push_back( cl_token );
				DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Token fully decoded: %s | type: %d | size: %d\n", cl_token.cl_str.c_str(), cl_token.e_type, cl_token.cl_str.size() );
				DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Tokens decoded: %d\n", clast_tokens.size() );
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
		if (clst_item == icl_equation_string.end())
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
		DRETURN_ARG("ERR%d: Unbalanced brackets | Open %d | Close %d", __LINE__, s32_cnt_open, s32_cnt_close );
		this->report_error( Error_code::CPS8_ERR_UNBALANCED_BRACKETS );
		//FAIL
		return true;
	}

	//--------------------------------------------------------------------------
    //
    //--------------------------------------------------------------------------
	//
	DPRINT("Equations decoded into %d tokens\n", clast_tokens.size() );
	for (std::vector<Token>::iterator cl_token_iter = clast_tokens.begin();cl_token_iter != clast_tokens.end();cl_token_iter++)
	{
		DPRINT("Token: >>%s<< | Type: %d | Size: %d\n", cl_token_iter->cl_str.c_str(), cl_token_iter->e_type, cl_token_iter->cl_str.size() );
	}

	//Recursively translate an array of token into a tree of tokens
	this->token_array_to_tree( clast_tokens, this->gcl_token_tree );

	this->gcl_token_tree.print();
	std::cout << "--------------------------------------\n";



    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return false; //OK
} //Public Setter: parse | const char * |

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	PUBLIC GETTERS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

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
    if (this->is_letter(is8_digit) == true)
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
	//Stop condition and found condition
	bool u1_continue = true;
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
				//Remove this element from the array
				irclacl_token_array.erase( cl_token_iterator );
				//Do not advance scan
			}
			//"Priority" close
			else if ((cl_token_iterator->e_type == Token_type::BASE_CLOSE) && (cl_token_iterator->s32_open_close_priority <= s32_min_priority))
			{
				//Remove this element from the array
				irclacl_token_array.erase( cl_token_iterator );
				//Do not advance scan
			}
			//"Non Priority"
			else
			{
				//Next
				cl_token_iterator++;
				//Update its priority
				cl_token_iterator->s32_open_close_priority -= s32_min_priority;
			}
		}	//While: scan is not complete
		DPRINT("Deleted redundant priority tokens | Tokens: %d\n", irclacl_token_array.size() );
	}	//If: I have redundant priority tokens

	//--------------------------------------------------------------------------
    //	SEEK HIGHEST PRIORITY "NON PRIORITY" TOKEN
    //--------------------------------------------------------------------------
    //	From the tokens remaining, find the token that would be at the top of a tree translation
    //	It must be a token with the lowest priority from open/close, but highest priority from operator types

    //Initialize seek
    std::vector<Token>::iterator cl_best_iterator;
    int s32_best_priority = -1;
	//Scan all tokens
    for (cl_token_iterator = irclacl_token_array.begin(); cl_token_iterator != irclacl_token_array.end(); cl_token_iterator++ )
    {
		//If the token has the lowest open/close priority
		if (cl_token_iterator->s32_open_close_priority <= s32_min_priority)
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

	//Return highest priority token
	orclacl_highest_priority_token = cl_best_iterator;

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Tokens: %d", irclacl_token_array.size() ); //Trace Return
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

	int s32_symbol_priority;
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
//! @brief Public method: my_public_method | void
/***************************************************************************/
//! @param irclacl_token_array | array of Tokens
//! @param orclacl_token_array | tree of tokens. This function will fill up the tree
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Recursive function that finds the highest priority token, and push that into the tree. Recursively push more tokens.
/***************************************************************************/

bool Equation_parser::token_array_to_tree( std::vector<Token> &irclacl_token_array, Tree<Token> &orcl_token_tree )
{
    DENTER_ARG("Token Array Size: %d | ", irclacl_token_array.size() ); //Trace Enter
    //--------------------------------------------------------------------------
    //	TREE PARSER
    //--------------------------------------------------------------------------
    //	Second pass translates an array of tokens into a tree of tokens
    //	This pass also specializes base token types into specialized token types if needed
    //	Algorithm
    //	it's a tile left/right algorithm
    //	1) search operator =
    //	2) move everything left of operator to LHS vector, move everything right to RHS vector
    //	3) add operator to tree
    //	4) on LHS -> 1), operator is added as leaf to
    //	5)

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
		}
		//If: RHS token
		else if (cl_token_iterator > cl_core_iterator)
		{
			clast_rhs.emplace_back( *cl_token_iterator );
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

	//Binary Operators must have both RHS and LHS
	if ((cl_core_iterator->e_type == Token_type::BASE_OPERATOR) && ( (clast_lhs.size() == 0) || (clast_rhs.size() == 0) ))
	{
		DRETURN_ARG("ERR:%d | Operator without RHS and LHS", __LINE__);
		return true;
	}

	//Equal is special, it's the first simbol that becomes the root of the tree
	if (cl_core_iterator->cl_str[0] == Token_legend::CS8_OPERATOR_EQUAL)
	{
		orcl_token_tree.set_payload( *cl_core_iterator );
		//Show the tree
		orcl_token_tree.print();
		//Execute the search on the LHS and RHS sides of the equation
		token_array_to_tree( clast_lhs, orcl_token_tree );
		token_array_to_tree( clast_rhs, orcl_token_tree );

	}
	else
	{
		unsigned int u32_index;
		//Add a leaf to the current branch holding the Payload of the core token found
		u1_ret = orcl_token_tree.create_leaf( *cl_core_iterator, u32_index );
		if (u1_ret == true)
		{
			DRETURN_ARG("ERR:%d | Failed to add branch to tree", __LINE__);
			return true;
		}
		//Show the tree
		orcl_token_tree.print();
		std::cout << "--------------------------------------\n";
		//Execute the search on the LHS and RHS sides of the equation
		if (clast_lhs.size() > 0)
		{
			token_array_to_tree( clast_lhs, orcl_token_tree[u32_index] );
		}
		if (clast_rhs.size() > 0)
		{
			token_array_to_tree( clast_rhs, orcl_token_tree[u32_index] );
		}
	}


	//Set the payload of the branch to the tiling token found
	//




    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return false;	//OK
}   //Public method: my_public_method | void

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
