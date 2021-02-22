#pragma once
#include <vector>
using namespace std;

float max(vector<float>vec)
{
	float m = vec[0];
	for (unsigned int i = 0; i < 3; i++)
	{
		if (vec[i] > m)
			m = vec[i];
	}
	return m;
}

float min(vector<float>vec)
{
	float m = vec[0];
	for (unsigned int i = 0; i < 3; i++)
	{
		if (vec[i] < m)
			m = vec[i];
	}
	return m;
}

float avg(vector<float>vec)
{
	float sum = 0;
	for (unsigned int i = 0; i < vec.size(); i++)
		sum += vec[i];
	return sum / 3;
}
