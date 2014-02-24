#ifndef VBC_GENLIB_H
#define VBC_GENLIB_H
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#pragma warning(disable:4305)
#pragma warning(disable:4309)
#pragma warning(disable:4800)
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<time.h>
#include<float.h>
//constants


#ifdef ISDLL
#define STDCALL __stdcall

#else 
#define STDCALL 

#endif;

namespace vbc_lib
{
//	extern bool inVecResize;
	extern long Seed;
	const float PI=3.141592654;
	const int ptrNull=0;
	
	//the class that is thrown with raise error
	class _vbc_UDTError
	{
		
	};

	enum _enumPtr
	{
		_PtrNull=0
	};
	
	extern _enumPtr TPtrNull;
	enum doRethrow
	{
		_noThrow,_errLabel,_unDefined
	};

	double Rnd();
	
	inline double Rnd(int i)
	{
		return Rnd();
	}

	void Randomize(long i);
	inline void Randomize()
	{
		Randomize(time(0));
	}

	template<class T>
	inline int Round(T i)
	{
			return int(i+0.5);
	}

	inline long _vbc_Abs(long i)
	{
		return labs(i);
	}

	inline int _vbc_Abs(int i)
	{
		return labs(i);
	}

	inline short _vbc_Abs(short i)
	{
		return abs(i);
	}

	inline double _vbc_Abs(double i)
	{
		return fabs(i);
	}
	
	template<class T>
	double pow(T i, int e)
	{
		
		bool isNeg=false;
		if(e==0)
			return 1;
		else if(e<0)
		{
			isNeg=true;
			e=-e;
		}
	
		//int tmp=e/2;
		double _pow;
		double powExp=i;
		int bit=2;

		if(e & 1)
			_pow=i;
		else
			_pow=1;


		while(e>=bit)
		{
			powExp*=powExp;
			if(e & bit)
				_pow*=powExp;

			bit*=2;
		}
		
		if(isNeg)
			return 1/_pow;
		else
			return _pow;
	}

	template<class T>
	inline double pow(T i, double e)
	{
		return ::pow(i,e);
	}
	

	inline double pow(int i, double e)
	{
		return ::pow(i,e);
	}

	template<class T>
	inline short _vbc_Sgn(T i)
	{
		if(i<0) return -1;
		else
			return 1;
	}
	
	//__________________________________
	inline bool isNumeric(double const &v){return true;}
	inline bool isNumeric(short v){return true;}
	inline bool isNumeric(float const &v){return true;}
	inline bool isNumeric(int v){return true;}
	inline bool isNumeric(long v){return true;}


	template<class T>
	inline float CFloat(T i)
	{
		return static_cast<float>(i);
	}

	template<class T>
	inline int CLng(T i)
	{
		return static_cast<int>(i);
	}

	template<class T>
	inline float CShort(const T i)
	{
		return static_cast<short>(i);
	}
	template<class T>
	inline double CDbl(const T i)
	{
		return static_cast<double>(i);
	}

	template<class T>
	inline T Min(T i, T j)
	{
		if(i<j)
			return i;
		else
			return j;
	}
	template<class T>
	inline T Max(T i, T j)
	{
		if(i>j)
			return i;
		else
			return j;
	}
	
	template<class T>
	inline bool isPtrNull(T* i)
	{
		if(i)
			return false;
		else
			return true;
	}

	inline bool isPtrNull(_enumPtr* i)//required because templates can not take const arguments
	{
		return true;
	}

}

#endif;