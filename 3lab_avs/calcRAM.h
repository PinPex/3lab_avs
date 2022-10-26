#pragma once
#include <iostream>
#include <ctime>
#include "comThings.h"


memory int_RAM(long long blSize) {
	memory time;
	int n = blSize / sizeof(int);
	int* mas = new int[n];
	//clock_t start, stop;

	auto start = chrono::steady_clock::now();
	//start = clock();
	for (int i = 0; i < n; ++i) {
		mas[i] = 123217512;
	}
	//stop = elapsedTime;
	auto end = chrono::steady_clock::now();
	time.write = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000000.0;;

	//StartCounter();
	//start = clock();
	auto start1 = chrono::steady_clock::now();
	for (int i = 0; i < n; ++i) {
		mas[i];
	}
	auto end1 = chrono::steady_clock::now();
	//stop = elapsedTime;
	time.read = chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() / 1000000000.0;
	delete[] mas;
	return time;
}

memory double_RAM(long long blSize) {
	memory time;
	int n = blSize / sizeof(int);
	double* mas = new double[n];
	clock_t start, stop;
	start = clock();
	for (int i = 0; i < n; ++i) {
		mas[i] = 3512367125361.241241546712547612;
	}
	stop = clock();
	time.write = time_calc(start, stop);

	start = clock();
	for (int i = 0; i < n; ++i) {
		mas[i];
	}
	stop = clock();
	time.read = time_calc(start, stop);
	return time;
}

memory float_RAM(long long blSize) {
	memory time;
	int n = blSize / sizeof(int);
	float* mas = new float[n];
	clock_t start, stop;
	start = clock();
	for (int i = 0; i < n; ++i) {
		mas[i] = 3512367125361.241241546712547612;
	}
	stop = clock();
	time.write = time_calc(start, stop);
	start = clock();
	for (int i = 0; i < n; ++i) {
		mas[i];
	}
	stop = clock();
	time.read = time_calc(start, stop);
	return time;
}

memory ll_RAM(long long blSize) {
	memory time;
	int n = blSize / sizeof(int);
	long long* mas = new long long[n];
	clock_t start, stop;
	start = clock();
	for (int i = 0; i < n; ++i) {
		mas[i] = 123217512;
	}
	stop = clock();
	time.write = time_calc(start, stop);
	start = clock();
	for (int i = 0; i < n; ++i) {
		mas[i];
	}
	stop = clock();
	time.read = time_calc(start, stop);
	return time;
}