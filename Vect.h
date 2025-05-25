#ifndef __VECT__
#define __VECT__
#include <iostream>
#include <string>
#include "VectError.h"

template<class T> class Vect {
public:
	explicit Vect() : first(0), last(0) {}
	explicit Vect(size_t _n, const T& _v = T()) {
		Allocate(_n);
		for (size_t i = 0; i < _n; ++i)
			*(first + i) = _v;
	}
	Vect(const Vect& other) {
		size_t n = other.size();
		Allocate(n);
		for (size_t i = 0; i < n; ++i)
			*(first + i) = *(other.first + i);
		markName = "Copy of " + other.markName;
#ifdef DEBUG
		std::cout << "Copy constructor: " << markName << std::endl;
#endif
	}
	Vect& operator=(const Vect& other) {
		if (this == &other) return *this;
		Destroy();
		size_t n = other.size();
		Allocate(n);
		for (size_t i = 0; i < n; ++i)
			*(first + i) = *(other.first + i);
		return *this;
	}
	~Vect() {
#ifdef DEBUG
		std::cout << "Destructor of " << markName << std::endl;
#endif
		Destroy();
		first = 0; last = 0;
	}

	void mark(std::string name) { markName = name; }
	std::string mark() const { return markName; }

	size_t size() const {
		if (first >= last) return 0;
		return last - first;
	}
	T* begin() const { return first; }
	T* end() const { return last; }
	T& operator[](size_t i) {
		if (i >= size())
			throw VectRangeErr(0, size() - 1, i);
		return *(first + i);
	}
	void insert(T* _P, const T& _x) {
		size_t n = size() + 1;
		T* new_first = new T[n];
		T* new_last = new_first + n;

		size_t offset = _P - first;
		for (size_t i = 0; i < offset; ++i)
			new_first[i] = first[i];
		new_first[offset] = _x;
		for (size_t i = offset; i < n - 1; ++i)
			new_first[i + 1] = first[i];

		Destroy();
		first = new_first;
		last = new_last;
	}
	void push_back(const T& _x) {
		if (!size()) {
			Allocate(1);
			*first = _x;
		}
		else insert(end(), _x);
	}
	void pop_back() {
		if (last == first)
			throw VectPopErr();
		--last;
		last->~T();
	}
	void show() const {
		std::cout << "\n===== Contents of " << markName << " =====" << std::endl;
		for (T* p = first; p != last; ++p)
			std::cout << *p << " ";
		std::cout << std::endl;
	}

protected:
	void Allocate(size_t _n) {
		first = new T[_n];
		last = first + _n;
	}
	void Destroy() {
		for (T* p = first; p != last; ++p)
			p->~T();
		delete[] first;
		first = nullptr;
		last = nullptr;
	}

	T* first;
	T* last;
	std::string markName;
};

#endif /* __VECT__ */