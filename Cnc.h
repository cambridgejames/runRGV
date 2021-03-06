// *----encoding: UTF-16 LE with BOM----*

#pragma once

//#include "Rgv.h"
extern class Rgv;

#include <iostream>
#include <fstream>
using namespace std;

class Cnc {
private:
	bool isDuang;				// 本次加工是否会宕机
	bool isPushed;
	bool isLoged;
	int probability;
	int state;	// CNC的状态: 0-空闲,1-加工中,2-等待,3-故障
	int currentComponent;
	int number;					// CNC的编号
	int processTime;			// CNC加工一个零件需要的时间
	int systemTime;				// 系统时间
	int runTime, duangTime;
	Rgv *rgv;
	ofstream outFileStart, outFileEnd, outFileError;
public:
	int sumDuang;

private:
	bool isDuangRandom();
public:
	Cnc();
	Cnc(int IprocessTime, int Iprobability, Rgv* Irgv);
	~Cnc();
	int getCurrentState();
	int getCurrentComponent();
	int onUpdate(int component);
	void onSystemTimeChange(int systemTime);
};
