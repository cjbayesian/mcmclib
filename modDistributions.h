#ifndef MODDISTRIBUTIONS_H
#define MODDISTRIBUTIONS_H
//#include <UDTprjCLib.h>
#include"IncGamma.h"
using namespace std;
using namespace vbc_lib;


namespace modDistributions
{




};
namespace _pmodDistributions
{


};
namespace modDistributions
{

	double Normal(double mean,double std);
	double ChiSquareProb(int v, double X2);
	double n_choose_k(int n, int k);
	double n_choose_k(int n, int k, double p,int *count);
	double binomial(int n, int k, double p);
	double cum_binomial(int n, int k, double p);
	short sample_binomial(int n, double p);
	double cum_neg_binomial(int n, int k, double p);

	//assumes v and w are integers.
	double Rnd_beta(int v, int w);
	double beta_pdf(int v, int w,double x);
	double ln_beta_pdf(double v, double w, double x);
	double beta_pdf(double v, double w,double x);
	short poisson(double b_d);
	double poisson_pdf(double g, int N);
	double ln_poisson_pdf(double g,int N);
	template <class T>
	void histogram(_vbc_vec<T>& d, _vbc_vec<int> *n,  double bin_size)
	{
		for(int i=1;i<=d.UBound();i++)
		{
			int j=1;

			for(;;)
			{
				if(d(i)<j*bin_size)
				{
					if((*n).UBound()>=j)
						(*n)(j)+=1;
					else
						(*n)((*n).UBound())+=1;

					break;
				}
				j++;
			}
		}
	}
};
namespace _pmodDistributions
{


};

#endif;
