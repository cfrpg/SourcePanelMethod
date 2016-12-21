#include <iostream>
#include <iomanip>
#include "MathHelper.h"
#include <fstream>
#include "Airfoil.h"
#include <cmath>
#include <cstdlib>

using namespace std;

int SourcePanelMethod(Airfoil& airfoil,char* path,Vector2 v);

int main(int argc,char *argv[])
{
	Airfoil airfoil;
	double xx,yy;
	if(argc==5)
	{
		airfoil.Load(argv[1]);
		sscanf(argv[3],"%lf",&xx);
		sscanf(argv[4],"%lf",&yy);
		SourcePanelMethod(airfoil,argv[2],Vector2(xx,yy));
	}
	else if(argc==1)
	{
		char str[512];
		printf("Source panel method\n");
		printf("\nInput file?\n");
		scanf("%s",str);
		airfoil.Load(str);
		printf("\nOutput file?\n");
		scanf("%s",str);
		printf("\nVinf.x?\n");
		scanf("%lf",&xx);
		printf("\nVinf.y?\n");
		scanf("%lf",&yy);
		SourcePanelMethod(airfoil,str,Vector2(xx,yy));
	}
	else
	{
        printf("Syntax：SourcePanelMethod in out vx vy\n\n");
        printf("in\tFull path of input file.\n");
        printf("out\tFull path of output file.\n");
        printf("vx\tx component of Vinf.\n");
        printf("vy\ty component of Vinf.\n");
        printf("\n");
        printf("example:\n");
        printf("SourcePanelMethod d:\\naca0012.dat d:\\ans.dat 1 0\n");
        printf("\n");
        printf("Startup without argument and follow the instructions can also run this application.\n\n");

	}
	return 0;
}

//面源法
//输出格式
//x y cp(x,y)
//Airfoil airfoil:用于计算的翼型
//char* path:输出文件保存路径
//Vector2 v:来流速度
int SourcePanelMethod(Airfoil &airfoil,char* path,Vector2 v)
{
	double **mat;	//计算源强度的方程组的增广矩阵
	double **mat2;	//计算压力系数的积分矩阵
	bool *l;		//高斯消元用
	double *ans;	//高斯消元用，值为点源强度
	double *cp;		//压力系数
	int n;			//面源个数
	ofstream out;
	//临时变量
	Vector2 vct;
	double A,B,C,D,E,S,S2;
	double phii,phij;
	double xi,yi,Xj,Yj;
	//打开文件
	out.open(path,ios::out | ios::trunc);
	if(!out.is_open())
	{
		printf("Cannot open the file!\n");
		return -1;
	}
	n=airfoil.Panels.size();
	//申请内存
	printf("Seting memory...\n");
	mat=(double**)malloc((n+2)*sizeof(double*));
	mat2=(double**)malloc((n+2)*sizeof(double*));
	for(int i=0;i<=n+1;i++)
	{
		mat[i]=(double*)malloc((n+2)*sizeof(double));
		mat2[i]=(double*)malloc((n+2)*sizeof(double));
	}
	l=(bool*)malloc((n+1)*sizeof(bool));
	ans=(double*)malloc((n+1)*sizeof(double));
	cp=(double*)malloc((n+1)*sizeof(double));
	printf("Calcing factor mat...\n");
	//计算系数矩阵
	//Ax=b
	for(int i=0;i<n;i++)
	{
		//计算b,也就是自由来流产生的法向速度的相反数
		mat[i][n]=-Vector2::Dot(v,airfoil.Panels[i].GetNormal())*2*PI;
	}
	for(int i=0;i<n;i++)//计算系数矩阵A
	{
		for(int j=0;j<n;j++)
		{
			if(i==j)
			{
				mat[j][i]=PI;
				mat2[i][j]=0;//面源对自己不起作用
			}
			else
			{
				//计算点源i对面源j产生的法向速度
				phii=airfoil.Panels[i].GetAngle();
				phij=airfoil.Panels[j].GetAngle();
				xi=airfoil.Panels[i].GetMidpoint().x;
				yi=airfoil.Panels[i].GetMidpoint().y;
				Xj=airfoil.Panels[j].GetX1();
				Yj=airfoil.Panels[j].GetY1();
				A=-(xi-Xj)*cos(phij)-(yi-Yj)*sin(phij);
				B=(xi-Xj)*(xi-Xj)+(yi-Yj)*(yi-Yj);
				C=sin(phii-phij);
				D=(yi-Yj)*cos(phii)-(xi-Xj)*sin(phii);
				S=airfoil.Panels[j].GetLength();
				S2=airfoil.Panels[j].GetLengthSqure();
				E=sqrt(B-A*A);
				mat[i][j]=(C/2)*log((S2+2*A*S+B)/B)+((D-A*C)/E)*(atan((S+A)/E)-atan(A/E));
				mat2[i][j]=((D-A*C)/(2*E))*log((S2+2*A*S+B)/B)-C*(atan((S+A)/E)-atan(A/E));
			}
		}
	}

	printf("Equation Num=%d\n",n);
	printf("Solving equations...\n");
	MathHelper::GaussianElimination(mat,l,ans,n);//解方程组
	//计算压力系数
	for(int i=0;i<n;i++)
	{
		cp[i]=0;
		for(int j=0;j<n;j++)
		{
			cp[i]+=mat2[i][j]*ans[j]/(2*PI);
		}
		cp[i]+=v.GetLength()*cos(airfoil.Panels[i].GetAngle());
		cp[i]=1-(cp[i]*cp[i])/v.GetLengthSqure();
	}

	printf("Saving...\n");
	//out<<setiosflags(ios::scientific)<<setprecision(12);
	for(int i=0;i<n;i++)
	{
		if(l[i]==0)
			ans[i]=0;
		if(fabs(ans[i])>1e20)
			ans[i]=0;
		out<<airfoil.Panels[i].GetMidpoint().x<<"\t"<<airfoil.Panels[i].GetMidpoint().y<<"\t"<<cp[i]<<endl;
	}


	printf("Disposing memory...\n");
	delete(mat);
	delete(mat2);
	delete(cp);
	delete(l);
	delete(ans);
	out.close();
	printf("Calc Successful.\n");
	return 0;
}

