/*
 * AOAReciver.h
 *
 *  Created on: May 25, 2018
 *      Author: leon
 */

#ifndef AOARECIVER_H_
#define AOARECIVER_H_

#include "LocationFrame.h"

class AOAReciver {
private:
	unsigned char lastKeys;
	bool open;
public:
	AOAReciver();
	void onReceiveData(unsigned char *mFrame);
	~AOAReciver();
};

#endif /* AOARECIVER_H_ */
