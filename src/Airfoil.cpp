#include "Airfoil.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "MathHelper.h"

//using namespace std;

Airfoil::Airfoil(void)
{
	Points.clear();
	Panels.clear();
}

void Airfoil::Load(char* path)
{
	double x,y;
	int cnt=0;
	ifstream in;
	Points.clear();
	printf("Opening the file...\n");
	in.open(path,ios::in);
	if(!in.is_open())
	{
		printf("Cannot open the file.\n");
		return;
	}
	printf("Loading points from the file...\n");
	while(in>>x>>y)
	{
		Points.push_back(Vector2(x,y));
		cnt++;
	}
	printf("%d points loaded.\n",cnt);

	printf("Making the panels...\n");
	cnt=0;
	Panels.clear();
	for(int i=1;i<Points.size();i++)//相邻两点间连一个面源，最后一点不和第一点相连
	{
		Panels.push_back(Panel2D(Points[i],Points[i-1]));
	}
	if(Points.size()%2==0)
		Panels.push_back(Panel2D(Points[0],Points[Points.size()-1]));

	printf("%d panels.\n",Panels.size());
	in.close();
	printf("Airfoil loaded successfully.\n");
}

Airfoil::~Airfoil(void)
{
}
