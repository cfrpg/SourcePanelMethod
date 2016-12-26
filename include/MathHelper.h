#ifndef MATHHELPER_H
#define MATHHELPER_H

#define EPS 1e-6
#define PI 3.1415926535897932

//数学辅助类，所有函数都是静态函数
class MathHelper
{
public:
	MathHelper(void);

	static int Compare(double a,double b);//比较两个浮点数的大小
	
	~MathHelper(void);
};

#endif // MATHHELPER_H
