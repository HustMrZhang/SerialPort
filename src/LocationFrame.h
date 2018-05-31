/*
 * LocationFrame.h
 *
 *  Created on: May 25, 2018
 *      Author: leon
 */

#ifndef LOCATIONFRAME_H_
#define LOCATIONFRAME_H_

#include "AOAFrame.h"

class LocationFrame: public AOAFrame {
public:
	LocationFrame(unsigned char *dataFrame);
	virtual ~LocationFrame();
	unsigned char seq_num;
	unsigned char Rev1;
	unsigned char Rev2;
	unsigned char battery;
	unsigned char keys;
	unsigned short int Tag_ID;
	unsigned short int distence;
	short int angle;
	unsigned char anchor_status;
	unsigned char quality;
};

#endif /* LOCATIONFRAME_H_ */
