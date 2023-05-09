/**********************************************************************************
**  ENVIROMENT VARIABILE
**********************************************************************************/

#ifndef EQUATION_SOLVER_H_
    #define EQUATION_SOLVER_H_

/**********************************************************************************
**  GLOBAL INCLUDES
**********************************************************************************/

#include <vector>

#include "tree.hpp"
#include "equation.h"

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
//! @class      Equation_solver
/************************************************************************************/
//!	@author     Orso Eric
//! @version    2023-05
//! @brief      Stores a system of equations (vector of Equation classes) and solves them using simple fraction method
//! @copyright  BSD 3-Clause License Copyright (c) 2020, Orso Eric
//! @todo		Equation.get_symbols creates a vector with all the symbols that appear in an equation
//! @details
//! \n	ALGORITHM: overall, I implements the simple fraction algorihm, that is very mechanical to execute.
//! \n	IDEA: I need a rule based system to handle the streamlining of the tree
//! \n	RULE: aggregate all +/- chains
//! \n	0 = 0 + 0 + 0 + 0
//! \n	parsed					after aggregation
//! \n	=						=
//! \n		0						0
//! \n		+						+
//! \n			0						0
//! \n			+						0
//! \n				0					0
//! \n				+					0
//! \n					0
//! \n					0
//! \n
//! \n	RULE:  solve operators with only number as children
//! \n	2+3 -> 5
//! \n
//! \n	IDEA: Could I make a script to explain the steps?
//! \n	IDEA: Convert a spice netlist into a system of equation to be solved
//! \n
/************************************************************************************/

class Equation_solver
{
    //Visible to all
    public:
        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  CONSTRUCTORS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Empty constructor
		Equation_solver( void );

		/*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  SETTERS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Load and parse an equation into a tree of tokens
        bool load( const char *ips8 );

		/*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Preprocess a tree to do trivial aggregations and slimplifications
        bool preprocess_tree( void );

	//Visible to derived classes
	protected:

	//Visible only inside the class
	private:

		/*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //List of the dependent and independent variables of the system of equation
        std::vector<std::string> gas_inputs;
        std::vector<std::string> gas_outputs;
		//System of equations
		std::vector<User::Equation> gacl_system_of_equation;
		//Equations that are the solution
		std::vector<User::Equation> gacl_solution;
};	//End Class: Equation

/**********************************************************************************
**  NAMESPACE
**********************************************************************************/

}	//end namespace

#else
    #warning "Multiple inclusion of hader file EQUATION_PARSER_H_"
#endif
