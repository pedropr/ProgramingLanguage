#pragma once

template <class value>
class Comparison {
public:
	static bool isGt(value a, value b);
	static bool isLt(value a, value b);
	static bool isGe(value a, value b);
	static bool isLe(value a, value b);
	static bool isEq(value a, value b);
	static bool isNe(value a, value b);
};

template <class value>
bool Comparison <value> ::isGt(value a, value b) {
	return a > b;
}

template <class value>
bool Comparison <value> ::isGe(value a, value b) {
	return a >= b;
}

template <class value>
bool Comparison <value> ::isLt(value a, value b) {
	return a < b;
}

template <class value>
bool Comparison <value> ::isLe(value a, value b) {
	return a <= b;
}

template <class value>
bool Comparison <value> ::isEq(value a, value b) {
	return a == b;
}

template <class value>
bool Comparison <value> ::isNe(value a, value b) {
	return a != b;
}
