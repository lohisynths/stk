/*
 * PipeReceiver.h
 *
 *  Created on: Sep 24, 2017
 *      Author: alax
 */

#ifndef PIPERECEIVER_H_
#define PIPERECEIVER_H_
#include <iostream>
#include <stdio.h>

#include <unistd.h>
#include <stdint.h>

#include <fcntl.h>
#include <sstream>

class PipeReceiver {

public:
	PipeReceiver();
	virtual ~PipeReceiver(){};

	size_t avaliable();

	void stdOutDump();

	void writeToPipe(uint8_t *data, size_t size );

	void readFromPipe(uint8_t *data, size_t &size);


	int getPipeFdRead();

	int getPipeFdWrite();

	FILE* getPipeFileHandle();

	std::ostream *getPipeFileStreamWrite();


private:
	static std::ostream *is;
	static uint8_t buff[128];
	static std::string message;
	static FILE* pipe_f;
	static int pipe_fd[2];

};

//static PipeReceiver stk_pipe;

#endif /* PIPERECEIVER_H_ */
