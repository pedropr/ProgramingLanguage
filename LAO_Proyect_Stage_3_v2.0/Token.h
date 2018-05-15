#pragma once
# include <iostream>
# include <string>
using namespace std;

class Token
{
private:
	char text[100];
	string type;

public:
	// Constructors and destructor
	Token();
	Token(const char* ch, string t);
	~Token();

	// Methods
	char getTextElement(int i);
	char* const getText();
	string getType();
	void setText(const char* ch);
	void setType(const string t);
};

