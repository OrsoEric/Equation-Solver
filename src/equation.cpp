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
#include "equation.h"

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
//! @brief Constructor: Equation | void
/***************************************************************************/
// @param
//! @return no return
//! @details
//! \n Empty constructor
/***************************************************************************/

Equation::Equation( void )
{
    DENTER_ARG("This: %p", (void*)(&(*this)));   //Trace Enter
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
}   //Constructor: Equation | void

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	DESTRUCTORS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//!	@brief Destructor: Equation | void
/***************************************************************************/
// @param
//! @return no return
//! @details
//! \n Empty destructor
/***************************************************************************/

Equation::~Equation( void )
{
    DENTER_ARG("This: %p", (void*)(&(*this)) );   //Trace Enter
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
}   //Destructor: Equation | void

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

std::ostream& operator<<( std::ostream& icl_stream, const Equation::Token &irst_rhs )
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

std::ostream& operator<<( std::ostream& icl_stream, std::vector<Equation::Token> &irclast_tokens )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

	//Header
    icl_stream << "Tokens ";
    DPRINT("Tokens   ");
	//Scan all tokens
    for (std::vector<Equation::Token>::iterator cl_token_iterator = irclast_tokens.begin(); cl_token_iterator != irclast_tokens.end(); cl_token_iterator++ )
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
    for (std::vector<Equation::Token>::iterator cl_token_iterator = irclast_tokens.begin(); cl_token_iterator != irclast_tokens.end(); cl_token_iterator++ )
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

std::string Equation::tree_to_equation( void )
{
    DENTER(); //Trace Enter
    std::string cl_str;

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------



    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG( "<%s> | %d", cl_str.c_str(), int(cl_str.size()) ); //Trace Return
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

const char *Equation::get_error( void )
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

/***************************************************************************/
//! @brief Public Getter: get_token_type_string | Token_type &ire_type |
/***************************************************************************/
//! @param ire_type The token type to convert to string
//! @return const char * A string representation of the token type
//! @details
//! \n This function returns a string corresponding to the given token type
//! \n It is used for debugging and error reporting purposes
//! \n If the token type is unknown, it returns "UNKNOWN"
/***************************************************************************/

const char* Equation::get_token_type_string(Token_type &ire_type)
{
	switch (ire_type)
	{
		case BASE_NUMBER:
			return "BASE_NUMBER";
		case BASE_SYMBOL:
			return "BASE_SYMBOL";
		case BASE_OPERATOR:
			return "BASE_OPERATOR";
		case BASE_OPEN:
			return "BASE_OPEN";
		case BASE_CLOSE:
			return "BASE_CLOSE";
		case SYMBOL_FUNCTION:
			return "SYMBOL_FUNCTION";
		case SYMBOL_INPUT:
			return "SYMBOL_INPUT";
		case SYMBOL_OUTPUT:
			return "SYMBOL_OUTPUT";
		case SYMBOL_VAR:
			return "SYMBOL_VAR";
		case SYMBOL_CONST:
			return "SYMBOL_CONST";
		default:
			break;
	}

	return "UNKNOWN";
}

/***************************************************************************/
//! @brief Public Getter: to_string | Equation::Token & |
/***************************************************************************/
//! @param irst_token token to be stringfied
//! @return const char *
//! @details
//! \n Convert a Token into a string. Converts into an error string if there is a problem. Handles negation and token type
/***************************************************************************/

std::string Equation::to_string( Equation::Token &irst_token )
{
	//--------------------------------------------------------------------------
    //	Construct String
    //--------------------------------------------------------------------------
    std::string s_ret;
	if ((irst_token.is_symbol()) || (irst_token.is_number()))
	{
		if (irst_token.u1_negative == false)
		{
			s_ret += std::string("+");
		}
		else //if (irst_token.u1_negative == true)
		{
			s_ret += std::string("-");
		}
	}
	else
	{
		s_ret += std::string(" ");
	}
	//Append token
	s_ret += irst_token.cl_str;
	//Also show token type
	//s_ret += std::string(" | ");
	//s_ret += Equation::get_token_type_string(irst_token.e_type);

	//--------------------------------------------------------------------------
    //	Return
    //--------------------------------------------------------------------------
    return s_ret;
}	//Public Getter: to_string | Equation::Token & |

/***************************************************************************/
//! @brief Public Getter: to_string | void |
/***************************************************************************/
//! @param
//! @return const char *
//! @details
//! \n reverse translate a tree into a token array into a string and return the string
/***************************************************************************/

bool Equation::to_string( std::string &ors_equation )
{
	DENTER_ARG("Tokens: %d", ors_equation.size() );
	//--------------------------------------------------------------------------
    //	Construct String
    //--------------------------------------------------------------------------

    //Allocate a vector for the array of token structure
    std::vector<Token> clast_tokens;
	//Reverse translate tree of token into an array of token
    bool x_fail = Equation::convert_token_tree_to_array( this->gcl_token_tree, clast_tokens);
    if (x_fail == true)
    {
		DRETURN_ARG("ERR%d: Failed to convert tree of token into array of token", __LINE__ );
		return true;
    }
	//Convert vector of token into a string
    x_fail = Equation::convert_token_array_to_string( clast_tokens, ors_equation );
    if (x_fail == true)
    {
		DRETURN_ARG("ERR%d: Failed to convert vector of token into string", __LINE__ );
		return true;
    }

	//--------------------------------------------------------------------------
    //	Return
    //--------------------------------------------------------------------------
    DRETURN_ARG("Equation: %s | Size: %d", ors_equation.c_str(), ors_equation.size() );
    return false;
}	//to_string | void

/***************************************************************************/
//! @brief Public Getter: to_string | void |
/***************************************************************************/
//! @return const char *
//! @details
//! \n reverse translate a tree into a token array into a string and return the string
/***************************************************************************/

std::string Equation::to_string( void )
{
	DENTER();
	//--------------------------------------------------------------------------
    //	Construct String
    //--------------------------------------------------------------------------

    //Allocate string
	std::string s_equation;
	bool x_fail = this->to_string( s_equation );
	if (x_fail == true)
	{
		DRETURN_ARG("ERR%d: Failed to reverse translate array of tokens...", __LINE__ );
		return std::string();
	}

	//--------------------------------------------------------------------------
    //	Return
    //--------------------------------------------------------------------------
    DRETURN_ARG("Equation: %s | Size: %d", s_equation.c_str(), s_equation.size() );
    return s_equation;
}	//to_string | void

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

bool Equation::my_public_method( void )
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

bool Equation::init_class_vars( void )
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

bool Equation::is_operator( char is8_digit )
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

bool Equation::is_symbol( char is8_digit )
{
    DENTER_ARG("Digit: >>%c<<", (is8_digit!='\0')?(is8_digit):(' ') ); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------
	//Temp return
	bool u1_ret;
    if (Equation::is_letter(is8_digit) == true)
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
//! @brief Private Static Method: parse | std::string | std::vector<std::string>& | std::vector<Equation::Token> &
/***************************************************************************/
//! @param icl_equation_string | string containing the equation to be parsed into a vector of string tokens
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Parse a string into a vector of string tokens. Basically slice the string into individual tokens.
//! \n Unary operators (+ and (- are tokenized at this stage, by deleting them and applying negation to the following token if needed
/***************************************************************************/

bool Equation::parse( std::string is_equation, std::vector<std::string>& oras_string_tokens, std::vector<Equation::Token> &orast_tokens, User::Tree<Equation::Token> &oracl_tree_tokens )
{
    DENTER_ARG("Parse: %s | Size: %d", is_equation.c_str(), int(is_equation.size()) ); //Trace Enter
    //--------------------------------------------------------------------------
    //	LINEAR PARSER
    //--------------------------------------------------------------------------
    //	The first pass translates a string into a vector of tokens with base token types

    //Try to translate an equation into an array of string tokens, and an array of token structure
    bool x_fail = Equation::convert_equation_string_to_array_token( is_equation, oras_string_tokens, orast_tokens );
	if (x_fail == true)
	{
		DRETURN_ARG("ERR%d | failed to parse an equation into an array of string tokens...\n", __LINE__ );
		return true;
	}
	//Link the decorator for the tree to print out the token
	std::string (*f_my_decorator)(Token ist_token) =
	[](Token ist_token)
	{
		return Equation::to_string( ist_token );
	};
	//Link the provided decorator to replace the default decorator
	oracl_tree_tokens.link_decorator( f_my_decorator );
	//Tree must be empty before conversion of token array to token tree
	if (oracl_tree_tokens.size() > 1)
	{
		DPRINT("Tree wasn't empty: %d | FLUSH\n", oracl_tree_tokens.size() );
		oracl_tree_tokens.flush();
	}
	//Recursively translate an array of token into a tree of tokens, starting from the root
	bool u1_ret = Equation::token_array_to_tree( orast_tokens, oracl_tree_tokens, 0 );
	if (u1_ret == true)
	{
		//Clear partial results
		oracl_tree_tokens.flush();
		DRETURN_ARG("ERR:%d | Could not convert from token array to tree...", __LINE__ );
		return true;
	}
	std::cout << "Array->Tree\n";
	oracl_tree_tokens.show(0);
	std::cout << "--------------------------------------\n";

	/*
	//Recursively
	int s32_ret = this->aggregate_tree_token_sum_diff( this->gcl_token_tree );
	if (s32_ret < 0)
	{
		//Clear partial results
		this->flush();
		DRETURN_ARG("ERR:%d | Could not aggregate sum/diff operators into wide sum operators...", __LINE__ );
		return true;
	}
	std::cout << "Aggregate\n";
	this->gcl_token_tree.show(0);
	std::cout << "--------------------------------------\n";
	*/

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG( "Number of String Tokens: %d | Number of Tokens: %d | Tree Token Size: %d", int(oras_string_tokens.size()), int(orast_tokens.size()), int(oracl_tree_tokens.size()) ); //Trace Return
    return false; //OK
} //Private Static Method: parse | const char * |

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
//! \n	-------------------------------------------------------------------
//! \n		BUG2023-05-05
//! \n	4=((((((1-2)+3)-4)+5)-6)+7)
//! \n                       ^
//! \n	- and + are both candidates, whish is the real problem?
//! \n	detecting the last symbol fixes it, but inverts all operands in chain operations
//! \n	I think it's a miscalculation of the min that lets the - pass throguh when it shoudln't
//! \n	-------------------------------------------------------------------
//! \n		BUG2023-05-16
//! \n	Y=3*4-5+6"
//! \n	Reverse translation:
//! \n	Y=(3*(4-(5+6)))
//! \n	Correct reverse translation:
//! \n	Y=(((3*4)-5)+6)
//! \n	When I have a choice of multiple operators, I have to pick the LOWEST first. I pick the highest priority non operator otherwise
//! \n	This way * gets at the bottom of the tree, - above, preserving RHS negation, then + that doesn't matter
//! \n
//! \n
//! \n
//! \n
/***************************************************************************/

bool Equation::compute_token_array_priority( std::vector<Token> &irclacl_token_array, std::vector<Token>::iterator &orclacl_highest_priority_token )
{
    DENTER_ARG("Tokens: %d", int(irclacl_token_array.size()) ); //Trace Enter
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
		Equation::compute_token_symbol_priority( *cl_token_iterator );
		//"Priority" open
		if (cl_token_iterator->e_type == Token_type::BASE_OPEN)
		{
			//Open, increase priority of what comes after
			s32_open_close_priority++;
			cl_token_iterator->s32_open_close_priority = s32_open_close_priority;
			DPRINT("Token%4d | Open | Priority: %d\n", size_t(cl_token_iterator -irclacl_token_array.begin()), s32_open_close_priority );
		}
		//"Priority" close
		else if (cl_token_iterator->e_type == Token_type::BASE_CLOSE)
		{
			//If: I have more close tokens than open tokens
			if (s32_open_close_priority <= 0)
			{
				DRETURN_ARG("ERR:%3d | Unbalanced Brackets, extra close at Token: %d", __LINE__, int(cl_token_iterator -irclacl_token_array.begin()) );
				return true;
			}
			//Open, decrease priority of what comes after
			cl_token_iterator->s32_open_close_priority = s32_open_close_priority;
			DPRINT("Token%4d | Close| Priority: %d\n", size_t(cl_token_iterator -irclacl_token_array.begin()), s32_open_close_priority );
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
			DPRINT("Token%4d | >%s< | Open Close Priority: %d | Symbol Priority %d \n", size_t(cl_token_iterator -irclacl_token_array.begin()), cl_token_iterator->cl_str.c_str() , s32_open_close_priority, cl_token_iterator->s32_symbol_priority );
		}
	}	//Scan the given array of token and compute the open/clsoe priority
	//DEBUG
	//std::cout << irclacl_token_array << "\n";

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
    //	s32_min_priority tells you the priority of the first non open non close token.
	//	when s32_min_priority is not zero, that's the number of open/close you can safely remove
	//	Remove extra parenthesis that are not needed
	//	Update the priority of what remains to avoid recomputing the priority

	//If: I have redundant priority tokens
	if (s32_min_priority > 0)
	{
		//Remember what's the highest priority bracket deleted
		int n_highest_priority_open_deleted = -1;
		//Initialize scan
		cl_token_iterator = irclacl_token_array.begin();
		//While: scan is not complete
		while (cl_token_iterator != irclacl_token_array.end())
		{
			//Redundant "Priority" open token
			if ((cl_token_iterator->e_type == Token_type::BASE_OPEN) && (cl_token_iterator->s32_open_close_priority <= s32_min_priority))
			{
				DPRINT("Delete Open %d | Priority: %d | Min Priority: %d \n", size_t(cl_token_iterator-irclacl_token_array.begin()), cl_token_iterator->s32_open_close_priority, s32_min_priority );
				//Is the highest priority deleted bracket?
				if ((n_highest_priority_open_deleted == -1) || (cl_token_iterator->s32_open_close_priority > n_highest_priority_open_deleted))
				{
					n_highest_priority_open_deleted = cl_token_iterator->s32_open_close_priority;
				}
				//Remove this element from the array
				irclacl_token_array.erase( cl_token_iterator );
				//Do not advance scan
			}
			//"Priority" close
			else if ((cl_token_iterator->e_type == Token_type::BASE_CLOSE) && (cl_token_iterator->s32_open_close_priority <= s32_min_priority))
			{
				DPRINT("Delete Close %d | Priority: %d | Min Priority: %d \n", size_t(cl_token_iterator-irclacl_token_array.begin()), cl_token_iterator->s32_open_close_priority, s32_min_priority );
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
		//If: algorithmic delition error
		if (n_highest_priority_open_deleted != s32_min_priority)
		{
			DRETURN_ARG("ERR: I was expected to delete open brackets up to %d open close priority but only deleted %d priority\n", s32_min_priority, n_highest_priority_open_deleted );
			return true;
		}
		//BUGFIX: This was super tricky
		//I'm done deleting redundant brackets and updating priority, now the minimum open close is by definition non redundant
		s32_min_priority -= n_highest_priority_open_deleted;
		//DEBUG show the tokens after deleting the redundant tokens
		DPRINT("Deleted redundant priority tokens | Tokens: %d | Min Open Close Priority: %d\n", int(irclacl_token_array.size()), s32_min_priority);
		for (cl_token_iterator = irclacl_token_array.begin(); cl_token_iterator != irclacl_token_array.end(); cl_token_iterator++ )
		{
			DPRINT("Token%4d | >%s< | Open Close Priority: %d | Symbol Priority %d \n", size_t(cl_token_iterator -irclacl_token_array.begin()), cl_token_iterator->cl_str.c_str() , cl_token_iterator->s32_open_close_priority, cl_token_iterator->s32_symbol_priority );
		}
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
    //false = no operators detected at this priority | true = at least an operator detected at this priority
	bool x_operator_detected = false;
	//Start search
	cl_token_iterator = irclacl_token_array.begin();

	bool x_continue = true;

	//Scan all tokens
	while (x_continue == true)
    {
			//Check forbracket balance
		//!@todo I can do better than repeating this code. Look to make a lambda or split hierarch and add incapsulate priority computation
		//"Equal" operator always is to be selected
		if (cl_token_iterator->cl_str[0] == Token_legend::CS8_OPERATOR_EQUAL)
		{
			//Equal found
			cl_best_iterator = cl_token_iterator;
			//Stop search
			x_continue = false;
			DPRINT("Equal\n");
		}
		//"Priority" open
		else if (cl_token_iterator->e_type == Token_type::BASE_OPEN)
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
				DRETURN_ARG("ERR:%d | Unbalanced Brackets, extra close at Token: %d", __LINE__, int(cl_token_iterator -irclacl_token_array.begin()) );
				return true;
			}
			//Close, decrease priority of what comes after
			cl_token_iterator->s32_open_close_priority = s32_open_close_priority;
			s32_open_close_priority--;
		}
		//! @todo s32_min_priority should ALWAYS be zero here?
		//If I haven't detected an high priority operator and the token has the lowest open/close priority
		else if (cl_token_iterator->s32_open_close_priority <= s32_min_priority)
		{
			//There is an algorithmic error, symbol priority is uninitialized
			if ((Config::CU1_INTERNAL_CHECKS == true) && (cl_token_iterator->s32_symbol_priority == -1))
			{
				DRETURN_ARG("ERR:%d | Symbol has uninitialized priority... | Index: %d ", __LINE__, int(cl_token_iterator -irclacl_token_array.begin()) );
				return true;
			}
			//No best token has been found yet
			else if (s32_best_priority == -1)
			{
				//If token is an operator
				if (Equation::is_token(*cl_token_iterator, Token_type::BASE_OPERATOR)==true)
				{
					//Switch detection mode. Now seek the lowest priority operator to resolve
					x_operator_detected = true;
				}
				//New best
				cl_best_iterator = cl_token_iterator;
				s32_best_priority = cl_token_iterator->s32_symbol_priority;
				DPRINT("Candidate%4d | >%s< | Open Close Priority %d | Symbol Priority %d | Min Priority %d | Default\n", size_t(cl_best_iterator -irclacl_token_array.begin()), cl_best_iterator->cl_str.c_str(), cl_token_iterator->s32_open_close_priority, cl_token_iterator->s32_symbol_priority, s32_min_priority );
			}
			//Current symbol has stronger priority then best symbol.
			//TIP: using <= instead of < inverts the order of children in same priority chains, but the result is still correct
			else if ((x_operator_detected == false) && (cl_token_iterator->s32_symbol_priority < s32_best_priority))
			{
				//If token is an operator
				if (Equation::is_token(*cl_token_iterator, Token_type::BASE_OPERATOR)==true)
				{
					//Switch detection mode. Now seek the lowest priority operator to resolve
					x_operator_detected = true;
				}
				//New best
				cl_best_iterator = cl_token_iterator;
				s32_best_priority = cl_token_iterator->s32_symbol_priority;
				DPRINT("High Priority Mode | Candidate%4d | >%s< | Open Close Priority %d | Symbol Priority %d | Min Priority %d\n", size_t(cl_best_iterator -irclacl_token_array.begin()), cl_best_iterator->cl_str.c_str(), cl_token_iterator->s32_open_close_priority, cl_token_iterator->s32_symbol_priority, s32_min_priority );
			}
			//If I detected an high priority operator token, I can only detect an operator with the same open/close priority, but LOWER symbol priority.
			else if ((x_operator_detected == true) && (Equation::is_token(*cl_token_iterator, Token_type::BASE_OPERATOR)==true) && (cl_token_iterator->s32_symbol_priority > s32_best_priority))
			{
				//New worse operator
				cl_best_iterator = cl_token_iterator;
				s32_best_priority = cl_token_iterator->s32_symbol_priority;
				DPRINT("Low Priority Mode | Candidate%4d | >%s< | Open Close Priority %d | Symbol Priority %d | Min Priority %d\n", size_t(cl_best_iterator -irclacl_token_array.begin()), cl_best_iterator->cl_str.c_str(), cl_token_iterator->s32_open_close_priority, cl_token_iterator->s32_symbol_priority, s32_min_priority );
			}
			//Current symbol has weaker priority then best symbol
			else
			{
				//Ignore it
				DPRINT("Ignore%4d | >%s< | Open Close Priority %d | Symbol Priority %d | Min Priority %d | Best Priority %d\n", size_t(cl_token_iterator -irclacl_token_array.begin()), cl_token_iterator->cl_str.c_str(), cl_token_iterator->s32_open_close_priority, cl_token_iterator->s32_symbol_priority, s32_min_priority, s32_best_priority );
			}
		}
		//If token has higher open/close priority
		else
		{
			//Ignore it
		}
		//Next token
		cl_token_iterator++;
		if (cl_token_iterator == irclacl_token_array.end())
		{
			x_continue = false;
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
	//Having deleted the open, what comes after is index +1 to be consistent with original input
	DPRINT("Token%4d | >%s< | Highest priority token\n", size_t(cl_best_iterator -irclacl_token_array.begin()), cl_best_iterator->cl_str.c_str() );
	/*
	if (( size_t(cl_best_iterator -irclacl_token_array.begin()) == 18 ) && (cl_best_iterator->cl_str[0] == '-'))
	{
		return false;
	}
	*/


    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Tokens: %d | Highest Priority Token: <%s> | %d %d", int(irclacl_token_array.size()), cl_best_iterator->cl_str.c_str(), cl_best_iterator->s32_open_close_priority, cl_best_iterator->s32_symbol_priority ); //Trace Return
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

bool Equation::compute_token_symbol_priority( Token &irst_token )
{
    DENTER_ARG_CONDITIONAL(Config::CU1_DEBUG_COMPUTE_SYMBOL_PRIORITY, "Token type: %d | Token size: %d", irst_token.e_type, int(irst_token.cl_str.size()) ); //Trace Enter
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
				s32_symbol_priority = 1;
				break;
			case Token_legend::CS8_OPERATOR_DIV:
				s32_symbol_priority = 2;
				break;

			case Token_legend::CS8_OPERATOR_DIFF:
				//Diff is not commutative, I need to preserve it's RHS
				s32_symbol_priority = 3;
				break;

			case Token_legend::CS8_OPERATOR_SUM:
				//Sum is commutative, I don't care about order
				s32_symbol_priority = 4;
				break;
		}
	}
	else if (irst_token.e_type == Token_type::BASE_SYMBOL)
	{
		s32_symbol_priority = 5;
	}
	else if (irst_token.e_type == Token_type::BASE_NUMBER)
	{
		s32_symbol_priority = 6;
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
//! @brief Private Method: convert_equation_string_to_array_token | std::string, std::vector<std::string> &, std::vector<Equation::Token> &
/***************************************************************************/
//! @return return false = OK | true = fail
//! @details
//! \n	Equation Tokenizer. Translates an equation in string form to an array of string tokens.
//! \n	2023-05-09BUGFIX "=-1" wasn't tripping the unary detection, despite being a valid token sequence. = followed by -1 number, trigger can happen if+/- is the first character
/***************************************************************************/

bool Equation::convert_equation_string_to_array_token( std::string is_equation, std::vector<std::string> &oras_token_array, std::vector<Equation::Token> &orast_token_array )
{
	DENTER_ARG("Parse: %s | Size: %d", is_equation.c_str(), int(is_equation.size()) ); //Trace Enter
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
	orast_token_array = std::vector<Equation::Token>();

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
    //Detect if the previous token allows for unary detection
    bool x_previous_token_can_trip_unary_detection = true;
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
                if (Equation::is_number(s8_digit) == true)
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
                else if (Equation::is_symbol(s8_digit) == true)
                {
					//Append digit to the token
					cl_token.cl_str.push_back( s8_digit );
					e_fsm_state = Fsm_state::TOKEN_SYMBOL;
                }
                //Detect Operator
                else if (Equation::is_operator(s8_digit))
                {
					//Special Unary Positive Detection. "(+"
					if ((x_previous_token_can_trip_unary_detection == true) && (s8_digit == Token_legend::CS8_OPERATOR_SUM))
					{
						//Detected a + unary operator, It has no effect other than deleting the token
						u1_unary_operator = true;
                        u1_unary_negation = false;
                        DPRINT("Unary + detected\n");
					}
					//Special Unary Negative Detection "(-"
					else if ((x_previous_token_can_trip_unary_detection == true) && (s8_digit == Token_legend::CS8_OPERATOR_DIFF))
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
				else if ((Equation::is_number(s8_digit)) || (s8_digit == Token_legend::CS8_DECIMAL_SEPARATOR))
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
				else if ((Equation::is_symbol(s8_digit) == true) || (Equation::is_number(s8_digit) == true))
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
				DPRINT("ERR%d: Unknown FSM state >>%d<<... Reset FSM\n", __LINE__, int(e_fsm_state) );
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
			//Special detection of previous token that can trip the Unary detection
			x_previous_token_can_trip_unary_detection = (cl_token.e_type == Token_type::BASE_OPEN) || is_token_type_operator( cl_token.e_type );
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
				DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Token fully decoded: %c%s | type: %d | size: %d\n", (cl_token.u1_negative)?('-'):(' '),cl_token.cl_str.c_str(), int(cl_token.e_type), int(cl_token.cl_str.size()) );
				DPRINT_CONDITIONAL( Config::CU1_PARSER_EXTENDED_DEBUG, "Tokens decoded: %d\n", int(orast_token_array.size()) );
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
	DPRINT("Equations decoded into %d tokens\n", int(orast_token_array.size()) );
	for (std::vector<Token>::iterator cl_token_iter = orast_token_array.begin();cl_token_iter != orast_token_array.end();cl_token_iter++)
	{
		DPRINT("Token: >>%s<< | Type: %d | Size: %d\n", cl_token_iter->cl_str.c_str(), int(cl_token_iter->e_type), int(cl_token_iter->cl_str.size()) );
	}

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Decoded %d tokens", int(oras_token_array.size()) );
    return false;
}   //Private Method: convert_equation_string_to_array_token | std::string, std::vector<std::string> &, std::vector<Equation::Token> &

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

bool Equation::token_array_to_tree( std::vector<Token> &irclacl_token_array, Tree<Token> &orcl_token_tree, size_t in_index_father )
{
    DENTER_ARG("Token Array Size: %d | Father %d", int(irclacl_token_array.size()), int(in_index_father) ); //Trace Enter
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
    bool u1_ret = Equation::compute_token_array_priority( irclacl_token_array, cl_core_iterator );
	if (u1_ret == true)
	{
		DRETURN_ARG("ERR:%d | Priority computation failed", __LINE__);
		return true;
    }
    DPRINT("Core Token: >%s< | Size: %d | Open/Close Priority: %d | Symbol Priority: %d\n", cl_core_iterator->cl_str.c_str(), int(cl_core_iterator->cl_str.size()), cl_core_iterator->s32_open_close_priority, cl_core_iterator->s32_symbol_priority );

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
	DPRINT("LHS Tokens: %d | RHS Tokens: %d\n", int(clast_lhs.size()), int(clast_rhs.size()) );

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
	if (cl_core_iterator->cl_str[0] == Token_legend::CS8_OPERATOR_EQUAL)
	{
		//If I get an equal operator that is not the root of the tree
		if ((in_index_father != 0) || (orcl_token_tree.size() != 1))
		{
			DRETURN_ARG("ERR:%d | Equal not as root of the tree! Father: %d | Tree size: %d", __LINE__, in_index_father, orcl_token_tree.size() );
			return true;
		}
		DPRINT("ROOT: >%s<\n", cl_core_iterator->cl_str.c_str() );
		//Write the payload on the root
		orcl_token_tree[0] = *cl_core_iterator;
		//Show the tree
		//orcl_token_tree.print();

		n_next_father = in_index_father;
		DPRINT("LHS: >%s<\n", cl_core_iterator->cl_str.c_str() );
	}
	else
	{
		//If the root hasn't been assigned yet
		if ((orcl_token_tree.size() == 1) && (in_index_father == 0) && (orcl_token_tree[0].cl_str[0] != Token_legend::CS8_OPERATOR_EQUAL))
		{
			DRETURN_ARG("ERR:%d | Root is not equal operator!", __LINE__ );
			return true;
		}
		//Add a child to the current branch holding the Payload of the core token found
		size_t n_child_index = orcl_token_tree.create_child( in_index_father, *cl_core_iterator );
		if (n_child_index >= orcl_token_tree.size() )
		{
			DRETURN_ARG("ERR:%d | Failed to add branch to tree | index: %d", __LINE__, int(n_child_index));
			return true;
		}
		n_next_father = n_child_index;
		//Show the tree
		//orcl_token_tree.print();
		//std::cout << "--------------------------------------\n";
	}
	//Propagate failure state of recursive calls
	bool x_fail = false;
	//Execute a recursive tree construction on the LHS and RHS sides of the equation
	if (clast_lhs.size() > 0)
	{
		//Recursive tree construction on LHS
		x_fail |= token_array_to_tree( clast_lhs, orcl_token_tree, n_next_father );
		DPRINT("LHS of size %d under father %d\n", clast_lhs.size(), n_next_father );
	}
	if (clast_rhs.size() > 0)
	{
		//Recursive tree construction on RHS
		x_fail |= token_array_to_tree( clast_rhs, orcl_token_tree, n_next_father );
		DPRINT("RHS of size %d under father %d\n", clast_rhs.size(), n_next_father );
	}

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("%s", (x_fail)?("FAIL"):("PASS") ); //Trace Return
    return x_fail;	//Propagate failure
}   //Static Private Method | token_array_to_tree | std::vector<Token> & | Tree<Token> & |

/***************************************************************************/
//! @brief Static Private Method | token_array_to_tree | std::vector<Token> & | Tree<Token> & |
/***************************************************************************/
//! @param ircl_tree_root | tree of tokens
//! @param orast_token_array | array of Tokens filled by method
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Reverse translation from a tree of tokens to a vector of token. Will add open and close tokens where needed
//! \n Algorithm:
//! \n	RULES:
//! \n	>Not first child?
//! \n		>Not x_already_processed?
//! \n			>APPEND this.father
//! \n	>Symbol/Number?
//! \n		>First Child?
//! \n			>APPEND Open "("
//! \n		>APPEND this
//! \n	>Operator?
//! \n		x_already_processed == false?
//! \n			Y>APPEND this with x_already_processed = true
//! \n			Y>APPEND this.children
//! \n		x_already_processed == true?
//! \n			Y>APPEND Close ")"
//! \n	@todo handle functions E.G. sin( 30.0 ) E.G. Int( 0, INF, 1/x)
//! \n
//! \n	E.g. A+B-C=100
//! \n	TOKEN	|	LHS		|	RHS		|	OP
//! \n	=		|	+		|	100		|	0/0 L0
//! \n	Push +
//! \n	Push 100
//! \n
//! \n	TOKEN	|	LHS		|	RHS		|	OP
//! \n	+		|	A		|	-		|	0/1	L1
//! \n	Push A
//! \n	Push -
//! \n
//! \n	TOKEN	|	LHS		|	RHS		|	OP
//! \n	A		|			|			|	0/1	L2
//! \n	>>Write OPEN "(" << Suppress the first bracket
//! \n	>>Write "A"
//!	\n	Pop this
//! \n
//! \n	TOKEN	|	LHS		|	RHS		|	OP
//! \n	-		|	B		|	C		|	1/1 L2
//! \n	Push B
//! \n	Push C
//! \n
//! \n	TOKEN	|	LHS		|	RHS		|	OP
//! \n	B		|			|			|	0/1 L3
//! \n	>>Write Open "("
//! \n	>>Write Symbol "B"
//!	\n	Pop this
//! \n
//! \n	TOKEN	|	LHS		|	RHS		|	OP
//! \n	C		|			|			|	1/1 L3
//! \n	>>Write Father "-"
//! \n	>>Write Symbol "C"
//!	\n	Pop this
//! \n
//! \n	TOKEN	|	LHS		|	RHS		|	OP
//! \n	-		|			|			|	1/1 L3
//! \n	>>Write Father "-"
//! \n	>>Write Symbol "C"
//! \n
//! \n	TOKEN	|	LHS		|	RHS		|	OP		|	NOTE
//! \n	-		|			|			|	1/1 L3	|	I reprocess the node "-", this time I pop it and close
//! \n	>>Write Symbol ")"
//!	\n	Pop this
//! \n
/***************************************************************************/

bool Equation::convert_token_tree_to_array( Tree<Token> &ircl_tree_root, std::vector<Token> &orast_token_array )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------

    //If empty tree
    if (ircl_tree_root.size() <= 0)
    {
		DRETURN_ARG("ERR%d: Empty Tree %d...", __LINE__, ircl_tree_root.size() );
		return true;
    }
    //I need to have root = with an LHS and a RHS, i reverse translate those, and merge the arrays together
	if (Equation::is_token_operator_equal(ircl_tree_root[0]) == false)
	{
		DRETURN_ARG("ERR%d: Tree root is not operator equal %s...", __LINE__, ircl_tree_root[0].to_string().c_str() );
		return true;
	}
	//Default tokens
	const User::Equation::Token cst_token_open = { std::string("("), Equation::Token_type::BASE_OPEN, 0, 0, false };
	const User::Equation::Token cst_token_close = { std::string(")"), Equation::Token_type::BASE_CLOSE, 0, 0, false };

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

	//! @brief stack entry. Minimum information required to do a reverse navigation of the tree. Can't be done with Tree::iterator because of additional metadata required
    struct Token_pseudorecursive_decoding
    {
		//
		size_t n_index_father;
		size_t n_index_own;
		size_t n_priority_max;
		size_t n_priority_own;
		size_t n_level;
		//true = when procesed the token is to be removed from the queue
		bool x_already_processed;
		//Fill the structure from a Node, cannot know the number of siblings (n_priority_max) and the level (depth could be wrong)
		bool load( User::Tree<User::Equation::Token>::Node irst_source, size_t in_priority_max, size_t in_level )
		{
			this->n_index_father = irst_source.n_index_father;
			this->n_index_own = irst_source.n_own_index;
			this->n_priority_max = in_priority_max;
			this->n_priority_own = irst_source.n_own_priority;
			this->n_level = in_level;
			this->x_already_processed = false;
			return false;
		}
		//Stringify the stack entry
		std::string to_string( void )
		{
			return std::string("Father: ") +std::to_string(this->n_index_father) + std::string(" | Index: ") + std::to_string(this->n_index_own) + std::string(" | Priority Max: ") + std::to_string(this->n_priority_max) + std::string(" | Priority Own: ") + std::to_string(this->n_priority_own) + std::string(" | Level: ") + std::to_string(this->n_level);
		}
    };
    //Minimum level that trigger OPEN/CLOSE
    const size_t cn_min_open_close_append = 0;
	//Temp stack element
    Token_pseudorecursive_decoding st_stack_entry;
    Token_pseudorecursive_decoding st_stack_child;
	//Allocate the stack
	std::stack<Token_pseudorecursive_decoding> ast_pseudorecursive_stack;
	//Temp level
    size_t n_old_level = 0;
	//Nested Open Close nesting. start from no breackets
	size_t n_open_close_priority = 0;
	//memory flag for the CLOSE. When I processed a last child, I need to POP the father operators that are reprocessed
	bool x_last_child_processed = false;

	bool x_pop = false;
	//Load the root
    st_stack_entry.load( ircl_tree_root.get_node(0), 0, n_old_level );
	ast_pseudorecursive_stack.push( st_stack_entry );
	DPRINT("PUSH | Token: %s | Size: %d | %s\n", ircl_tree_root[st_stack_entry.n_index_own].to_string().c_str(), ast_pseudorecursive_stack.size() ,st_stack_entry.to_string().c_str() );
	//Allocate vector of children
	std::vector<size_t> an_children;
	//While there are stack elements to be processed
	while (ast_pseudorecursive_stack.size() > 0)
	{
		//PEEK
		//Get the next node information
		st_stack_entry = ast_pseudorecursive_stack.top();
		DPRINT("PEEK | Token: %s | Size: %d | Stack: %s\n", ircl_tree_root[st_stack_entry.n_index_own].to_string().c_str(), ast_pseudorecursive_stack.size(), st_stack_entry.to_string().c_str() );
		ast_pseudorecursive_stack.pop();
		//REVERSE DECODE INTO TOKEN
		//If going down one level and not first bracked, OPEN
		if (st_stack_entry.n_level == n_old_level +1)
		{
			//
			if (st_stack_entry.n_level >= cn_min_open_close_append +2)
			{
				orast_token_array.push_back( cst_token_open );
				DPRINT("APPEND | OPEN | Tokens: %d | Level %d\n", orast_token_array.size(), st_stack_entry.n_level );
			}
			else
			{
				DPRINT("SKIP | OPEN | Level %d\n", st_stack_entry.n_level );
			}
		}
		Token &rst_token = ircl_tree_root[st_stack_entry.n_index_own];
		//If the token is NOT the first child, append also the father
		//e.g. 3 +2 +4 you need to write the father on each later child
		if ((st_stack_entry.n_priority_own != 0) && (st_stack_entry.x_already_processed == false))
		{
			Token &rst_token_father = ircl_tree_root[st_stack_entry.n_index_father];
			//Append the father
			orast_token_array.push_back( rst_token_father );
			DPRINT("APPEND FATHER | %s | Tokens: %d\n", rst_token_father.to_string().c_str(), orast_token_array.size() );
		}
		//if token is a symbol/number append it to the token vector
		if (Equation::is_token_type_symbol(rst_token.e_type) || Equation::is_token_type_number(rst_token.e_type))
		{
			if ((Config::CU1_INTERNAL_CHECKS == true) && (st_stack_entry.x_already_processed == true))
			{
				DRETURN_ARG("ERR%d: a symbol should have been popped when processed, it's still here!!!");
				orast_token_array.clear();
				return true;
			}
			/*
			if ((Config::CU1_INTERNAL_CHECKS == true) && (ircl_tree_root.count_children( st_stack_entry.n_index_own ) > 0))
			{
				DRETURN_ARG("ERR%d: A symbol should not have children...");
				orast_token_array.clear();
				return true;
			}
			*/
			//Append the token
			orast_token_array.push_back( rst_token );
			DPRINT("APPEND OWN | %s | Tokens: %d\n", rst_token.to_string().c_str(), orast_token_array.size() );
		}
		//Operator
		else if (Equation::is_token_type_operator(rst_token.e_type))
		{
			//If wasn't processed before
			if (st_stack_entry.x_already_processed == false)
			{
				//Symbols are to be removed from queue when decoded
				st_stack_entry.x_already_processed = true;
				//Repush the item with the processed flag to true
				ast_pseudorecursive_stack.push( st_stack_entry );
				DPRINT("PUSH*| Token: %s | Size: %d | %s\n", ircl_tree_root[st_stack_entry.n_index_own].to_string().c_str(), ast_pseudorecursive_stack.size() ,st_stack_entry.to_string().c_str() );
				//Get the children of this node
				ircl_tree_root.get_children( st_stack_entry.n_index_own, an_children );
				//Push the children, push in reverse order, so that the highest priority child is popped first
				for (std::vector<size_t>::reverse_iterator cl_iterator = an_children.rbegin();cl_iterator != an_children.rend(); cl_iterator++ )
				{
					//Push the child on top of the stack
					st_stack_child.load( ircl_tree_root.get_node( (*cl_iterator) ), st_stack_entry.n_priority_own, st_stack_entry.n_level +1 );
					ast_pseudorecursive_stack.push( st_stack_child );
					DPRINT("PUSH | Token: %s | Size: %d | %s\n", ircl_tree_root[(*cl_iterator)].to_string().c_str(), ast_pseudorecursive_stack.size() ,st_stack_child.to_string().c_str() );
				}
			}
			//Was processed before
			else
			{
				//If it's not a blank bracket
				if (st_stack_entry.n_level > cn_min_open_close_append)
				{
					orast_token_array.push_back( cst_token_close );
					DPRINT("APPEND | CLOSE | Tokens: %d | Level %d\n", orast_token_array.size(), st_stack_entry.n_level );
				}
				else
				{
					DPRINT("SKIP | CLOSE | Level %d\n", st_stack_entry.n_level );
				}
			}
		}
		else
		{
			DRETURN_ARG("ERR%d: Token not implemented yet...", __LINE__ );
			orast_token_array.clear();
			return true;
		}
		//Remember level for next pseudorecirsive cycle
		n_old_level = st_stack_entry.n_level;
	}
    DPRINT("Scan: ");
    //Scan the tree
    for (auto cl_iterator_tree = orast_token_array.begin();cl_iterator_tree != orast_token_array.end();cl_iterator_tree++)
    {
		DPRINT_NOTAB(" %s |", (*cl_iterator_tree).cl_str.c_str());
    }
    DPRINT_NOTAB("\n");

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return false;	//OK
}   //Static Private Method | token_array_to_tree | std::vector<Token> & | Tree<Token> & |

/***************************************************************************/
//! @brief Private Method: convert_token_array_to_string | std::vector<Token> & | std::string &
/***************************************************************************/
//! @param irast_token_array | reference to array of tokens, source of the reverse translation
//! @param ors_equation | string where the result is loaded
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Reverse translation from an array of tokens to a string
/***************************************************************************/

bool Equation::convert_token_array_to_string( std::vector<Token> &irast_token_array, std::string &ors_equation )
{
    DENTER_ARG("Tokens: %d", irast_token_array.size() ); //Trace Enter
    //--------------------------------------------------------------------------
    //	INIT
    //--------------------------------------------------------------------------

    if ((Config::CU1_EXTERNAL_CHECKS == true) && (false))
    {

		return true;
    }

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    for (auto cl_iterator_tree = irast_token_array.begin();cl_iterator_tree != irast_token_array.end();cl_iterator_tree++)
    {
		//Token
		//Equation::Token &rst_token = (*cl_iterator_tree);
		//If token is negated
		if ((*cl_iterator_tree).u1_negative == true)
		{
			//Token_legend::CS8_OPERATOR_DIFF
			ors_equation += std::string("-");
		}
		//Append token
		ors_equation += (*cl_iterator_tree).cl_str;
    }
    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Equation: %s | length: %d", ors_equation.c_str(), ors_equation.size() ); //Trace Return
    return false;	//OK
}   //Private Method: convert_token_array_to_string | std::vector<Token> & | std::string &

/***************************************************************************/
//! @brief Static Private Method | aggregate_tree_token_sum_diff | Tree<Token> & |
/***************************************************************************/
//! @param ircl_token_tree | tree of tokens
//! @return int | -1 fail | return number of tokens merged
//! @details
//! \n	Within a tree of tokens, search for sum and diff operators, aggregate them in sum operators with a greater number of leaves
//! \n	Navigate the tree
//! \n	search for a node whose children are ALL numbers/symbols and whose father, is a sum/diff operator
//! \n	the children are promoted as children of the father, if diff, apply negation.
//! \n	the node is destroyed when it has no more children
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
//! \n
//! \n	Aggregate sum/diff needs to transform - into + and offload the negative into token negation
//!	\n when I find a candidate, I need to turn all - into +, and remember what needs to be sign flipped
//! \n	e.g.
//! \n 	+1	+2	+3 	+4
//! \n	+	+1	+2	+3	+4
//! \n
//! \n 	-1 +2 +3 +4
//! \n	+	-1	+2	+3	+4
//! \n	-					+				+
//! \n		+1					-1				-1
//! \n		+					+2				+2
//! \n			+2				+				+3
//! \n			+					+3			+4
//! \n				+3				+4
//! \n				+4
//! \n
//! \n 	-1 +2 -3 +4
//! \n	-					+				+
//! \n		+1					-1				-1
//! \n		+					+2				+2
//! \n			+2				-				-3
//! \n			-					+3			+4
//! \n				+3				+4
//! \n				+4
//! \n	1 - 2 + 3 - 4
//! \n 	+1  - +2  + +3  - +4
//! \n	-					+!				+
//! \n		+1					+1				+1
//! \n		+					-2!				-2
//! \n			+2				-				+3
//! \n			-					+3			-4!
//! \n				+3				+4
//! \n				+4
/***************************************************************************/

int Equation::aggregate_tree_token_sum_diff( Tree<Token> &ircl_tree_root )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //Performance counters
    size_t n_cnt_ereased = 0;
    size_t n_cnt_moved = 0;
    //List of children of target node, no need to deallocate
	std::vector<size_t> an_index_children;
	//Remember the tree size. Used for loop protection
    size_t n_mem_num_nodes = ircl_tree_root.size();
    //Start from the node after the root, as the root cannot be aggregated as the root has no father
    size_t n_index_token = 1;
    //While scan is not complete
	while (n_index_token < ircl_tree_root.size())
	{
		//Get the index of the father of the current token
		size_t n_index_father = ircl_tree_root.get_index_father( n_index_token );
		if (n_index_father >= ircl_tree_root.size())
		{
			DRETURN_ARG("ERR%d | Failed to get father index %d\n", __LINE__, n_index_father );
			return -1;
		}
		//The node is an aggregation candidate
		if
		(
			//The node is a sum/diff operator
			(Equation::is_operator_sum_diff( ircl_tree_root[n_index_token] ) == true) &&
			//It's father is a sum/diff operator
			(Equation::is_operator_sum_diff( ircl_tree_root[n_index_father] ) == true)
		)
		{
			//This token is a candidate for aggregation.
			//To be selected it needs to have ONLY symbols/numbers as children? NO. I can promote the subtrees upward!
			DPRINT("Candidate %d\n", n_index_token );
				//DIFF HANDLING
			//I need to turn all - operators into + operators and offload the negation to the individual tokens


			//While the target node has children
			do
			{
				//get an array filled with all the children of this node
				bool x_fail = ircl_tree_root.get_children( n_index_token, an_index_children );
				if (an_index_children.size() > 0)
				{
					DPRINT("Children: %d\n", an_index_children.size() );
					//promote the children by moving the child with all its children upward
					bool x_fail = ircl_tree_root.move( an_index_children[0], n_index_father, Tree<Token>::Move_mode::SUBTREE );
					if (x_fail == true)
					{
						DRETURN_ARG("ERR%d | Failed to move node %d under new father %d\n", an_index_children[0], n_index_father );
						return -1;
					}
					else
					{
						n_cnt_moved++;
					}
				}
			}
			//while the node has children
			while (an_index_children.size() > 0);
			//Here I moved all children of candidate under the father
			//Delete the now useless childless node
			bool x_fail = ircl_tree_root.erease( n_index_token, Tree<Token>::Erease_mode::NODE );
			if (x_fail == true)
			{
				DRETURN_ARG("ERR%d | Failed to erease node %d", n_index_token );
				return -1;
			}
			else
			{
				n_cnt_ereased++;
			}
			//This may have scrambled the indexes, I need to rescan the tree
			//! @todo I should restart the scan from the earliest modified node, but right now from outside the tree I can't see this information. It's safer to just invalidate the scan and restart
			n_index_token = 1;
			//Loop protection: The tree now has one fewer nodes
			if ( n_mem_num_nodes != (ircl_tree_root.size() +1) )
			{
				DRETURN_ARG("ERR:%d | Aggregate operation should have resulted in one fewer nodes in the tree. Before: %d | After: %d", __LINE__, n_mem_num_nodes, ircl_tree_root.size() );
				return -1;
			}
			else
			{
				//Update memory
				n_mem_num_nodes = ircl_tree_root.size();
			}

		}	//is an aggregation candidate
		//Not an aggregation candidate
		else
		{
			//Next candidate
			n_index_token++;
		}
	}	//While scan is not complete

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Ereased: %d | Moved: %d", n_cnt_ereased, n_cnt_moved ); //Trace Return
    return 0;	//OK
}   //Static Private Method | aggregate_tree_token_sum_diff | Tree<Token> & |

/***************************************************************************/
//! @brief Private Method | flush | void
/***************************************************************************/
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n flush the token array and the token tree
/***************************************************************************/

bool Equation::flush( void )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //Clear the array of tokens
    /*
    this->gclacl_tokens.clear();
    if (this->gclacl_tokens.size() != 0)
    {
		DRETURN_ARG("ERR%d | CRITICAL ERROR!!! COULD NOT CLEAR VECTOR", int(this->gclacl_tokens.size()) );
		return true;
    }
    */

    //Clear the array of tokens
    this->gcl_token_tree.flush();
    if (this->gcl_token_tree.size() != 1)
    {
		DRETURN_ARG("ERR%d | CRITICAL ERROR!!! COULD NOT FLUSH TREE", int(this->gcl_token_tree.size()) );
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

bool Equation::report_error( const char *ips8_error_code )
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

bool Equation::error_recovery( void )
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

bool Equation::my_private_method( void )
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
