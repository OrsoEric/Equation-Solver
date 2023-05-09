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
**	St_test_pattern
*****************************************************************
**  Array filled with test patterns to be fed to the unit test
**	Meant to test the various features of the tokenizer, the treeificator aggregator
****************************************************************/

//structure holding the test patterns. I have the source, and the expected outputs, and they have to match.
struct St_test_pattern
{
	//User adds a note to the test pattern explaining what it's testing
	const char *s_user_note;
	//Equation fed to the parser
	const char *s_equation;
	//Expected result of the parser. true=FAIL | false=PASS
	bool x_fail;
	//Expected string tokens after a successful parse
	std::vector<std::string> as_token_vector;
	//Expected tree structure after a successful parse
	std::vector<User::Tree<User::Equation::Token>::St_minimal_node> ast_minimal_node;
};

//A tree holding just the root with an equal sign
const User::Tree<User::Equation::Token>::St_minimal_node cst_default_equal =
{
	User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
};

//Create the test patterns alongside the expected result of the pattern. Can detect a misbehaviour of the parser
St_test_pattern ast_test_pattern[] =
{
	St_test_pattern{ "Empty String (FAIL)", "", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation::Token>::St_minimal_node>( { cst_default_equal, } ) },
	St_test_pattern{ "Lack of equal sign (FAIL)", "1", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation::Token>::St_minimal_node>( { cst_default_equal, } ) },
	St_test_pattern{ "Unbalanced brackets L (FAIL)", "(1", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation::Token>::St_minimal_node>( { cst_default_equal, } ) },
	St_test_pattern{ "Unbalanced brackets R (FAIL)", "1(", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation::Token>::St_minimal_node>( { cst_default_equal, } ) },
	St_test_pattern{ "Unbalanced brackets L (FAIL)", "((1)", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation::Token>::St_minimal_node>( { cst_default_equal, } ) },
	St_test_pattern{ "Two equal signs (FAIL)", "1=1=1", true, std::vector<std::string>(), std::vector<User::Tree<User::Equation::Token>::St_minimal_node>( { cst_default_equal, } ) },
	St_test_pattern
	{
		"Balanced bracket (PASS)",
		"1=((((((1))))))",
		false,
		std::vector<std::string>
		(
			{
				std::string("1"),
				std::string("="),
				std::string("("),
				std::string("("),
				std::string("("),
				std::string("("),
				std::string("("),
				std::string("("),
				std::string("1"),
				std::string(")"),
				std::string(")"),
				std::string(")"),
				std::string(")"),
				std::string(")"),
				std::string(")")
			}
		),
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
			}
		),

	},
	St_test_pattern
	{
		"Two Number Equation (PASS)",
		"1=1",
		false,
		std::vector<std::string>
		(
			{
				std::string("1"),
				std::string("="),
				std::string("1")
			}
		),
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
			}
		),
	},
	St_test_pattern
	{
		"Floating Point Equation (PASS)",
		"3/2=1.5000000000",
		false,
		std::vector<std::string>
		(
			{
				std::string("3"),
				std::string("/"),
				std::string("2"),
				std::string("="),
				std::string("1.5000000000")
			}
		),
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("/"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1.5000000000"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 1, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("2"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 1, },
			}
		),
	},
	St_test_pattern
	{
		"Three Number Equation (PASS)",
		"5=2+3",
		false,
		std::vector<std::string>
		(
			{
				std::string("5"),
				std::string("="),
				std::string("2"),
				std::string("+"),
				std::string("3"),
			}
		),
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("5"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("2"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
			}
		),
	},

	St_test_pattern
	{
		"Four Number Equation (PASS)",
		//Source equation string to be fed
		"1+4=2+3",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("1"),
				std::string("+"),
				std::string("4"),
				std::string("="),
				std::string("2"),
				std::string("+"),
				std::string("3"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 1, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("4"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 1, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("2"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
			}
		),
	},
	//Add symbols to equation
	St_test_pattern
	{
		"One Symbol Equation (PASS)",
		//Source equation string to be fed
		"X=1",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("X"),
				std::string("="),
				std::string("1"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("X"), User::Equation::Token_type::BASE_SYMBOL, 0, 0, false, }, 00, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
			}
		),
	},
	//! @todo * is higher priority than +, but is parsed in wrong order without brackets
	//Add more symbols to equation
	St_test_pattern
	{
		"Three Symbol Equation (PASS)",
		//Source equation string to be fed
		"3*X=(5*Y)+C",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("3"),
				std::string("*"),
				std::string("X"),
				std::string("="),
				std::string("("),
				std::string("5"),
				std::string("*"),
				std::string("Y"),
				std::string(")"),
				std::string("+"),
				std::string("C"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("*"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 1, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("X"), User::Equation::Token_type::BASE_SYMBOL, 0, 0, false, }, 1, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("*"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("C"), User::Equation::Token_type::BASE_SYMBOL, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("5"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 5, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("Y"), User::Equation::Token_type::BASE_SYMBOL, 0, 0, false, }, 5, },
			}
		),
	},
	//long symbols
	St_test_pattern
	{
		"Long Symbol Equation (PASS)",
		//Source equation string to be fed
		"Pippo=Pluto+self_awareness",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("Pippo"),
				std::string("="),
				std::string("Pluto"),
				std::string("+"),
				std::string("self_awareness"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("Pippo"), User::Equation::Token_type::BASE_SYMBOL, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("Pluto"), User::Equation::Token_type::BASE_SYMBOL, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("self_awareness"), User::Equation::Token_type::BASE_SYMBOL, 0, 0, false, }, 2, },
			}
		),
	},
	//TEST PATTERN 14
	St_test_pattern
	{
		"Sum aggregator (PASS)",
		//Source equation string to be fed
		"3=1+1+1",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("3"),
				std::string("="),
				std::string("1"),
				std::string("+"),
				std::string("1"),
				std::string("+"),
				std::string("1"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
			}
		),
	},
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	St_test_pattern
	{
		"Deep sum aggregator (PASS)",
		//Source equation string to be fed
		"28=1+2+3+4+5+6+7",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("28"),
				std::string("="),
				std::string("1"),
				std::string("+"),
				std::string("2"),
				std::string("+"),
				std::string("3"),
				std::string("+"),
				std::string("4"),
				std::string("+"),
				std::string("5"),
				std::string("+"),
				std::string("6"),
				std::string("+"),
				std::string("7"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("28"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("2"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("4"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("5"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("6"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("7"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
			}
		),
	},
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	St_test_pattern
	{
		"Complex sum aggregator (PASS)",
		//Source equation string to be fed
		"Y=1+(3*X)+2+(5*sephiroth +100 +101)+4",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("Y"),
				std::string("="),
				std::string("1"),
				std::string("+"),
				std::string("("),
				std::string("3"),
				std::string("*"),
				std::string("X"),
				std::string(")"),
				std::string("+"),
				std::string("2"),
				std::string("+"),
				std::string("("),
				std::string("5"),
				std::string("*"),
				std::string("sephiroth"),
				std::string("+"),
				std::string("100"),
				std::string("+"),
				std::string("101"),
				std::string(")"),
				std::string("+"),
				std::string("4"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("Y"), User::Equation::Token_type::BASE_SYMBOL, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },

				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("*"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("2"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("*"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("4"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },

				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 4, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("X"), User::Equation::Token_type::BASE_SYMBOL, 0, 0, false, }, 4, },

				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("5"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 6, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 6, },

				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("sephiroth"), User::Equation::Token_type::BASE_SYMBOL, 0, 0, false, }, 11, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("100"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 11, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("101"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 11, },

			}
		),
	},
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	St_test_pattern
	{
		"Deep sum diff aggregator (PASS)",
		//Source equation string to be fed
		"28=1+2+3+4+5+6+7",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("28"),
				std::string("="),
				std::string("1"),
				std::string("+"),
				std::string("2"),
				std::string("+"),
				std::string("3"),
				std::string("+"),
				std::string("4"),
				std::string("+"),
				std::string("5"),
				std::string("+"),
				std::string("6"),
				std::string("+"),
				std::string("7"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("28"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("2"), User::Equation::Token_type::BASE_NUMBER, 0, 0, true, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("4"), User::Equation::Token_type::BASE_NUMBER, 0, 0, true, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("5"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("6"), User::Equation::Token_type::BASE_NUMBER, 0, 0, true, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("7"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
			}
		),
	},
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	St_test_pattern
	{
		"Deep sum diff aggregator (PASS)",
		//Source equation string to be fed
		"4=1-2+3-4+5-6+7",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("4"),
				std::string("="),
				std::string("1"),
				std::string("-"),
				std::string("2"),
				std::string("+"),
				std::string("3"),
				std::string("-"),
				std::string("4"),
				std::string("+"),
				std::string("5"),
				std::string("-"),
				std::string("6"),
				std::string("+"),
				std::string("7"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("28"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("2"), User::Equation::Token_type::BASE_NUMBER, 0, 0, true, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("4"), User::Equation::Token_type::BASE_NUMBER, 0, 0, true, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("5"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("6"), User::Equation::Token_type::BASE_NUMBER, 0, 0, true, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("7"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
			}
		),
	},
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	St_test_pattern
	{
		"Forced deep sum diff aggregator (PASS)",
		//Source equation string to be fed
		"4=((((((+1-2)+3)-4)+5)-6)+7)",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("4"),
				std::string("="),
				std::string("("),
				std::string("("),
				std::string("("),
				std::string("("),
				std::string("("),
				std::string("("),
				std::string("1"),
				std::string("-"),
				std::string("2"),
				std::string(")"),
				std::string("+"),
				std::string("3"),
				std::string(")"),
				std::string("-"),
				std::string("4"),
				std::string(")"),
				std::string("+"),
				std::string("5"),
				std::string(")"),
				std::string("-"),
				std::string("6"),
				std::string(")"),
				std::string("+"),
				std::string("7"),
				std::string(")"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("28"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("2"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("4"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("5"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("6"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("7"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
			}
		),
	},
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	St_test_pattern
	{
		"Forced deep sum diff aggregator (PASS)",
		//Source equation string to be fed
		"4=(+1-(2+(3-(4+(5-(6+(7)))))))",
		//Expected failure state
		false,
		//Expected output of the tokenizer
		std::vector<std::string>
		(
			{
				std::string("4"),
				std::string("="),
				std::string("("),
				std::string("1"),
				std::string("-"),
				std::string("("),
				std::string("2"),
				std::string("+"),
				std::string("("),
				std::string("3"),
				std::string("-"),
				std::string("("),
				std::string("4"),
				std::string("+"),
				std::string("("),
				std::string("5"),
				std::string("-"),
				std::string("("),
				std::string("6"),
				std::string("+"),
				std::string("("),
				std::string("7"),
				std::string(")"),
				std::string(")"),
				std::string(")"),
				std::string(")"),
				std::string(")"),
				std::string(")"),
				std::string(")"),
			}
		),
		//Expected output of the treeficator
		std::vector<User::Tree<User::Equation::Token>::St_minimal_node>
		(
			{
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("="), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("28"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("+"), User::Equation::Token_type::BASE_OPERATOR, 0, 0, false, }, 0, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("1"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("2"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("3"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("4"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("5"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("6"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
				User::Tree<User::Equation::Token>::St_minimal_node{ User::Equation::Token{ std::string("7"), User::Equation::Token_type::BASE_NUMBER, 0, 0, false, }, 2, },
			}
		),
	},


};	//Test pattern array
