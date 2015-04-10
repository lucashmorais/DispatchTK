/*
 * RandomTaskDispatcher.h
 *
 *  Created on: Apr 8, 2015
 *      Author: lucas
 */

#ifndef RANDOMTASKDISPATCHER_H_
#define RANDOMTASKDISPATCHER_H_

#include "TaskDispatcher.h"

class RandomTaskDispatcher: public TaskDispatcher {
public:
	RandomTaskDispatcher();
	virtual ~RandomTaskDispatcher();
};

#endif /* RANDOMTASKDISPATCHER_H_ */
