// *----encoding: UTF-16 LE with BOM----*

#pragma once

#include <iostream>
using namespace std;

struct TaskNode {
	int number;					// CNC编号
	int launchTime;				// 请求时的系统时间
	TaskNode() {};
	TaskNode(int number, int launchTime) {
		this->number = number;
		this->launchTime = launchTime;
	};
};

class Rgv {
private:
	int current;				// RGV的当前位置
	int beginTime, endTime;		// 指令的开始和结束时间
	TaskNode taskList[8];		// RGV的指令缓存区
public:
	int time1, time2, time3;	// 移动1，2，3个单位需要的时间
	int timeUper1, timeUper2;	// 上下料时间
	int timeCleaner;			// 清洗时间

private:						// 返回值为消耗的时间
	int onMove(int number);
	int onUpdate(int number);
	int onWash();
public:
	Rgv();
	Rgv(int Itime1, int Itime2, int Itime3, int ItimeUper1, int ItimeUper2, int ItimeCleaner);
	~Rgv();
	bool push(int object);
	bool pull();
};