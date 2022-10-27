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

//int launchNum = 1;

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
		//cout << result.write << " " << result.read << endl;
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

vector<memory> absolute(vector<memory> results) {
	vector<memory> abs(results.size());
	for (int i = 0; i < results.size(); ++i) {
		abs[i].write = fabsl(results[i].write - avTime(results).write);
		abs[i].read = fabsl(results[i].read - avTime(results).read);
	}
	return abs;
}



void writeCSV(string memType, long long blSize, string elemType,int launchNum, memory result,
	memory avtime, memory avband, vector<memory> abs, vector<memory> rel) {
	ofstream file;
	file.open("results.csv", std::ios::app);
	file
		<< 
		setprecision(9)
		<<
		memType
		<< ";"
		<< blSize / 1024.0 / 1024.0 //
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
		<< abs[launchNum - 1].write
		<< ";"
		<< rel[launchNum - 1].write
		<< ";"
		<< result.read // ReadTime
		<< ";"
		<< avtime.read // AverangeReadTime
		<< ";"
		<< avband.read// ReadBandwidth
		<< ";"
		<< abs[launchNum - 1].read
		<< ";"
		<< rel[launchNum - 1].read
		<< endl;

}

void Calc_cach(vector<memory> results, long long* caches, string memType) {
	for (int i = 0; i < results.size(); ++i) {
		memory sum = sumM(results);
		//cout << fixed << sum.write << " " << sum.read << endl << endl;

		memory avtime = avTime(results);
		//cout << "Averenge time" << endl;
		//cout << fixed << avtime.write << " " << avtime.read << endl;

		memory avband;
		//cout << (double)(caches[i]) << endl;
		avband.write = (double)(caches[i]) / (double)(avtime.write) / 1024.0 / 1024.0;
		avband.read = (double)(caches[i]) / (double)(avtime.read) / 1024.0 / 1024.0;
		//cout << "Band" << endl;
		//cout << fixed << avband.write << " " << avband.read << endl;

		//memory disp = disper(results);

		vector<memory> abs = absolute(results);
		//abs.write = sqrt(disp.write / results.size());
		//abs.read = sqrt(disp.read / results.size());
		/*abs.write = (avtime.write - sum.write) / (4 + i * 4);
		abs.read = (avtime.read - sum.read) / (4 + i * 4);*/
		//cout << fixed << abs.write << " " << abs.read << endl << endl;

		vector<memory> rel(results.size());
		for (int i = 0; i < results.size(); ++i) {
			rel[i].write = double(abs[i].write) / double(avtime.write) * 100.0;
			rel[i].read = double(abs[i].read) / double(avtime.read) * 100.0;
			
		}
		for (auto i : rel) {
			cout << i.write << " "  << i.read << endl;
		}
		//cout << rel.write << " " << rel.read << endl << endl << endl;
		writeCSV(memType, caches[i], "int", i + 1, results[i], avtime, avband, abs, rel);
	}
}

void Calc_mb(vector<memory> results, long long* mb4, string memType) {
	for (int i = 0; i < results.size(); ++i) {
		memory sum = sumM(results);
		//cout << fixed << sum.write << " " << sum.read << endl << endl;

		memory avtime = avTime(results);
		//cout << "Averenge time" << endl;
		//cout << fixed << avtime.write << " " << avtime.read << endl;

		memory avband;
		//cout << (double)(mb4[i]) << endl;
		avband.write = (double)(mb4[i]) / (double)(avtime.write) / 1024.0 / 1024.0;
		avband.read = (double)(mb4[i]) / (double)(avtime.read) / 1024.0 / 1024.0;
		//cout << "Band" << endl;
		//cout << fixed << avband.write << " " << avband.read << endl;

		//memory disp = disper(results);

		vector<memory> abs = absolute(results);
		//abs.write = sqrt(disp.write / results.size());
		//abs.read = sqrt(disp.read / results.size());
		/*abs.write = (avtime.write - sum.write) / (4 + i * 4);
		abs.read = (avtime.read - sum.read) / (4 + i * 4);*/
		//cout << fixed << abs.write << " " << abs.read << endl << endl;

		vector<memory> rel(results.size());
		for (int i = 0; i < results.size(); ++i) {
			rel[i].write = double(abs[i].write) / double(avtime.write) * 100.0;
			rel[i].read = double(abs[i].read) / double(avtime.read) * 100.0;
		}

		for (auto i : rel) {
			cout << i.write << " " << i.read << endl;
		}
		//rel.write = abs.write / avtime.write * 100;
		//rel.read = abs.read / avtime.read * 100;
		//cout << "Relative" << endl;
		//cout << rel.write << " " << rel.read << endl;
		writeCSV(memType, mb4[i], "int", i + 1, results[i], avtime, avband, abs, rel);
	}
}


int main() {
	long long* caches = new long long[5];
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

	Calc_cach(results, caches, "RAM");
	//launchNum = 1;

	vector<memory> results2;
	vector<memory> results3;
	//int mb4 = 4 * 1024 * 1024;
	long long mb4[20];
	for (int i = 0; i < 20; ++i) {
		mb4[i] = 4 * 1024 * 1024 + (long long)i * 4 * 1024 * 1024;
	}

	for (int i = 0; i < 20; ++i) {
		results2.push_back(testMem("SSD", mb4[i]));
		//cout << "Chlen" << endl;
		//cout << setprecision(9) << result[0].write << " " << result[0].read << " " << result[1].write << " " << result[1].read << " " << result[2].write << " " << result[2].read << " " << result[3].write << " " << result[3].read << endl;
	}
	//launchNum = 1;
	for (int i = 0; i < 20; ++i) {
		results3.push_back(testMem("flash", mb4[i]));
		//cout << "Chlen" << endl;
		//cout << setprecision(9) << result[0].write << " " << result[0].read << " " << result[1].write << " " << result[1].read << " " << result[2].write << " " << result[2].read << " " << result[3].write << " " << result[3].read << endl;
	}
	//launchNum = 1;
	Calc_mb(results2, mb4, "SSD");
	Calc_mb(results3, mb4, "flash");

}