#include"vbc_genlib.h"
#include<float.h>
namespace vbc_lib
{
	_enumPtr TPtrNull;
	long Seed=1;
	void Randomize(long i)
	{
		Seed=i;
		//the first Rnds seem to be fixed.
		//therefore, let's waste a few Rnds
		for(int j=1;j<30;j++)
		{
			Rnd();
		}


	}

	double Rnd()
	{
		long im1=2147483563, im2=2147483399, imm1=im1-1, \
			 ia1=40014,  ia2=40692, iq1=53668, iq2=52774, ir1=12211, ir2=3791, \
			 ntab=31, ndiv=1+imm1/ntab;
		double am=1.0/im1;
		double eps=FLT_EPSILON, rnmx=1.0-eps;

		long j, k;
		static long iv[32], iy=0, idum2=123456789;

		if(Seed <= 0)
		{
		   Seed=Max(-Seed,long(1));
		   
			idum2=Seed;
		   for(short j=ntab+8;j>= 0;j--)
		   {
			   k=Seed/iq1;
			  Seed=ia1*(Seed-k*iq1)-k*ir1;
			  if(Seed < 0)
				  Seed=Seed+im1;
			  if(j <= ntab)
				  iv[j]=Seed;
		   }

		   iy=iv[0];
		}
		k=Seed/iq1;
		Seed=ia1*(Seed-k*iq1)-k*ir1;
		if(Seed < 0)
			Seed+=im1;

		k=idum2/iq2;

		idum2=ia2*(idum2-k*iq2)-k*ir2;

		if(idum2 < 0)
			idum2+=im2;
		
		j=iy/ndiv;
		iy=iv[j]-idum2;
		iv[j]=Seed;
		if(iy < 1)
			iy+=imm1;
		
		return Min(am*iy, rnmx);

	}

}
