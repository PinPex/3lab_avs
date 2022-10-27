#pragma once
#include <iostream>
#include "comThings.h"
#include <stdio.h>
#include <cstdio>
#include <fstream>

memory int_flash(long long blSize, string pathFlash) {
	memory time;
	pathFlash += "1.dat";
	FILE* file = fopen(pathFlash.c_str(), "wb");
	if (!file) {
		time.write = 0;
		time.read = 0;
		cout << "Error, flash is absent" << endl;
		return time;
	}
	//std::fstream file;
	//file.open(pathFlash, std::ios::app | std::ios::binary);

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
	//fwrite(mas, sizeof(int), n, file);
	auto end = chrono::steady_clock::now();

	//stop = elapsedTime;


	fclose(file);

	time.write = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1000000000.0;
	mas = new int[n];
	file = fopen(pathFlash.c_str(), "rb");

	//StartCounter();
	//start = clock();

	auto start1 = chrono::steady_clock::now();
	fread(mas, sizeof(int), n, file);
	//fread(mas, sizeof(int), n, file);
	auto end1 = chrono::steady_clock::now();

	//stop = elapsedTime;


	fclose(file);
	time.read = chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() / 1000000000.0;
	remove(pathFlash.c_str());
	//file.close();
	delete[] mas;
	return time;
}

memory double_flash(long long blSize, string pathFlash) {
	memory time;
	pathFlash += "1.dat";
	FILE* file = fopen(pathFlash.c_str(), "wb");
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
	file = fopen(pathFlash.c_str(), "rb");
	start = clock();
	fread(mas, sizeof(double), n, file);
	stop = clock();
	fclose(file);
	time.read = time_calc(start, stop);
	remove(pathFlash.c_str());
	delete[] mas;
	return time;
}

memory float_flash(long long blSize, string pathFlash) {
	memory time;
	pathFlash += "1.dat";
	FILE* file = fopen(pathFlash.c_str(), "wb");
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
	file = fopen(pathFlash.c_str(), "rb");
	start = clock();
	fread(mas, sizeof(float), n, file);
	stop = clock();
	fclose(file);
	time.read = time_calc(start, stop);
	remove(pathFlash.c_str());
	delete[] mas;
	return time;
}

memory ll_flash(long long blSize, string pathFlash) {
	memory time;
	pathFlash += "1.dat";
	FILE* file = fopen(pathFlash.c_str(), "wb");
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
	file = fopen(pathFlash.c_str(), "rb");
	start = clock();
	fread(mas, sizeof(long long), n, file);
	stop = clock();
	fclose(file);
	time.read = time_calc(start, stop);
	remove(pathFlash.c_str());
	delete[] mas;
	return time;
}