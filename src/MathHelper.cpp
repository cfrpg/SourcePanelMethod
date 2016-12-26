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

MathHelper::~MathHelper(void)
{
}

