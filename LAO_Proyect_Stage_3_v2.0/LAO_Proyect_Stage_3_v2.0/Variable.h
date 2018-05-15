#pragma once
# include <iostream>
# include <string>
using namespace std;

class Variable
{
private:
	char text[100];
	string type;
	int intValue;
	double realValue;
	char stringValue[100];

public:
	// Constructors and destructor
	Variable();
	Variable(const char* ch, int value);
	Variable(const char* ch, double value);
	Variable(const char* ch, const char* value);
	Variable(const Variable & aVariable);
	~Variable();

	// Get & set methods
	void setText(const char* ch);
	void setType();
	void setIntValue(int value);
	void setRealValue(double value);
	void setStringValue(const char* ch);
	char* const getText();
	string const getType();
	int const getIntValue();
	double const getRealValue();
	char* const getStringValue();
	char copyStringValue(int element);
};
