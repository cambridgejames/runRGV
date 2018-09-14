// *----encoding: UTF-16 LE with BOM----*

#pragma once

#include "stdafx.h"
#include "Rgv.h"
#include <iostream>
#include <math.h>
using namespace std;

Rgv::Rgv() {
	Rgv(0, 0, 0, 0, 0, 0);
}

Rgv::Rgv(int Itime1, int Itime2, int Itime3, int ItimeUper1, int ItimeUper2, int ItimeCleaner): time1(Itime1), time2(Itime2), time3(Itime3), timeUper1(ItimeUper1), timeUper2(ItimeUper2), timeCleaner(ItimeCleaner), current(0), beginTime(0), endTime(0) {
	for (int i = 0; i < 8; i++) {
		this->taskList[i].number = i + 1;
		this->taskList[i].launchTime = -1;
	}

	cout << "创建了1个RGV实例：" << endl;
	cout << ">>移动1个单位所需的时间： " << this->time1 << endl;
	cout << ">>移动2个单位所需的时间： " << this->time2 << endl;
	cout << ">>移动3个单位所需的时间： " << this->time3 << endl;
	cout << ">>单数序号CNC上下料所需时间： " << this->timeUper1 << endl;
	cout << ">>双数序号CNC上下料所需时间： " << this->timeUper2 << endl;
	cout << ">>清洗物料所需时间： " << this->timeCleaner << endl;
	cout << ">>本RGV实例的当前位置：" << this->current << endl;
	cout << ">>消息列表：" << endl;
	cout << "\tCNC序号：";
	for (int i = 0; i < 8; i++) {
		cout << "\t" << this->taskList[i].number;
	}
	cout << endl;
	cout << "\t发起时间：";
	for (int i = 0; i < 8; i++) {
		cout << "\t" << this->taskList[i].launchTime;
	}
	cout << endl;
}

Rgv::~Rgv() {
	cout << "删除了1个RGV实例" << endl;
}

int Rgv::onMove(int number) {
	int object = (number - 1) / 2;
	int time = 0;
	switch(abs(object - this->current)) {
		case 0: time = 0;
		case 1: time = this->time1;
		case 2: time = this->time2;
		default: time = this->time3;
	}
	this->current = object;
	return time;
}

int Rgv::onUpdate(int number) {
	if ((number / 2) == 0) {
		return this->timeUper1;
	} else {
		return this->timeUper2;
	}
}

int Rgv::onWash() {
	return this->timeCleaner;
}

bool Rgv::push(int object) {
	//move(object) + timeUper;
	return true;
}

bool Rgv::pull() {
	cout << "RGV正在取指..." << endl;
	for(int i = 0; i < 8; i++) {

	}
	return true;
}