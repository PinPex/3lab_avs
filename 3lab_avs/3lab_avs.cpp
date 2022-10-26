#define _CRT_SECURE_NO_WARNINGS

#include "strParse.h"
#include "calcRAM.h"
#include "HDDorSSD.h"
#include "flash.h"
#include "comThings.h"
#include <fstream>
#include <math.h>
#include <iomanip>
#include <vector>

int launchNum = 1;

memory testMem(string memType, long long blSize) {
	srand(time(0));

	memory result;

	if (memType == "RAM") {
		result = int_RAM(blSize);
	}
	if (memType == "HDD" || memType == "SSD") {
		result = int_HDD_SSD(blSize);
	}
	if (memType == "flash") {
		string path = "D://";
		result = int_flash(blSize, path);
		cout << result.write << " " << result.read << endl;
	}

	return result;

}

memory sumM(vector<memory> results) {
	memory sum;
	sum.write = 0;
	sum.read = 0;
	for (int i = 0; i < results.size(); ++i) {
		sum.write += results[i].write;
		sum.read += results[i].read;
	}
	return sum;
}

memory avTime(vector<memory> results) {
	memory sum;
	sum = sumM(results);
	sum.write /= results.size();
	sum.read /= results.size();
	return sum;
}

memory disper(vector<memory> results) {
	memory disp;
	disp.write = 0;
	disp.read = 0;
	for (int i = 0; i < results.size(); ++i) {
		disp.write += pow(results[i].write - avTime(results).write, 2);
		disp.read += pow(results[i].read - avTime(results).read, 2);
	}
	return disp;
}



void writeCSV(string memType, long long blSize, string elemType, memory result,
	memory avtime, memory avband, memory abs, memory rel) {
	ofstream file;
	file.open("results.csv", std::ios::app);
	file
		<< 
		setprecision(9)
		<<
		memType
		<< ";"
		<< blSize //
		<< ";"
		<< elemType //ElementsType
		<< ";"
		<< launchNum
		<< ";"
		<< "chrono()" //Timer
		<< ";"
		<< result.write // WriteTime
		<< ";"
		<< avtime.write // AverangeWriteTime
		<< ";"
		<< avband.write// WriteBandwidth
		<< ";"
		<< abs.write
		<< ";"
		<< rel.write
		<< ";"
		<< result.read // ReadTime
		<< ";"
		<< avtime.read // AverangeReadTime
		<< ";"
		<< avband.read// ReadBandwidth
		<< ";"
		<< abs.read
		<< ";"
		<< rel.read
		<< endl;

}

void Calc(vector<memory> results, int* caches, string memType, int* mb4, int count) {
	for (int i = 0; i < count; ++i) {
		memory sum = sumM(results);
		cout << fixed << sum.write << " " << sum.read << endl << endl;

		memory avtime = avTime(results);
		cout << fixed << avtime.write << " " << avtime.read << endl << endl;

		memory avband;
		avband.write = caches[i] / avtime.write / 1024 / 1024;
		avband.read = caches[i] / avtime.read / 1024 / 1024;
		cout << fixed << avband.write << " " << avband.read << endl << endl;

		memory disp = disper(results);

		memory abs;
		abs.write = sqrt(disp.write / results.size());
		abs.read = sqrt(disp.read / results.size());
		/*abs.write = (avtime.write - sum.write) / (4 + i * 4);
		abs.read = (avtime.read - sum.read) / (4 + i * 4);*/
		cout << fixed << abs.write << " " << abs.read << endl << endl;

		memory rel;
		rel.write = abs.write / avtime.write * 10;
		rel.read = abs.read / avtime.read * 10;

		cout << rel.write << " " << rel.read << endl << endl << endl;
		if(mb4 != NULL) 
			writeCSV(memType, mb4[i], "int", results[i], avtime, avband, abs, rel);
		else
			writeCSV(memType, caches[i], "int", results[i], avtime, avband, abs, rel);
		launchNum++;
	}
}


int main() {
	int* caches = new int[5];
	caches[0] = 64;
	caches[1] = 320 * 1024;
	caches[2] = 2 * 1024 * 1024;
	caches[3] = 6 * 1024 * 1024;
	caches[4] = 30 * 1024 * 1024;
	cout << "RAM: " << endl;
	ofstream file;
	vector<memory> results;
	file.open("results.csv", std::ios::app);
	file << "MemoryType;BlockSize;ElementType;LaunchNum;Timer;WriteTime;AverageWriteTime;WriteBandwidth;AbsError(write);RelError(write);ReadTime;AverageReadTime;ReadBandwidth;AbsError(read);RelError(read);" << endl;
	for (int i = 0; i < 5; ++i) {
		results.push_back(testMem("RAM", caches[i]));
		//cout << setprecision(9) << result[0].write << " " << result[0].read << " " << result[1].write << " " << result[1].read << " " << result[2].write << " " << result[2].read << " " << result[3].write << " " << result[3].read << endl;
	}

	Calc(results, caches, "RAM", NULL, 5);

	vector<memory> results2;
	vector<memory> results3;
	//int mb4 = 4 * 1024 * 1024;
	int mb4[20];
	for (int i = 0; i < 20; ++i) {
		mb4[i] = 4 * 1024 * 1024 + i * 4 * 1024 * 1024;
	}

	for (int i = 0; i < 20; ++i) {
		results2.push_back(testMem("SSD", mb4[i]));
		results3.push_back(testMem("flash", mb4[i]));
		//cout << "Chlen" << endl;
		//cout << setprecision(9) << result[0].write << " " << result[0].read << " " << result[1].write << " " << result[1].read << " " << result[2].write << " " << result[2].read << " " << result[3].write << " " << result[3].read << endl;
	}
	Calc(results2, caches, "SSD", mb4, 20);
	Calc(results3, caches, "flash", mb4, 20);

}