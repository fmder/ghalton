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

#include "Halton.hpp"
#include "Constants.hpp"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <sstream>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif

/*!
 * Generalized Halton sequencer constructor.
 * \param inDim The dimensionality of the generator, srand is initialized
 * with time(NULL).
 */
GeneralizedHalton::GeneralizedHalton(unsigned long inDim) : mDim(inDim) {
	seed((PyObject*)NULL);
}

/*!
 * Generalized Halton sequencer constructor.
 * \param inDim The dimensionality of the generator.
 * \param inSeed A long integer from which to seed srand.
 */
GeneralizedHalton::GeneralizedHalton(unsigned long inDim, unsigned long inSeed) : mDim(inDim) {
	seed(inSeed);
}

/*!
 * Generalized Halton sequencer constructor.
 * \param inScrambling A sequence of randomized sequences of integers
 * representing the generalized Halton scramblings. The dimension of the
 * sequence is determined by the number of subsequences the permutation
 * contains.
 */
GeneralizedHalton::GeneralizedHalton(PyObject* inScrambling) {
	mDim = PySequence_Size(inScrambling);
	seed(inScrambling);
}

/*!
 * Function to seed the generalized Halton sequencer, this function calls 
 * reset then set the configuration according to the inScrambling argument.
 * \param inSeed A long integer from which to seed srand.
 */
void GeneralizedHalton::seed(unsigned long inSeed){
	reset();
	
	srand(inSeed);
	mPermutations = std::vector<std::vector<unsigned long> >(mDim);
	for(unsigned long i = 0; i < mDim; ++i){
		mPermutations.push_back(std::vector<unsigned long>());
		for(unsigned long j = 0; j < PRIMES[i]; ++j){
			mPermutations[i].push_back(j);
		}
		std::random_shuffle(mPermutations[i].begin() + 1, mPermutations[i].end());
	}
}

/*!
 * Function to seed the generalized Halton sequencer, this function calls 
 * reset then set the configuration according to the inScrambling argument.
 * \param inScrambling A randomized sequence of integers representing the 
 * generalized Halton scrambling, if not provided, srand is initialized with
 * time(NULL).
 */
void GeneralizedHalton::seed(PyObject* inScrambling /*= NULL*/){
	reset();
	
	if(inScrambling){
		PyObject* lNumber = NULL;
		PyObject* lDSeq = NULL;
        mPermutations = std::vector<std::vector<unsigned long> >(0);

		for(unsigned long i = 0; i < mDim; ++i){
			mPermutations.push_back(std::vector<unsigned long>(PRIMES[i]));
			lDSeq = PySequence_GetItem(inScrambling, i);
			
			if(PySequence_Size(lDSeq) != PRIMES[i]){
				std::ostringstream lMessage;
				lMessage << "Wrong scrambling size, for dimension " << i+1 << " the scrambling size must be ";
				lMessage << PRIMES[i] << ". ";
	            lMessage << "Current size is " << PySequence_Size(lDSeq) << ".";
				throw(SizeError(lMessage.str()));
			}
			
			
			for(unsigned long j = 0; j < PRIMES[i]; ++j){
                lNumber = PySequence_GetItem(lDSeq, j);
#ifdef PY3K
                mPermutations[i][j] = PyLong_AsLong(lNumber);
#else
                mPermutations[i][j] = PyInt_AsLong(lNumber);
#endif
                Py_DECREF(lNumber);
                lNumber = NULL;
			}
			Py_DECREF(lDSeq);
			lDSeq = NULL;
		}
	}else{
		srand(time(NULL));
		mPermutations = std::vector<std::vector<unsigned long> >(mDim);
		for(unsigned long i = 0; i < mDim; ++i){
			mPermutations.push_back(std::vector<unsigned long>());
			for(unsigned long j = 0; j < PRIMES[i]; ++j){
				mPermutations[i].push_back(j);
			}
			std::random_shuffle(mPermutations[i].begin() + 1, mPermutations[i].end());
		}
	}
}

/*!
 * Reset the generator, the next point to be drawn will be the same as the 
 * first one.
 */
void GeneralizedHalton::reset() {
	mBases.clear();
	mBases.insert(mBases.begin(), &PRIMES[0], &PRIMES[0] + mDim);
	
	mCounters.resize(mDim);
	for(unsigned long i = 0; i < mDim; ++i) mCounters[i].clear();
	
	mCount = 0;
}

/*!
 * Retreive the next point(s) from the generator. Each call to this function
 * will return inCount points, in a list of lists.
 * \param inCount Tells how many points to return at a time.
 */
PyObject* GeneralizedHalton::get(unsigned long inCount /*= 1*/){
	PyObject* lMatrix = PyList_New(inCount);
	for(unsigned long i = 0; i < inCount; ++i){
		PyObject* lArray = PyList_New(mDim);
		for(unsigned long j = 0; j < mDim; ++j){
			// Increment the counter values according to their basis.
			unsigned int lIndex = 0;
			while((lIndex<mCounters[j].size()) && (mCounters[j][lIndex]==(mBases[j]-1))) {
				mCounters[j][lIndex] = 0;
				++lIndex;
			}
			if(lIndex==mCounters[j].size()) mCounters[j].push_back(1);
			else ++mCounters[j][lIndex];
			
			// Unscramble the counter value and convert it from its prime basis.
			const unsigned int lCountSizeI = mCounters[j].size();
			unsigned long lBasesPow = mBases[j];
			double lValue = mPermutations[j][mCounters[j][lCountSizeI-1]];
			for(unsigned int k = lCountSizeI-1; k >= 1; --k) {
				lValue += (mPermutations[j][mCounters[j][k-1]] * lBasesPow);
				lBasesPow *= mBases[j];
			}
			
			PyList_SetItem(lArray, j, PyFloat_FromDouble(lValue / lBasesPow));
		}
		PyList_SetItem(lMatrix, i, lArray);
	}
	return lMatrix;
}

/*!
 * Halton sequencer constructor, same as the generalized sequencer using 
 * the scrambling [[0, 1], [0, 1, 2], [0, 1, 2, ...], ...]
 * \param inDim The dimensionality of the generator
 */
Halton::Halton(unsigned long inDim){
	mDim = inDim;
	PyObject* lScrambling = PyList_New(inDim);
	unsigned long lIndex = 0;
	for(unsigned long i = 0; i < inDim; ++i){
		PyObject* lDScr = PyList_New(PRIMES[i]);
		for(unsigned long j = 0; j < PRIMES[i]; ++j){
#ifdef PY3K
			PyList_SetItem(lDScr, j, PyLong_FromLong(j));
#else
			PyList_SetItem(lDScr, j, PyInt_FromLong(j));
#endif
		}
		PyList_SetItem(lScrambling, i, lDScr);
	}
	GeneralizedHalton::seed(lScrambling);
}
