// *----encoding: UTF-16 LE with BOM----*

#pragma once

#include "stdafx.h"
#include "Cnc.h"
#include "Rgv.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

Cnc::Cnc() {
	Cnc(0, 0, NULL);
}

Cnc::Cnc(int IprocessTime, int Iprobability, Rgv* Irgv): processTime(IprocessTime), isDuang(false), isPushed(false), probability(Iprobability), state(0), systemTime(0), runTime(0), duangTime(0), rgv(Irgv), sumDuang(0) {
	number = rgv->onRegister(this);

	cout << "创建了1个CNC实例：" << endl;
	cout << ">>本实例的故障概率为：" << probability << endl;
	cout << ">>本实例在RGV中注册的编号为： #" << number << endl;
	cout << ">>本实例加工一个零件需要的时间： " << processTime << "s" << endl;
	cout << endl;

	srand((unsigned)time(NULL));

	outFileStart.open("solution_Start.txt", ios::trunc);
	outFileEnd.open("solution_End.txt", ios::trunc);
	outFileError.open("solution_Error.txt", ios::trunc);
	outFileStart.close();
	outFileEnd.close();
	outFileError.close();
	outFileStart.open("solution_Start.txt", ios::app);
	outFileEnd.open("solution_End.txt", ios::app);
	outFileError.open("solution_Error.txt", ios::app);
}

Cnc::~Cnc() {
	cout << "删除了编号为 #" << number << " 的CNC实例" << endl;
	cout << endl;

	outFileStart.close();
	outFileEnd.close();
	outFileError.close();
}

bool Cnc::isDuangRandom() {
	if ((rand() % 100 + 1) <= probability) {
		runTime = rand() % processTime;
		duangTime = rand() % 601 + 600;
		sumDuang++;
		return true;
	} else {
		runTime = processTime;
		duangTime = 0;
		return false;
	}
}

int Cnc::getCurrentState() {
	return state;
}

int Cnc::getCurrentComponent() {
	return currentComponent;
}

int Cnc::onUpdate(int component) {
	isPushed = false;
	isLoged = false;
	if (currentComponent != 0) {
		// 第一组
		//outFileEnd << currentComponent << '\t' << number << '\t' << systemTime - (currentComponent % 2 == 0 ? 31 : 28) - 3 + currentComponent / 2 * 2 + (currentComponent - 1) / 2 * 1 << endl;

		// 第二组
		//outFileEnd << currentComponent << '\t' << number << '\t' << systemTime - (currentComponent % 2 == 0 ? 35 : 30) - 5 + currentComponent / 2 * 4 + (currentComponent - 1) / 2 * 1 << endl;

		// 第三组
		outFileEnd << currentComponent << '\t' << number << '\t' << systemTime - (currentComponent % 2 == 0 ? 32 : 27) - 5 + currentComponent / 2 * 4 + (currentComponent - 1) / 2 * 1 << endl;
	}
	currentComponent = component;
	isDuangRandom();
	//cout << "CNC #" << number << " ：已完成上下料，开始加工第" << currentComponent << "号零件" << endl;

	// 第一组
	//outFileStart << currentComponent << '\t' << number << '\t' << systemTime - (currentComponent % 2 == 0 ? 31 : 28) - 3 + currentComponent / 2 * 2 + (currentComponent - 1) / 2 * 1 << endl;

	// 第二组
	//outFileStart << currentComponent << '\t' << number << '\t' << systemTime - (currentComponent % 2 == 0 ? 35 : 30) - 5 + currentComponent / 2 * 4 + (currentComponent - 1) / 2 * 1 << endl;

	// 第三组
	outFileStart << currentComponent << '\t' << number << '\t' << systemTime - (currentComponent % 2 == 0 ? 32 : 27) - 5 + currentComponent / 2 * 4 + (currentComponent - 1) / 2 * 1 << endl;

	return 0;
}

void Cnc::onSystemTimeChange(int systemTime) {
	this->systemTime = systemTime;

	int stateCache = -1;
	if (runTime > 0) {
		stateCache = 1;
		//cout << "CNC #" << number << " ：正在加工第" << currentComponent << "号零件" << endl;
		runTime--;
	} else if (runTime == 0 && duangTime > 0) {
		stateCache = 3;
		if (!isLoged) {
			isLoged = true;
			outFileError << currentComponent << '\t' << number << '\t' << systemTime << '\t' << systemTime + duangTime << endl;
		}
		//cout << "CNC #" << number << " ：出现故障，第" << currentComponent << "号零件报废，正在修理" << endl;
		currentComponent = 0;
		duangTime--;
	} else {
		if (!isPushed) {
			isPushed = true;
			rgv->onPush(number);
			//cout << "CNC #" << number << " ：已向RGV发送请求" << endl;
		}
		if (currentComponent == 0) {
			stateCache = 0;
			//cout << "CNC #" << number << " ：空闲，正在等待RGV上料" << endl;
		} else {
			stateCache = 2;
			//cout << "CNC #" << number << " ：第" << currentComponent << "号零件已加工完成，正在等待RGV上下料" << endl;
		}
	}

	state = stateCache;
}
