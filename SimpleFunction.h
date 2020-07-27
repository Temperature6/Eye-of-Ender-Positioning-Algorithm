#pragma once
float max(float arr[], int len) {
	float max = arr[0];

	for (int i = 0; i < len; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

float min(float arr[], int len) {
	float min = arr[0];

	for (int j = 0; j < len; j++) {
		if (min > arr[j]) {
			min = arr[j];
		}
	}
	return min;
}

int len(float arr[]) {
	return sizeof(arr) / sizeof(arr[0]);
}

float avg(float arr[], int len)
{
	float sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum += arr[i];
	}
	return sum / len;
}