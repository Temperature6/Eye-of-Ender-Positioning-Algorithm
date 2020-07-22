//末影之眼定位算法,2020年7月18日 19:58创建工程
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "SimpleFunction.h"
#define Pi 3.141592653589793238f
using namespace std;

float radians(float a) {
	//radians:角度转弧度
	//a:传入角度
	return a * (Pi / 180);
}

float* Analytical_calculation(float cdnte_arr[]) {
	//Analytical_calculation:计算坐标输出解析式参数
	//coordinate_arr:坐标数组
	//parameter_arr:参数数组
	float k, b;
	float x1 = cdnte_arr[0], z1 = cdnte_arr[1];
	float x2 = cdnte_arr[2], z2 = cdnte_arr[3];

	k = (z2 - z1) / (x2 - x1);
	b = z1 - k * x1;

	cdnte_arr[0] = k;
	cdnte_arr[1] = b;

	return cdnte_arr;
}

float* Auxiliary_point(float *arr) {
	//Auxiliary_point:分析点，将一点及其方向角转化为两点坐标
	//*arr:传入指针，输出指针

	float x = arr[0];
	float z = arr[1];
	float r = arr[2];
	float X, Z;


	if (0 < r && r <= 90) {
		//printf("0 < r <= 90\n");
		X = x - 100;
		Z = 100 / tan(radians(r)) + z;
	}
	else if (-90 <= r && r < 0) {
		//printf("-90 <= r < 0\n");
		X = x + 100;
		Z = -100 / tan(radians(r)) + z;
	}
	else if (-180 <= r && r < -90) {
		//printf("-180 <= r < -90\n");
		X = x + 100;
		Z = -100 / tan(radians(r)) + z;
	}
	else {
		//printf("90 < r < 180\n");
		X = x - 100;
		Z = 100 / tan(radians(r)) + z;
	}
	
	arr[0] = x;
	arr[1] = z;
	arr[2] = X;
	arr[3] = Z;
	return arr;
}

float* Intersection_calculation(float para_arr[]) {
	//Intersection_calculation:交点计算
	//para_arr1[]:解析式参数1
	//para_arr2[]:解析式参数2
	float its_x, its_z;
	float k1 = para_arr[0], b1 = para_arr[1];
	float k2 = para_arr[2], b2 = para_arr[3];

	its_x = (b2 - b1) / (k1 - k2);
	its_z = k1 * its_x + b1;

	para_arr[0] = its_x;
	para_arr[1] = its_z;
	para_arr[2] = 0;
	para_arr[3] = 0;

	cout << its_x << endl;
	cout << its_z << endl;

	return para_arr;
}

int main() {
	
	printf("这个程序用来计算主世界末地传送门的坐标。\n\n");
	printf("使用方法：\n");
	printf("\t1、你需要抛出一颗末影之眼，用准星瞄准末影之眼最后的位置;\n\n");
	printf("\t2、保持不动，将此时的 X轴坐标，Z轴坐标，y_rotation值 依次输入程序;\n\n");
	printf("\t3、共需输入三次，第三次输入完成后程序会计算主世界末地传送门并显示;\n\n\n");
	printf("计算得出的位置可能有偏差，扔出的三点相隔的距离要适当\n\n");
	printf("如果输入的数据出现问题可能导致计算结果出现错误，例如出现\"inf\"\n\n\n\n");

	int choose1;
	printf("输入1开始，0退出:");
	cin >> choose1;
	if (choose1 != 1) {
		exit(1);
	}
	system("cls");

FLAG:
	//存放三点的x轴坐标，z轴坐标，y_rotation值
	float throw_point[3][4];

	//循环存放用户输入的数据
	for (int i = 0; i < 3; i++) {
		printf("输入第%i个点的数据(x轴坐标，z轴坐标，y_rotation值)\n", i + 1);
		printf("x轴坐标:");
		cin >> throw_point[i][0];
		printf("z轴坐标:");
		cin >> throw_point[i][1];
		printf("y_rotation值:");
		cin >> throw_point[i][2];

		system("cls");
	}

	//备份原坐标数组
	float point[3][3] = { {throw_point[0][0], throw_point[0][1], throw_point[0][2]},
						  {throw_point[1][0], throw_point[1][1], throw_point[1][2]},
						  {throw_point[2][0], throw_point[2][1], throw_point[2][2]} };

	//转化为两点坐标并存入新数组
	float* point_g1 = Auxiliary_point(throw_point[0]);
	float* point_g2 = Auxiliary_point(throw_point[1]);
	float* point_g3 = Auxiliary_point(throw_point[2]);

	//储存解析式参数
	float *analytic_parameters1 = Analytical_calculation(point_g1);
	float *analytic_parameters2 = Analytical_calculation(point_g2);
	float *analytic_parameters3 = Analytical_calculation(point_g3);

	//计算三个解析式交点
	float line1_2[4] = { analytic_parameters1[0], analytic_parameters1[1],
						analytic_parameters2[0], analytic_parameters2[1]};
	float line1_3[4] = { analytic_parameters1[0], analytic_parameters1[1],
						analytic_parameters3[0], analytic_parameters3[1] };
	float line2_3[4] = { analytic_parameters2[0], analytic_parameters2[1],
						analytic_parameters3[0], analytic_parameters3[1] };

	float* its_line1_2 = Intersection_calculation(line1_2);
	float* its_line1_3 = Intersection_calculation(line1_3);
	float* its_line2_3 = Intersection_calculation(line2_3);

	float x_arr[3] = { its_line1_2[0], its_line1_3[0], its_line2_3[0] };
	float z_arr[3] = { its_line1_2[1], its_line1_3[1], its_line2_3[1] };
	
	float X = (max(x_arr, len(x_arr)) + min(x_arr, len(x_arr))) / 2;
	float Z = (max(z_arr, len(z_arr)) + min(z_arr, len(z_arr))) / 2;

	//用户交互界面
	system("cls");
	printf("\n————————————————————————调试信息————————————————————————\n");
	printf("输入三点:\n");
	for (int j = 0; j < 3; j++) {
		printf("\t第%i个点:\t\tX:%.2lf\t\tZ:%.2lf\t\ty_rotation:%.2lf\n", j + 1, point[j][0], point[j][1], point[j][2]);
	}
	

	printf("\n解析式:\n");
	printf("\ty=%.2lfx%+.2lf\n", analytic_parameters1[0], analytic_parameters1[1]);
	printf("\ty=%.2lfx%+.2lf\n", analytic_parameters2[0], analytic_parameters2[1]);
	printf("\ty=%.2lfx%+.2lf\n", analytic_parameters3[0], analytic_parameters3[1]);

	printf("\n交点坐标:\n");
	printf("\t直线1与直线2交点:(%.2lf, %.2lf)\n", its_line1_2[0], its_line1_2[1]);
	printf("\t直线1与直线3交点:(%.2lf, %.2lf)\n", its_line1_3[0], its_line1_3[1]);
	printf("\t直线2与直线3交点:(%.2lf, %.2lf)\n", its_line2_3[0], its_line2_3[1]);
	
	printf("\n————————————————————————计算结果————————————————————————\n");
	printf("\n目标位于: X=%.2lf, Z=%.2lf\n\n", X, Z);
	printf("传送命令: /tp @s %.2lf ~ %.2lf\n", X, Z);

	int choose2;
	printf("\n\n\n\n输入1重启，输入0退出:");
	cin >> choose2;

	if (choose2 == 1) {
		system("cls");
		goto FLAG;
	}
	else {
		system("pause");
		exit(1);
	}

}