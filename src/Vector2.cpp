#include "Vector2.h"
#include "mathhelper.h"
#include <cmath>
#include <cstdlib>

Vector2::Vector2(void)
{
	x=0;
	y=0;
}

Vector2::Vector2(double _x,double _y)
{
	x=_x;
	y=_y;
}

Vector2::Vector2(double _l)
{
	x=_l;
	y=_l;
}

Vector2 Vector2::Up()
{
	return Vector2(0,1);
}

Vector2 Vector2::Down()
{
	return Vector2(0,-1);
}

Vector2 Vector2::Left()
{
	return Vector2(-1,0);
}

Vector2 Vector2::Right()
{
	return Vector2(1,0);
}

Vector2 operator+(const Vector2 &l,const Vector2 &r)
{
	return Vector2(l.x+r.x,l.y+r.y);
}

Vector2 operator-(const Vector2 &l,const Vector2 &r)
{
	return Vector2(l.x-r.x,l.y-r.y);
}

Vector2 operator*(const Vector2 &l,const double &r)
{
	return Vector2(l.x*r,l.y*r);
}

Vector2 operator*(const double &r,const Vector2 &l)
{
	return Vector2(l.x*r,l.y*r);
}

Vector2 operator/(const double &r,const Vector2 &l)
{
	return Vector2(l.x/r,l.y/r);
}


bool Vector2::operator==(const Vector2 &r)
{
	return ((MathHelper::Compare(x,r.x)==0)&&(MathHelper::Compare(y,r.y)==0));
}

bool Vector2::operator!=(const Vector2 &r)
{
	return ((MathHelper::Compare(x,r.x)!=0)||(MathHelper::Compare(y,r.y)!=0));
}

Vector2 Vector2::operator-()
{
	return Vector2(-x,-y);
}

void Vector2::operator+=(const Vector2 &r)
{
	x+=r.x;
	y+=r.y;
}

void Vector2::operator-=(const Vector2 &r)
{
	x-=r.x;
	y-=r.y;
}

void Vector2::operator*=(const double &r)
{
	x*=r;
	y*=r;
}

void Vector2::operator/=(const double &r)
{
	x/=r;
	y/=r;
}

double Vector2::Distance(Vector2 v1,Vector2 v2)
{
	return sqrt((v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v2.y));
}

double Vector2::Dot(Vector2 v1,Vector2 v2)
{
	return v1.x*v2.x+v1.y*v2.y;
}

double Vector2::GetLengthSqure()
{
	return x*x+y*y;
}

double Vector2::GetLength()
{
	return sqrt(GetLengthSqure());
}

void Vector2::Normalize()
{
	double l=GetLength();
	x/=l;
	y/=l;
}

Vector2::~Vector2(void)
{
}

