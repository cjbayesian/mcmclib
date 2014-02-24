//#########################################################
//
// Generates MCMC samples using an adaptive
// Metropolis-Hastings Algorithm
//
// Author: COREY CHIVERS, 2012
// McGill University 
// Deptartment of Biology
//
// Updated July, 2012
//
// Uses standard calls to a user defined log-likelihood
// and prior functions in n-dimensional parameter space.  
// Undergoes adaptive phases (adjusting the proposal density)
// for efficiency of convergence.
//
//######################################################### 

#ifndef _METRO_HASTINGS_H
#define _METRO_HASTINGS_H

#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<cstdlib>
#include<time.h>


#include"modDistributions.h"
#include"vbc_genlib.h"
#include"vbc_vector.h"
#include"mvrnorm.h"

using namespace std;
using namespace vbc_lib;
using namespace modDistributions;
using namespace mvrnorm;

namespace mcmcMD
{
	void STDCALL run_mcmc(_vbc_vec<float>, 
      _vbc_vec<float>, 
      void (STDCALL *)(_vbc_vec<float>* ,float*,int ), 
      float (STDCALL *)(_vbc_vec<float> ,int), 
      bool (STDCALL *)(_vbc_vec<float>), 
      int, 
      int, 
      int,
      const char*,
      bool header=1,
      bool verbose=0,
      bool resample=0,
      int adapt_l=100,
      int adapt_n=10);
	
   void mh_base(_vbc_vec<float> *, 
      _vbc_vec<float>, 
      int, 
      void (STDCALL *)(_vbc_vec<float>*, float*,int), 
      float (STDCALL *)(_vbc_vec<float>,int), 
      bool (STDCALL *)(_vbc_vec<float>),
      float*,
      bool);

	void var_track(_vbc_vec<float> *, 
      _vbc_vec<float> *, 
      _vbc_vec<float> *, 
      _vbc_vec<float> *, 
      _vbc_vec<float> *, 
      int, 
      int);

   _vbc_vec<float> diag(_vbc_vec<float>);

};

#endif
