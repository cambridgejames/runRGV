// *----encoding: UTF-16 LE with BOM----*

#pragma once

#include <iostream>
//#include "Rgv.h"
using namespace std;

extern class Rgv;

class Cnc {
private:
	bool isDuang;// 是否为宕机状态
	int state;
	int currentComponent;
	int fixTime;				// 修好需要的时间
	int number;					// CNC的编号
	int processTime;			// CNC加工一个零件需要的时间
	int systemTime;				// 系统时间
	int beginTime, endTime;		// 指令的开始和结束时间
	Rgv *rgv;

public:
	Cnc();
	Cnc(int IprocessTimem, Rgv* Irgv);
	~Cnc();
	int onUpdate();
	int getCurrentState();
	int getCurrentComponent();
	void onSystemTimeChange(int systemTime);
};