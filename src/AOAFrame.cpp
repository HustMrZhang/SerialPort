/*
 * AOAFrame.cpp
 *
 *  Created on: May 17, 2018
 *      Author: leon
 */

#include "AOAFrame.h"

AOAFrame::AOAFrame(unsigned char *dataFrame) {
	m_frame = dataFrame;
	type = dataFrame[2];
	dataLength = dataFrame[1] - 6;
	data = new unsigned char[dataLength];
	for (unsigned int i = 3, j = 0; j < dataLength; i++, j++) {
		data[j] = dataFrame[i];
	}
}

unsigned int AOAFrame::getType() {
	return type;
}

unsigned int AOAFrame::getDataLength() {
	return dataLength;
}

unsigned char * AOAFrame::getData() {
	return data;
}

void AOAFrame::println() {
	std::cout << "AOA Frame is : ";
	for (int i = 0; i < m_frame[1]; i++) {
		std::cout << " 0x" << std::hex << (unsigned int) m_frame[i];
	}
	std::cout << std::endl;
}

void AOAFrame::printDataln() {
	std::cout << "Data is : ";
	for (unsigned int i = 0; i < dataLength; i++) {
		std::cout << " 0x" << std::hex << (unsigned int) data[i];
	}
	std::cout << std::endl;
}

AOAFrame::~AOAFrame() {
	delete[] data;
	delete[] m_frame;
	std::cout << "AOAFrame had be destory." << std::endl;
}
