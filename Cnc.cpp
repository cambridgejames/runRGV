// *----encoding: UTF-16 LE with BOM----*

#pragma once

#include "stdafx.h"
#include "Cnc.h"
#include <iostream>
using namespace std;

Cnc::Cnc() {
	Cnc(0, NULL);
}

Cnc::Cnc(int IprocessTime, Rgv* Irgv): processTime(IprocessTime), isDuang(false), fixTime(0), beginTime(0), endTime(0), rgv(Irgv) {
	cout << "创建了一个CNC实例" << endl;
	cout << rgv->timeCleaner << endl;
}

Cnc::~Cnc() {
	cout << "删除了一个CNC实例" << endl;
}