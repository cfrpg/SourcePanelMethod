#include "MathHelper.h"
#include <cmath>



MathHelper::MathHelper(void)
{
}

int MathHelper::Compare(double a,double b)
{
	if(fabs(a-b)<EPS)
		return 0;
	if(a<b)
		return -1;
	return 1;
}

int MathHelper::GaussianElimination(double **a,bool *l,double *ans,const int &n)
{
	int res=0,r=0;
	double temp;
	double tmp;
	for(int i=0;i<n;i++)
	{
		l[i]=false;
	}
	for(int i=0;i<n;i++)
	{
		for(int j=r;j<n;j++)
		{
			if(fabs(a[j][i])>EPS)
			{
				for(int k=i;k<=n;k++)
				{
					temp=a[j][k];
					a[j][k]=a[r][k];
					a[r][k]=temp;
				}
				break;
			}
		}
		if(fabs(a[r][i])<EPS)
		{
			res++;
			continue;
		}
		for(int j=0;j<n;j++)
		{
			if(j!=r&&fabs(a[j][i])>EPS)
			{
				tmp=a[j][i]/a[r][i];
				for(int k=i;k<=n;k++)
				{
					a[j][k]-=tmp*a[r][k];
				}
			}
		}
		l[i]=true;
		r++;
	}
	for(int i=0;i<n;i++)
	{
		if(l[i])
		{
			for(int j=0;j<n;j++)
			{
				if(fabs(a[j][i])>EPS)
				{
					ans[i]=a[j][n]/a[j][i];
				}
			}
		}
	}
	return res;
}



MathHelper::~MathHelper(void)
{
}

