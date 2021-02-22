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
	system("title ĩӰ֮�۶�λ�㷨");
	printf("���������������������ĩ�ش����ŵ����ꡣ\n\n");
	printf("ʹ�÷�����\n");
	printf("\t1������Ҫ�׳�һ��ĩӰ֮�ۣ���׼����׼ĩӰ֮������λ��;\n\n");
	printf("\t2�����ֲ���������ʱ�� X�����꣬Z�����꣬y_rotationֵ �����������;\n\n");
	printf("\t3�������������Σ�������������ɺ��������������ĩ�ش����Ų���ʾ;\n\n\n");
	printf("����ó���λ�ÿ�����ƫ��ӳ�����������ľ���Ҫ�ʵ�\n\n");
	printf("�����������ݳ���������ܵ��¼��������ִ����������\"inf\"\n\n\n\n");

	int choose;
	printf("ѡ�����:\n");
	printf("\t1����> ��ʼ\n");
	printf("\t2����> ����Ƶ�̳�\n");
	printf("\t3����> ��GitHub�ֿ���ַ\n");
	printf("\t0����> �˳�\n:");
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
		printf("��զ������nie?\n");
		goto START;
		break;
	}
	system("cls");

	//��������x�����꣬z�����꣬y_rotationֵ
	float point[3][4];

	//ѭ������û����������
	for (int i = 0; i < 3; i++)
	{
		printf("���������%i���������(x�����꣬z�����꣬y_rotationֵ)������֮��ʹ�ÿո��Tab����\n", i + 1);
		scanf_s("%f %f %f", &point[i][0], &point[i][1], &point[i][2]);
		system("cls");
	}

	//��ӡ����Ϣ
	system("cls");
	printf("\n������������������������������������������������������Ϣ������������������������������������������������\n");
	printf("��������:\n");
	for (int j = 0; j < 3; j++) {
		printf("\t��%i����:\t\tX:%.2lf\t\tZ:%.2lf\t\ty_rotation:%.2lf\n", j + 1, point[j][0], point[j][1], point[j][2]);
	}
	//ת��Ϊ�������겢����������
	vector <float> PointGroup1 = Auxiliary_point(point[0]);
	vector <float> PointGroup2 = Auxiliary_point(point[1]);
	vector <float> PointGroup3 = Auxiliary_point(point[2]);

	//�������ʽ����
	PointGroup1 = Analytical_calculation(PointGroup1);
	PointGroup2 = Analytical_calculation(PointGroup2);
	PointGroup3 = Analytical_calculation(PointGroup3);
		//��ӡ����ʽ
	printf("\n����ʽ:\n");
	printf("\ty=%.2lfx%+.2lf\n", PointGroup1[0], PointGroup1[1]);
	printf("\ty=%.2lfx%+.2lf\n", PointGroup2[0], PointGroup2[1]);
	printf("\ty=%.2lfx%+.2lf\n", PointGroup3[0], PointGroup3[1]);
	//������������ʽ����
		//����ʽ����һ��
	vector <float> line12 = { PointGroup1[0], PointGroup1[1], PointGroup2[0], PointGroup2[1] };
	vector <float> line13 = { PointGroup1[0], PointGroup1[1], PointGroup3[0], PointGroup3[1] };
	vector <float> line23 = { PointGroup2[0], PointGroup2[1], PointGroup3[0], PointGroup3[1] };
		//ִ�м���,��ʱ�����������(ǰ����)�Ѿ�����˽�������
	line12 = Intersection_calculation(line12);
	line13 = Intersection_calculation(line13);
	line23 = Intersection_calculation(line23);
		//��ӡ��������
	printf("\n��������:\n");
	printf("\tֱ��1��ֱ��2����:(%.2lf, %.2lf)\n", line12[0], line12[1]);
	printf("\tֱ��1��ֱ��3����:(%.2lf, %.2lf)\n", line13[0], line13[1]);
	printf("\tֱ��2��ֱ��3����:(%.2lf, %.2lf)\n", line23[0], line23[1]);

	//����������
		//��X��Z������ֱ��Ϊ����
	vector <float> x_pos = { line12[0], line13[0], line23[0] };
	vector <float> z_pos = { line12[1], line13[1], line23[1] };
		//Ǧ���ߺ�ˮƽ���ƽ��
	float _X = (max(x_pos) + min(x_pos)) / 2;
	float _Z = (max(z_pos) + min(z_pos)) / 2;
		//����ƽ��
	float X = avg(x_pos);
	float Z = avg(z_pos);
		//��ӡ���
	printf("\n������������������������������������������������������������������������������������������������������\n");
	printf("\nĿ��λ��(Ǧ���ߺ�ˮƽ����е�): X=%.2lf, Z=%.2lf\n", _X, _Z);
	printf("��������(Ǧ���ߺ�ˮƽ����е�): /tp @s %.2lf ~ %.2lf\n\n", _X, _Z);
	printf("\nĿ��λ��(�������������ƽ����): X=%.2lf, Z=%.2lf\n", X, Z);
	printf("��������(�������������ƽ����): /tp @s %.2lf ~ %.2lf\n\n", X, Z);
	printf("�����������\n");
	system("pause");
	goto START;
}

float radians(float a) {
	//radians:�Ƕ�ת����
	//a:����Ƕ�
	return a * (Pi / 180);
}

vector <float> Auxiliary_point(float* arr) {
	//Auxiliary_point:�����㣬��һ�㼰�䷽���ת��Ϊ��������
	//*arr:����ָ�룬���ָ��

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