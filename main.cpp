#include <iostream>
#include <iomanip>
#include "MathHelper.h"
#include <fstream>
#include "Airfoil.h"
#include <cmath>
#include <cstdlib>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>

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
	gsl_matrix *mat;	//计算源强度的方程组的矩阵
	gsl_matrix *mat2;	//计算压力系数的积分矩阵
	gsl_vector *strength;	//面源强度
	gsl_vector *b;	//方程组常数项
	gsl_permutation *p;
	gsl_vector *cp;		//压力系数
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
	mat=gsl_matrix_alloc(n,n);
	mat2=gsl_matrix_alloc(n,n);
    strength=gsl_vector_alloc(n);
    b=gsl_vector_alloc(n);
	cp=gsl_vector_alloc(n);
	p=gsl_permutation_alloc(n);
	gsl_permutation_init(p);

	printf("Calcing factor mat...\n");
	//计算系数矩阵
	//Ax=b
	for(int i=0;i<n;i++)
	{
		//计算b,也就是自由来流产生的法向速度的相反数
		gsl_vector_set(b,i,-Vector2::Dot(v,airfoil.Panels[i].GetNormal())*2*PI);
	}
	for(int i=0;i<n;i++)//计算系数矩阵A
	{
		for(int j=0;j<n;j++)
		{
			if(i==j)
			{
				gsl_matrix_set(mat,i,j,PI);
				gsl_matrix_set(mat2,i,j,0);
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
				gsl_matrix_set(mat,i,j,(C/2)*log((S2+2*A*S+B)/B)+((D-A*C)/E)*(atan((S+A)/E)-atan(A/E)));
				gsl_matrix_set(mat2,i,j,((D-A*C)/(2*E))*log((S2+2*A*S+B)/B)-C*(atan((S+A)/E)-atan(A/E)));
			}
		}
	}

	printf("Equation Num=%d\n",n);
	printf("Solving equations...\n");

    int s;
    gsl_linalg_LU_decomp(mat,p,&s);
    gsl_linalg_LU_solve(mat,p,b,strength);

	//计算压力系数
	for(int i=0;i<n;i++)
	{
		gsl_vector_set(cp,i,cos(airfoil.Panels[i].GetAngle()));
	}
	gsl_blas_dgemv(CblasNoTrans,1.0/(2*PI),mat2,strength,v.GetLength(),cp);

	printf("Saving...\n");
	out<<setiosflags(ios::scientific)<<setprecision(12);
	for(int i=0;i<n;i++)
	{
		double res=gsl_vector_get(cp,i);
		res=1-(res*res)/v.GetLengthSqure();
		out<<airfoil.Panels[i].GetMidpoint().x<<"\t"<<airfoil.Panels[i].GetMidpoint().y<<"\t"<<res<<endl;
	}

	printf("Disposing memory...\n");
	gsl_matrix_free(mat);
	gsl_matrix_free(mat2);
	gsl_vector_free(strength);
	gsl_vector_free(b);
	gsl_vector_free(cp);
	gsl_permutation_free(p);
	out.close();
	printf("Calc Successful.\n");
	return 0;
}


