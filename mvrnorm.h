//#########################################################
//
// Generates MULTIVARIATE NORMAL DEVIATES
//
// Author: COREY CHIVERS, 2012
// Modified from: John Burkardt 
// (see licensing details inside function defs)
//
// McGill University 
// Deptartment of Biology
//
// Updated July, 2012
//
//
//######################################################### 

#ifndef _MVRNORM_H
#define _MVRNORM_H

# include <cstdlib>
# include <cmath>
# include <ctime>
# include <iostream>
#include"vbc_genlib.h"
#include"vbc_vector.h"

#define MATHLIB_STANDALONE 1
#include <Rmath.h>

using namespace std;
using namespace vbc_lib;

namespace mvrnorm
{
_vbc_vec<float> multinormal_sample ( int m, _vbc_vec<float> , _vbc_vec<float> mu);
_vbc_vec<float> cholseky_fact ( int n, _vbc_vec<float> a );
bool is_pos_def (int n, _vbc_vec<float> a);
};
#endif
