#include <iostream>
#include <vector>
#include "function.h"
#define Pi 3.141592653589793238f
using namespace std;

float radians(float a);
vector <float> Auxiliary_point(float* arr);
vector <float> Analytical_calculation(vector<float>vec);
vector <float> Intersection_calculation(vector<float>vec);

int main()
{
	system("title 末影之眼定位算法");
	printf("这个程序用来计算主世界末地传送门的坐标。\n\n");
	printf("使用方法：\n");
	printf("\t1、你需要抛出一颗末影之眼，用准星瞄准末影之眼最后的位置;\n\n");
	printf("\t2、保持不动，将此时的 X轴坐标，Z轴坐标，y_rotation值 依次输入程序;\n\n");
	printf("\t3、共需输入三次，第三次输入完成后程序会计算主世界末地传送门并显示;\n\n\n");
	printf("计算得出的位置可能有偏差，扔出的三点相隔的距离要适当\n\n");
	printf("如果输入的数据出现问题可能导致计算结果出现错误，例如出现\"inf\"\n\n\n\n");

	int choose;
	printf("选择操作:\n");
	printf("\t1——> 开始\n");
	printf("\t2——> 打开视频教程\n");
	printf("\t3——> 打开GitHub仓库网址\n");
	printf("\t0——> 退出\n:");
START:
	cin >> choose;
	switch (choose)
	{
	case 0:
		exit(1);
	case 1:
		;
		break;
	case 2:
		system("start https://www.bilibili.com/video/BV1V5411e7kh");
		system("cls");
		goto START;
		break;
	case 3:
		system("start https://github.com/Temperature6/Eye-of-Ender-Positioning-Algorithm");
		system("cls");
		goto START;
		break;
	default:
		printf("你咋不听话nie?\n");
		goto START;
		break;
	}
	system("cls");

	//存放三点的x轴坐标，z轴坐标，y_rotation值
	float point[3][4];

	//循环存放用户输入的数据
	for (int i = 0; i < 3; i++)
	{
		printf("依次输入第%i个点的数据(x轴坐标，z轴坐标，y_rotation值)，数据之间使用空格或Tab隔开\n", i + 1);
		scanf_s("%f %f %f", &point[i][0], &point[i][1], &point[i][2]);
		system("cls");
	}

	//打印点信息
	system("cls");
	printf("\n————————————————————————调试信息————————————————————————\n");
	printf("输入三点:\n");
	for (int j = 0; j < 3; j++) {
		printf("\t第%i个点:\t\tX:%.2lf\t\tZ:%.2lf\t\ty_rotation:%.2lf\n", j + 1, point[j][0], point[j][1], point[j][2]);
	}
	//转化为两点坐标并存入新数组
	vector <float> PointGroup1 = Auxiliary_point(point[0]);
	vector <float> PointGroup2 = Auxiliary_point(point[1]);
	vector <float> PointGroup3 = Auxiliary_point(point[2]);

	//储存解析式参数
	PointGroup1 = Analytical_calculation(PointGroup1);
	PointGroup2 = Analytical_calculation(PointGroup2);
	PointGroup3 = Analytical_calculation(PointGroup3);
		//打印解析式
	printf("\n解析式:\n");
	printf("\ty=%.2lfx%+.2lf\n", PointGroup1[0], PointGroup1[1]);
	printf("\ty=%.2lfx%+.2lf\n", PointGroup2[0], PointGroup2[1]);
	printf("\ty=%.2lfx%+.2lf\n", PointGroup3[0], PointGroup3[1]);
	//计算三个解析式交点
		//解析式两两一组
	vector <float> line12 = { PointGroup1[0], PointGroup1[1], PointGroup2[0], PointGroup2[1] };
	vector <float> line13 = { PointGroup1[0], PointGroup1[1], PointGroup3[0], PointGroup3[1] };
	vector <float> line23 = { PointGroup2[0], PointGroup2[1], PointGroup3[0], PointGroup3[1] };
		//执行计算,此时数组里的内容(前两个)已经变成了交点坐标
	line12 = Intersection_calculation(line12);
	line13 = Intersection_calculation(line13);
	line23 = Intersection_calculation(line23);
		//打印交点坐标
	printf("\n交点坐标:\n");
	printf("\t直线1与直线2交点:(%.2lf, %.2lf)\n", line12[0], line12[1]);
	printf("\t直线1与直线3交点:(%.2lf, %.2lf)\n", line13[0], line13[1]);
	printf("\t直线2与直线3交点:(%.2lf, %.2lf)\n", line23[0], line23[1]);

	//分析计算结果
		//将X、Z轴坐标分别存为两组
	vector <float> x_pos = { line12[0], line13[0], line23[0] };
	vector <float> z_pos = { line12[1], line13[1], line23[1] };
		//铅锤高和水平宽的平均
	float _X = (max(x_pos) + min(x_pos)) / 2;
	float _Z = (max(z_pos) + min(z_pos)) / 2;
		//坐标平均
	float X = avg(x_pos);
	float Z = avg(z_pos);
		//打印结果
	printf("\n————————————————————————计算结果————————————————————————\n");
	printf("\n目标位于(铅垂高和水平宽的中点): X=%.2lf, Z=%.2lf\n", _X, _Z);
	printf("传送命令(铅垂高和水平宽的中点): /tp @s %.2lf ~ %.2lf\n\n", _X, _Z);
	printf("\n目标位于(三交点横纵坐标平均数): X=%.2lf, Z=%.2lf\n", X, Z);
	printf("传送命令(三交点横纵坐标平均数): /tp @s %.2lf ~ %.2lf\n\n", X, Z);
	printf("按任意键重启\n");
	system("pause");
	goto START;
}

float radians(float a) {
	//radians:角度转弧度
	//a:传入角度
	return a * (Pi / 180);
}

vector <float> Auxiliary_point(float* arr) {
	//Auxiliary_point:分析点，将一点及其方向角转化为两点坐标
	//*arr:传入指针，输出指针

	float x = arr[0];
	float z = arr[1];
	float r = arr[2];
	float X, Z;


	if (0 < r && r <= 90) 
	{
		X = x - 100;
		Z = 100 / tan(radians(r)) + z;
	}
	else if (-90 <= r && r < 0)
	{
		X = x + 100;
		Z = -100 / tan(radians(r)) + z;
	}
	else if (-180 <= r && r < -90)
	{
		X = x + 100;
		Z = -100 / tan(radians(r)) + z;
	}
	else
	{
		X = x - 100;
		Z = 100 / tan(radians(r)) + z;
	}

	vector <float> result = { x, z, X, Z };
	return result;
}

vector <float> Analytical_calculation(vector<float>vec)
{
	float k, b;
	float x1 = vec[0], z1 = vec[1];
	float x2 = vec[2], z2 = vec[3];

	k = (z2 - z1) / (x2 - x1);
	b = z1 - k * x1;

	vec[0] = k; vec[1] = b; vec[2] = 0; vec[3] = 0;
	return vec;
}

vector <float> Intersection_calculation(vector<float>vec) 
{
	float its_x, its_z;
	float k1 = vec[0], b1 = vec[1];
	float k2 = vec[2], b2 = vec[3];

	its_x = (b2 - b1) / (k1 - k2);
	its_z = k1 * its_x + b1;

	vec[0] = its_x;
	vec[1] = its_z;
	vec[2] = 0;
	vec[3] = 0;

	return vec;
}