/*
 * AOAListener.h
 *
 *  Created on: May 25, 2018
 *      Author: leon
 */

#ifndef AOALISTENER_H_
#define AOALISTENER_H_
#include "AOAFrame.h"

class AOAListener {
public:
	AOAListener();
	virtual void onReceiveData(AOAFrame &mFrame);
	virtual ~AOAListener();
};

#endif /* AOALISTENER_H_ */
