/*
 * Copying and distribution of this file, with or without modification,
 * are permitted in any medium without royalty provided the copyright
 * notice and this notice are preserved.  This file is offered as-is,
 * without any warranty.
 *
 * author: Francois-Michel De Rainville
 * version: 0.2.0
 * date: 23/03/2011
 */
 
#include "Python.h"

#include <string>
#include <vector>

class SizeError {
public:
	SizeError(std::string inMessage) : mMessage(inMessage){}
	virtual const char* what() const throw(){return mMessage.c_str();}
private:
	std::string mMessage;
};

class GeneralizedHalton {
public:
	GeneralizedHalton(unsigned long inDim);
	GeneralizedHalton(unsigned long inDim, unsigned long inSeed);
	GeneralizedHalton(PyObject* inScrambling);
	virtual ~GeneralizedHalton(){}
	
	PyObject*	get(unsigned long inCount = 1);
	void		reset();
	void		seed(unsigned long inSeed);
	void		seed(PyObject* inScrambling = NULL);
	
protected:
	GeneralizedHalton(){}
	
	std::vector<unsigned int>					mBases;
	unsigned long								mCount;
	unsigned long								mDim;
	std::vector<std::vector<unsigned int> >		mCounters;
	std::vector<std::vector<unsigned long> >	mPermutations;
	
};

class Halton : public GeneralizedHalton {
public:
	Halton(unsigned long inDim);
	
private:
	void		seed(PyObject* inScrambling = NULL){}
};
