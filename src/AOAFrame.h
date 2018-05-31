/*
 * AOAFrame.h
 *
 *  Created on: May 17, 2018
 *      Author: leon
 */
#ifndef AOAFRAME_H_
#define AOAFRAME_H_
#include <iostream>
#include <iomanip>
#include <deque>

class AOAFrame {
public:
	AOAFrame(unsigned char *dataFrame);
	unsigned int getType();
	unsigned int getDataLength();
	unsigned char * getData();
	virtual ~AOAFrame();
	void println();
	void printDataln();
public:
	unsigned char *m_frame;
	unsigned int dataLength;
	unsigned char type;
	unsigned char *data;
};

#endif /* AOAFRAME_H_ */
