# include "Token.h"
# include <string>


// Constructors and destructor
Token::Token()
{
	text[0] = '\0';
	type = "none";
}


Token::Token(const char* ch, string t)
{
	setText(ch);
	type = t;
}

Token::~Token()
{	// No resources to liberate.
} // End of destructor


// Methods
char Token::getTextElement(int i)
{
	return (text[i]);
} // End of getTextElement


char* const Token::getText()
{
	return text;
} // End of getText


string Token::getType()
{
	return type;
}

void Token::setText(const char* ch)
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


void Token::setType(const string t)
{
	type = t;
} // End of setType

