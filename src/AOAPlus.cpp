//============================================================================
// Name        : AOAPlus.cpp
// Author      : liuyi
// Version     :
// Copyright   : by robotech
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "datamaker.h"
#include "LocationFrame.h"
#include "AOAReciver.h"
using namespace std;

int main() {
	AOAReciver aoaReciver;
	DataMaker mDataMaker((AOAReciver*) &aoaReciver);
	int result = mDataMaker.startWork(ttyUSB0);
	while (1) {
		sleep(10);
	}
	return result;
}
