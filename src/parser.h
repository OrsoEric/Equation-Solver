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

/**********************************************************************************
**  ENVIROMENT VARIABILE
**********************************************************************************/

#ifndef EQUATION_PARSER_H_
    #define EQUATION_PARSER_H_

/**********************************************************************************
**  GLOBAL INCLUDES
**********************************************************************************/

#include <vector>

#include "tree.hpp"
//#include "tree_interface.h"

/**********************************************************************************
**  DEFINES
**********************************************************************************/

/**********************************************************************************
**  MACROS
**********************************************************************************/

/**********************************************************************************
**  NAMESPACE
**********************************************************************************/

//! @namespace custom namespace
namespace User
{

/**********************************************************************************
**  TYPEDEFS
**********************************************************************************/

/**********************************************************************************
**  PROTOTYPE: STRUCTURES
**********************************************************************************/

/**********************************************************************************
**  PROTOTYPE: GLOBAL VARIABILES
**********************************************************************************/

/**********************************************************************************
**  PROTOTYPE: CLASS
**********************************************************************************/

/************************************************************************************/
//! @class      Equation_parser
/************************************************************************************/
//!	@author     Orso Eric
//! @version    2022-06-DD
//! @brief      xxx
//! @copyright  BSD 3-Clause License Copyright (c) 2020, Orso Eric
//! @details
//! \n This class translates an equation in string form into an equation in tree form
//! \n 2022-08-09 Implements Unary +/- Operators
//! \n 2022-08-09 Functions work out of the box. It's a symbol with leaves. It's parsed correctly.
/************************************************************************************/

class Equation_parser
{
    //Visible to all
    public:
		/*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC ENUMS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //! @brief Error codes of the class
        typedef union _Error_code
        {
			//No error
			static constexpr const char *CPS8_OK = "OK";
			//Generic error
			static constexpr const char *CPS8_ERR = "ERR";
			//FSM Error
			static constexpr const char *CPS8_ERR_FSM = "ERR:FSM";
			//Invalid user digit
			static constexpr const char *CPS8_ERR_USER_DIGIT = "ERR:FORBIDDEN DIGIT";
			//Unbalanced Brackets
			static constexpr const char *CPS8_ERR_UNBALANCED_BRACKETS = "ERR:Unbalanced Brackets";
        } Error_code;

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC TYPEDEFS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

		//! @brief Describe the token type
		enum Token_type
        {
				//Base symbols. Decoded by the linear parser first step
			//Generic Number
			BASE_NUMBER,
			//Generic Symbol
			BASE_SYMBOL,
			//Generic Operator
			BASE_OPERATOR,
			//Priority and argument operators
			BASE_OPEN,
			BASE_CLOSE,

				//Specialized Symbols. Decoded by the tree parser translator
			//Symbol is a function with arguments
			SYMBOL_FUNCTION,
			//Symbol is an input variable name
			SYMBOL_INPUT,
			//Symbol is an output variable name
			SYMBOL_OUTPUT,
			//Symbol is a variable
			SYMBOL_VAR,
			//Symbol is a constant
			SYMBOL_CONST,

			//Unknown type
			UNKNOWN,
        };
        //! @brief Describe a token. A token can be a symbol, a number or an operator. Symbols are further specialized as variable, function names, etc...
        struct Token
        {
			//String containing the token
			std::string cl_str;
			//Token type as decoded by the parser. Token type is decoded
			Token_type e_type;
			//Token priority. Priority is forced by open/close operators
			int s32_open_close_priority;
			//Token priority. Piriority due to the symbol itself. e.g. = is higher priority than *
			int s32_symbol_priority;
			//true = the token is applied with negative sign, it's addictive to diff and sum operators
			bool u1_negative;
			//Define equal operator between tokens
			friend bool operator==(const Token& lhs, const Token& rhs)
			{
				if (lhs.cl_str != rhs.cl_str)
				{
					DPRINT("Unequal string | LHS: %s | RHS: %s\n", lhs.cl_str.c_str(), rhs.cl_str.c_str() );
					return false;
				}
				if (lhs.e_type != rhs.e_type)
				{
					DPRINT("Unequal type | LHS: %d | RHS: %d\n", lhs.e_type, rhs.e_type );
					return false;
				}
				if (lhs.s32_open_close_priority != rhs.s32_open_close_priority)
				{
					DPRINT("Unequal open close | LHS: %d | RHS: %d\n", lhs.s32_open_close_priority, rhs.s32_open_close_priority );
					return false;
				}
				if (lhs.s32_open_close_priority != rhs.s32_open_close_priority)
				{
					DPRINT("Unequal priority | LHS: %d | RHS: %d\n", lhs.s32_symbol_priority, rhs.s32_symbol_priority );
					return false;
				}
				if (lhs.s32_open_close_priority != rhs.s32_open_close_priority)
				{
					DPRINT("Unequal negation | LHS: %s | RHS: %s\n", lhs.s32_symbol_priority?"-":"+", rhs.s32_symbol_priority?"-":"+" );
					return false;
				}
				return true;
			}
			//Defiene unequal operator
			friend bool operator!=(const Token& lhs, const Token& rhs)
			{
				return (!(lhs == rhs));
			}

        };

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  CONSTRUCTORS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Empty Constructor
        Equation_parser( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  DESTRUCTORS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Empty destructor
        ~Equation_parser( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC OPERATORS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC SETTERS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Parse a string as an equation
        bool parse( std::string is_equation );
        bool parse( const char *ipcs8_equation_string )
        {
			return parse( std::string( ipcs8_equation_string ) );
        }

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC GETTERS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //! @brief return reference to the array of tokens
        std::vector<std::string> get_array_of_token( void )
        {
			return this->gclacl_tokens;
        }
        //! @brief return the tree of token that represent the equation
        User::Tree<Token> get_tree_of_token( void )
        {
			return this->gcl_token_tree;
        }
        //Get current error state of the library
        const char *get_error( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC TESTERS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Reverse translation of a tree of tokens back to an equation is string form
        std::string tree_to_equation( void );
		//Equation_parser public method
        bool my_public_method( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC STATIC METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC VARS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

    //Visible to derived classes
    protected:
        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PROTECTED METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PROTECTED VARS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

    //Visible only inside the class
    private:
        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE ENUM
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

		//! @brief Configurations of the class
        typedef union _Config
        {
            //Checks to be performed on user dependent data
			static const bool CU1_EXTERNAL_CHECKS = true;
			//Checks to be performed on input dependent on internal algorithms
			static const bool CU1_INTERNAL_CHECKS = true;
			//Show extended parser debug strings on log
			static const bool CU1_PARSER_EXTENDED_DEBUG = true;
            //Enable the detailed debug of individual functions
			static const bool CU1_DEBUG_COMPUTE_SYMBOL_PRIORITY = false;
        } Config;

		//! @brief Legend of all special tokens recognized by the parser
        typedef union _Token_legend
        {
			//Numeric separator for decimal numbers
			static const char CS8_THOUSAND_SEPARATOR = ',';
			static const char CS8_DECIMAL_SEPARATOR = '.';
			//Force priority of token resolution
			static const char CS8_PRIORITY_OPEN = '(';
			static const char CS8_PRIORITY_CLOSE = ')';
			//Operators
			static const char CS8_OPERATOR_EQUAL = '=';
			static const char CS8_OPERATOR_SUM = '+';
			static const char CS8_OPERATOR_DIFF = '-';
			static const char CS8_OPERATOR_MUL = '*';
			static const char CS8_OPERATOR_DIV = '/';
			//Allowed symbol digits
			static const char CS8_SYMBOL_DIGIT_UNDERSCORE = '_';

        } Token_legend;

        //! @brief states of the parser FSM
        typedef enum _Fsm_state
        {
			//Machine is IDLE and searching for the beginning of the next token
			SEEK_NEXT_TOKEN,
			//FSM is parsing a number
			TOKEN_NUMBER,
			//FSM is parsing a symbol
			TOKEN_SYMBOL,
        } Fsm_state;

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE TYPEDEFS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE INIT
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Initialize class vars
        bool init_class_vars( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE TESTER
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //! @brief true = digit is a number
        static bool is_number( char is8_digit )
        {
			return ((is8_digit >= '0') && (is8_digit <= '9'));
        }
        //! @brief true = digit is a lower case letter
        static bool is_letter_lower_case( char is8_digit )
        {
			return ((is8_digit >= 'a') && (is8_digit <= 'z'));
        }
        //! @brief true = digit is an upper case letter
        static bool is_letter_upper_case( char is8_digit )
        {
			return ((is8_digit >= 'A') && (is8_digit <= 'Z'));
        }
        //! @brief true = digit is a letter
        static bool is_letter( char is8_digit )
        {
			return ((Equation_parser::is_letter_lower_case( is8_digit )) || (Equation_parser::is_letter_upper_case( is8_digit )));
        }
        //returns true if the digit is an operator token
		static bool is_operator( char is8_digit );
		//Return true if a token is of the type under test
		//bool is_operator( Token &irst_token, Token_legend ie_token_type );
		//returns true if the digit is a symbol digit
		static bool is_symbol( char is8_digit );

		/*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE STATIC METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Equation Tokenizer. Translates an equation in string form to an array of string tokens.
        static bool equation_to_token_array( std::string is_equation, std::vector<std::string> &oras_token_array, std::vector<Token> &orast_token_array );
		//Recursive function that finds the highest priority token, and push that into the tree. Recursively push more tokens.
        static bool token_array_to_tree( std::vector<Token> &irclacl_token_array, Tree<Token> &orcl_token_tree, size_t in_index_father );
        //Reverse translation from a tree of tokens to a vector of token. Will add open and close tokens where needed
        static bool token_tree_to_array( Tree<Token> &ircl_token_tree, std::vector<Token> &irast_token_array );
        //Takes a vector of tokens, and compute priority
        static bool compute_token_array_priority( std::vector<Token> &irclacl_token_array, std::vector<Token>::iterator &orclacl_highest_priority_token );
		//Compute the priority of a token removed from the open/close priority. Used to decide precedence between operators
        static bool compute_token_symbol_priority( Token &irst_token );
		//Within a tree of tokens, search for sum and diff operators, and use only sum operators with a greater number of leaves | -1 fail | return number of tokens merged
        static int aggregate_tree_token_sum_diff( Tree<Token> &ircl_token_tree );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //! @brief flush the token array and the token tree
        bool flush( void );
        //Report an error. return false: OK | true: Unknown error code
        bool report_error( const char *ips8_error_code );
        //Tries to recover from an error. Automatically called by get_error. return false = OK | true = fail
        bool error_recovery( void );
        //Equation_parser method to copy the code
        bool my_private_method( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PUBLIC FRIENDS METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Overloads the std stream operator for Token
        friend std::ostream& operator<<( std::ostream& icl_stream, const Token &irst_rhs );
        //Overloads the std stream operator to print out Arrays of Tokens
		friend std::ostream& operator<<( std::ostream& icl_stream, std::vector<Token> &irclast_tokens );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE VARS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //! @brief Error code of the class
        const char *gps8_error_code;
        //! @brief Array of tokens
        std::vector<std::string> gclacl_tokens;
        //! @brief Tree representing an equation
        Tree<Token> gcl_token_tree;

};	//End Class: Equation_parser

/**********************************************************************************
**  NAMESPACE
**********************************************************************************/

}	//end namespace

#else
    #warning "Multiple inclusion of hader file EQUATION_PARSER_H_"
#endif
