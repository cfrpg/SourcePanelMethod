#ifndef AIRFOIL_H
#define AIRFOIL_H

#include <vector>
#include <string>
#include "Vector2.h"
#include "Panel2D.h"

using namespace std;

//描述翼型的类
class Airfoil
{
public:
	Airfoil(void);

	vector<Vector2> Points;//所有点的集合
	vector<Panel2D> Panels;//所有面源的集合

	void Load(char* path);//从文件载入翼型

	~Airfoil(void);
private:

};

#endif // AIRFOIL_H
