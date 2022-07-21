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


	for (std::vector<Token>::iterator cl_token_iter = clast_tokens.begin();cl_token_iter != clast_tokens.end();cl_token_iter++)
	{
		DPRINT("Token: >>%s<< | Type: %d | Size: %d\n", cl_token_iter->cl_str.c_str(), cl_token_iter->e_type, cl_token_iter->e_type );

	}



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
**	PRIVATE METHODS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

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
