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

#ifndef TREE_H_
    #define TREE_H_

/**********************************************************************************
**  GLOBAL INCLUDES
**********************************************************************************/

//Used to store leaves
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
//! @class      Tree
/************************************************************************************/
//!	@author     Orso Eric
//! @version    2022-06-17
//! @brief      Generic tree template implementation
//! @copyright  BSD 3-Clause License Copyright (c) 2022, Orso Eric
//! @bug Avoid push_back | add a move constructor C(C&& c) C(const &c) | use emplace-back | construct/destruct https://stackoverflow.com/questions/21798396/destructor-is-called-when-i-push-back-to-the-vector
//! @bug swap can be done with std::swap std::vector::swap, the second is the fastest for vectors | https://stackoverflow.com/questions/41090557/c-swap-two-elements-of-two-different-vectors
//! @details
//! \n A basic tree class that stores a template payload
//! \n
/************************************************************************************/

template <class Payload>
class Tree
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
        } Config;

        //! @brief Error codes of the class
        typedef union _Error_code
        {
			//No error
			static constexpr const char *CPS8_OK = "OK";
			//Generic error
			static constexpr const char *CPS8_ERR = "ERR";
			//Out Of Boundary
			static constexpr const char *CPS8_ERR_OOB = "ERR:OOB";
			//std::vector failed to do something
			static constexpr const char *CPS8_ERR_STDVECTOR = "ERR:std::vector";
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
        Tree( void );
        //Initialized COPY constructor to Payload
        Tree( Payload it_payload );
        //Initialized MOVE constructor
        //Tree( Tree&& ircl_source );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  DESTRUCTORS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Empty destructor
        ~Tree( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC OPERATORS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Operator Bracket. Access leaf of a given index
        Tree<Payload> &operator []( unsigned int iu32_index );

        Payload &payload( void )
        {
			return this->gt_payload;
        }

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC SETTERS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //
        bool set_payload( Payload it_payload )
        {
			this->gt_payload = it_payload;
			return false;
        }
		//Create a new leaf with a given payload
        bool create_leaf( Payload it_payload, unsigned int &oru32_index );
        bool create_leaf( Payload it_payload )
        {
			unsigned int u32_dummy = 0;
			return this->create_leaf( it_payload, u32_dummy );
        }
		//Destroy the leaf of given index, recursively destroy all leaves of that leaf
        bool destroy_leaf( unsigned int iu32_index );
		//Swap the leaves of two different branches. Does not require branch pointer
        bool swap_leaves( unsigned int iu32_own_index, Tree<Payload> &ircl_branch, unsigned int iu32_branch_index );
        //Swap two leaves. Requires branch pointer
        //bool swap_leaves( Tree<Payload> &ircl_branch );
		//Move a leaf of the current root to a new root
        bool move_leaf( unsigned int iu32_own_index, Tree<Payload> &ircl_branch, unsigned int &oru32_branch_index );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC GETTERS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        int get_num_leaves( void )
        {
			return this->gclat_leaves.size();
        }

        //Get current error state of the library
        const char *get_error( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC TESTERS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

		//! @brief return true if class is in error. Errors needs to be acknoweldged by get_error to recover
        bool is_error( void )
        {
			return (this->gps8_error_code != Error_code::CPS8_OK);	//true = ERR | false == OK
        }

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **  PUBLIC METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

		//Tree public method
        bool my_public_method( void );
		//Print the content of the tree in tree form
        bool print( unsigned int iu32_depth );
        bool print( void )
        {
			return this->print( 0 ); //Print everything from root down
        }

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

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE INIT
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Initialize class vars
        bool init_class_vars( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE METHODS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Report an error. return false: OK | true: Unknown error code
        bool report_error( const char *ips8_error_code );
        //Tries to recover from an error. Automatically called by get_error. return false = OK | true = fail
        bool error_recovery( void );

        //Tree method to copy the code
        bool my_private_method( void );

        /*********************************************************************************************************************************************************
        **********************************************************************************************************************************************************
        **	PRIVATE VARS
        **********************************************************************************************************************************************************
        *********************************************************************************************************************************************************/

        //Dummy payload
        static const Payload gccl_dummy;
        //! @brief Error code of the class
        const char *gps8_error_code;
		//! @brief Payload stored inside a node
        Payload gt_payload;
		//! @brief Individual leaves to this leaf are stored inside a vector
        std::vector<Tree> gclat_leaves;
};	//End Class: Tree

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	CONSTRUCTORS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Constructor: Tree | void
/***************************************************************************/
//! @return no return
//! @details
//! \n Empty constructor
/***************************************************************************/

template <class Payload>
Tree<Payload>::Tree( void )
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
}   //Constructor: Tree | void

/***************************************************************************/
//! @brief Constructor: Tree | Payload
/***************************************************************************/
//! @param it_payload | payload of the root node
//! @return no return
//! @details
//! \n Initialized constructor. Takes care of initializing the root node
/***************************************************************************/

template <class Payload>
Tree<Payload>::Tree( Payload it_payload )
{
    DENTER_ARG("This: %p", this);   //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //Initialize class vars
    this->init_class_vars();
	//Initialize payload
    this->gt_payload = it_payload;

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN();  //Trace Return
    return;
}   //Constructor: Tree | Payload

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	DESTRUCTORS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//!	@brief Destructor: Tree | void
/***************************************************************************/
// @param
//! @return no return
//! @details
//! \n Empty destructor
/***************************************************************************/

template <class Payload>
Tree<Payload>::~Tree( void )
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
}   //Destructor: Tree | void

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	PUBLIC OPERATORS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//!	@brief Bracket operator | operator [] | unsigned int
/***************************************************************************/
//!	@param iu32_index | index to the leaves
//! @return Tree & | reference to leaf of index | reference to self if fail
//!	@details
//!	Bracket Operator access a leaf of a given index
//!	If said leaf doesn't exist, class reports an OOB error
/***************************************************************************/

template <class Payload>
Tree<Payload> &Tree<Payload>::operator []( unsigned int iu32_index )
{
	DENTER_ARG("Object: %p, Index: %d", (void *)this, iu32_index );
	//--------------------------------------------------------------------------
    //  BODY
    //--------------------------------------------------------------------------
	//if: user asks for an element outside array range
    if (iu32_index >= this->gclat_leaves.size())
    {
		//Out Of Boundary
		this->report_error(Error_code::CPS8_ERR_OOB);
		//Error. Return reference to self
		DRETURN_ARG("ERR:OOB | Index: %d | Size: %d", iu32_index, this->gclat_leaves.size() );
		return (*this);
    }

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
	DRETURN();
	return this->gclat_leaves[iu32_index];
}	//end method: Bracket operator | operator [] | int

/*********************************************************************************************************************************************************
**********************************************************************************************************************************************************
**	PUBLIC SETTERS
**********************************************************************************************************************************************************
*********************************************************************************************************************************************************/

/***************************************************************************/
//! @brief Public Setter: create_leaf | Payload
/***************************************************************************/
//! @param it_payload | payload to be attached to this leaf
//! @param oru32_index | return index of newly created leaf. can be accessed with safe [] operator
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Create a new leaf with a given payload
//! \n std::vector takes care of memory allocation and destruction
/***************************************************************************/

template <class Payload>
bool Tree<Payload>::create_leaf( Payload it_payload, unsigned int &oru32_index )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------
	//if class is in error, leaf cannot be created
    if (this->gps8_error_code != Error_code::CPS8_OK)
    {
		DRETURN_ARG("ERR: Tree is in error: %s | Cannot create leaf", this->gps8_error_code ); //Trace Return
		return true;
    }

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //Get current number of leaves
    unsigned int u32_num_leaves = this->gclat_leaves.size();
    //! @TODO a local Tree is created and destroyed just to allow vector to add an element. Rework to be more efficient.
    //Ask vector to allocate a new leaf with the given payload
    this->gclat_leaves.push_back( Tree( it_payload ) );
    //this->gclat_leaves.emplace_back( Tree( it_payload ) );
    //if: std::vector has not increased in size by one
    if ((Config::CU1_INTERNAL_CHECKS == true) && ((u32_num_leaves+1) != this->gclat_leaves.size()) )
    {
		this->report_error(Error_code::CPS8_ERR_STDVECTOR );
		DRETURN_ARG("ERR:std::vector | Leaves: %d -> %d", u32_num_leaves, this->gclat_leaves.size() ); //Trace Return
		return true;	//FAIL
    }
	//Return to caller the index of the added leaf
	oru32_index = u32_num_leaves;

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Leaves: %d", u32_num_leaves+1 ); //Trace Return
    return false;	//OK
}   //Public Setter: create_leaf | Payload

/***************************************************************************/
//! @brief Public Setter: destroy_leaf | unsigned int
/***************************************************************************/
//! @param iu32_index | index of the leaf
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Destroy the leaf of given index, recursively destroy all leaves of that leaf
/***************************************************************************/

template <class Payload>
bool Tree<Payload>::destroy_leaf( unsigned int iu32_index )
{
    DENTER(); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------
	//if class is in error, leaf cannot be created
    if (this->gps8_error_code != Error_code::CPS8_OK)
    {
		DRETURN_ARG("ERR: Tree is in error: %s | Cannot destroy leaf", this->gps8_error_code ); //Trace Return
		return true;
    }
	//if: user asks for an element outside array range
    if (iu32_index >= this->gclat_leaves.size())
    {
		//Out Of Boundary
		this->report_error(Error_code::CPS8_ERR_OOB);
		//Error
		DRETURN_ARG("ERR:OOB | Index: %d | Size: %d", iu32_index, this->gclat_leaves.size() );
		return true;
    }

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //! @TODO a local Tree is created and destroyed just to allow vector to add an element. Rework to be more efficient.

    //Ask vector to allocate a new leaf with the given payload
    this->gclat_leaves.erase( this->gclat_leaves.begin() +iu32_index );

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Leaves: %d", this->gclat_leaves.size() ); //Trace Return
    return false;	//OK
}   //Public Setter: destroy_leaf | unsigned int

/***************************************************************************/
//! @brief Public Setter: swap_leaves | unsigned int | Tree<Payload> & | unsigned int |
/***************************************************************************/
//! @param iu32_own_index | index of the leaf under this root to be moved
//! @param ircl_branch | target tree node with the second target
//! @param iu32_branch_index | index of leaf under target node
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Swap the leaves of two different branches
/***************************************************************************/

template <class Payload>
bool Tree<Payload>::swap_leaves( unsigned int iu32_own_index, Tree<Payload> &ircl_branch, unsigned int iu32_branch_index )
{
    DENTER_ARG("(%p,%d)<->(%p,%d)", this, iu32_own_index, &ircl_branch, iu32_branch_index); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------
	//if class is in error
    if ((Config::CU1_INTERNAL_CHECKS == true) && (this->gps8_error_code != Error_code::CPS8_OK))
    {
		DRETURN_ARG("ERR: Tree is in error: %s | Cannot destroy leaf", this->gps8_error_code ); //Trace Return
		return true;
    }
	//if: user asks for an element outside array range
    if ((Config::CU1_EXTERNAL_CHECKS == true) && (iu32_own_index >= this->gclat_leaves.size()))
    {
		//Out Of Boundary
		this->report_error(Error_code::CPS8_ERR_OOB);
		//Error
		DRETURN_ARG("ERR:OOB | Index: %d | Size: %d", iu32_own_index, this->gclat_leaves.size() );
		return true;
    }

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

    //swap two elements of Vector
    std::swap( this->gclat_leaves[iu32_own_index], ircl_branch.gclat_leaves[iu32_branch_index] );

	//std::vector<Tree<Payload>>::swap( this->gclat_leaves[iu32_own_index], ircl_branch.gclat_leaves[iu32_branch_index] );

	//this->gclat_leaves[iu32_own_index].swap( ircl_branch.gclat_leaves[iu32_branch_index] );

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN(); //Trace Return
    return false;	//OK
}   //Public Setter: swap_leaves | unsigned int | Tree<Payload> & | unsigned int |

//Move a leaf of the current root to a new root
;

/***************************************************************************/
//! @brief Public Setter: move_leaf | unsigned int | Tree<Payload> & | unsigned int & |
/***************************************************************************/
//! @param iu32_own_index | index of the leaf under this root to be moved
//! @param ircl_target | target tree node, leaf will be moved under that node
//! @param oru32_target_index | resulting leaf index under target node
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Swap the leaves of two different branches
/***************************************************************************/

template <class Payload>
bool Tree<Payload>::move_leaf( unsigned int iu32_own_index, Tree<Payload> &ircl_target, unsigned int &oru32_target_index )
{
    DENTER_ARG("(%p,%d)-->(%p)", this, iu32_own_index, &ircl_target ); //Trace Enter
    //--------------------------------------------------------------------------
    //	CHECK
    //--------------------------------------------------------------------------
	//if class is in error
    if ((Config::CU1_INTERNAL_CHECKS == true) && (this->gps8_error_code != Error_code::CPS8_OK))
    {
		DRETURN_ARG("ERR: Tree is in error: %s | Cannot destroy leaf", this->gps8_error_code ); //Trace Return
		return true;
    }
	//if: user asks for an element outside array range
    if ((Config::CU1_EXTERNAL_CHECKS == true) && (iu32_own_index >= this->gclat_leaves.size()))
    {
		//Out Of Boundary
		this->report_error(Error_code::CPS8_ERR_OOB);
		//Error
		DRETURN_ARG("ERR:OOB | Index: %d | Size: %d", iu32_own_index, this->gclat_leaves.size() );
		return true;
    }

    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

	//Access directly to the std::vector and add the tree node with all its subnodes
	ircl_target.gclat_leaves.push_back( this->gclat_leaves[iu32_own_index] );
	//Delete the leaf from the root
	this->gclat_leaves.erase( this->gclat_leaves.begin() +iu32_own_index );


    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("(%p,%d)-->(%p, %d)", this, iu32_own_index, &ircl_target, oru32_target_index ); //Trace Return
    return false;	//OK
}   //Public Setter: move_leaf | unsigned int | Tree<Payload> & | unsigned int & |

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

template <class Payload>
const char *Tree<Payload>::get_error( void )
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

template <class Payload>
bool Tree<Payload>::my_public_method( void )
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

/***************************************************************************/
//! @brief Public method: print | void
/***************************************************************************/
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Print the content of the tree in tree form, from this leaf forward
/***************************************************************************/

template <class Payload>
bool Tree<Payload>::print( unsigned int iu32_depth )
{
    DENTER_ARG_CONDITIONAL(iu32_depth==0, ""); //Trace Enter only for the top iteration
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------

	//Print a spacer for each level of descent into the tree
    for (unsigned int i = 0;i < iu32_depth;i++)
	{
		if ( i != iu32_depth-1 )
		{
			std::cout << "    ";
		}
		else
		{
			std::cout << "|-- ";
		}
	}
	std::cout << this->gt_payload << "\n";
	//Recursively explore the tree at the next level of depth for each leaf
	for (unsigned int i = 0;i < this->gclat_leaves.size();i++)
	{
		this->gclat_leaves.at(i).print( iu32_depth+1 );
	}

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG_CONDITIONAL(iu32_depth==0, ""); //Trace Enter only for the top iteration
    return false;	//OK
}   //Public method: print | void

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

template <class Payload>
bool Tree<Payload>::init_class_vars( void )
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

template <class Payload>
bool Tree<Payload>::report_error( const char *ips8_error_code )
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

template <class Payload>
bool Tree<Payload>::error_recovery( void )
{
    DENTER_ARG("ERR: %s", this->gps8_error_code); //Trace Enter
    //--------------------------------------------------------------------------
    //	BODY
    //--------------------------------------------------------------------------
	//If class is not OK
    if (this->gps8_error_code != Error_code::CPS8_OK)
    {
		//Class is OK
		this->gps8_error_code = Error_code::CPS8_OK;
    }

    //--------------------------------------------------------------------------
    //	RETURN
    //--------------------------------------------------------------------------
    DRETURN_ARG("Recovered: %s", this->gps8_error_code);      //Trace Return
    return false;    //FAIL
}   //Private Method: error_recovery | void |

/***************************************************************************/
//! @brief Private Method: my_private_method | void
/***************************************************************************/
// @param
//! @return bool | false = OK | true = FAIL |
//! @details
//! \n Method
/***************************************************************************/

template <class Payload>
bool Tree<Payload>::my_private_method( void )
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
**  NAMESPACE
**********************************************************************************/

}	//end namespace: User

#else
    #warning "Multiple inclusion of hader file TREE_H_"
#endif
