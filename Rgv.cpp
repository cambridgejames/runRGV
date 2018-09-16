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

Rgv::Rgv(int Itime1, int Itime2, int Itime3, int ItimeUper1, int ItimeUper2, int ItimeCleaner): time1(Itime1), time2(Itime2), time3(Itime3), timeUper1(ItimeUper1), timeUper2(ItimeUper2), timeCleaner(ItimeCleaner), current(0), systemTime(0), moveTime(0), updateTime(0), washTime(0), state(0), sumNew(0), sumDone(0), oldComponent(0) {
	for (int i = 0; i < 8; i++) {
		taskList[i].number = i + 1;
		taskList[i].launchTime = -2;
		cnc[i] = NULL;
	}

	cout << "创建了1个RGV实例：" << endl;
	cout << ">>移动1个单位所需的时间： " << time1 << "s" << endl;
	cout << ">>移动2个单位所需的时间： " << time2 << "s" << endl;
	cout << ">>移动3个单位所需的时间： " << time3 << "s" << endl;
	cout << ">>单数序号CNC上下料所需时间： " << timeUper1 << "s" << endl;
	cout << ">>双数序号CNC上下料所需时间： " << timeUper2 << "s" << endl;
	cout << ">>清洗物料所需时间： " << timeCleaner << "s" << endl;
	cout << ">>本RGV实例的当前位置：" << current << "s" << endl;
	cout << endl;
	
	showTaskList();
}

Rgv::~Rgv() {
	cout << "删除了1个RGV实例" << endl;
	cout << endl;
}

void Rgv::showTaskList() {
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
	cout << endl;
}

bool Rgv::onPush(int number) {
	taskList[number - 1].launchTime = systemTime;
	return true;
}

bool Rgv::onPull() {
	int objectIndex = -1;
	for (int i = 0; i < 8; i = i + 2) {
		if (taskList[i].launchTime != -1 && taskList[i + 1].launchTime != -1) {
			objectIndex = i + 1;
			taskList[i + 1].launchTime = -1;
			currentCnc = objectIndex;
			break;
		}
	}
	return objectIndex != -1;
}

int Rgv::onRegister(Cnc* cnc) {
	for (int i = 0; i < 8; i++) {
		if (taskList[i].launchTime == -2) {
			taskList[i].launchTime = 0;
			this->cnc[i] = cnc;
			return i + 1;
		}
	}
	return 0;
}

void Rgv::onSystemTimeChange(int systemTime) {
	this->systemTime = systemTime;

	switch(state) {
		case 0:
			if (onPull()) {
				if (current == currentCnc / 2) {
					state = 2;
					moveTime = currentCnc % 2 == 0 ? timeUper1 : timeUper2;
					moveTime--;
				} else {
					state = 1;
					switch(abs(current - currentCnc / 2)) {
						case 1: moveTime = time1; break;
						case 2: moveTime = time2; break;
						case 3: moveTime = time3; break;
					}
					moveTime--;
				}
			}
			break;
		case 1:
			moveTime--;
			if (moveTime == 0) {
				state = 2;
				current = currentCnc / 2;
				moveTime = currentCnc % 2 == 0 ? timeUper1 : timeUper2;
			}
			break;
		case 2:
			moveTime--;
			if (moveTime == 0) {
				if (cnc[currentCnc]->getCurrentComponent() == 0) {
					state = 0;
				} else {
					state = 3;
					moveTime = timeCleaner;
				}

				if (currentCnc % 2 != 0) {
					oldComponent = cnc[currentCnc]->getCurrentComponent();
					sumNew++;
					cnc[currentCnc]->onUpdate(sumNew);
				} else {
					cnc[currentCnc]->onUpdate(oldComponent);
				}
			}
			break;
		case 3:
			moveTime--;
			if (moveTime == 0) {
				if (currentCnc % 2 == 0) {
					sumDone++;
					state = 0;
				} else {
					state = 2;
					currentCnc--;
					taskList[currentCnc].launchTime = -1;
					moveTime = currentCnc % 2 == 0 ? timeUper1 : timeUper2;
				}
			}
			break;
	}
}
