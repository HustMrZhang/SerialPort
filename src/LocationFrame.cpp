/*
 * LocationFrame.cpp
 *
 *  Created on: May 25, 2018
 *      Author: leon
 */

#include "LocationFrame.h"

LocationFrame::LocationFrame(unsigned char *dataFrame) :
		AOAFrame(dataFrame) {
	seq_num = data[0];
	Rev1 = data[1];
	Rev2 = data[2];
	battery = data[3];
	keys = data[4];
	Tag_ID = data[6];
	Tag_ID = Tag_ID << 8 | data[5];
	distence = data[8];
	distence = distence << 8 | data[7];
	angle = data[10];
	angle = angle << 8 | data[9];
	anchor_status = data[11];
	quality = data[12];
}

LocationFrame::~LocationFrame() {
}

