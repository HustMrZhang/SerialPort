/*
 * datamaker.cpp
 *
 *  Created on: May 23, 2018
 *      Author: leon
 */

#include "datamaker.h"
#include <pthread.h>
#include <iostream>
#include <iomanip>
#include "AOAFrame.h"
#include "LocationFrame.h"

void* runnable(void *runner) {
	DataMaker * tar = (DataMaker*) runner;
	tar->run();
	pthread_detach((pthread_t) pthread_self());
	pthread_exit(0);
}

DataMaker::DataMaker(AOAReciver *listener) {
	m_serial = new Serial();
	m_serial_fd = -1;
	m_rec_threadid = -1;
	m_read_thread_alive = false;
	m_listener = listener;
}

DataMaker::~DataMaker() {
	delete m_serial;
	m_serial = NULL;
}

int DataMaker::startWork(int index) {
	m_serial_fd = m_serial->OpenPort(index);
	if (m_serial_fd < 0) {
		printf("Open serial port %d failed!\n", index);
		return -1;
	} else {
		printf("Open serial port %d Success\n", m_serial_fd);
	}

	m_serial->SetPara(m_serial_fd, 6);
	m_read_thread_alive = true;
	if (pthread_create(&m_rec_threadid, NULL, runnable, this) != 0) {
		printf("creat Receive_Thread failed \n");
		m_read_thread_alive = false;
		m_serial->ClosePort(m_serial_fd);
		m_serial_fd = -1;
		return -1;
	}
	return 0;
}

int DataMaker::stop() {
	m_read_thread_alive = false;
	return 0;
}

void DataMaker::run() {
	printf("begin read serial port device\n");
	unsigned char buffer[100];
	while (m_read_thread_alive) {
		int length = m_serial->ReadData(m_serial_fd, buffer, 38);
//		std::cout << "get " << length << " bytes data." << std::endl;

		if (length > 0) {
			frames.insert(frames.end(), buffer, buffer + length);
			clear(buffer, length);
			analysisData();
		} else if (length < 0) {
			std::cout << "device had closed." << std::endl;
			break;
		}
		usleep(20 * 1000);
	}
}

void DataMaker::analysisData() {
	if (frames.empty()) {
		return;
	}
	unsigned int offset = 0;
	unsigned int dataLength = 0;
	for (std::deque<unsigned char>::iterator itor = frames.begin();
			itor != frames.end(); ++itor, ++offset) {
		if (*itor == 'Y' && frames[frames[offset + 1] + offset - 1] == 'G') {
			dataLength = frames[offset + 1];
			break;
		}
	}

	if (offset + 1 == frames.size()) {
		return;
	}

	if (offset > 0) {
		frames.erase(frames.begin(), frames.begin() + offset);
	}
	datas = std::deque<unsigned char>(frames.begin(),
			frames.begin() + dataLength);
	frames.erase(frames.begin(), frames.begin() + dataLength);

	publishData();
}

void DataMaker::publishData() {
	if (datas.empty()) {
		return;
	}
	if (checkCrc16(&datas)) {
		perror("crc check invalid.");
		return;
	}

	for (std::deque<unsigned char>::iterator itor = datas.begin();
			itor != datas.end(); itor++) {
		std::cout << std::hex << (int) *itor << " ";
	}
	std::cout << std::endl << std::endl;

	unsigned char data[datas.size()];
	convertDequeToArrays((unsigned char *) &data[0], &datas);
	switch (data[2]) {
	case 0x63:
		m_listener->onReceiveData(data);
		break;
	}
}

void DataMaker::convertDequeToArrays(unsigned char *data,
		std::deque<unsigned char>* pucFrame) {
	for (unsigned int i = 0; i < pucFrame->size(); i++) {
		data[i] = pucFrame->at(i);
	}
}

int DataMaker::checkCrc16(std::deque<unsigned char> *pucFrame) {
	unsigned short int crcData = pucFrame->at(pucFrame->size() - 3);
	crcData = pucFrame->at(pucFrame->size() - 2) << 8 | crcData;
	unsigned char data[pucFrame->size()];
	convertDequeToArrays(data, pucFrame);
	unsigned short int crcNum = Get_Crc16((unsigned char *) &data[0],
			pucFrame->size() - 3);
	return crcData != crcNum;
}

unsigned short int Get_Crc16(unsigned char *pucFrame,
		unsigned short int usLen) {
	unsigned char ucCRCHi = 0xFF;
	unsigned char ucCRCLo = 0xFF;
	int iIndex;
	while (usLen--) {
		iIndex = ucCRCLo ^ *(pucFrame++);
		ucCRCLo = (unsigned char) (ucCRCHi ^ aucCRCHi[iIndex]);
		ucCRCHi = aucCRCLo[iIndex];
	}
	return (unsigned short int) (ucCRCHi << 8 | ucCRCLo);
}

void clear(unsigned char * data, int length) {
	memset(data, 0, length);
}
