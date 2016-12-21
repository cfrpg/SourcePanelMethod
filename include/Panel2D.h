#ifndef PANEL2D_H
#define PANEL2D_H
#include "Vector2.h"
//描述平面的类
class Panel2D
{
public:
	Panel2D(void);
	Panel2D(Vector2 _v1,Vector2 _v2);	//用两点初始化平面
	Vector2 GetNormal();				//获取法线,法线为v1->v2方向左侧
	Vector2 GetMidpoint();				//获取中点
	void Reset(Vector2 v1,Vector2 v2);	//重设平面
	void Reverse();						//交换v1,v2
	double GetAngle();					//获取与x轴的夹角
	Vector2 GetDirection();
	double GetX1();
	double GetY1();
	double GetX2();
	double GetY2();
	double GetLength();
	double GetLengthSqure();
	~Panel2D(void);
private:
	Vector2 v1,v2;		//两点
	Vector2 normal;		//法线
	double angle;		//
	double lengthSqure;
	Vector2 direction;
	Vector2 midpoint;	//中点
};
#endif // PANEL2D_H
