// *----encoding: UTF-16 LE with BOM----*

#pragma once

#include <iostream>
#include "Cnc.h"
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
	bool isUpdated;
	int time1, time2, time3;	// 移动1，2，3个单位需要的时间
	int timeUper1, timeUper2;	// 上下料时间
	int timeCleaner;			// 清洗时间
	int current;				// RGV的当前位置
	int currentCnc;
	int moveTime, updateTime, washTime;
	int systemTime;			// 系统时间
	int state;	// RGV的状态: 0-空闲,1-移动,2-上下料,3-清洗
	TaskNode taskList[8];		// RGV的请求缓存区
	Cnc* cnc[8];
public:
	int sumNew, sumDone, oldComponent;

private:
	bool onPull();	// 取请求并填充指令队列
	int onMove(int number);		// 返回值为消耗的时间
	int onUpdate(int number);
	int onWash();
	void showTaskList();
public:
	Rgv();
	Rgv(int Itime1, int Itime2, int Itime3, int ItimeUper1, int ItimeUper2, int ItimeCleaner);
	~Rgv();
	bool onPush(int number);
	int onRegister(Cnc* cnc);
	void onSystemTimeChange(int systemTime);
};