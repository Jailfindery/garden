#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "socket.h"

#include <iostream>

/* One may be able to override this,
 * but I have never tried...
 */
#ifndef QUEUE_LENGTH
#define QUEUE_LENGTH 5
#endif

using namespace tcp;

socket_server::socket_server(int portno)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// Error-handling?

	bzero((char*)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;

	client_len = sizeof(client_addr);

	// ASSIGN THE DAMN PORT!
	set_port(portno);

	for(int i = 0; i < 256; i++)
		buffer[i] = '\0';
}

socket_server::~socket_server()
{
	close(sockfd);
}

int socket_server::ssaccept()
{
	confd = accept(sockfd, (sockaddr*)&client_addr, &client_len);
	if(confd < -1)
	{
		return -1;
	}
	return 0;
}

int socket_server::ssbind()
{
	if(bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		return -1;
	}
	return 0;
}

void socket_server::close_con()
{
	close(confd);
}

std::string socket_server::dump_buf()
{
	std::string result;
	for(int i = 0; buffer[i] != '\0'; i++)
		result += buffer[i];
	return result;
}

void socket_server::sslisten()
{
	listen(sockfd, QUEUE_LENGTH);
}

int socket_server::ssread()
{
	int result = read(confd, buffer, 255);
	return result;
}

void socket_server::set_port(int portno)
{
	server_addr.sin_port = htons(portno);
}

int socket_server::sswrite(std::string data)
{
	int result = write(confd, data.c_str(), (data.length() * 8));
	return result;
}

