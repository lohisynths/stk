#include "PipeReceiver.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>


#include <ext/stdio_filebuf.h>

FILE* PipeReceiver::pipe_f;
int PipeReceiver::pipe_fd[2];
uint8_t PipeReceiver::buff[128];
std::string PipeReceiver::message;
std::ostream *PipeReceiver::is=NULL;

PipeReceiver::PipeReceiver()
{
	static bool init=false;
	if(!init)
	{
		init=true;
		std::cout << " pipe initialized\n";
		///create pipe
		if( pipe(pipe_fd) < 0)
		{
			std::cout << " pipe initialized failed\n";
			exit(0);
		}

		/// set non blocking
		int flags = fcntl(pipe_fd[0], F_GETFL, 0);
		fcntl(pipe_fd[0], F_SETFL, flags | O_NONBLOCK);

		std::cout << pipe_fd[0] << " " << pipe_fd[1] << " pipe fd" << std::endl;

		pipe_f = fdopen(pipe_fd[1], "w");
		if(pipe_f<0 )
		{
			std::cout << " fdopen(pipe_1 iled\n";
			exit(0);
		}





//		__gnu_cxx::stdio_filebuf<char> filebuf(getPipeFdWrite(), std::ios::out); // 1
//		is = new std::ostream(&filebuf) ; // 2



	}
}

size_t PipeReceiver::avaliable()
{
	//std::cout << " pipe avaliable\n";
	message="";
	size_t message_size=0;
	while (1)
	{
		//std::cout << " pipe red\n";
		int bytes = read(pipe_fd[0], &buff, (size_t)sizeof(buff) );
		if (bytes > 0)
		{
			message_size+=bytes;
			message += (char*)buff;
			//std::cout <<message << "\n\n";
		}
		else
			break;
	}
	return message_size;
}

void PipeReceiver::stdOutDump()
{
	std::cout << "message size: " <<  message.size() << std::endl;
	std::cout << message;
}

void PipeReceiver::writeToPipe(uint8_t *data, size_t size )
{
	/// send data
	int ret = write( pipe_fd[1], data, size );
	if(ret < 0)
	{
		std::cout << "PipeReceiver write cos nie tak \n\n";
	}
	else
	{
		std::cout << "PipeReceiver write ok \n\n";

	}
}

void PipeReceiver::readFromPipe(uint8_t *data, size_t &size)
{
	std::cout << " pipe readFromPipe\n";


	//strcpy((char*)data, message.c_str());

	message.copy((char*)data, message.size());

//		memccpy((void*)data, (void*)&message.c_str(), message.size());
	size = message.size();
}


int PipeReceiver::getPipeFdRead()
{
	std::cout << " pipe getPipeFdRead\n";

	return pipe_fd[0];
}

int PipeReceiver::getPipeFdWrite()
{
	std::cout << " pipe getPipeFdWrite " << pipe_fd[1] << "\n";;

	return pipe_fd[1];
}

FILE* PipeReceiver::getPipeFileHandle()
{
	return pipe_f;
}


std::ostream *PipeReceiver::getPipeFileStreamWrite()
{

	return is;
}

