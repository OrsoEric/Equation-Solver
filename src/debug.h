#ifndef DEBUG_H_
	#define DEBUG_H_

	/**********************************************************************************
	**	ENVIROMENT VARIABILE
	**********************************************************************************/

	#ifdef ENABLE_DEBUG
		#include <cstdio>
	#endif // ENABLE_DEBUG

	/**********************************************************************************
	**	GLOBAL INCLUDE
	**********************************************************************************/

	/**********************************************************************************
	**	DEFINE
	**********************************************************************************/

	#define _DEBUG_MAX_INDENT_LEVEL	12

	/**********************************************************************************
	**	MACRO
	**********************************************************************************/

	#ifdef ENABLE_DEBUG

		///----------------------------------------------------------------
		///	GLOBAL VARIABLES
		///----------------------------------------------------------------

		//Variable prototypes for debug
		#define DEBUG_VARS_PROTOTYPES()	\
			extern FILE *_debug_file;	\
			extern int _debug_indent_level, _debug_show_level

		//Global variables for debug
		#define DEBUG_VARS()	\
			FILE  *_debug_file = NULL;	\
			int _debug_indent_level = 0, _debug_show_level = 0

        //Change the show level
        #define DSHOW( level )  \
            _debug_show_level = (level)

		///----------------------------------------------------------------
		///	DEBUG FILE MACROS
		///----------------------------------------------------------------

		//Open file and start debugging
		#define DSTART( user__debug_show_level )	\
			_debug_file = fopen( "debug.log", "w+"), _debug_indent_level = 0, _debug_show_level = user__debug_show_level , fprintf(_debug_file, "Start Debug!\n")

		//Stop debugging and close file
		#define DSTOP()	\
			((_debug_file != NULL)?fprintf(_debug_file, "\nDebug has Ended!\n"), fflush(_debug_file), fclose(_debug_file), _debug_file = NULL:(0))

		///----------------------------------------------------------------
		///	DEBUG PRINT MACROS
		///----------------------------------------------------------------

		//Print a given number of tab characters
		#define DTAB(n)	\
			(((_debug_file != NULL) && (_debug_indent_level >= _debug_show_level))?(fprintf(_debug_file,"%.*s", n, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t")):(0));

		//Print a number of tab equal to indent level than print user defined string
		#define DPRINT( ... )	\
			(((_debug_file != NULL) && (_debug_indent_level >= _debug_show_level))?(fprintf(_debug_file,"%.*s", _debug_indent_level, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"), fprintf(_debug_file, __VA_ARGS__ )):(0))

		//print user defined string
		#define DPRINT_NOTAB( ... )	\
			(((_debug_file != NULL) && (_debug_indent_level >= _debug_show_level))?(fprintf(_debug_file, __VA_ARGS__ )):(0))

		#define DPRINT_CONDITIONAL( iu1_enable, ... ) \
			((iu1_enable==false)?(false):(DPRINT(__VA_ARGS__)))

		//Just print the tabs
		#define DPRINT_TAB()	\
			(((_debug_file != NULL) && (_debug_indent_level >= _debug_show_level))?(fprintf(_debug_file,"%.*s", _debug_indent_level, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t") ):(0))

		///----------------------------------------------------------------
		///	FUNCTION TRACE MACROS
		///----------------------------------------------------------------

		//Enter Function and increase indent level. No argument print version
		#define DENTER()	\
			DPRINT( "-->> \"%s\" |\n", __PRETTY_FUNCTION__), (_debug_indent_level<_DEBUG_MAX_INDENT_LEVEL)?(++_debug_indent_level):(_DEBUG_MAX_INDENT_LEVEL)
		#define DENTER_CONDITIONAL( iu1_enable, ... ) \
			((iu1_enable==false)?:(DENTER(__VA_ARGS__)))

		//Return from function and decrease indent level. No argument version
		#define DRETURN()	\
			(_debug_indent_level>0)?(--_debug_indent_level):(0), DPRINT( "<<-- \"%s\" |\n", __PRETTY_FUNCTION__)
		#define DRETURN_CONDITIONAL( iu1_enable, ... ) \
			((iu1_enable==false)?:(DRETURN(__VA_ARGS__)))

		//Enter Function and increase indent level. No argument print version
		#define DENTER_ARG( ... )	\
			DPRINT( "-->> \"%s\" | ", __PRETTY_FUNCTION__), DPRINT_NOTAB( __VA_ARGS__ ), DPRINT_NOTAB( "\n" ), (_debug_indent_level<_DEBUG_MAX_INDENT_LEVEL)?(++_debug_indent_level):(_DEBUG_MAX_INDENT_LEVEL)
		#define DENTER_ARG_CONDITIONAL( iu1_enable, ... ) \
			((iu1_enable==false)?(false):(DENTER_ARG(__VA_ARGS__)))

		//Return from function and decrease indent level. No argument version
		#define DRETURN_ARG( ... )	\
			(_debug_indent_level>0)?(--_debug_indent_level):(0), DPRINT( "<<-- \"%s\" | ", __PRETTY_FUNCTION__), DPRINT_NOTAB( __VA_ARGS__ ), DPRINT_NOTAB( "\n" )
		#define DRETURN_ARG_CONDITIONAL( iu1_enable, ... ) \
			((iu1_enable==false)?(false):(DRETURN_ARG(__VA_ARGS__)))

	#else
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

	/**********************************************************************************
	**	TYPEDEF
	**********************************************************************************/

	/**********************************************************************************
	**	PROTOTYPE: STRUCTURE
	**********************************************************************************/

	/**********************************************************************************
	**	PROTOTYPE: GLOBAL VARIABILE
	**********************************************************************************/

	//Global variables prototype
	DEBUG_VARS_PROTOTYPES();

	/**********************************************************************************
	**	PROTOTYPE: FUNCTION
	**********************************************************************************/

#else
	#warning "multiple inclusion of DEBUG_H_"
#endif



