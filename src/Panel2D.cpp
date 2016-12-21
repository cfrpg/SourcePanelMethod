#include "Panel2D.h"
#include "MathHelper.h"
#include <cmath>
#include <cstdio>
Panel2D::Panel2D(void)
{
}

Panel2D::Panel2D(Vector2 _v1,Vector2 _v2)
{
	v1=_v1;
	v2=_v2;
	midpoint=v1+v2;
	midpoint/=2;
	normal=-Vector2((v2-v1).y,-(v2-v1).x);
	angle=atan2(v2.y-v1.y,v2.x-v1.x);
	if(angle<0)
		angle+=2*PI;
	direction=(v2-v1);
	direction.Normalize();
	normal.Normalize();
	lengthSqure=(v2-v1).GetLengthSqure();
}

Vector2 Panel2D::GetNormal()
{
	return normal;
}

Vector2 Panel2D::GetMidpoint()
{
	return midpoint;
}

void Panel2D::Reset(Vector2 _v1,Vector2 _v2)
{
	v1=_v1;
	v2=_v2;
	midpoint=v1+v2;
	midpoint/=2;
	normal.x=-(v2-v1).y;
	normal.y=(v2-v1).x;
	angle=atan2(v2.y-v1.y,v2.x-v1.x);
	if(angle<0)
		angle+=2*PI;
	direction=(v2-v1);
	direction.Normalize();
}

void Panel2D::Reverse()
{
	normal=-normal;
	v1+=v2;
	v2=v1-v2;
	v1-=v2;
}

double Panel2D::GetAngle()
{
	return angle;
}

Vector2 Panel2D::GetDirection()
{
	return direction;
}

double Panel2D::GetX1()
{
	return v1.x;
}

double Panel2D::GetY1()
{
	return v1.y;
}

double Panel2D::GetX2()
{
	return v2.x;
}

double Panel2D::GetY2()
{
	return v2.y;
}

double Panel2D::GetLengthSqure()
{
	return lengthSqure;
}

double Panel2D::GetLength()
{
	return sqrt(lengthSqure);
}

Panel2D::~Panel2D(void)
{
}
