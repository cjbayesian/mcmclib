#include "mvrnorm.h"

#define MATHLIB_STANDALONE 1
#include <Rmath.h>

#ifndef MVRNORM_H
#define MVRNORM_H
#endif;
namespace mvrnorm
{
//****************************************************************************80
_vbc_vec<float> multinormal_sample ( int m, _vbc_vec<float> a, _vbc_vec<float> mu )

//****************************************************************************80
//
//  Purpose:
//
//    MULTINORMAL_SAMPLE samples a multivariate normal distribution.
//
//  Discussion:
//
//    The multivariate normal distribution for the M dimensional vector X
//    has the form:
//
//      pdf(X) = (2*pi*det(A))**(-M/2) * exp(-0.5*(X-MU)'*inverse(A)*(X-MU))
//
//    where MU is the mean vector, and A is a positive definite symmetric
//    matrix called the variance-covariance matrix.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    16 July 2012
//
//  Author:
//
//    Corey Chivers modified from original by John Burkardt
//
//  Parameters:
//
//    Input, int m, the dimension of the space.
//    Input, float A[M*M], the variance-covariance 
//    matrix.  A must be positive definite symmetric.
//
{
  _vbc_vec<float> r;
  _vbc_vec<float> x(1,m);
  _vbc_vec<float> y(1,m);
//
//  Compute the upper triangular Cholesky factor R of the variance-covariance
//  matrix.
//
  r = cholseky_fact ( m, a );

//
//  Y = M vector of samples of the 1D normal distribution with mean 0
//  and variance 1.  
//

   for(int j=1;j<=m;j++)
      y(j) = rnorm (0 , 1);

//
//  Compute X = MU + R' * Y.
//

    for (int i = 1; i <= m; i++ )
    {
      x(i) = mu(i);
      for (int k = 1; k <= m; k++ )
      {
        x(i) = x(i) + r(i,k) * y(k);
      }
    }     

  return x;
}
//****************************************************************************80


//****************************************************************************80

_vbc_vec<float> cholseky_fact ( int n, _vbc_vec<float> a )

//****************************************************************************80
//
//    The positive definite symmetric matrix A has a Cholesky factorization
//    of the form:
//
//      A = R' * R
//
//    where R is an upper triangular matrix with positive elements on
//    its diagonal.  
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    16 July 2012
//
//  Author:
//
//    Original FORTRAN77 version by Dongarra, Bunch, Moler, Stewart.
//    C++ version by John Burkardt.
//    Modified by Corey Chivers.
//
//  Reference:
//
//    Jack Dongarra, Jim Bunch, Cleve Moler, Pete Stewart,
//    LINPACK User's Guide,
//    SIAM, 1979,
//    ISBN13: 978-0-898711-72-1,
//    LC: QA214.L56.
//
{
  _vbc_vec<float> b;
  b=a;
  float s;

  for (int j = 1; j <= n; j++ )
  {
    for (int k = 1; k < j; k++ )
    {
      for (int i = 1; i < k; i++ )
      {
        b(j,k) = b(j,k) - b(k,i) * b(j,i);
      }
      b(j,k) = b(j,k) / b(k,k);
    }

    s = b(j,j);
    for (int i = 1; i < j; i++ )
    {
      s = s - b(j,i) * b(j,i);
    }

    if ( s <= 0.0 )
    {
       cout << "\n";
       cout << "MULTINORMAL_SAMPLE - Fatal error!\n";
       cout << "  The variance-covariance matrix is not positive definite symmetric.\n";
       cout << "s = "<<s<<"\tj = "<<j<<"\n";
       exit ( 1 );
    }

    b(j,j) = sqrt ( s );
  }

  return b;
}
//****************************************************************************80



//****************************************************************************80
bool is_pos_def (int n, _vbc_vec<float> a)

//****************************************************************************80
//
//   Check whether the matrix positive definite symmetric
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    Aug 2012
//
//  Author:
//
//   Corey Chivers.
//
{
  _vbc_vec<float> b;
  b=a;
  float s;

  for (int j = 1; j <= n; j++ )
  {
    for (int k = 1; k < j; k++ )
    {
      for (int i = 1; i < k; i++ )
      {
        b(j,k) = b(j,k) - b(k,i) * b(j,i);
      }
      b(j,k) = b(j,k) / b(k,k);
    }

    s = b(j,j);
    for (int i = 1; i < j; i++ )
    {
      s = s - b(j,i) * b(j,i);
    }

    if ( s <= 0.0 )
    {
       return FALSE;
    }

    b(j,j) = sqrt ( s );
  }

  return TRUE;
}

};
