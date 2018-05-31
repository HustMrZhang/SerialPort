/*
 * AOAReciver.cpp
 *
 *  Created on: May 25, 2018
 *      Author: leon
 */
#include "AOAReciver.h"
#include <stdio.h>

using namespace std;

AOAReciver::AOAReciver() {
// TODO Auto-generated constructor stub
	lastKeys = 0x00;
	open = true;
}

void AOAReciver::onReceiveData(unsigned char *data) {
	LocationFrame* mFrame = new LocationFrame(data);

	if (mFrame->keys == 0x00 && lastKeys == 0x10) {
		cout << "change open flag" << endl;
		open = open ? false : true;
	}
	lastKeys = mFrame->keys;

	if (open) {
		cout << "liuyi seq:" << (int) mFrame->seq_num << "  TagId:"
				<< (int) mFrame->Tag_ID << "  angle:" << dec
				<< (double) (mFrame->angle / 1000. / 3.1415926535897932 * 180)
				<< "  dist(m):" << (float) (mFrame->distence / 100.)
				<< "  quality:" << (int) mFrame->quality << endl;
	}
//	delete mFrame;
}

AOAReciver::~AOAReciver() {
// TODO Auto-generated destructor stub

}
