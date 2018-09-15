// *----encoding: UTF-8----*

#pragma once

#include "stdafx.h"
#include <iostream>
#include "Rgv.h"
#include "Cnc.h"
using namespace std;

int main()
{
	Rgv *rgv = new Rgv(20, 33, 46, 28, 31, 25);
	Cnc *cnc1 = new Cnc(560, rgv);
	Cnc *cnc2 = new Cnc(560, rgv);
	Cnc *cnc3 = new Cnc(560, rgv);
	Cnc *cnc4 = new Cnc(560, rgv);
	Cnc *cnc5 = new Cnc(560, rgv);
	Cnc *cnc6 = new Cnc(560, rgv);
	Cnc *cnc7 = new Cnc(560, rgv);
	Cnc *cnc8 = new Cnc(560, rgv);

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

	cout << "\n\n最终加工的零件个数为：" << rgv->sum << "个\n\n" << endl;

	delete cnc1;
	delete cnc2;
	delete cnc3;
	delete cnc4;
	delete cnc5;
	delete cnc6;
	delete cnc7;
	delete cnc8;
	delete rgv;
    return 0;
}

