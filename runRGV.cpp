// runRGV.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "Rgv.h"
#include "Cnc.h"
using namespace std;

int main()
{
	Rgv *rgv = new Rgv(20, 33, 46, 28, 31, 25);
	rgv->pull();
	Cnc *cnc1 = new Cnc(560, rgv);
    return 0;
}

