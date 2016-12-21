#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
	Vector2(void);							//创建零向量
	Vector2(double _x,double _y);			//创建(x,y)向量
	Vector2(double _l);						//创建(l,l)向量

	static Vector2 Up();	//(0,1)
	static Vector2 Down();	//(0,-1)
	static Vector2 Left();	//(-1,0)
	static Vector2 Right();	//(1,0)

	friend Vector2 operator+(const Vector2 &l,const Vector2 &r);	//向量加法
	friend Vector2 operator-(const Vector2 &l,const Vector2 &r);	//向量减法
	friend Vector2 operator*(const Vector2 &l,const double &r);		//向量数乘
	friend Vector2 operator/(const Vector2 &l,const double &r);		//向量除以标量
	friend Vector2 operator*(const double &r,const Vector2 &l);		//向量数乘，标量为左操作数
	bool operator == (const Vector2 &r);				//判断相等
	bool operator != (const Vector2 &r);				//判断不等
	Vector2 operator-();			//取反
	void operator +=(const Vector2 &r);	//加法
	void operator -=(const Vector2 &r);	//减法
	void operator *=(const double &r);	//数乘
	void operator /=(const double &r);	//数除

	static double Distance(Vector2 v1,Vector2 v2);	//求两点间距离
	static double Dot(Vector2 v1,Vector2 v2);		//点积

	double GetLength();		//获取长度
	double GetLengthSqure();	//获取长度的平方
	void Normalize();		//单位化

	double x;	//x
	double y;	//y

	~Vector2(void);
};

#endif // VECTOR2_H
