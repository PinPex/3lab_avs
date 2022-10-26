#pragma once
#include <time.h>
#include <windows.h>
#include <chrono>

using namespace std;

/** Use to init the clock */
//#define TIMER_INIT \
    LARGE_INTEGER frequency; \
    LARGE_INTEGER t1,t2; \
    double elapsedTime; \
    QueryPerformanceFrequency(&frequency);


/** Use to start the performance timer */
//#define TIMER_START QueryPerformanceCounter(&t1);

/** Use to stop the performance timer and output the result to the standard stream. Less verbose than \c TIMER_STOP_VERBOSE */
//#define TIMER_STOP \
    QueryPerformanceCounter(&t2); \
    elapsedTime=(double)(t2.QuadPart-t1.QuadPart)/frequency.QuadPart; \
    //std::wcout<<elapsedTime<<L" sec"<<endl;

struct memory {
	double write;
	double read;
	int lNum;
};


double time_calc(clock_t start, clock_t stop) {
	return (double)(stop - start) / (double)CLOCKS_PER_SEC;
}
