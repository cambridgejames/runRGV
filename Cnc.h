// *----encoding: UTF-16 LE with BOM----*

#pragma once

#include <iostream>
#include "Rgv.h"
using namespace std;

class Cnc {
private:
	bool isDuang;				// 是否为宕机状态
	int fixTime;				// 修好需要的时间
	int number;					// CNC的编号
	int beginTime, endTime;		// 指令的开始和结束时间
	Rgv *rgv;
private:
	int processTime;			// CNC加工一个零件需要的时间
public:
	Cnc();
	Cnc(int IprocessTimem, Rgv* Irgv);
	~Cnc();
};