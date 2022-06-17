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

#ifndef TOKENIZER_H_
    #define TOKENIZER_H_

/**********************************************************************************
**  GLOBAL INCLUDES
**********************************************************************************/

#include <vector>

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
//! @class      Tokenizer
/************************************************************************************/
//!	@author     Orso Eric
//! @version    2020-MM-DD
//! @brief      xxx
//! @copyright  BSD 3-Clause License Copyright (c) 2020, Orso Eric
//! @details
//! \n Verbose description
/************************************************************************************/

class Tokenizer
{
    //Visible to all
    public:
		/*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC ENUMS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //! @brief Configurations of the class
        typedef union _Config
        {
            //Checks to be performed on user dependent data
			static const bool CU1_EXTERNAL_CHECKS = true;
			//Checks to be performed on input dependent on internal algorithms
			static const bool CU1_INTERNAL_CHECKS = true;

            //Decimal Separator
            static const char CS8_DECIMAL_SEPARATOR = '.';
            //Maximum number of character that makes up a token name or a number
            static const int CS32_MAX_ARG_LENGTH = 32;

        } Config;

        //! @brief Error codes of the class
        typedef union _Error_code
        {
			//No error
			static constexpr const char *CPS8_OK = "OK";
			//Generic error
			static constexpr const char *CPS8_ERR = "ERR";
        } Error_code;

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC TYPEDEFS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  CONSTRUCTORS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Empty Constructor
        Tokenizer( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  DESTRUCTORS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Empty destructor
        ~Tokenizer( void );

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

        bool parse( const char *ips8_equation );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC GETTERS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

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

		//Tokenizer public method
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

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE TYPEDEFS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //I can make token a base class, and specialize it to the various types of tokens I can have
        //  token -> binary_operator (one father, two children LHS RHS)
        //  token -> number (one father, no children)
        typedef struct _Token Token;
        struct _Token
        {
            //Token type


            //Array that points to a number of tokens
            std::vector<Token *> clapst_leaves;
        };

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

        bool is_number( char is8_digit )
        {
            return ( (is8_digit == Config::CS8_DECIMAL_SEPARATOR) || ((is8_digit >= '0') && (is8_digit <= '9')) );
        }

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Report an error. return false: OK | true: Unknown error code
        bool report_error( const char *ips8_error_code );
        //Tries to recover from an error. Automatically called by get_error. return false = OK | true = fail
        bool error_recovery( void );

        //Tokenizer method to copy the code
        bool my_private_method( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE VARS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //! @brief Error code of the class
        const char *gps8_error_code;

};	//End Class: Tokenizer

//Base class, all tokens are compatible with this
class Token
{
    public:
        Token( void )
        {
			DENTER_ARG("this: %p", this);
            //No type
            this->gpcs8_token_type = Token_type::CPS8_NONE;
            //No father
            this->gpcl_father = nullptr;

            DRETURN();
            return;
        }
        ~Token()
		{
			DENTER();
			DRETURN();
		}

    protected:
        typedef union _Token_type
        {
            static constexpr const char *CPS8_NONE = "None";
            static constexpr const char *CPS8_BINARY_OPERATOR = "Binary Operator";
            static constexpr const char *CPS8_NUMBER = "Number";
        } Token_type;

        //Token type
        const char *gpcs8_token_type;
        //
        Token *gpcl_father;
    private:


};

//Binary operators have two children and an operator type that describe its function
class Binary_operator : public Token
{
	public:
		//Types of operators: from outside there is need to know what types are
        typedef union _Binary_operator_type
        {
            //Equal Operator
            static constexpr const char *CPS8_EQUAL = "=";
            //Binary Mul Operator
            static constexpr const char *CPS8_MUL = "*";
        } Binary_operator_type;

		Binary_operator()
		{
			DENTER_ARG("this: %p", this);
			//I'm constructing a binary operator
			this->gpcs8_token_type = Token_type::CPS8_BINARY_OPERATOR;
			DRETURN();
			return;
		}
		~Binary_operator()
		{
			DENTER();
			DRETURN();
		}

    private:

        //Operator type
        const char *ps8_operator_type;
        //Pointers to leaves. Left Hand Side and Right Hand Side
        Token *pcl_lhs;
        Token *pcl_rhs;
};


class Number : public Token
{
    private:

};

//Class that contains equation manipulating function
//Takes care of creating an equation from strings
class Equation
{
	public:

		//Create a new token of a given type
		Token *create_binary_operator( Binary_operator::Binary_operator_type ie_binary_operator_type );
		//Destroy a binary operator, and return all the non null leaves in a vector for destruction
		bool destroy_binary_operator( std::vector<Token *>& orclapcl_leaves );
		//Pointer to the root of the solution tree
        Token *gpcl_root;
	private:
		//String holding the equation
		char *gpas8_equation;

};

//Takes in multiple equations in order to solve a problem
class Solver
{
	public:
		//register an equation inside the problem
		bool register_equation( std::string icl_equation, int &ors32_index );
		//Register a token to be an output token.
		bool register_output_token( std::string icl_output_token );
		//Register a token to be an indepentend variable. solver wants all of them to be on RHS
		bool register_input_token( std::string icl_output_token );
		//All tokens that are not input or output are taken as numeric constant

		//The solver will try very hard to solve the problem if within its limits.
		//Solver wants to generate one equation per output token with said token as sole LHS
		//The Solver tries to isolate input tokens on RHS as best as it can, prioritizing linear
		//The solver wants to minimize the overall number of tokens needed to represent an equation
		bool solve( void );
};


/**********************************************************************************
**  NAMESPACE
**********************************************************************************/

}	//end namespace

#else
    #warning "Multiple inclusion of hader file TOKENIZER_H_"
#endif
