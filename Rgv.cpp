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

Rgv::Rgv(int Itime1, int Itime2, int Itime3, int ItimeUper1, int ItimeUper2, int ItimeCleaner): time1(Itime1), time2(Itime2), time3(Itime3), timeUper1(ItimeUper1), timeUper2(ItimeUper2), timeCleaner(ItimeCleaner), current(0), systemTime(0), moveTime(0), updateTime(0), washTime(0), sumNew(0), sumDone(0), oldComponent(0) {
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
	int wasteTime = 28800, distance = 4, requestTime = -1;
	int wastTimeCache = 0, distanceCache = -1;
	int objectIndex = -1;
	for (int i = 0; i < 8; i++) {
		if (taskList[i].launchTime == -1) { continue; }

		distanceCache = abs((taskList[i].number - 1) / 2 - current);
		switch(distanceCache) {
			case 0: wastTimeCache += 0; break;
			case 1: wastTimeCache += time1; break;
			case 2: wastTimeCache += time2; break;
			default: wastTimeCache += time3;
		}
		wastTimeCache += taskList[i].number % 2 != 0 ? timeUper1 : timeUper2;

		if (wasteTime > wastTimeCache) {
			wasteTime = wastTimeCache;
			distance = distanceCache;
			requestTime = taskList[i].launchTime;
			objectIndex = i;
		} else if (wasteTime <= wastTimeCache && distance > distanceCache) {
			wasteTime = wastTimeCache;
			distance = distanceCache;
			requestTime = taskList[i].launchTime;
			objectIndex = i;
		} else if (wasteTime <= wastTimeCache && distance <= distanceCache && requestTime < taskList[i].launchTime) {
			wasteTime = wastTimeCache;
			distance = distanceCache;
			requestTime = taskList[i].launchTime;
			objectIndex = i;
		}
	}

	if (objectIndex == -1) {
		return false;
	} else {

		currentCnc = objectIndex;
		taskList[objectIndex].launchTime = -1;
		switch(distance) {
			case 0: moveTime = 0; break;
			case 1: moveTime = time1; break;
			case 2: moveTime = time2; break;
			default: moveTime = time3;
		}
		updateTime = objectIndex % 2 != 0 ? timeUper1 : timeUper2;
		washTime = cnc[objectIndex]->getCurrentState() == 0 ? 0 : timeCleaner;

		return true;
	}
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

	int stateCache = -1;
	if (moveTime > 0) {
		stateCache = 1;
		//cout << "RGV：正在向 #" << currentCnc + 1 << " 号CNC移动，起始位置：" << current << endl;
		moveTime--;
		if (moveTime == 0) {
			current = currentCnc / 2;
			//cout << "RGV：移动结束，当前位置：" << current << endl;
		}
	} else if (moveTime == 0 && updateTime > 0) {
		stateCache = 2;
		//cout << "RGV：正在为 #" << currentCnc + 1 << " 号CNC上下料，新物料编号为：" << sumNew + 1 << "，旧物料编号为：" << cnc[currentCnc]->getCurrentComponent() << endl;
		updateTime--;
		if (updateTime == 0) {
			sumNew++;
			oldComponent = cnc[currentCnc]->getCurrentComponent();
			cnc[currentCnc]->onUpdate(sumNew);
			//cout << "RGV： #" << currentCnc + 1 << " 号CNC上下料结束，新物料编号为：" << cnc[currentCnc]->getCurrentComponent() << "，旧物料编号为：" << oldComponent << endl;
		}
	} else if (moveTime == 0 && updateTime == 0 && washTime > 0) {
		stateCache = 3;
		//cout << "RGV：正在清洗第" << oldComponent << "号零件" << endl;
		washTime--;
		if (washTime == 0) {
			//cout << "RGV：第" << oldComponent << "号零件清洗结束" << endl;
			sumDone++;
		}
	} else {
		stateCache = 0;
		//cout << "RGV：空闲中，";
		if (onPull()) {
			//cout << "接受请求成功，目标为 #" << currentCnc + 1 << " 号CNC" << endl;
			bool isReduced = false;
			/*if (moveTime > 0) {
				moveTime--;
			} else if (updateTime > 0) {
				updateTime--;
			} else {
				washTime--;
			}*/
		} else {
			//cout << "请求缓冲区为空，将保持空闲" << endl;
		}
	}

	state = stateCache;
}
