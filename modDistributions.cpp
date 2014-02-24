
#include "modDistributions.h"


namespace modDistributions
{

};
namespace _pmodDistributions
{

};
namespace modDistributions
{



	double Normal(double mean,double std)
	{
		double _Normal = 0;
		double x = 0, y = 0, r = 0;

 		do
		{ 
			x = Rnd();
			y = Rnd();
			r = pow(( x * x + y * y), 0.5);
		} while( r > 1); 
		
		if( Rnd() < 0.5)
		{ 
			_Normal = pow((-log(1-r * r)), 0.5) * x / r /(pow(0.5, 0.5)) * std + mean;
		}
		else
		{ 
			_Normal =-pow((-log(1-r * r)), 0.5) * x / r /(pow(0.5, 0.5)) * std + mean;
		} 
		return _Normal;  
	}
	double ChiSquareProb(int v, double X2)
	{
		using namespace distrib;
		return gammq(v/2.0,X2/2.0);
	}
	double n_choose_k(int n, int k)
	{
		double f=1;
		int max,count=0;
		if(k>n-k)
		{
			max=k+1;
		}
		else
		{
			max=n-k+1;
		}
		for(int i=max;i<=n;i++)
		{
			count++;
			f*=1.0*i/count;
		}
		return f;
	}
	double n_choose_k(int n, int k, double p,int *count)
	{
		double f=1;
		int max;
		*count=0;
		if(k>n-k)
		{
			max=k+1;
		}
		else
		{
			max=n-k+1;
		}
		for(int i=max;i<=n;i++)
		{
			(*count)++;
			f*=1.0*i/(*count)*p;
		}
		return f;
	}
	double binomial(int n, int k, double p)
	{
		int count=0;
		//pass the smaller of the 2
		if(p<.5)
		{
			return n_choose_k(n,k,p,&count)*pow(p,k-count)*pow(1-p,n-k);
		}
		else
		{
			return n_choose_k(n,k,1-p,&count)*pow(p,k)*pow(1-p,n-k-count);
		}
	}


	double cum_binomial(int n, int k, double p)
	{
		//must sum
		//returns left side of distribution, inclusive of k
		//sum(i=0-k) of (n choose i)p^i q^n-i
		int min; 
		double param,compParam;
		int dir=1;
		double f;
		double sum;

		
		if(k==n) return 1.0;



		//because distribution is symmetric, need only decide which direction we are moving
		//p^0q^n or p^nq^0
		if(k<n-k)
		{
			//sum from 0-k
			min=k;
			param=p;
			compParam=(1-p);
		}
		else
		{
			//sum from k+1 to n, same as summing from 0 to n-(k+1), moving backwards
			
			min=n-(k+1);
			param=(1-p);
			compParam=p;
			dir=-1;
		}

		//initialize: when i=0;
		f=pow(compParam,n);
		sum=f;
		
		for(int i=1; i<=min;i++)
		{
			f*=param/compParam*(n-i+1)/i;
			sum+=f;
		}
		if(dir==-1)
		{
			return 1-sum;
		}
		else
		{
			return sum;
		}
	}

	short sample_binomial(int n, double p)
	{
		//must sum
		//returns left side of distribution, inclusive of k
		//sum(i=0-k) of (n choose i)p^i q^n-i
		if(p*n>5 && (1-p)* n>5)
		{
			return int(.5+Normal(p* n,pow(p*(1-p)* n,.5)));

		}

		short i=0; 
		double param,compParam;
		int dir=0;
		double f;
		double sum=0;
		double r=Rnd();
		int k=0;

		if(p>.5)
		{
			param=1-p;
			compParam=p;
			dir=-1;
		}
		else
		{
			param=p;
			compParam=1-p;
			dir=1;
		}

		f=pow(compParam,n);
		sum=f;
		i=0;
		//because distribution is symmetric, need only decide which direction we are moving
		//p^0q^n or p^nq^0
		
		while(sum<r && i<n)		
		{
			i++;
			f*=param/compParam*(n-i+1)/i;
			sum+=f;
		}

		if(dir==-1)
		{
			return n-i;
		}
		else
		{
			return i;
		}
	}
	
	
	double cum_neg_binomial(int success, int failure, double p)
	{
		//must sum
		//returns number of failures before xth success
		//sum(i=1-failure) of (success+i-1 choose i)p^x q^i
		double q=1-p;
		double f;
		double sum;

		//for i=0 and 1
		f=success*q;

		sum=1+f;
		
		for(int i=2; i<=failure;i++)
		{
			f*=q/i*(success+i-1);//*(success-i+1);
			sum+=f;
		}
		return pow(p,success)*sum;
	}

	double Rnd_beta(int v, int w)
	{
		double tmp_v=1,tmp_w=1;
		int i;
		for(i=1;i<=v;i++)
		{
			tmp_v*=Rnd();
		}
		for(i=1;i<=w;i++)
		{
			tmp_w*=Rnd();
		}
		tmp_v=-log(tmp_v);
		tmp_w=-log(tmp_w);
		return tmp_v/(tmp_v+tmp_w);
	}
	double beta_pdf(double v, double w, double x)
	{
		
		return exp(ln_beta_pdf(v,w,x));
	}
	double ln_beta_pdf(double v, double w, double x)
	{
		using namespace distrib;
		double a,a2;
		a=(v-1)*log(x)+(w-1)*log(1-x);
		a2=gammln(v)+gammln(w)-gammln(v+w);
		return a-a2;

	}
	double beta_pdf(int v, int w,double x)
	{
		return n_choose_k(v+w-1,v-1)*w*pow(x,v-1)*pow(1-x,w-1);
	}
	double poisson_pdf(double g, int N)
	{
		return exp(ln_poisson_pdf(g,N));

	}
	double ln_poisson_pdf(double g, int N)
	{
		double v=0;
		for(int i=1;i<=N;i++)
		{
			v+=log(i);
		}
		
//underflow or overflow errors?
		return -g+N*log(g)-v;
	}


	short poisson(double b_d)
	{
		if(b_d<9)
		{
			double r=Rnd();
			double c=0;
			double c_b_d=1/b_d;
			double exp_b_d=exp(-b_d);
			int i=-1;
			int c_i=1;
			while(r>c)
			{
				i++;
				c_b_d*=b_d;
				if(i>1)
					c_i*=i;

				c+=c_b_d*exp_b_d/c_i;
			}
			return i;
		}
		else
		{
			int i=int(Normal(b_d,pow(b_d,0.5))+.5);
			if(i<0)
				i=0;
			return i;
		}
	}

};
namespace _pmodDistributions
{


};
