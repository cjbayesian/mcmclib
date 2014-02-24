#ifndef VBC_VECTOR_H
#define VBC_VECTOR_H

#pragma warning(disable:4786)
#pragma warning(disable:4503)
#pragma warning(disable:4305)
#pragma warning(disable:4309)
#pragma warning(disable:4800)
#include<iostream>
#include"vbc_genlib.h"
#include<vector>
#include"vbc_class.h"
#include<algorithm>
using namespace std;
namespace vbc_lib
{
	class boundFail
	{
	};
//NOTE: removing or adding elements directly via V will invalidate
//Dimensioning

	template<class T>
	class _vbc_vec
	{
	private:
		int lb1,lb2,lb3,lb4,lb5;
		int dimen;
		int ub1,ub2,ub3,ub4,ub5;
		int sCum2,sCum3,sCum4,sCum5;
		bool fixedArr;
		
	//	bool isClass;//requires reference counting
		//void getAllVals(int LB1,int LB2)

		bool doRedim(int LB1, int UB1,int LB2=0, \
			int UB2=0,int LB3=0, int UB3=0,int LB4=0, int UB4=0,int LB5=0,int UB5=0)

		{
			//try{
				V.clear(); 
				V.resize((UB1-LB1+1)*(UB2-LB2+1)*(UB3-LB3+1)*(UB4-LB4+1)*(UB5-LB5+1));

				hasInit=true;
				lb1=LB1;
				lb2=LB2;
				lb3=LB3;
				lb4=LB4;
				lb5=LB5;
				ub1=UB1;
				ub2=UB2;
				ub3=UB3;
				ub4=UB4;
				ub5=UB5;
				sCum2=UB1-LB1+1;
				sCum3=sCum2*(UB2-LB2+1);
				sCum4=sCum3*(UB3-LB3+1);
				sCum5=sCum4*(UB4-LB4+1);
			//}
			//catch(...){return false;}
			return true;

		}
		bool doResize(int UB, int tmpLB, int *tmpUB, int scalar)
		{
		//may change this
			//try
			//{
				if(UB<tmpLB) throw boundFail();
				if(UB<*tmpUB)
				{
					V.resize((UB-tmpLB+1)*scalar);
					hasInit=true;
					*tmpUB=UB;
					return true;
				}

				if(UB>=*tmpUB)
				{
//					inVecResize=true;
					V.resize((UB-tmpLB+1)*scalar);
//					inVecResize=false;
					*tmpUB=UB;
					hasInit=true;
					return true;
				}
				
				
				return true;

			//}

			//catch(...){return false;}

		}

		



	public:
		bool hasInit;
		vector<T> V;
		//this must have been redim, others must be dim
		_vbc_vec():V(),lb1(0),ub1(0),lb2(0),ub2(0),lb3(0),ub3(0),lb4(0),ub4(0),lb5(0),ub5(0),dimen(0),fixedArr(false),hasInit(false){};
		_vbc_vec(int LB1,int UB1):V(UB1-LB1+1),lb1(LB1),dimen(1),ub1(UB1),lb4(0),ub4(0),lb2(0),ub2(0),lb3(0),ub3(0),lb5(0),ub5(0),fixedArr(true),hasInit(true){};
		_vbc_vec(int LB1,int UB1,int LB2,int UB2):V((UB1-LB1+1)*(UB2-LB2+1)),lb1(LB1),lb2(LB2),lb4(0),ub4(0),lb3(0),ub3(0),lb5(0),ub5(0)
		,dimen(2),ub1(UB1),ub2(UB2),sCum2(UB1-LB1+1),fixedArr(true),hasInit(true){};

		_vbc_vec(int LB1,int UB1,int LB2,int UB2,int LB3,int UB3):V((UB1-LB1+1)*(UB2-LB2+1)*(UB3-LB3+1)),
		lb1(LB1),lb2(LB2),lb3(LB3),ub1(UB1),ub2(UB2)
		,ub3(UB3),lb4(0),ub4(0),lb5(0),ub5(0),sCum2(UB1-LB1+1),sCum3(sCum2*(UB2-LB2+1)),dimen(3),fixedArr(true),hasInit(true){};

		_vbc_vec(int LB1,int UB1,int LB2,int UB2,int LB3,int UB3,int LB4,int UB4):V((UB1-LB1+1)*(UB2-LB2+1)*(UB3-LB3+1)*(UB4-LB4+1))
		,lb1(LB1),lb2(LB2),lb3(LB3),lb4(LB4),lb5(0),ub5(0),dimen(4)
		,ub1(UB1),ub2(UB2),ub3(UB3),ub4(UB4),sCum2(UB1-LB1+1)
		,sCum3(sCum2*(UB2-LB2+1)),sCum4(sCum3*(UB3-LB3+1)),fixedArr(true),hasInit(true){};

		_vbc_vec(int LB1,int UB1,int LB2,int UB2,int LB3,int UB3,int LB4,int UB4, int LB5,int UB5):
		V((UB1-LB1+1)*(UB2-LB2+1)*(UB3-LB3+1)*(UB4-LB4+1)*(UB5-LB5+1))
		,lb1(LB1),lb2(LB2),lb3(LB3),lb4(LB4),lb5(LB5),ub5(UB5),dimen(5)
		,ub1(UB1),ub2(UB2),ub3(UB3),ub4(UB4),sCum2(UB1-LB1+1)
		,sCum3(sCum2*(UB2-LB2+1)),sCum4(sCum3*(UB3-LB3+1)),sCum5(sCum4*(UB4-LB4+1)),fixedArr(true),hasInit(true){};

		virtual ~_vbc_vec(){}//this allows to be held in map. If destroyed, all elements
		//decremented

		virtual void FuncReturn(){}//need to increase counter for funcReturn

		int getDimen()
		{
			return dimen;
		}
		int UBound()
		{
			return ub1;
		};

		int UBound(int i)
		{
			if(i > 0 && i<=dimen) 
			{
				switch(i)
				{
				case 1:
				return ub1;
				break;
				case 2:
				return ub2;
				break;
				case 3:
				return ub3;
				break;
				case 4:
				return ub4;
				break;
				case 5:
				return ub5;
				break;
				}
			}
				return -9999;
		}

		int LBound()
		{
			return lb1;
		};

		int LBound(int i)
		{
			if(i>0&&i<=dimen) 
			{
				switch(i)
				{
				case 1:
				return lb1;
				break;
				case 2:
				return lb2;
				break;
				case 3:
				return lb3;
				break;
				case 4:
				return lb4;
				break;
				case 5:
				return lb5;
				break;
				}
			}
				return -9999;
		}




		bool redim(int LB1, int UB1)
		{
			if(LB1>UB1) throw boundFail();
			dimen=1;
			return doRedim(LB1,UB1);
		};

		bool redim(int LB1, int UB1,int LB2, int UB2)
		{
			if(LB1>UB1|| LB2>UB2) throw boundFail();
			dimen=2;
			return doRedim(LB1,UB1,LB2,UB2);
		}

		bool redim(int LB1, int UB1,int LB2, int UB2,int LB3, int UB3)
		{
			if(LB1>UB1|| LB2>UB2 || LB3>UB3) throw boundFail();
			dimen=3;
			return doRedim(LB1,UB1,LB2,UB2,LB3,UB3);
		};

		bool redim(int LB1, int UB1,int LB2, int UB2,int LB3, int UB3,int LB4, int UB4)
		{
			if(LB1>UB1|| LB2>UB2 || LB3>UB3 || LB4>UB4) throw boundFail();
			dimen=4;
			return doRedim(LB1,UB1,LB2,UB2,LB3,UB3,LB4,UB4);
		};
		bool redim(int LB1, int UB1,int LB2, int UB2,int LB3, int UB3,int LB4, int UB4,int LB5, int UB5)
		{
			if(LB1>UB1|| LB2>UB2 || LB3>UB3 || LB4>UB4|| LB5>UB5) throw boundFail();
			dimen=5;
			return doRedim(LB1,UB1,LB2,UB2,LB3,UB3,LB4,UB4,LB5,UB5);
		};


		bool resizeUB(int LB1, int UB1)
		{
			if(V.empty()) 
				return redim(LB1,UB1);
			else
				return doResize(UB1,lb1,&ub1,1);
		};
		bool resizeUB(int LB1, int UB1,int LB2, int UB2)
		{
			if(V.empty()) 
				return redim(LB1,UB1,LB2,UB2);
			else

				return doResize(UB2,lb2,&ub2,sCum2);
		};
		bool resizeUB(int LB1, int UB1,int LB2, int UB2,int LB3, int UB3)
		{
			if(V.empty()) 
				return redim(LB1,UB1,LB2,UB2,LB3,UB3);
			else
				return doResize(UB3,lb3,&ub3,sCum3);
		};
		bool resizeUB(int LB1, int UB1,int LB2, int UB2,int LB3, int UB3,int LB4, int UB4)
		{
			if(V.empty()) 
				return redim(LB1,UB1,LB2,UB2,LB3,UB3,LB4,UB4);
			else

				return doResize(UB4,lb4,&ub4,sCum4);
		};
		bool resizeUB(int LB1, int UB1,int LB2, int UB2,int LB3, int UB3,int LB4, int UB4,int LB5, int UB5)
		{
			if(V.empty()) 
				return redim(LB1,UB1,LB2,UB2,LB3,UB3,LB4,UB4,LB5,UB5);
			else

				return doResize(UB5,lb5,&ub5,sCum5);
		};


		
	 	virtual void pop_back()
		{
			V.pop_back();
		}
		
		virtual void clear()
		{
			if(fixedArr)
			{
				for(typename vector<T>::iterator vi=V.begin();vi!=V.end();vi++)
				{
					*vi=T();
				}
			}
			else
			{
				dimen=0;
				lb1=0;				
				lb2=0;
				lb3=0;
				lb4=0;
				lb5=0;
				ub1=0;
				ub2=0;
				ub3=0;
				ub4=0;
				ub5=0;
				sCum2=0;
				sCum3=0;
				sCum4=0;
				sCum5=0;

				hasInit=false;
				V.clear();
			}
		}


/*			
		const T& at(int i) const
		{return V.at(i-lb1);}
		const T& at(int i,int j) const
		{return V.at(i-lb1+sCum2*(j-lb2));}

		const T& at(int i,int j,int k) const
		{return V.at(i-lb1+sCum2*(j-lb2)+sCum3*(k-lb3));}

		const T& at(int i,int j,int k,int l) const
		{return V.at(i-lb1+sCum2*(j-lb2)+sCum3*(k-lb3)+sCum4*(l-lb4));}

		T& at(int i)
		{return V.at(i-lb1);}
		
		T& at(int i,int j)
		{return V.at(i-lb1+sCum2*(j-lb2));}

		T& at(int i,int j,int k)
		{return V.at(i-lb1+sCum2*(j-lb2)+sCum3*(k-lb3));}
		
		T& at(int i,int j,int k,int l)
		{return V.at(i-lb1+sCum2*(j-lb2)+sCum3*(k-lb3)+sCum4*(l-lb4));}

*/			
		T& operator()(int i)
		{
			if(i<lb1 || i> ub1) 
				throw boundFail();


			return V[i-lb1];
		}

		T& operator()(int i,int j)
		{
			if(i<lb1 || i> ub1) throw boundFail();
			if(j<lb2 || j> ub2) throw boundFail();
			return V[i-lb1+sCum2*(j-lb2)];
		}

		T& operator()(int i,int j,int k)
		{
			if(i<lb1 || i> ub1) throw boundFail();
			if(j<lb2 || j> ub2) throw boundFail();
			if(k<lb3 || k> ub3) throw boundFail();
			return V[i-lb1+sCum2*(j-lb2)+sCum3*(k-lb3)];
		}
		
		T& operator()(int i,int j,int k,int l)
		{
			if(i<lb1 || i> ub1) throw boundFail();
			if(j<lb2 || j> ub2) throw boundFail();
			if(k<lb3 || k> ub3) throw boundFail();
			if(l<lb4 || l> ub4) throw boundFail();
			return V[i-lb1+sCum2*(j-lb2)+sCum3*(k-lb3)+sCum4*(l-lb4)];
		}

		T& operator()(int i,int j,int k,int l, int m)
		{
			if(i<lb1 || i> ub1) throw boundFail();
			if(j<lb2 || j> ub2) throw boundFail();
			if(k<lb3 || k> ub3) throw boundFail();
			if(l<lb4 || l> ub4) throw boundFail();
			if(m<lb5 || m> ub5) throw boundFail();
			return V[i-lb1+sCum2*(j-lb2)+sCum3*(k-lb3)+sCum4*(l-lb4)+sCum5*(m-lb5)];
		}

		const T& operator()(int i) const 
		{
			if(i<lb1 || i> ub1) throw boundFail();
			return V[i-lb1];
		}

		const T& operator()(int i,int j) const 
		{
			if(i<lb1 || i> ub1) throw boundFail();
			if(j<lb2 || j> ub2) throw boundFail();
			return V[i-lb1+sCum2*(j-lb2)];
		}

		const T& operator()(int i,int j,int k) const 
		{
			if(i<lb1 || i> ub1) throw boundFail();
			if(j<lb2 || j> ub2) throw boundFail();
			if(k<lb3 || k> ub3) throw boundFail();
			return V[i-lb1+sCum2*(j-lb2)+sCum3*(k-lb3)];
		}
		
		const T& operator()(int i,int j,int k,int l) const
		{
			if(i<lb1 || i> ub1) throw boundFail();
			if(j<lb2 || j> ub2) throw boundFail();
			if(k<lb3 || k> ub3) throw boundFail();
			if(l<lb4 || l> ub4) throw boundFail();
			return V[i-lb1+sCum2*(j-lb2)+sCum3*(k-lb3)+sCum4*(l-lb4)];
		}

		const T& operator()(int i,int j,int k,int l, int m) const
		{
			if(i<lb1 || i> ub1) throw boundFail();
			if(j<lb2 || j> ub2) throw boundFail();
			if(k<lb3 || k> ub3) throw boundFail();
			if(l<lb4 || l> ub4) throw boundFail();
			if(m<lb5 || m> ub5) throw boundFail();
			return V[i-lb1+sCum2*(j-lb2)+sCum3*(k-lb3)+sCum4*(l-lb4)+sCum5*(m-lb5)];
		}

		virtual _vbc_vec& operator=(const _vbc_vec& i)
		{
			if(this!=&i)
			{
				V.resize(i.V.size());

				lb1=i.lb1;
				lb2=i.lb2;
				lb3=i.lb3;
				lb4=i.lb4;
				lb5=i.lb5;

				ub1=i.ub1;
				ub2=i.ub2;
				ub3=i.ub3;
				ub4=i.ub4;
				ub5=i.ub5;
				
				sCum2=i.sCum2;
				sCum3=i.sCum3;
				sCum4=i.sCum4;
				sCum5=i.sCum5;
				hasInit=i.hasInit;
				dimen=i.dimen;
				V=i.V;
			}
			
			return *this;
		}


	};
	template <class T>
	inline int UBound(_vbc_vec<T>& v)
	{
		if(!v.hasInit) throw boundFail();
		return v.UBound();
	}

	template <class T>
	inline int UBound(_vbc_vec<T>& v,int i)
	{
		if(!v.hasInit) throw boundFail();
		return v.UBound(i);
	}

	template <class T>
	inline int LBound(_vbc_vec<T>& v)
	{
		if(!v.hasInit) throw boundFail();
		return v.LBound();
	}

	template <class T>
	inline int LBound(_vbc_vec<T>& v,int i)
	{
		if(!v.hasInit) throw boundFail();
		return v.LBound(i);
	}

	template <class T>
	inline int testUB(_vbc_vec<T>& v)
	{
		if(!v.hasInit) return 0;
		return v.UBound();
	}

	template <class T>
	inline int testUB(_vbc_vec<T>& v,int i)
	{
		if(!v.hasInit) return 0;
		return v.UBound(i);
	}

	template <class T>
	inline int testLB(_vbc_vec<T>& v)
	{
		if(!v.hasInit) return 0;
		return v.LBound();
	}

	template <class T>
	inline int testLB(_vbc_vec<T>& v,int i)
	{
		if(!v.hasInit) return 0;
		return v.LBound(i);
	}

	template<class T>
	inline void fillArray(T a[],_vbc_vec<T>& v,int b, int e)
	{
		for(int i=b; i<=e;i++)
		{
			v(i)=a[i-b];
		}

	}
	template<class T>
	inline void redimUnknown(_vbc_vec<T>* v, int lb, int ub)
	{
		v->redim(lb,ub);
	}


	inline void redimUnknown(_enumPtr* v, int lb, int ub)
	{
	}

	template<class T,class U>
	inline void assignUnknown(_vbc_vec<T>* v, int el, const U& val)
	{
		(*v)(el)=val;
	}
	template<class T>
	inline void assignUnknown(_enumPtr* v, int el, const T& val)
	{
	}
};

#endif;
