// *----encoding: UTF-16 LE with BOM-----*

#pragma once

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <fstream>
#include "Rgv.h"
#include "Cnc.h"
using namespace std;

int main() {
	// 第一组
	Rgv *rgv = new Rgv(20, 33, 46, 28, 31, 25);
	int probability = 0, processTime = 560;

	// 第二组
	/*Rgv *rgv = new Rgv(23, 41, 59, 30, 35, 30);
	int probability = 1, processTime = 580;*/

	// 第三组
	/*Rgv *rgv = new Rgv(18, 32, 46, 27, 32, 25);
	int probability = 1, processTime = 545;*/

	Cnc *cnc1 = new Cnc(processTime, probability, rgv);
	Cnc *cnc2 = new Cnc(processTime, probability, rgv);
	Cnc *cnc3 = new Cnc(processTime, probability, rgv);
	Cnc *cnc4 = new Cnc(processTime, probability, rgv);
	Cnc *cnc5 = new Cnc(processTime, probability, rgv);
	Cnc *cnc6 = new Cnc(processTime, probability, rgv);
	Cnc *cnc7 = new Cnc(processTime, probability, rgv);
	Cnc *cnc8 = new Cnc(processTime, probability, rgv);

	for (int systemTime = 0; systemTime < 28800; systemTime++) {
		cout << "System Time: " << systemTime << "s" << endl;

		cnc1->onSystemTimeChange(systemTime);
		cnc2->onSystemTimeChange(systemTime);
		cnc3->onSystemTimeChange(systemTime);
		cnc4->onSystemTimeChange(systemTime);
		cnc5->onSystemTimeChange(systemTime);
		cnc6->onSystemTimeChange(systemTime);
		cnc7->onSystemTimeChange(systemTime);
		cnc8->onSystemTimeChange(systemTime);
		rgv->onSystemTimeChange(systemTime);

		cout << endl;
	}

	cout << "\n\n最终加工的零件个数为：" << rgv->sumDone << "个\n\n" << endl;
	cout << "\n\n最终报废的零件个数为：" << cnc1->sumDuang + cnc2->sumDuang + cnc3->sumDuang + cnc4->sumDuang + cnc5->sumDuang + cnc6->sumDuang + cnc7->sumDuang + cnc8->sumDuang << "个\n\n" << endl;

	delete cnc1;
	delete cnc2;
	delete cnc3;
	delete cnc4;
	delete cnc5;
	delete cnc6;
	delete cnc7;
	delete cnc8;
	delete rgv;

	while(true) {	// 用于在运行结束后响铃吵醒用户查看数据
		Beep(1000,80);
		Sleep(80);
	}

    return 0;
}

