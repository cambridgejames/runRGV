// *----encoding: UTF-16 LE with BOM----*

#pragma once

#include "stdafx.h"
#include "Cnc.h"
#include "Rgv.h"
#include <iostream>
using namespace std;

Cnc::Cnc() {
	Cnc(0, NULL);
}

Cnc::Cnc(int IprocessTime, Rgv* Irgv): processTime(IprocessTime), isDuang(false), fixTime(0), systemTime(-1), beginTime(0), endTime(0), rgv(Irgv) {
	this->number = rgv->onRegister(this);

	cout << "创建了1个CNC实例:" << endl;
	cout << ">>本实例在RGV中注册的编号为： #" << this->number << endl;
	cout << ">>本实例加工一个零件需要的时间： " << this->processTime << "s" << endl;
	cout << endl;
}

Cnc::~Cnc() {
	cout << "删除了编号为 #" << this->number << " 的CNC实例" << endl;
	cout << endl;
}

int Cnc::onUpdate() {
	this->beginTime = this->systemTime;
	this->endTime = this->beginTime + this->processTime;
	cout << "CNC #" << this->number << " 已经完成上下料" << endl;
	return 0;
}

void Cnc::onSystemTimeChange(int systemTime) {
	this->systemTime = systemTime;
	if (this->systemTime >= this->endTime) {
		if (this->systemTime = this->endTime) {
			rgv->onPush(this->number);
		}
		cout << "CNC #" << this->number << " 等待中..." << endl;
	} else {
		cout << "CNC #" << this->number << " 正在加工零件" << endl;
	}
}
