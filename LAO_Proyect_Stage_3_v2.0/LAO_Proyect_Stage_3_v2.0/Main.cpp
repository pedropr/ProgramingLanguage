//STAGE 3(REM, ASSIGNMENT, PRINT Y END)
//LAO Stage 3 v0.1
# include <iostream>
# include <fstream>
# include <string>
#include "Comparison.h"
# include "Variable.h"
# include "Token.h"

using namespace std;

// Function prototypes:
// Token validation functions
bool isLetter(char ch);
bool isVariable(const char* ch);
bool isLogicalOperator(const char* ch);
bool isRelationalOperator(const char* ch);
bool isArithmeticOperator(const char* ch);
bool isAddOperator(const char* ch);
bool isSubOperator(const char* ch);
bool isMulOperator(const char* ch);
bool isDivOperator(const char* ch);
bool isString(char *);
bool isInteger(const char* ch);
bool isNumber(const char* ch);
bool isReal(const char* ch);
bool isRealVariable(const char* ch);
bool isIntegerVariable(const char* ch);
bool isStringVariable(const char* ch);
bool isPrintKeyword(const char* ch);
//==================================
// Function for statement validation or parts of
bool isReadKeyword(const char* ch);
bool isEndKeyword(const char* ch);
bool isRemKeyword(const char* ch);
bool isIfKeyword(const char* ch);
bool isComment(const char* ch);
bool isRead(const char* ch);
bool isEnd(const char* ch);
bool isAssignmentStatement(const char* ch); // ::= <variable> = <arithmetic expression>
bool isArithmeticExpression(const char* ch, string variableType); // ::= <term> | <arithmetic expresiion> + <term> | <arithmetic expression> - <term>
bool assignmentTypeMatch(char c, const char* value);
bool isAssignmentOperator(const char* ch); //
bool isPrintStatement(const char* ch);
int getLocThen(const char* ch);
bool isIfThenValid(const char* ch);
int findLogicalAnd(const char* ch);
int findLogicalOr(const char* ch);
bool isConditionValid(const char* ch);
bool isCommandValid(const char* ch);
int findComparisonKey(const char* ch);
bool isCompOperValid(const char* ch);

// Global variables and arrays
int lineCount = 0;
Variable symbolTable[100];
int totalVariables = 0;
bool executionError = false;

// Symbol Table functions
void updateSymbolTable(const Variable aVariable);
// Siguientes funciones devuelven cierto o falso para dejar saber si se encontró la variable
// El valor de la variable, si se encuentra, se pasa por parametro de referencia
bool findVariable(const char* ch);
bool findIntegerVariable(const char* ch, int & value);
bool findRealVariable(const char* ch, double & value);
bool findStringVariable(const char* ch, char* value);

// Execution functions
bool executeAssignmentStatement(const char* ch);
double realToValue(const char* ch);
bool mul(Token & operand1, Token & operand2);
bool div(Token & operand1, Token & operand2);
bool add(Token & operand1, Token & operand2);
bool sub(Token & operand1, Token & operand2);

//if then method
bool parseIfThen(const char* ch);
bool parseAndOrNot(const char* ch);
bool parseComparison(const char* ch);
double parseNumberToken(const char* ch);



// Real main for proyect. Uncomment to use
int main() //Main Function Execution
{
	// Declare array to hold user input
	char input[300];
	char firstToken[300];
	int i = 0;
	bool endFlag = false;
	bool endReached = false;

	ifstream endIn("Text.txt");
	ifstream in("Text.txt");


	if (!in)//si no encuentra el file
	{
		cout << "Couldn't find text file!!!" << endl;
	}
	else
	{
		while (endIn)//hasta que encuentre el eof
		{
			endIn.getline(input, 300);
			if (isEnd(input))
				endFlag = true;
		}

		if (!endFlag)
		{
			cout <<"Line: "<<lineCount<<"->MISSING END STATEMENT!!!" << endl;
			return 0;
		}

		while ((in) && (!endReached))//hasta que encuentre el eof
		{

			in.getline(input, 300);//guarda solo un linea a la vez por cada iteracion
			lineCount++; // Actualiza el # de linea leida

			//cout << "Line #: " << lineCount << endl; // For testing
			//cout << input << endl << endl; // For testing

			// Identify the first token of the sentence given by the user
			for (i = 0; (input[i] != ' ') && (i < strlen(input)); i++)
			{
				firstToken[i] = input[i];
			}
			firstToken[i] = '\0';

			// Validate statement types and execute if valid
			if (isRemKeyword(firstToken))
			{
				if (!(isComment(input)))
				{
					system("cls");
					cout << "Line: " << lineCount << "->\nInvalid Comment statement." << endl;
				}
			}

			else if (isVariable(firstToken))
			{
				if (!(isAssignmentStatement(input)))
				{
					system("cls");
					cout << "Line: " << lineCount << "->\nInvalid ASSIGNMENT statement." << endl;
				}
				else
				{
					executionError = !executeAssignmentStatement(input);
					if (executionError)
						cout << "Error in line: " << lineCount << endl;
				}
			}

			else if (isPrintKeyword(firstToken))
			{
				if (!(isPrintStatement(input)))
				{
					system("cls");
					cout << "Line: " << lineCount << "->\nInvalid PRINT statement." << endl;
				}
			}

			else if (isReadKeyword(firstToken))
			{
				if (!(isRead(input)))
				{
					system("cls");
					cout << "Line: " << lineCount << "->\nInvalid READ statement." << endl;
				}
			}

			else if (isIfKeyword(firstToken))
			{
				if (!(isIfThenValid(input)));
		
			}

			else if (isEndKeyword(firstToken))
			{
				if (!(isEnd(input)))
				{
					system("cls");
					cout << "Line: " << lineCount << "->\nInvalid End statement." << endl;
				}
				else
					endReached = true;
			}

			else
			{
				
					system("cls");
					cout << "Line: " << lineCount << "->\nUNRECONGNIZABLE STATEMENT!!!" << endl;
				cout << "Expected a variable or keyword (other than THEN).\n";
			}

		} // End of while loop that reads, validates and execute line of code in LAO
	} // End of instructions if text file was found.


	return 0;

} // End of main


bool isReadKeyword(const char* ch)
{
	bool result = false;
	// Validate char array is 4 characters long
	if (strlen(ch) != 4)
		return result;
	// Validate if text is the keyword 'READ'
	if ((tolower(ch[0]) == 'r')
		&& (tolower(ch[1]) == 'e')
		&& (tolower(ch[2]) == 'a')
		&& (tolower(ch[3]) == 'd'))
		result = true;
	// Return result (false or true)
	return result;
} // End of isReadKeyword

bool isEndKeyword(const char* ch)
{
	bool result = false;
	// Validate char array is 4 characters long
	if (strlen(ch) != 4)
		return result;
	// Validate if text is the keyword 'END.'
	if ((tolower(ch[0]) == 'e')
		&& (tolower(ch[1]) == 'n')
		&& (tolower(ch[2]) == 'd')
		&& (ch[3] == '.'))
		result = true;
	// Return result (false or true)
	return result;
} // End of isEndKeyword

bool isRemKeyword(const char* ch)
{
	bool result = false;
	// Validate char array is 3 characters long
	if (strlen(ch) != 3)
		return result;
	// Validate if text is the keyword 'REM'
	if ((tolower(ch[0]) == 'r')
		&& (tolower(ch[1]) == 'e')
		&& (tolower(ch[2]) == 'm'))
		result = true;
	// Return result (false or true)
	return result;
} // End of isRemKeyword

bool isIfKeyword(const char* ch)
{
	bool result = false;
	// Validate char array is 2 characters long
	if (strlen(ch) != 2)
		return result;
	// Validate if text is the keyword 'IF'
	if ((tolower(ch[0]) == 'i')
		&& (tolower(ch[1]) == 'f'))
		result = true;
	// Return result (false or true)
	return result;
} // End of isIfKeyword

// Functions definition
bool isKeyword(const char* ch)
{
	bool result = false;
	// Validate char array is 2 to 5 characters long
	if ((strlen(ch) < 2) || (strlen(ch) > 5))
		return result;
	// Validate if text is the keyword 'IF'
	if (strlen(ch) == 2)
	{
		if ((tolower(ch[0]) == 'i') && (tolower(ch[1]) == 'f'))
			result = true;
	}
	else if (strlen(ch) == 3) // Validate if text is the keyword 'END'
	{
		if ((tolower(ch[0]) == 'r') && (tolower(ch[1]) == 'e') && (tolower(ch[2]) == 'm'))
			result = true;
	}
	else if (strlen(ch) == 4) // Validate if text is the keyword 'THEN' or 'READ'
	{
		if (((tolower(ch[0]) == 't') && (tolower(ch[1]) == 'h') && (tolower(ch[2]) == 'e') && (tolower(ch[3]) == 'n'))
			|| ((tolower(ch[0]) == 'r') && (tolower(ch[1]) == 'e') && (tolower(ch[2]) == 'a') && (tolower(ch[3]) == 'd'))
			|| ((tolower(ch[0]) == 'e') && (tolower(ch[1]) == 'n') && (tolower(ch[2]) == 'd') && (tolower(ch[3]) == '.')))
			result = true;
	}
	else // Validate if text is the keyword 'PRINT'
	{
		if ((tolower(ch[0]) == 'p')
			&& (tolower(ch[1]) == 'r')
			&& (tolower(ch[2]) == 'i')
			&& (tolower(ch[3]) == 'n')
			&& (tolower(ch[4]) == 't'))
			result = true;
	}
	// Return result (false or true)
	return result;
} // End of isKeyword

bool isLetter(char ch) {
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return true;
	else
		return false;
}

bool isVariable(const char* ch) {
	bool result = true;
	//int i = 0;
	if (!(isLetter(ch[0])))
	{
		return false;
	}

	if (isKeyword(ch))
	{
		return false;
	}

	if (strlen(ch) > 1) //subcriptList needed for STATEMENT State category
	{
		for (int i = 0; i < strlen(ch); i++) {
			result = (isLetter(ch[i]));
			if (!result)
				return result;
		}
	}
	return result;
}

bool isLogicalOperator(const char* ch)
{
	// Validate char array is 4 or 5 characters long
	if (!((strlen(ch) == 4) || (strlen(ch) == 5)))
		return false;
	// Validate first and last char are '.'
	if ((ch[0] != '.') || (ch[strlen(ch) - 1] != '.'))
		return false;
	// Validate middle characters
	if (strlen(ch) == 4)
	{
		if ((tolower(ch[1]) == 'o') && (tolower(ch[2]) == 'r'))
			return true;
	}
	else // strlen(ch) == 5
	{
		if (((tolower(ch[1]) == 'a') && (tolower(ch[2]) == 'n') && (tolower(ch[3]) == 'd'))
			|| ((tolower(ch[1]) == 'n') && (tolower(ch[2]) == 'o') && (tolower(ch[3]) == 't')))
			return true;
	}
	// Return false if failed previous validation
	return false;
} // End of isLogicalOperator

bool isRelationalOperator(const char* ch)
{
	bool result = false;
	// Validate char array is 4 characters long
	if (strlen(ch) != 4)
		return result;
	// Validate first and last char are '.'
	if ((ch[0] != '.') || (ch[3] != '.'))
		return result;
	// Validate second and third chars combinations are valid
	if (((tolower(ch[1]) == 'g') && (tolower(ch[2]) == 't'))
		|| ((tolower(ch[1]) == 'l') && (tolower(ch[2]) == 't'))
		|| ((tolower(ch[1]) == 'e') && (tolower(ch[2]) == 'q'))
		|| ((tolower(ch[1]) == 'g') && (tolower(ch[2]) == 'e'))
		|| ((tolower(ch[1]) == 'l') && (tolower(ch[2]) == 'e'))
		|| ((tolower(ch[1]) == 'n') && (tolower(ch[2]) == 'e')))
		result = true;
	// Return result (false or true)
	return result;
} // End of isRelationalOperator

bool isArithmeticOperator(const char* ch)
{
	bool result = false;
	// Validate char array is 5 characters long
	if (strlen(ch) != 5)
		return result;
	// Validate first and last char are '.'
	if ((ch[0] != '.') || (ch[4] != '.'))
		return result;
	// Validate second and third chars combinations are valid
	if (((tolower(ch[1]) == 'a') && (tolower(ch[2]) == 'd') && (tolower(ch[3]) == 'd'))
		|| ((tolower(ch[1]) == 's') && (tolower(ch[2]) == 'u') && (tolower(ch[3]) == 'b'))
		|| ((tolower(ch[1]) == 'm') && (tolower(ch[2]) == 'u') && (tolower(ch[3]) == 'l'))
		|| ((tolower(ch[1]) == 'd') && (tolower(ch[2]) == 'i') && (tolower(ch[3]) == 'v')))
		result = true;
	// Return result (false or true)
	return result;
} // End of isArithmeticOperator


bool isAddOperator(const char* ch)
{
	bool result = false;
	// Validate char array is 5 characters long
	if (strlen(ch) != 5)
		return result;
	// Validate first and last char are '.'
	if ((ch[0] != '.') || (ch[4] != '.'))
		return result;
	// Validate second and third chars combinations are valid
	if ((tolower(ch[1]) == 'a') && (tolower(ch[2]) == 'd') && (tolower(ch[3]) == 'd'))
		result = true;
	// Return result (false or true)
	return result;
} // End of is AddOperator


bool isSubOperator(const char* ch)
{
	bool result = false;
	// Validate char array is 5 characters long
	if (strlen(ch) != 5)
		return result;
	// Validate first and last char are '.'
	if ((ch[0] != '.') || (ch[4] != '.'))
		return result;
	// Validate second and third chars combinations are valid
	if ((tolower(ch[1]) == 's') && (tolower(ch[2]) == 'u') && (tolower(ch[3]) == 'b'))
		result = true;
	// Return result (false or true)
	return result;
} // End of is SubOperator


bool isMulOperator(const char* ch)
{
	bool result = false;
	// Validate char array is 5 characters long
	if (strlen(ch) != 5)
		return result;
	// Validate first and last char are '.'
	if ((ch[0] != '.') || (ch[4] != '.'))
		return result;
	// Validate second and third chars combinations are valid
	if ((tolower(ch[1]) == 'm') && (tolower(ch[2]) == 'u') && (tolower(ch[3]) == 'l'))
		result = true;
	// Return result (false or true)
	return result;
} // End of is MulOperator


bool isDivOperator(const char* ch)
{
	bool result = false;
	// Validate char array is 5 characters long
	if (strlen(ch) != 5)
		return result;
	// Validate first and last char are '.'
	if ((ch[0] != '.') || (ch[4] != '.'))
		return result;
	// Validate second and third chars combinations are valid
	if ((tolower(ch[1]) == 'd') && (tolower(ch[2]) == 'i') && (tolower(ch[3]) == 'v'))
		result = true;
	// Return result (false or true)
	return result;
} // End of is DivOperator


bool isString(char *p)
{
	//bool flag = true;
	int lastChar = 0;
	int count = 0;
	int i = 0;
	for (i = 0; *(p + i) != '\0'; i++)
	{
		if (i == 0)
		{
			if (*(p + i) != '"')
				return false;
			else
				count++;
		}
		if (*(p + i + 1) != '\0')
			lastChar++;
	}
	if (*(p + lastChar) != '"')
		return false;
	if (i == 1)
		return false;
	else
		return true;

} // End of isString


bool isInteger(const char* ch)
{
	// Declare variables
	int i = 0;
	bool digitFound = false;
	// Validate if first character is a sign (+/-)
	if ((ch[i] == '-') || (ch[i] == '+'))
		i++;
	// Validate the rest of the text is digits
	for (; i < strlen(ch); i++)
	{
		if (!((ch[i] >= '0') && (ch[i] <= '9')))
			return false;
		else
			digitFound = true;
	}
	return digitFound;
} // End of isInteger


bool isReal(const char* ch)
{
	// Declare variables
	int i = 0;                    // counter for loops and char array element
	bool periodFound = false;    // validate if a period was found
	bool exponentFound = false;    // validate if an exponent was found
	bool integerFound = false;    // validate if an integer part was found
	bool decimalFound = false;    // validate if a decimal part was found
	bool expIntFound = false;    // validate if an integer part for the exponent was found
	bool expDecFound = false;    // validate if a decimal part for the exponent was found
	// Validate if first character is a sign (+/-)
	if ((ch[i] == '-') || (ch[i] == '+'))
		i++;
	// Validate that the following characters are digits up until finding a period
	for (; (i < strlen(ch)) && (!periodFound); i++)
	{
		if (ch[i] == '.')
			periodFound = true;
		else if (!((ch[i] >= '0') && (ch[i] <= '9')))
			return false;
		else
			integerFound = true;
	}
	// Return false if integer digits were not found
	if (!integerFound)
		return integerFound;
	// Validate that all remaining characters after the period are digits
	// up until finding an exponent or the end of the array
	for (; (i < strlen(ch)) && (!exponentFound); i++)
	{
		if ((ch[i] == 'e') || (ch[i] == 'E'))
			exponentFound = true;
		else if (!((ch[i] >= '0') && (ch[i] <= '9')))
			return false;
		else
			decimalFound = true;
	}
	// Return false if decimal digits were not found
	if (!decimalFound)
		return decimalFound;
	// Validate exponent part if it has an exponent part
	if (exponentFound)
	{
		periodFound = false;
		exponentFound = false;
		// Validate if first character is a sign (+/-)
		if ((ch[i] == '-') || (ch[i] == '+'))
			i++;
		// Validate that the following characters are digits up until finding a period
		for (; (i < strlen(ch)) && (!periodFound); i++)
		{
			if (ch[i] == '.')
				periodFound = true;
			else if (!((ch[i] >= '0') && (ch[i] <= '9')))
				return false;
			else
				expIntFound = true;
		}
		// Return false if integer digits were not found
		if (!expIntFound)
			return expIntFound;
		// Validate that all remaining characters after the period are digits
		// up until finding an exponent or the end of the array
		for (; (i < strlen(ch)); i++)
		{
			if (!((ch[i] >= '0') && (ch[i] <= '9')))
				return false;
			else
				expDecFound = true;
		}
		// Return false if decimal digits were not found
		if (!expDecFound)
			return expDecFound;
	} // End of validation of exponent part
	// Return true if period and digits were found
	return (true);
} // End of isReal

bool isNumber(const char* ch)
{
	return (isInteger(ch) || isReal(ch));
} // End of isNumber

bool isRealVariable(const char* ch)
{
	if ((ch[0] >= 'g' && ch[0] <= 'n') || (ch[0] >= 'G' && ch[0] <= 'N'))
		return true;
	return false;
} // End of isRealVariable

bool isIntegerVariable(const char* ch)
{
	if ((ch[0] >= 'a' && ch[0] <= 'f') || (ch[0] >= 'A' && ch[0] <= 'F'))
		return true;
	return false;
} // End of isIntegerVariable

bool isStringVariable(const char* ch)
{
	if ((ch[0] >= 'o' && ch[0] <= 'z') || (ch[0] >= 'O' && ch[0] <= 'Z'))
		return true;
	return false;
} // End of isStringVariable

bool isPrintKeyword(const char* ch)
{
	bool result = false;
	// Validate char array is 2 to 5 characters long
	if (strlen(ch) != 5)
		return result;
	// Validate if text is the keyword 'IF'
	if ((tolower(ch[0]) == 'p')
		&& (tolower(ch[1]) == 'r')
		&& (tolower(ch[2]) == 'i')
		&& (tolower(ch[3]) == 'n')
		&& (tolower(ch[4]) == 't'))
		result = true;
	// Return result (false or true)
	return result;
} // End of isPrintKeyword

bool isPrintStatement(const char* ch)
{
	bool validKeyword;
	bool validToken;
	// Return false if input was blank
	if (strlen(ch) == 0)
	{
		cout << "Error: Text is blank.\nExpected a PRINT keyword\n";
		return false;
	}
	// Trim leading blank spaces
	int i = 0;
	while (ch[i] == ' ')
		i++;
	// Return false if not enough characters for PRINT keyword are available.
	if (strlen(ch) - i < 5)
	{
		cout << "Error: Expected a PRINT keyword\n";
		return false;
	}
	// copy first token to validate
	char print[6] = { ch[i], ch[i + 1], ch[i + 2], ch[i + 3], ch[i + 4], '\0' };
	validKeyword = isPrintKeyword(print);
	// If first part is not PRINT return false
	if (!validKeyword)
	{
		cout << "Error: Expected a PRINT keyword\n";
		return validKeyword;
	}
	// Validate if there are more characters in the text
	if (strlen(ch) - i > 5)
	{
		// Update i
		i += 5;
		// Trim spaces
		while (ch[i] == ' ')
			i++;
		// Validate text after print keyword if there is any
		if (ch[i] != '\0')
		{
			char value[300];
			int j = 0;
			for (; i < strlen(ch); i++, j++) // Copy following text
			{
				value[j] = ch[i];
			}
			value[j] = '\0';
			// Validate if text is a valid token
			validToken = isVariable(value)
				|| isNumber(value)
				|| isString(value);
			//if (!validToken)
				//cout << "Error: Expected a variable, number or string after PRINT keyword.\n";

			if (isString(value) || isNumber(value))
			{
				cout << value << endl;
			}

			if (isVariable(value))
			{
				if (findVariable(value))
				{
					for (int i = 0;i < totalVariables; i++)
					{
						if (symbolTable[i].getText() == value)
							break;
					}

					if (isIntegerVariable(value))
					{
						int intData;
						if (findIntegerVariable(value, intData))
							cout << intData << endl;
					}

					if (isRealVariable(value))
					{
						double doubleData;
						if (findRealVariable(value, doubleData))
							cout << doubleData << endl;
					}

					if (isStringVariable(value))
					{
						char stringData[100];
						if (findStringVariable(value, stringData))
							cout << stringData << endl;
					}
				}
				else
				{
					cout << "\nERROR LINE #" << lineCount << ": VARIABLE NOT DEFINED!!!" << endl;
					return 0;
				}

			}


			return (validToken);
		}
		else // Return true if only blank spaces were found after PRINT keyword
			return validKeyword;
	} // End of: if (strlen(ch) - i > 5)
	else // If there are no more characters after PRINT keyword return true
		return validKeyword;
} // End of isPrintStatement

bool isEnd(const char* ch)
{
	if ((tolower(ch[0]) == 'e') && (tolower(ch[1]) == 'n') && (tolower(ch[2]) == 'd') && (tolower(ch[3]) == '.') && strlen(ch) == 4)
		return true;
	else
		return false;
} // End of isEnd

bool isComment(const char* ch)
{
	if ((tolower(ch[0]) == 'r') && (tolower(ch[1]) == 'e') && (tolower(ch[2]) == 'm'))
		return true;
	else
		return false;
} // End of isComment

bool isRead(const char* ch)
{
	int i = 5;
	char value[300];
	int j = 0;


	for (; i < strlen(ch); i++, j++) // Copy following text
	{
		value[j] = ch[i];
	}

	value[j] = '\0';


	if ((tolower(ch[0]) == 'r') && (tolower(ch[1]) == 'e') && (tolower(ch[2]) == 'a') && (tolower(ch[3]) == 'd')
		&& ch[4] == ' ' && isVariable(value))
	{
		if (isRealVariable(value))
		{
			double doubleData;
			cin >> doubleData;
			Variable tempDouble(value, doubleData);
			updateSymbolTable(tempDouble);
		}

		if (isIntegerVariable(value))
		{
			int intData;
			cin >> intData;
			Variable tempIntData(value, intData);
			updateSymbolTable(tempIntData);
		}

		if (isStringVariable(value))
		{
			char stringData[100];
			cin >> stringData;
			Variable tempString(value, stringData);
			updateSymbolTable(tempString);
		}

		return true;
	}
	else
		return false;

} // End of isRead

bool isAssignmentOperator(const char* ch) {

	if (strlen(ch) != 1)
		return false;

	if (ch[0] == '=')
		return true;
	return false;
}// End of isAssignmentOperator

bool isAssignmentStatement(const char* ch)
{

	int i = 0, j = 0;
	char value[300];
	bool integerVariable = false;
	bool realVariable = false;
	bool stringVariable = false;
	string type;

	for (; ((ch[i]) != ' ') && (i < strlen(ch)); i++)
	{
		value[i] = ch[i];
	}
	value[i] = '\0';

	if (!(isVariable(value)))
	{
			system("cls");
			cout << "Line: " << lineCount << "->\nInitial VARIABLE not found\n" << endl;
		return false;
	}
	else
	{
		if (isIntegerVariable(value))
		{
			integerVariable = true;
			type = "integer";
		}			
		else if (isRealVariable(value))
		{
			realVariable = true;
			type = "real";
		}
		else
		{
			stringVariable = true;
			type = "string";
		}
	}

	while (ch[i] == ' ' && i < strlen(ch))
		i++;

	for (; ((ch[i]) != ' ') && (i < strlen(ch)); i++, j++) {

		value[j] = ch[i];
	}
	value[j] = '\0';
	j = 0;

	if (!(isAssignmentOperator(value)))
	{
		system("cls");
		cout << "Line: " << lineCount << "->\n The Assignment Symbol wasn't found as expected\n" << endl;
		return false;
	}

	for (; i < strlen(ch); i++, j++)
	{
		value[j] = ch[i];
	}
	value[j] = '\0';
	j = 0;

	if (!(isArithmeticExpression(value, type)))
	{
		system("cls");
		cout << "Line: " << lineCount << "->\nA valid Arithmetic Expression is expected after the '=' symbol\n" << endl;
		return false;
	}

	return true;
}// End of isAssignmentStatement

bool isArithmeticExpression(const char* ch, string variableType)
{

	int i = 0, j = 0;
	char token[300];
	bool searchValue = true;
	bool integerFound = false;
	bool realFound = false;
	bool stringFound = false;
	string resultType;

	do {
		while (ch[i] == ' ' && i < strlen(ch))
			i++;
		for (; (ch[i]) != ' ' && i < strlen(ch); i++, j++) {

			token[j] = ch[i];
		}
		token[j] = '\0';
		j = 0;

		if (searchValue) {
			if (!(isNumber(token) || isVariable(token) || isString(token)))
			{

				
				system("cls");
				cout << "Line: " << lineCount << "->\nA NUMBER or a VARIABLE or a STRING was expected\n" << endl;
				return false;
			}

			if ((isInteger(token)) || (isIntegerVariable(token)))
			{
				integerFound = true;
			}
			else if ((isReal(token)) || (isRealVariable(token)))
			{
				realFound = true;
			}
			else if ((isString(token)) || (isStringVariable(token)))
			{
				stringFound = true;
			}
			searchValue = false;
		}
		else {
			if (!(isArithmeticOperator(token))) {

				
				system("cls");
				cout << "Line: " << lineCount << "->\nA Arithmetic OPERATOR was expected and not found\n" << endl;
				return false;
			}
			searchValue = true;
		}
	} while (i < strlen(ch));

	if (searchValue)
	{

		
		system("cls");
		cout << "Line: " << lineCount << "->\nAn Operator token can not end an Arithmetic Expression\n" << endl;
		return false;
	}
	else // Validate variable type matches result of arithmetic expression
	{
		// Calculate result type
		if (stringFound)
			resultType = "string";
		else if (realFound)
			resultType = "real";
		else if (integerFound)
			resultType = "integer";

		// Compare variable type with result type
		if (variableType != resultType)
		{
		
			system("cls");
			cout << "Line: " << lineCount << "->\nResult of arithmetic expression does not match variable type.\n";
			cout << "\tVariable type: " << variableType << endl;
			cout << "\tType of arithmetic expression: " << resultType << endl;
		}
	}
	
	return true;
}//End of isArithmeticExpression


/*
Get Location of then keyword
Return location in the array or -1 if their is no then
*/
int getLocThen(const char* ch) {
	for (int i = 0; i < strlen(ch) - 3; i++) {
		if (ch[i] == 't' && ch[i + 1] == 'h' && ch[i + 2] == 'e' && ch[i + 3] == 'n' && ch[i + 4] == ' ') {
			return i;
		}
	}
	return -1;

} // End of getLocThen


/*
Check If then valid
Return if then valid is valid
*/

bool isIfThenValid(const char* ch) {
	//check that at the beginning
	if (!(tolower(ch[0]) == 'i' && tolower(ch[1]) == 'f' && tolower(ch[2]) == ' '))
		return false;
	//check that their is a then statement
	if (getLocThen(ch) == -1)
		return false;
	//Divide If Sentence in 2 part, condition and is valid commnad(print, rem, etc)
	char condition[300];
	char command[300];

	//Get condition part
	int i = 0;
	int getLoc = getLocThen(ch);
	for (i = 3; i < strlen(ch) - (strlen(ch) - getLoc) - 1; i++) {
		condition[i - 3] = ch[i];
	}
	condition[i - 3] = '\0';

	bool conditionValid = isConditionValid(condition); // HERE GOES THE CHECK CONDITION
	if (!conditionValid) {    //First Error Message, expect more information as lower the is goes
		//cout << "Error: Invalid condtion: Expected: ";
		return false;
	}
	bool operation = parseAndOrNot(condition);
	if (!operation) {
		return false;
	}
	//Get then command
	for (i = getLocThen(ch) + 5; i < strlen(ch); i++) {
		command[i - getLocThen(ch) - 5] = ch[i];
	}
	command[i - getLocThen(ch) - 5] = '\0';

	bool commandValid = isCommandValid(command); // HERE GOES THE CHECK command

	if (commandValid) {
		if (!((tolower(command[0]) == 'p' && tolower(command[1]) == 'r' && tolower(command[2]) == 'i' && tolower(command[3]) == 'n' && tolower(command[4]) == 't' && tolower(command[5]) == ' ')
			||!(tolower(command[0]) == 'r' && tolower(command[1]) == 'e' && tolower(command[2]) == 'a' && tolower(command[3]) == 'd' && tolower(command[4]) == ' '))) {
			bool executionStatus = executeAssignmentStatement(command);
			if (executionStatus)
				cout << "Error: Invalid Assigment Statement";
		}
	}

	if (!commandValid) {
		return false;
	}

	return true;
}  // isIfThenValid


/*
Find a logical operator 'and'
-1 mean no 'and' detected
*/

int findLogicalAnd(const char* ch) {
	for (int i = 0; i < strlen(ch); i++) {
		if (ch[i] == '.') {
			if (((tolower(ch[i]) == '.' && tolower(ch[i + 1]) == 'a' && tolower(ch[i + 2]) == 'n' && tolower(ch[i + 3]) == 'd' && tolower(ch[i + 4]) == '.' && tolower(ch[i + 5]) == ' '))) {
				return i;
			}
		}
	}
	return -1;
} // End of findLogicalAnd


/*
Find a logical operator 'or'
-1 mean no 'or' detected
*/

int findLogicalOr(const char* ch) {
	for (int i = 0; i < strlen(ch); i++) {
		if (ch[i] == '.') {
			if (((tolower(ch[i]) == '.' && tolower(ch[i + 1]) == 'o' && tolower(ch[i + 2]) == 'r' && tolower(ch[i + 3]) == '.'&& tolower(ch[i + 4] == ' ')))) {
				return i;
			}
		}
	}
	return -1;
}  // End of findLogicalOr

/*
Check that condition is valid
Divide and, or, expression
<Operation> and <Operation>, this can compound and will self call himself until no '.and.', '.or.', '.not.' expression is found
*/
bool isConditionValid(const char* ch) {

	//Check for not statement
	if (tolower(ch[0]) == '.' && tolower(ch[1]) == 'n' && tolower(ch[2]) == 'o' && tolower(ch[3]) == 't' && tolower(ch[4]) == '.' && tolower(ch[5]) == ' ') {
		return isConditionValid(ch + 6);
	}//End of removal of not
	if (findLogicalOr(ch) != -1 || findLogicalAnd(ch) != -1) { //Check if their any and or keywords

		if (findLogicalOr(ch) != -1 && findLogicalAnd(ch) != -1) { //Check if their 2 more 'and' or 'or' keywords

			if (findLogicalOr(ch) < findLogicalAnd(ch)) { // Take the first 'and' or 'or'  and start dividing

				int logicalOr = findLogicalOr(ch);
				int i = 0;
				char oper1[300];
				char oper2[300];

				//First Division
				for (i = 0; i < logicalOr - 1; i++) {
					oper1[i] = ch[i];
				}
				oper1[i + 1] = '\0';
				//End of First Division

				bool validOper = isConditionValid(oper1); // Check this part is valid

				//Start of Second Division
				if (!validOper)
					return false;

				for (i = logicalOr + 5; i < strlen(ch); i++) {
					oper2[i - logicalOr - 5] = ch[i];
				}
				oper2[i - logicalOr - 5] = '\0';
				//End of Second Division
				validOper = isConditionValid(oper2); //Check this part is valid

				if (!validOper)
					return false;
				return true;

			}
			else {
				int logicalAnd = findLogicalAnd(ch);
				int i = 0;
				char oper1[300];
				char oper2[300];

				//First Division
				for (i = 0; i < logicalAnd - 1; i++) {
					oper1[i] = ch[i];
				}
				oper1[i] = '\0';
				//Check Oper1
				bool validOper = isConditionValid(oper1);

				if (!validOper)
					return false; //Return false if operator is invalid stucture
				//Second Division
				for (i = logicalAnd + 6; i < strlen(ch); i++) {
					oper2[i - logicalAnd - 6] = ch[i];
				}
				//Check Oper2
				oper2[i - logicalAnd - 6] = '\0';

				validOper = isConditionValid(oper2);

				if (!validOper)
					return false; //Return false if operator is invalid structure
				return true;
			}

		}
		if (findLogicalAnd(ch) != -1) { // One 'and' and no 'or' decteded
			int logicalAnd = findLogicalAnd(ch);
			int i = 0;
			char oper1[300];
			char oper2[300];

			//First Division
			for (i = 0; i < logicalAnd - 1; i++) {
				oper1[i] = ch[i];
			}
			oper1[i] = '\0';

			bool validOper = isConditionValid(oper1); // Check if operator is valid

			if (!validOper)
				return false;

			//Second Division
			for (i = logicalAnd + 6; i < strlen(ch); i++) {
				oper2[i - logicalAnd - 6] = ch[i];
			}
			oper2[i - logicalAnd - 6] = '\0';

			validOper = isConditionValid(oper2); //Check if operator is valid

			if (!validOper)
				return false;
			return true;
		}
		else { //One 'or' and no 'and' decteded
			int logicalOr = findLogicalOr(ch);
			int i = 0;
			char oper1[300];
			char oper2[300];
			//First Division
			for (i = 0; i < logicalOr - 1; i++) {
				oper1[i] = ch[i];
			}
			oper1[i] = '\0';

			bool validOper = isConditionValid(oper1); //Check if operator is valid

			if (!validOper)
				return false;
			//Second Divison
			for (i = logicalOr + 5; i < strlen(ch); i++) {
				oper2[i - logicalOr - 5] = ch[i];
			}
			oper2[i - logicalOr - 5] = '\0';

			validOper = isConditionValid(oper2); // Check if operator is valid

			if (!validOper)
				return false;
			return true;
		}
	}

	return isCompOperValid(ch);
}  // End of isConditionValid

/*
Check that the command is valid
Receive Print, Read, Asig
*/
bool isCommandValid(const char* ch) {
	int i = 0;
	char firstToken[300];
	for (i = 0; (ch[i] != ' ') && (i < strlen(ch)); i++)
	{
		firstToken[i] = ch[i];
	}
	firstToken[i] = '\0';

	if (strlen(ch) == 0)
	{
		cout << "Error: Expected a Print, Read or Assignment Statement after THEN keyword.\n";
		return false;
	}
	else if (isPrintKeyword(firstToken))
		return (isPrintStatement(ch));
	else if (isReadKeyword(firstToken))
		return (isRead(ch));
	else if (isVariable(firstToken))
		return (isAssignmentStatement(ch));
	else
	{
		cout << "Error: Expected a Print, Read or Assignment Statement after THEN keyword.\n";
		return false;
	}
} // End of isCommandValid

/*
Find a comparison key
Return -1 if their is no comparison
Return start of comparison key.
*/

int findComparisonKey(const char* ch) {
	for (int i = 0; i < strlen(ch); i++) {
		if (ch[i] == ' ') {
			if ((tolower(ch[i + 1]) == '.' && tolower(ch[i + 2]) == 'e' && tolower(ch[i + 3]) == 'q' && tolower(ch[i + 4]) == '.'&& tolower(ch[i + 5] == ' ')) ||
				(tolower(ch[i + 1]) == '.' && tolower(ch[i + 2]) == 'n' && tolower(ch[i + 3]) == 'e' && tolower(ch[i + 4]) == '.'&& tolower(ch[i + 5] == ' ')) ||
				(tolower(ch[i + 1]) == '.' && tolower(ch[i + 2]) == 'l' && tolower(ch[i + 3]) == 't' && tolower(ch[i + 4]) == '.'&& tolower(ch[i + 5] == ' ')) ||
				(tolower(ch[i + 1]) == '.' && tolower(ch[i + 2]) == 'l' && tolower(ch[i + 3]) == 'e' && tolower(ch[i + 4]) == '.'&& tolower(ch[i + 5] == ' ')) ||
				(tolower(ch[i + 1]) == '.' && tolower(ch[i + 2]) == 'g' && tolower(ch[i + 3]) == 't' && tolower(ch[i + 4]) == '.'&& tolower(ch[i + 5] == ' ')) ||
				(tolower(ch[i + 1]) == '.' && tolower(ch[i + 2]) == 'g' && tolower(ch[i + 3]) == 'e' && tolower(ch[i + 4]) == '.' && tolower(ch[i + 5] == ' ')))
			{
				return i;
			}
		}
	}
	return -1;
}  // End of findComparisonKey

/*
Check that operation is valid
Input are, 3 .qt. var, etc combination. There will be no 'and', 'or', 'not' in this place.
*/

bool isCompOperValid(const char* ch) {
	if (findComparisonKey(ch) == -1) { //First Error
		cout << "Error: No Valid comparison found \n ";
		return false;
	}
	else
	{
		int logicalCompareLoc = findComparisonKey(ch);
		int i = 0;
		bool firstValueValid = false;
		bool firstValueString = false;
		bool secondValueValid = false;
		bool secondValueString = false;
		char value1[300];
		char value2[300];
		//Divide Input in 2 part.
		for (i = 0; i < strlen(ch) - (strlen(ch) - logicalCompareLoc); i++) {
			value1[i] = ch[i];
		}
		value1[i] = '\0';
		//End of first Division

		//Divide Input in 2 part
		for (i = logicalCompareLoc + 6; i < strlen(ch); i++) {
			value2[i - logicalCompareLoc - 6] = ch[i];
		}
		value2[i - logicalCompareLoc - 6] = '\0';
		//End of second Division

		//Check First Value
		if ((isVariable(value1)) || (isNumber(value1)) || (isString(value1)))
		{
			firstValueValid = true;
			if ((isString(value1)) || (isStringVariable(value1)))
				firstValueString = true;
		}
		else
		{
			cout << "Error: Invalid Value for comparison\n";
			return false;
		}

		//Check Second Value if first value was valid
		if (firstValueValid)
		{
			if ((isVariable(value2)) || (isNumber(value2)) || (isString(value2)))
			{
				firstValueValid = true;
				if ((isString(value2)) || (isStringVariable(value2)))
					secondValueString = true;
			}
			else
			{
				cout << "Error: Invalid Value for comparison\n";
				return false;
			}
		}

		// Check if there is a String value that it is compared only to another String
		if (firstValueString || secondValueString)
		{
			if (firstValueString && secondValueString) // If both are true, return true
				return true;
			else {// Return false if both are not String
				cout << "Error: Comparision need to be between String and String\n";
				return false;
			}
		}
		else // Values are valid numbers, returns true
			return true;
	}
}  // End of isCompOperValid

void updateSymbolTable(Variable aVariable)
{
	if (totalVariables == 0)
	{
		symbolTable[0] = aVariable;
		totalVariables++;
	}
	else
	{
		int i = 0;
		bool variableFound = false;
		for (; (i < totalVariables) && (!variableFound); i++)
		{
			if (strcmp(symbolTable[i].getText(),aVariable.getText()) == 0)
			{
				symbolTable[i] = aVariable;
				variableFound = true;
			}
		}
		if (!variableFound)
		{
			symbolTable[i] = aVariable;
			totalVariables++;
		}
	}
} // End of updateSymbolTable


bool findVariable(const char* ch)
{
	if (totalVariables == 0)
	{
		return false;
	}
	else
	{
		int i = 0;
		for (; (i < totalVariables); i++)
		{
			if (strcmp(symbolTable[i].getText(), ch) == 0)
				return true;
		}
		return false;
	}
}


bool findIntegerVariable(const char* ch, int & value)
{
	if (totalVariables == 0)
	{
		return false;
	}
	else
	{
		int i = 0;
		for (; (i < totalVariables) ; i++)
		{
			if (strcmp(symbolTable[i].getText(),ch) == 0)
			{
				value = symbolTable[i].getIntValue();
				return true;
			}
		}
		return false;
	}
} // End of findIntVariable


bool findRealVariable(const char* ch, double & value)
{
	if (totalVariables == 0)
	{
		return false;
	}
	else
	{
		int i = 0;
		for (; (i < totalVariables); i++)
		{
			if (strcmp(symbolTable[i].getText(),ch) == 0)
			{
				value = symbolTable[i].getRealValue();
				return true;
			}
		}
		return false;
	}
} // End of findRealVariable


bool findStringVariable(const char* ch, char* value)
{
	if (totalVariables == 0)
	{
		return false;
	}
	else
	{
		int i = 0;
		for (; (i < totalVariables); i++)
		{
			if (strcmp(symbolTable[i].getText(),ch) == 0)
			{
				int j = 0;
				for (; j < strlen(symbolTable[i].getStringValue()); j++)
				{
					value[j] = symbolTable[i].copyStringValue(j);
				}
				value[j] = '\0';
				return true;
			}
		}
		return false;
	}
} // End of findStringVariable


bool executeAssignmentStatement(const char* ch)
{
	// Declaration of variables and arrays
	bool operationCompleted = true;
	int i = 0, j = 0;
	char variable[300];
	string variableType;
	Token tempToken();
	Token tokenArray[50];
	int tokenAmount = 0;
	char tempArray[100];
	string tokenType;
	int countMulDiv = 0;
	int countAddSub = 0;
	bool operatorFound;
	int intNumber;
	double realNumber;


	// Trim leading blank spaces
	while (ch[i] == ' ' && i < strlen(ch))
		i++;

	// Read variable name
	for (; ((ch[i]) != ' ') && (i < strlen(ch)); i++, j++)
	{
		variable[j] = ch[i];
	}
	variable[j] = '\0';
	j = 0;

	// Find variable type
	if (isIntegerVariable(variable))
		variableType = "integer";
	else if (isRealVariable(variable))
		variableType = "real";
	else
		variableType = "string";

	// Trim blank spaces and assignment operator
	while (((ch[i] == ' ') || (ch[i] == '=')) && (i < strlen(ch)))
		i++;

	// Create tokens and place in array
	while (i < strlen(ch))
	{
		int counter = 0;
		for (; (ch[i] != ' ') && (i < strlen(ch)); i++, counter++)
		{
			tempArray[counter] = ch[i];
		}
		tempArray[counter] = '\0';
		counter = 0;
		i++;

		if (isIntegerVariable(tempArray))
			tokenType = "integer variable";
		else if (isRealVariable(tempArray))
			tokenType = "real variable";
		else if (isStringVariable(tempArray))
			tokenType = "string variable";
		else if (isInteger(tempArray))
			tokenType = "integer";
		else if (isReal(tempArray))
			tokenType = "real";
		else if (isString(tempArray))
			tokenType = "string";
		else if (isAddOperator(tempArray))
		{
			tokenType = "add";
			countAddSub++;
		}
		else if (isSubOperator(tempArray))
		{
			tokenType = "sub";
			countAddSub++;
		}
		else if (isMulOperator(tempArray))
		{
			tokenType = "mul";
			countMulDiv++;
		}
		else if (isDivOperator(tempArray))
		{
			tokenType = "div";
			countMulDiv++;
		}

		tokenArray[tokenAmount].setText(tempArray);
		tokenArray[tokenAmount].setType(tokenType);
		tokenAmount++;
	} // Finished creating tokens

	// Testing
	/*int k = 0;
	cout << "Testing tokenArray before arithmetic operations:\n";
	for (; k < tokenAmount; k++)
	{
		cout << "tokenArray[" << k << "]: " << endl;
		cout << "\tText: " << tokenArray[k].getText() << endl;
		cout << "\tType: " << tokenArray[k].getType() << endl;
	}
	cout << endl;*/
	// End testing
	

	// Search mul and div operations
	while(countMulDiv > 0)
	{
		operatorFound = false;
		for (int s = 1; (s < tokenAmount) && (!operatorFound); s++)
		{
			if (tokenArray[s].getType() == "mul")
			{
				operatorFound = true;
				operationCompleted = mul(tokenArray[s - 1], tokenArray[s + 1]);
				if (!operationCompleted)
					return operationCompleted;
			}
			else if (tokenArray[s].getType() == "div")
			{
				operatorFound = true;
				operationCompleted = div(tokenArray[s - 1], tokenArray[s + 1]);
				if (!operationCompleted)
					return operationCompleted;
			}
			
			if (operatorFound)
			{				
				countMulDiv--; // Reduce count of mul/div operators left

				if ((tokenAmount - 2) == s) // operation worked was the last in tokenArray.
					tokenAmount -= 2; // "Delete" last operator and value
				else // If there are more operators and values to the right
				{
					int a = s;
					for (; a < (tokenAmount - 2); a++)
					{
						tokenArray[a] = tokenArray[a + 2];
					}
					tokenAmount -= 2;
				}
			} // end if operator found
			// Don't do anything if operator was not found. Let for loop search the next tokens.
		} // End of for loop
	} // End of while (countMulDiv > 0)
	
	// Search add and sub operators
	while (countAddSub > 0)
	{
		operatorFound = false;
		for (int s = 1; (s < tokenAmount) && (!operatorFound); s++)
		{
			if (tokenArray[s].getType() == "add")
			{
				operatorFound = true;
				operationCompleted = add(tokenArray[s - 1], tokenArray[s + 1]);
				if (!operationCompleted)
					return operationCompleted;
			}
			else if (tokenArray[s].getType() == "sub")
			{
				operatorFound = true;
				operationCompleted = sub(tokenArray[s - 1], tokenArray[s + 1]);
				if (!operationCompleted)
					return operationCompleted;
			}

			if (operatorFound)
			{
				countAddSub--; // Reduce count of mul/div operators left

				if ((tokenAmount - 2) == s) // operation worked was the last in tokenArray.
					tokenAmount -= 2; // "Delete" last operator and value
				else // If there are more operators and values to the right
				{
					int a = s;
					for (; a < (tokenAmount - 2); a++)
					{
						tokenArray[a] = tokenArray[a + 2];
					}
					tokenAmount -= 2;
				}
			} // end if operator found
			// Don't do anything if operator was not found. Let for loop search the next tokens.
		} // End of for loop
	} // End of while (countAddSub > 0)

	// Testing
	/*cout << "Testing tokenArray after arithmetic expressions:\n";
	for (int k = 0; k < tokenAmount; k++)
	{
		cout << "tokenArray[" << k << "]: \n";
		cout << "\tText: " << tokenArray[k].getText() << endl;
		cout << "\tType: " << tokenArray[k].getType() << endl;
	}*/
	
	// Create variable in symbolTable
	if (variableType == "integer")
	{
		intNumber = atoi(tokenArray[0].getText());
		Variable tempVariable(variable, intNumber);
		updateSymbolTable(tempVariable);		
	}
	else if (variableType == "real")
	{
		realNumber = realToValue(tokenArray[0].getText());
		Variable tempVariable(variable, realNumber);
		updateSymbolTable(tempVariable);
	}
	else if (variableType == "string")
	{
		Variable tempVariable(variable, tokenArray[0].getText());
		updateSymbolTable(tempVariable);
	}
	
	return true;
} // End of executeAssignment Statement


double realToValue(const char* ch)
{
	char intBase[20];
	char decBase[20];
	char intExp[20];
	char decExp[20];
	bool dotFound = false;
	bool exponentFound = false;
	int i = 0;
	double result;

	// Cut and save integer part of base
	for (; i < strlen(ch) && ch[i] != '.'; i++)
	{
		intBase[i] = ch[i];
	}
	intBase[i] = '\0';
	i++;

	// Cut and save decimal part of base
	int dbCounter = 0;
	for (; (i < strlen(ch)) && (tolower(ch[i]) != 'e'); i++, dbCounter++)
	{
		decBase[dbCounter] = ch[i];
	}
	decBase[dbCounter] = '\0';

	// Validate if there is an exponential part
	if (tolower(ch[i]) == 'e') 
	{
		exponentFound = true;
		i++;
	}

	if (exponentFound) // If there is an exponential part ...
	{
		// ... cut and save the integer part of the exponential part
		int ieCounter = 0;
		for (; (i < strlen(ch)) && (tolower(ch[i]) != '.'); i++, ieCounter++)
		{
			intExp[ieCounter] = ch[i];
		}
		intExp[ieCounter] = '\0';
		i++;

		// Cut and save the decimal part of the exponential part
		int deCounter = 0;
		for (; (i < strlen(ch)) && (tolower(ch[i]) != '.'); i++, deCounter++)
		{
			decExp[deCounter] = ch[i];
		}
		decExp[deCounter] = '\0';
		i++;
	}

	// Convert and calculate value
	if (exponentFound)
	{
		double intPart = atof(intBase);
		double decPart;
		if (intPart < 0)
			decPart = (-1) * atof(decBase) / pow(10, strlen(decBase));
		else
			decPart = atof(decBase) / pow(10, strlen(decBase));
		double intExpPart = atof(intExp);
		double decExpPart = atof(decExp) / pow(10, strlen(decExp));
		double base = intPart + decPart;
		double exponent = intExpPart + decExpPart;
		result = pow(base, exponent);
		return result;
	}
	else // No exponential part
	{
		double intPart = atof(intBase);
		double decPart;
		if (intPart < 0)
			decPart = (-1) * atof(decBase) / pow(10, strlen(decBase));
		else
			decPart = atof(decBase) / pow(10, strlen(decBase));
		double result = intPart + decPart;
		return result;
	}

} // End of realToValue


bool mul(Token & operand1, Token & operand2)
{
	int intNumber1, intNumber2, intResult;
	double doubleNumber1, doubleNumber2, doubleResult;
	bool variableFound;
	char tempArray[100];
	string tempString;

	if (((operand1.getType() == "integer") || (operand1.getType() == "integer variable"))
		&& ((operand2.getType() == "integer") || (operand2.getType() == "integer variable")))
	{
		// Get first value
		if (operand1.getType() == "integer")
			intNumber1 = atoi(operand1.getText());
		else
		{
			variableFound = findIntegerVariable(operand1.getText(), intNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}
		// Get second value
		if (operand2.getType() == "integer")
			intNumber2 = atoi(operand2.getText());
		else
		{
			variableFound = findIntegerVariable(operand2.getText(), intNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		intResult = intNumber1 * intNumber2;
		itoa(intResult, tempArray, 10);
		operand1.setText(tempArray);

		return true;
	} // End if integer vs. integer

	else if (((operand1.getType() == "integer") || (operand1.getType() == "integer variable"))
		&& ((operand2.getType() == "real") || (operand2.getType() == "real variable")))
	{
		// Get first value
		if (operand1.getType() == "integer")
			intNumber1 = atoi(operand1.getText());
		else
		{
			variableFound = findIntegerVariable(operand1.getText(), intNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}
		// Get second value
		if (operand2.getType() == "real")
		{
			doubleNumber2 = realToValue(operand2.getText());
		}
		else
		{
			variableFound = findRealVariable(operand2.getText(), doubleNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = double(intNumber1) * doubleNumber2;
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);
		operand1.setType("real");

		return true;
	} // End of integer vs. real

	else if (((operand1.getType() == "real") || (operand1.getType() == "real variable"))
		&& ((operand2.getType() == "integer") || (operand2.getType() == "integer variable")))
	{
		// Get first value
		if (operand1.getType() == "real")
		{
			doubleNumber1 = realToValue(operand1.getText());
		}
		else
		{
			variableFound = findRealVariable(operand1.getText(), doubleNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "integer")
			intNumber2 = atoi(operand2.getText());
		else
		{
			variableFound = findIntegerVariable(operand2.getText(), intNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = doubleNumber1 * double(intNumber2);
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);

		return true;
	}

	else if (((operand1.getType() == "real") || (operand1.getType() == "real variable"))
		&& ((operand2.getType() == "real") || (operand2.getType() == "real variable")))
	{
		// Get first value
		if (operand1.getType() == "real")
		{
			doubleNumber1 = realToValue(operand1.getText());
		}
		else
		{
			variableFound = findRealVariable(operand1.getText(), doubleNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "real")
		{
			doubleNumber2 = realToValue(operand2.getText());
		}
		else
		{
			variableFound = findRealVariable(operand2.getText(), doubleNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = doubleNumber1 * doubleNumber2;
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);

		return true;
	}
	cout << "checking fail\n";
	return false; // Should not happen
} // End of mul


bool div(Token & operand1, Token & operand2)
{
	int intNumber1, intNumber2, intResult;
	double doubleNumber1, doubleNumber2, doubleResult;
	bool variableFound;
	char tempArray[100];
	string tempString;

	if (((operand1.getType() == "integer") || (operand1.getType() == "integer variable"))
		&& ((operand2.getType() == "integer") || (operand2.getType() == "integer variable")))
	{
		// Get first value
		if (operand1.getType() == "integer")
			intNumber1 = atoi(operand1.getText());
		else
		{
			variableFound = findIntegerVariable(operand1.getText(), intNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}
		// Get second value
		if (operand2.getType() == "integer")
			intNumber2 = atoi(operand2.getText());
		else
		{
			variableFound = findIntegerVariable(operand2.getText(), intNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		intResult = intNumber1 / intNumber2;
		itoa(intResult, tempArray, 10);
		operand1.setText(tempArray);

		return true;
	} // End if integer vs. integer

	else if (((operand1.getType() == "integer") || (operand1.getType() == "integer variable"))
		&& ((operand2.getType() == "real") || (operand2.getType() == "real variable")))
	{
		// Get first value
		if (operand1.getType() == "integer")
			intNumber1 = atoi(operand1.getText());
		else
		{
			variableFound = findIntegerVariable(operand1.getText(), intNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}
		// Get second value
		if (operand2.getType() == "real")
		{
			doubleNumber2 = realToValue(operand2.getText());
		}
		else
		{
			variableFound = findRealVariable(operand2.getText(), doubleNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = double(intNumber1) / doubleNumber2;
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);
		operand1.setType("real");

		return true;
	} // End of integer vs. real

	else if (((operand1.getType() == "real") || (operand1.getType() == "real variable"))
		&& ((operand2.getType() == "integer") || (operand2.getType() == "integer variable")))
	{
		// Get first value
		if (operand1.getType() == "real")
		{
			doubleNumber1 = realToValue(operand1.getText());
		}
		else
		{
			variableFound = findRealVariable(operand1.getText(), doubleNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "integer")
			intNumber2 = atoi(operand2.getText());
		else
		{
			variableFound = findIntegerVariable(operand2.getText(), intNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = doubleNumber1 / double(intNumber2);
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);

		return true;
	}

	else if (((operand1.getType() == "real") || (operand1.getType() == "real variable"))
		&& ((operand2.getType() == "real") || (operand2.getType() == "real variable")))
	{
		// Get first value
		if (operand1.getType() == "real")
		{
			doubleNumber1 = realToValue(operand1.getText());
		}
		else
		{
			variableFound = findRealVariable(operand1.getText(), doubleNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "real")
		{
			doubleNumber2 = realToValue(operand2.getText());
		}
		else
		{
			variableFound = findRealVariable(operand2.getText(), doubleNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = doubleNumber1 / doubleNumber2;
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);

		return true;
	}
	cout << "checking fail\n";
	return false; // Should not happen
} // End of div


bool sub(Token & operand1, Token & operand2)
{
	int intNumber1, intNumber2, intResult;
	double doubleNumber1, doubleNumber2, doubleResult;
	bool variableFound;
	char tempArray[100];
	string tempString;

	if (((operand1.getType() == "integer") || (operand1.getType() == "integer variable"))
		&& ((operand2.getType() == "integer") || (operand2.getType() == "integer variable")))
	{
		// Get first value
		if (operand1.getType() == "integer")
			intNumber1 = atoi(operand1.getText());
		else
		{
			variableFound = findIntegerVariable(operand1.getText(), intNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}
		// Get second value
		if (operand2.getType() == "integer")
			intNumber2 = atoi(operand2.getText());
		else
		{
			variableFound = findIntegerVariable(operand2.getText(), intNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		intResult = intNumber1 - intNumber2;
		itoa(intResult, tempArray, 10);
		operand1.setText(tempArray);

		return true;
	} // End if integer vs. integer

	else if (((operand1.getType() == "integer") || (operand1.getType() == "integer variable"))
		&& ((operand2.getType() == "real") || (operand2.getType() == "real variable")))
	{
		// Get first value
		if (operand1.getType() == "integer")
			intNumber1 = atoi(operand1.getText());
		else
		{
			variableFound = findIntegerVariable(operand1.getText(), intNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}
		// Get second value
		if (operand2.getType() == "real")
		{
			doubleNumber2 = realToValue(operand2.getText());
		}
		else
		{
			variableFound = findRealVariable(operand2.getText(), doubleNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = double(intNumber1) - doubleNumber2;
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);
		operand1.setType("real");

		return true;
	} // End of integer vs. real

	else if (((operand1.getType() == "real") || (operand1.getType() == "real variable"))
		&& ((operand2.getType() == "integer") || (operand2.getType() == "integer variable")))
	{
		// Get first value
		if (operand1.getType() == "real")
		{
			doubleNumber1 = realToValue(operand1.getText());
		}
		else
		{
			variableFound = findRealVariable(operand1.getText(), doubleNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "integer")
			intNumber2 = atoi(operand2.getText());
		else
		{
			variableFound = findIntegerVariable(operand2.getText(), intNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = doubleNumber1 - double(intNumber2);
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);

		return true;
	}

	else if (((operand1.getType() == "real") || (operand1.getType() == "real variable"))
		&& ((operand2.getType() == "real") || (operand2.getType() == "real variable")))
	{
		// Get first value
		if (operand1.getType() == "real")
		{
			doubleNumber1 = realToValue(operand1.getText());
		}
		else
		{
			variableFound = findRealVariable(operand1.getText(), doubleNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "real")
		{
			doubleNumber2 = realToValue(operand2.getText());
		}
		else
		{
			variableFound = findRealVariable(operand2.getText(), doubleNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = doubleNumber1 - doubleNumber2;
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);

		return true;
	}
	cout << "checking fail\n";
	return false; // Should not happen
} // End of sub


bool add(Token & operand1, Token & operand2)
{
	int intNumber1, intNumber2, intResult;
	double doubleNumber1, doubleNumber2, doubleResult;
	char string1[100];
	string1[0] = '\0';
	char string2[100];
	string2[0] = '\0';
	bool variableFound;
	char tempArray[100];
	string tempString;

	if (((operand1.getType() == "integer") || (operand1.getType() == "integer variable"))
		&& ((operand2.getType() == "integer") || (operand2.getType() == "integer variable")))
	{
		// Get first value
		if (operand1.getType() == "integer")
			intNumber1 = atoi(operand1.getText());
		else
		{
			variableFound = findIntegerVariable(operand1.getText(), intNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}
		// Get second value
		if (operand2.getType() == "integer")
			intNumber2 = atoi(operand2.getText());
		else
		{
			variableFound = findIntegerVariable(operand2.getText(), intNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		intResult = intNumber1 + intNumber2;
		itoa(intResult, tempArray, 10);
		operand1.setText(tempArray);
		operand1.setType("integer");

		return true;
	} // End if integer vs. integer

	else if (((operand1.getType() == "integer") || (operand1.getType() == "integer variable"))
		&& ((operand2.getType() == "real") || (operand2.getType() == "real variable")))
	{
		// Get first value
		if (operand1.getType() == "integer")
			intNumber1 = atoi(operand1.getText());
		else
		{
			variableFound = findIntegerVariable(operand1.getText(), intNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}
		// Get second value
		if (operand2.getType() == "real")
		{
			doubleNumber2 = realToValue(operand2.getText());
		}
		else
		{
			variableFound = findRealVariable(operand2.getText(), doubleNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = double(intNumber1) + doubleNumber2;
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);
		operand1.setType("real");

		return true;
	} // End of integer vs. real

	else if (((operand1.getType() == "real") || (operand1.getType() == "real variable"))
		&& ((operand2.getType() == "integer") || (operand2.getType() == "integer variable")))
	{
		// Get first value
		if (operand1.getType() == "real")
		{
			doubleNumber1 = realToValue(operand1.getText());
		}
		else
		{
			variableFound = findRealVariable(operand1.getText(), doubleNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "integer")
			intNumber2 = atoi(operand2.getText());
		else
		{
			variableFound = findIntegerVariable(operand2.getText(), intNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = doubleNumber1 + double(intNumber2);
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);
		operand1.setType("real");

		return true;
	} // End of real vs. integer

	else if (((operand1.getType() == "real") || (operand1.getType() == "real variable"))
		&& ((operand2.getType() == "real") || (operand2.getType() == "real variable")))
	{
		// Get first value
		if (operand1.getType() == "real")
		{
			doubleNumber1 = realToValue(operand1.getText());
		}
		else
		{
			variableFound = findRealVariable(operand1.getText(), doubleNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "real")
		{
			doubleNumber2 = realToValue(operand2.getText());
		}
		else
		{
			variableFound = findRealVariable(operand2.getText(), doubleNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		doubleResult = doubleNumber1 + doubleNumber2;
		tempString = to_string(doubleResult);
		int i = 0;
		for (; i < tempString.length(); i++)
		{
			tempArray[i] = tempString.at(i);
		}
		tempArray[i] = '\0';
		operand1.setText(tempArray);
		operand1.setType("real");

		return true;
	} // End of real vs. real


	else if (((operand1.getType() == "integer") || (operand1.getType() == "integer variable"))
		&& ((operand2.getType() == "string") || (operand2.getType() == "string variable")))
	{
		// Get first value
		if (operand1.getType() == "integer")
			strcpy(string1,operand1.getText());
		else
		{
			variableFound = findIntegerVariable(operand1.getText(), intNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
			itoa(intNumber1, string1, 10);
		}
		
		// Get second value
		if (operand2.getType() == "string")
		{
			strcpy(string2, operand2.getText());
		}
		else
		{
			variableFound = findStringVariable(operand2.getText(), string2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		strcat(string1, string2);
		operand1.setText(string1);
		operand1.setType("string");
		return true;
	} // End if integer vs. string


	else if (((operand1.getType() == "string") || (operand1.getType() == "string variable"))
		&& ((operand2.getType() == "integer") || (operand2.getType() == "integer variable")))
	{
		// Get first value
		if (operand1.getType() == "string")
		{
			strcpy(string1, operand1.getText());
		}
		else
		{
			variableFound = findStringVariable(operand1.getText(), string1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "integer")
		{
			strcpy(string2, operand2.getText());
		}
		else
		{
			variableFound = findIntegerVariable(operand2.getText(), intNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
			itoa(intNumber2, string2, 10);
		}

		// Calculate and save result
		strcat(string1, string2);
		operand1.setText(string1);
		operand1.setType("string");

		return true;
	} // End if string vs. integer

	
	else if (((operand1.getType() == "string") || (operand1.getType() == "string variable"))
		&& ((operand2.getType() == "string") || (operand2.getType() == "string variable")))
	{
		// Get first value
		if (operand1.getType() == "string")
		{
			strcpy(string1, operand1.getText());
		}
		else
		{
			variableFound = findStringVariable(operand1.getText(), string1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "string")
		{
			strcpy(string2, operand2.getText());
		}
		else
		{
			variableFound = findStringVariable(operand2.getText(), string2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result

		strcat(string1, string2);
		operand1.setText(string1);
		operand1.setType("string");

		return true;
	} // End if string vs. string


	else if (((operand1.getType() == "real") || (operand1.getType() == "real variable"))
		&& ((operand2.getType() == "string") || (operand2.getType() == "string variable")))
	{
		// Get first value
		if (operand1.getType() == "real")
		{
			strcpy(string1, operand1.getText());
		}
		else
		{
			variableFound = findRealVariable(operand1.getText(), doubleNumber1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
			tempString = to_string(doubleNumber1);
			int i = 0;
			for (; i < tempString.length(); i++)
			{
				string1[i] = tempString.at(i);
			}
			string1[i] = '\0';
		}

		// Get second value
		if (operand2.getType() == "string")
		{
			strcpy(string2, operand2.getText());
		}
		else
		{
			variableFound = findStringVariable(operand2.getText(), string2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Calculate and save result
		strcat(string1, string2);
		operand1.setText(string1);
		operand1.setType("string");

		return true;

	} // End if real vs. string


	else if (((operand1.getType() == "string") || (operand1.getType() == "string variable"))
		&& ((operand2.getType() == "real") || (operand2.getType() == "real variable")))
	{
		// Get first value
		if (operand1.getType() == "string")
		{
			strcpy(string1, operand1.getText());
		}
		else
		{
			variableFound = findStringVariable(operand1.getText(), string1);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand1.getText() << " has not been declared yet.\n";
				return false;
			}
		}

		// Get second value
		if (operand2.getType() == "real")
		{
			strcpy(string2, operand2.getText());
		}
		else
		{
			variableFound = findRealVariable(operand2.getText(), doubleNumber2);
			if (!variableFound)
			{
				cout << "Execution Error: Variable " << operand2.getText() << " has not been declared yet.\n";
				return false;
			}
			tempString = to_string(doubleNumber2);
			int i = 0;
			for (; i < tempString.length(); i++)
			{
				string2[i] = tempString.at(i);
			}
			string2[i] = '\0';
		}

		// Calculate and save result
		strcat(string1, string2);
		operand1.setText(string1);
		operand1.setType("string");

		return true;

	} // End if string vs. real


	// Should not happen
	cout << "Final test of failure.\n";
	return false; 

} // End of add

bool parseIfThen(const char* ch) {
	//Divide If Sentence in 2 part, condition and is valid commnad(print, rem, etc)
	char condition[300];
	char command[300];

	//Get condition part
	int i = 0;
	int getLoc = getLocThen(ch); //Delete this
	for (i = 3; i < strlen(ch) - (strlen(ch) - getLoc) - 1; i++) {
		condition[i - 3] = ch[i];
	}
	condition[i - 3] = '\0';

	//Get then command
	for (i = getLocThen(ch) + 5; i < strlen(ch); i++) {
		command[i - getLocThen(ch) - 5] = ch[i];
	}
	command[i - getLocThen(ch) - 5] = '\0';
	
	bool runCommand = parseAndOrNot(condition);
	if (runCommand) {
		if (isAssignmentStatement)
		{
			bool ok = executeAssignmentStatement(command);
			if (!ok)
				cout << "Error in assignment statement.\n";
		}
		//Send command char to is parse.
	}
	return runCommand;
}

bool parseAndOrNot(const char* ch) {
	int LocOr = findLogicalOr(ch);
	int LocAnd = findLogicalAnd(ch);
	
	

	if (LocOr >= 0) {
		int i = 0;
		char oper1[300];
		char oper2[300];

		cout << "testing";
		//First Division
		for (i = 0; i < LocOr - 1; i++) {
			oper1[i] = ch[i];
		}
		oper1[i] = '\0';
		
		for (i = LocOr + 5; i < strlen(ch); i++) {
			oper2[i - LocOr - 5] = ch[i];
		}
		oper2[i - LocOr - 5] = '\0';
		//cout << oper2 << "/";//testing
		return parseAndOrNot(oper1) || parseAndOrNot(oper2);
	
	}
	else if (LocAnd >= 0) {
		int i = 0;
		char oper1[300];
		char oper2[300];

		//First Division
		for (i = 0; i < LocAnd - 1; i++) {
			oper1[i] = ch[i];
		}
		oper1[i] = '\0';
		//cout << oper1 << "/";//testing
		for (i = LocAnd + 6; i < strlen(ch); i++) {
			oper2[i - LocAnd - 6] = ch[i];
		}
		//Check Oper2
		oper2[i - LocAnd - 6] = '\0';
		
		//cout << oper1;//testing
		//cout << oper2;//testing


		//bool useless1 = parseAndOrNot(oper1);
		//cout << useless1;

		//bool useless2 = parseAndOrNot(oper2);
		//cout << useless2;

		return parseAndOrNot(oper1) && parseAndOrNot(oper2);
	}
	else if (tolower(ch[0]) == '.' && tolower(ch[1]) == 'n' && tolower(ch[2]) == 'o' && tolower(ch[3]) == 't' && tolower(ch[4]) == '.' && tolower(ch[5]) == ' ') {
		return !parseComparison(ch + 6);
	}
	//bool useless = parseComparison(ch);
	//cout << useless;
	return parseComparison(ch);

}
//strcmp(value1, value2);
bool parseComparison(const char *ch) {
	int logicalCompareLoc = findComparisonKey(ch);
	int i = 0;
	char value1[300];
	char value2[300];

	for (i = 0; i < strlen(ch) - (strlen(ch) - logicalCompareLoc); i++) {
		value1[i] = ch[i];
	}
	value1[i] = '\0';
	//End of first Division

	//Divide Input in 2 part
	for (i = logicalCompareLoc + 6; i < strlen(ch); i++) {
		value2[i - logicalCompareLoc - 6] = ch[i];
	}
	value2[i - logicalCompareLoc - 6] = '\0';
	//End of second Division
	// strcmp(value1, value2) if negative value 2 is greater than value 1
	if (tolower(ch[logicalCompareLoc + 2]) == 'g' && tolower(ch[logicalCompareLoc + 3]) == 't') {
		if (isVariable(value1)) {// one is variable
			if (isNumber(value2)) {
				if (isIntegerVariable(value1)) {
					int intValue1;
					findIntegerVariable(value1, intValue1);
					return Comparison<double>::isGt(intValue1, atof(value2)); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value1, douValue1);
					return Comparison<double>::isGt(douValue1, atof(value2));// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				int value = strcmp(charValue1, value2);// need to change to use value1 variable data
				if (value <= 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value2)) {// one is variable
			if (isNumber(value1)) {
				if (isIntegerVariable(value1)) {
					int intValue2;
					findIntegerVariable(value2, intValue2);
					return Comparison<double>::isGt(atof(value1), intValue2); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value2, douValue1);
					return Comparison<double>::isGt(atof(value1), douValue1);// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(value1, charValue2);// need to change to use value2 variable data
				if (value <= 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value1) && isVariable(value2)) { //both ara variable
			if (isIntegerVariable(value1)) {
				int intValue1;
				findIntegerVariable(value1, intValue1);
				int intValue2;
				findIntegerVariable(value2, intValue2);
				return Comparison<double>::isGt(intValue1, intValue2); // Need to change value 2 to use variable value
			}
			else if (isRealVariable(value1)) {
				double douValue1;
				findRealVariable(value1, douValue1);
				double douValue2;
				findRealVariable(value2, douValue2);
				return Comparison<double>::isGt(douValue1, douValue2);// Need to change value 2 to use variable value
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(charValue1, charValue2);// need to change to use value2 variable data
				if (value <= 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else {//Both are just values
			if (isNumber(value1)) {
				return Comparison<double>::isGt(atof(value1), atof(value2));
			}
			else {//Modified for each condition
				int value = strcmp(value1, value2);
				if (value <= 0) {
					return false;
				}
				else {
					return true;
				}
			}

		}
	}
	if (tolower(ch[logicalCompareLoc + 2]) == 'g' && tolower(ch[logicalCompareLoc + 3]) == 'e') {
		if (isVariable(value1)) {// one is variable
			if (isNumber(value2)) {
				if (isIntegerVariable(value1)) {
					int intValue1;
					findIntegerVariable(value1, intValue1);
					return Comparison<double>::isGe(intValue1, atof(value2)); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value1, douValue1);
					return Comparison<double>::isGe(douValue1, atof(value2));// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				int value = strcmp(charValue1, value2);// need to change to use value1 variable data
				if (value < 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value2)) {// one is variable
			if (isNumber(value1)) {
				if (isIntegerVariable(value1)) {
					int intValue2;
					findIntegerVariable(value2, intValue2);
					return Comparison<double>::isGe(atof(value1), intValue2); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value2, douValue1);
					return Comparison<double>::isGe(atof(value1), douValue1);// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(value1, charValue2);// need to change to use value2 variable data
				if (value < 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value1) && isVariable(value2)) { //both ara variable
			if (isIntegerVariable(value1)) {
				int intValue1;
				findIntegerVariable(value1, intValue1);
				int intValue2;
				findIntegerVariable(value2, intValue2);
				return Comparison<double>::isGe(intValue1, intValue2); // Need to change value 2 to use variable value
			}
			else if (isRealVariable(value1)) {
				double douValue1;
				findRealVariable(value1, douValue1);
				double douValue2;
				findRealVariable(value2, douValue2);
				return Comparison<double>::isGe(douValue1, douValue2);// Need to change value 2 to use variable value
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(charValue1, charValue2);// need to change to use value2 variable data
				if (value < 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else {//Both are just values
			if (isNumber(value1)) {
				return Comparison<double>::isGe(atof(value1), atof(value2));
			}
			else {//Modified for each condition
				int value = strcmp(value1, value2);
				if (value < 0) {
					return false;
				}
				else {
					return true;
				}
			}

		}

	}

	if (tolower(ch[logicalCompareLoc + 2]) == 'l' && tolower(ch[logicalCompareLoc + 3]) == 't') {
		if (isVariable(value1)) {// one is variable
			if (isNumber(value2)) {
				if (isIntegerVariable(value1)) {
					int intValue1;
					findIntegerVariable(value1, intValue1);
					return Comparison<double>::isLt(intValue1, atof(value2)); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value1, douValue1);
					return Comparison<double>::isLt(douValue1, atof(value2));// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				int value = strcmp(charValue1, value2);// need to change to use value1 variable data
				if (value >= 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value2)) {// one is variable
			if (isNumber(value1)) {
				if (isIntegerVariable(value1)) {
					int intValue2;
					findIntegerVariable(value2, intValue2);
					return Comparison<double>::isLt(atof(value1), intValue2); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value2, douValue1);
					return Comparison<double>::isLt(atof(value1), douValue1);// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(value1, charValue2);// need to change to use value2 variable data
				if (value >= 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value1) && isVariable(value2)) { //both ara variable
			if (isIntegerVariable(value1)) {
				int intValue1;
				findIntegerVariable(value1, intValue1);
				int intValue2;
				findIntegerVariable(value2, intValue2);
				return Comparison<double>::isLt(intValue1, intValue2); // Need to change value 2 to use variable value
			}
			else if (isRealVariable(value1)) {
				double douValue1;
				findRealVariable(value1, douValue1);
				double douValue2;
				findRealVariable(value2, douValue2);
				return Comparison<double>::isLt(douValue1, douValue2);// Need to change value 2 to use variable value
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(charValue1, charValue2);// need to change to use value2 variable data
				if (value >= 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else {//Both are just values
			if (isNumber(value1)) {
				return Comparison<double>::isLt(atof(value1), atof(value2));
			}
			else {//Modified for each condition
				int value = strcmp(value1, value2);
				if (value >= 0) {
					return false;
				}
				else {
					return true;
				}
			}

		}

	}

	if (tolower(ch[logicalCompareLoc + 2]) == 'l' && tolower(ch[logicalCompareLoc + 3]) == 'e') {
		if (isVariable(value1)) {// one is variable
			if (isNumber(value2)) {
				if (isIntegerVariable(value1)) {
					int intValue1;
					findIntegerVariable(value1, intValue1);
					return Comparison<double>::isLe(intValue1, atof(value2)); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value1, douValue1);
					return Comparison<double>::isLe(douValue1, atof(value2));// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				int value = strcmp(charValue1, value2);// need to change to use value1 variable data
				if (value > 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value2)) {// one is variable
			if (isNumber(value1)) {
				if (isIntegerVariable(value1)) {
					int intValue2;
					findIntegerVariable(value2, intValue2);
					return Comparison<double>::isLe(atof(value1), intValue2); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value2, douValue1);
					return Comparison<double>::isLe(atof(value1), douValue1);// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(value1, charValue2);// need to change to use value2 variable data
				if (value > 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value1) && isVariable(value2)) { //both ara variable
			if (isIntegerVariable(value1)) {
				int intValue1;
				findIntegerVariable(value1, intValue1);
				int intValue2;
				findIntegerVariable(value2, intValue2);
				return Comparison<double>::isLe(intValue1, intValue2); // Need to change value 2 to use variable value
			}
			else if (isRealVariable(value1)) {
				double douValue1;
				findRealVariable(value1, douValue1);
				double douValue2;
				findRealVariable(value2, douValue2);
				return Comparison<double>::isLe(douValue1, douValue2);// Need to change value 2 to use variable value
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(charValue1, charValue2);// need to change to use value2 variable data
				if (value > 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else {//Both are just values
			if (isNumber(value1)) {
				return Comparison<double>::isLt(atof(value1), atof(value2));
			}
			else {//Modified for each condition
				int value = strcmp(value1, value2);
				if (value > 0) {
					return false;
				}
				else {
					return true;
				}
			}

		}
	}

	if (tolower(ch[logicalCompareLoc + 2]) == 'e' && tolower(ch[logicalCompareLoc + 3]) == 'q') {
		if (isVariable(value1)) {// one is variable
			if (isNumber(value2)) {
				if (isIntegerVariable(value1)) {
					int intValue1;
					findIntegerVariable(value1, intValue1);
					return Comparison<double>::isEq(intValue1, atof(value2)); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value1, douValue1);
					return Comparison<double>::isEq(douValue1, atof(value2));// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				int value = strcmp(charValue1, value2);// need to change to use value1 variable data
				if (value != 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value2)) {// one is variable
			if (isNumber(value1)) {
				if (isIntegerVariable(value1)) {
					int intValue2;
					findIntegerVariable(value2, intValue2);
					return Comparison<double>::isEq(atof(value1), intValue2); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value2, douValue1);
					return Comparison<double>::isEq(atof(value1), douValue1);// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(value1, charValue2);// need to change to use value2 variable data
				if (value != 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value1) && isVariable(value2)) { //both ara variable
			if (isIntegerVariable(value1)) {
				int intValue1;
				findIntegerVariable(value1, intValue1);
				int intValue2;
				findIntegerVariable(value2, intValue2);
				return Comparison<double>::isEq(intValue1, intValue2); // Need to change value 2 to use variable value
			}
			else if (isRealVariable(value1)) {
				double douValue1;
				findRealVariable(value1, douValue1);
				double douValue2;
				findRealVariable(value2, douValue2);
				return Comparison<double>::isEq(douValue1, douValue2);// Need to change value 2 to use variable value
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(charValue1, charValue2);// need to change to use value2 variable data
				if (value != 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else {//Both are just values
			if (isNumber(value1)) {
				return Comparison<double>::isEq(atof(value1), atof(value2));
			}
			else {//Modified for each condition
				int value = strcmp(value1, value2);
				if (value != 0) {
					return false;
				}
				else {
					return true;
				}
			}

		}
	}

	if (tolower(ch[logicalCompareLoc + 2]) == 'n' && tolower(ch[logicalCompareLoc + 3]) == 'e') {
		if (isVariable(value1)) {// one is variable
			if (isNumber(value2)) {
				if (isIntegerVariable(value1)) {
					int intValue1;
					findIntegerVariable(value1, intValue1);
					return Comparison<double>::isNe(intValue1, atof(value2)); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value1, douValue1);
					return Comparison<double>::isNe(douValue1, atof(value2));// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				int value = strcmp(charValue1, value2);// need to change to use value1 variable data
				if (value == 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value2)) {// one is variable
			if (isNumber(value1)) {
				if (isIntegerVariable(value1)) {
					int intValue2;
					findIntegerVariable(value2, intValue2);
					return Comparison<double>::isNe(atof(value1), intValue2); // Need to change value 1 to use variable value
				}
				else {
					double douValue1;
					findRealVariable(value2, douValue1);
					return Comparison<double>::isNe(atof(value1), douValue1);// Need to change value 1 to use variable value
				}
			}
			else {//Modified for each condition
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(value1, charValue2);// need to change to use value2 variable data
				if (value == 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else if (isVariable(value1) && isVariable(value2)) { //both ara variable
			if (isIntegerVariable(value1)) {
				int intValue1;
				findIntegerVariable(value1, intValue1);
				int intValue2;
				findIntegerVariable(value2, intValue2);
				return Comparison<double>::isNe(intValue1, intValue2); // Need to change value 2 to use variable value
			}
			else if (isRealVariable(value1)) {
				double douValue1;
				findRealVariable(value1, douValue1);
				double douValue2;
				findRealVariable(value2, douValue2);
				return Comparison<double>::isNe(douValue1, douValue2);// Need to change value 2 to use variable value
			}
			else {//Modified for each condition
				char charValue1[200];
				findStringVariable(value1, charValue1);
				char charValue2[200];
				findStringVariable(value2, charValue2);
				int value = strcmp(charValue1, charValue2);// need to change to use value2 variable data
				if (value == 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
		else {//Both are just values
			if (isNumber(value1)) {
				return Comparison<double>::isNe(atof(value1), atof(value2));
			}
			else {//Modified for each condition
				int value = strcmp(value1, value2);
				if (value == 0) {
					return false;
				}
				else {
					return true;
				}
			}

		}
	}
	return false;
}// End of add

