#pragma once
#include "comThings.h"
#include <stdio.h>
#include <cstdio>

memory int_HDD_SSD(long long blSize) {
	memory time;
	FILE* file = fopen("1.dat", "wb");
	int n = blSize / sizeof(int);
	int* mas = new int[n];
	for (int i = 0; i < n; ++i) {
		mas[i] = 123217512;
	}
	//clock_t start, stop;
	//StartCounter();
	//start = clock();
	auto start = chrono::steady_clock::now();
	fwrite(mas, sizeof(int), n, file);
	auto end = chrono::steady_clock::now();
	
	
	
	//stop = elapsedTime;
	fclose(file);

	file = fopen("1.dat", "rb");
	time.write = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000000.0;
	mas = new int[n];
	//StartCounter();
	//start = clock();
	auto start1 = chrono::steady_clock::now();
	fread(mas, sizeof(int), n, file);
	auto end1 = chrono::steady_clock::now();

	//stop = elapsedTime;
	fclose(file);
	time.read = chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() / 1000000000.0;
	remove("1.dat");
	delete[] mas;
	return time;
}

memory double_HDD_SSD(long long blSize) {
	memory time;
	FILE* file = fopen("1.dat", "wb");
	int n = blSize / sizeof(int);
	double* mas = new double[n];
	for (int i = 0; i < n; ++i) {
		mas[i] = 3512367125361.241241546712547612;
	}
	clock_t start, stop;

	start = clock();
	fwrite(mas, sizeof(double), n, file);
	stop = clock();
	fclose(file);
	time.write = time_calc(start, stop);
	mas = new double[n];
	file = fopen("1.dat", "rb");
	start = clock();
	fread(mas, sizeof(double), n, file);
	stop = clock();
	fclose(file);
	time.read = time_calc(start, stop);
	remove("1.dat");
	return time;
}

memory float_HDD_SSD(long long blSize) {
	memory time;
	FILE* file = fopen("1.dat", "wb");
	int n = blSize / sizeof(int);
	float* mas = new float[n];
	for (int i = 0; i < n; ++i) {
		mas[i] = 3512367125361.241241546712547612;
	}
	clock_t start, stop;

	start = clock();
	fwrite(mas, sizeof(float), n, file);
	stop = clock();
	fclose(file);
	time.write = time_calc(start, stop);
	mas = new float[n];
	file = fopen("1.dat", "rb");
	start = clock();
	fread(mas, sizeof(float), n, file);
	stop = clock();
	fclose(file);
	time.read = time_calc(start, stop);
	remove("1.dat");
	return time;
}

memory ll_HDD_SSD(long long blSize) {
	memory time;
	FILE* file = fopen("1.dat", "wb");
	int n = blSize / sizeof(int);
	long long* mas = new long long[n];
	for (int i = 0; i < n; ++i) {
		mas[i] = 123217512;
	}
	clock_t start, stop;

	start = clock();
	fwrite(mas, sizeof(long long), n, file);
	stop = clock();
	fclose(file);
	time.write = time_calc(start, stop);

	mas = new long long[n];
	file = fopen("1.dat", "rb");
	start = clock();
	fread(mas, sizeof(long long), n, file);
	stop = clock();
	fclose(file);
	time.read = time_calc(start, stop);
	remove("1.dat");
	return time;
}