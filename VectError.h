#ifndef _VECT_ERROR
#define _VECT_ERROR
#include <iostream>

#define DEBUG

class VectError {
public:
	VectError() {}
	virtual void ErrMsg() const {
		std::cerr << "Error with Vect object.\n";
	}
	void Continue() const {
#ifdef DEBUG
		std::cerr << "Debug: program is being continued.\n";
#else
		throw;
#endif
	}
};

class VectRangeErr : public VectError {
public:
	VectRangeErr(int _min, int _max, int _actual)
		: min(_min), max(_max), actual(_actual) {
	}
	void ErrMsg() const {
		std::cerr << "Error of index: ";
		std::cerr << "possible range: " << min << " - " << max << ", ";
		std::cerr << "actual index: " << actual << std::endl;
		Continue();
	}
private:
	int min, max, actual;
};

class VectPopErr : public VectError {
public:
	void ErrMsg() const {
		std::cerr << "Error of pop\n";
		Continue();
	}
};

#endif /* _VECT_ERROR */