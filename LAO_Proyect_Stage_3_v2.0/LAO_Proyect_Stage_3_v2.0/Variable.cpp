#include "Variable.h"

// Constructors and destructor
Variable::Variable()
{
	text[0] = '\0';
	type = "none";
	intValue = 0;
	realValue = 0.0;
	stringValue[0] = '\0';

} // End of default constructor


Variable::Variable(const char* ch, int value)
{
	setText(ch);
	setType();
	setIntValue(value);
	// default values not to be used:
	setRealValue(0.0);
	stringValue[0] = '\0';
} // End of constructor with integer parameter

Variable::Variable(const char* ch, double value)
{
	setText(ch);
	setType();
	setRealValue(value);
	// default values not to be used:
	setIntValue(0);
	stringValue[0] = '\0';
} // End of constructor with double parameter

Variable::Variable(const char* ch, const char* value)
{
	setText(ch);
	setType();
	setStringValue(value);
	// default values not to be used:
	setIntValue(0);
	setRealValue(0.0);
} // End of constructor with char array parameter

Variable::Variable(const Variable & aVariable)
{
	setText(aVariable.text);
	setType();
	setIntValue(aVariable.intValue);
	setRealValue(aVariable.realValue);
	setStringValue(aVariable.stringValue);
} //  End of copy constructor


Variable::~Variable()
{
	// No resources to liberate.
} // End of destructor

// Get & set methods
void Variable::setText(const char* ch)
{
	if (strlen(ch) == 0)
		text[0] = '\0';
	else
	{
		int i = 0;
		for (; i < strlen(ch); i++)
		{
			text[i] = tolower(ch[i]);
		}
		text[i] = '\0';
	}
} // End of setText


void Variable::setType()
{
	if ((tolower(text[0]) >= 'a') && (tolower(text[0]) <= 'f'))
		type = "integer";
	else if ((tolower(text[0]) >= 'g') && (tolower(text[0]) <= 'n'))
		type = "real";
	else
		type = "string";
} // End of setType


void Variable::setIntValue(int value)
{
	intValue = value;
} // End of setIntValue


void Variable::setRealValue(double value)
{
	realValue = value;
} // End of setRealValue


void Variable::setStringValue(const char* ch)
{
	if (strlen(ch) == 0)
		stringValue[0] = '\0';
	else
	{
		int i = 0;
		for (; i < strlen(ch); i++)
		{
			stringValue[i] = tolower(ch[i]);
		}
		stringValue[i] = '\0';
	}
} // End of setStringValue


char* const Variable::getText()
{
	return this->text;
} // End of getText


string const Variable::getType()
{
	return this->type;
} // End of getType


int const Variable::getIntValue()
{
	return this->intValue;
} // End of getIntValue


double const Variable::getRealValue()
{
	return this->realValue;
} // End of getRealValue


char* const Variable::getStringValue()
{
	return this->stringValue;
} // End of getStringValue


char Variable::copyStringValue(int element)
{
	return (stringValue[element]);
} // End of copyStringValue