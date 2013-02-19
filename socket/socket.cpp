/*
 *
 *  Socket implementation class functions for garden.
 *  Copyright (C) 2013 Joshua Schell (joshua.g.schell@gmail.com)
 *
 *  garden is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  garden is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with garden.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "socket.h"

/* One may be able to override this,
 * but I have never tried...
 */
#ifndef QUEUE_LENGTH
#define QUEUE_LENGTH 5
#endif

using namespace tcp;

base_socket::base_socket(int portno)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// Error-handling?

	bzero((char*)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	set_port(portno);

	for(int i = 0; i < 256; i++)
		buffer[i] = '\0';
}

base_socket::~base_socket()
{
	close(sockfd);
}

std::string base_socket::dump_buf()
{
	std::string result;
	for(int i = 0; i < 256; i++)
		result += buffer[i];
	return result;
}

void base_socket::set_port(int portno)
{
	server_addr.sin_port = htons(portno);
}

server_socket::server_socket(int portno) : base_socket(portno)
{
	server_addr.sin_addr.s_addr = INADDR_ANY;
	client_len = sizeof(client_addr);
}

int server_socket::saccept()
{
	confd = accept(sockfd, (sockaddr*)&client_addr, &client_len);
	if(confd < 0)
	{
		return -1;
	}
	return 0;
}

int server_socket::sbind()
{
	int result = bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr));
	return result;
}

void server_socket::close_con()
{
	close(confd);
}

void server_socket::slisten()
{
	listen(sockfd, QUEUE_LENGTH);
}

int server_socket::sread()
{
	int result = read(confd, buffer, 255);
	return result;
}

int server_socket::swrite(std::string data)
{
	int result = write(confd, data.c_str(), (data.length() * 8));
	return result;
}

client_socket::client_socket(std::string host, int portno) : base_socket(portno)
{
	server = gethostbyname(host.c_str());
	bcopy((char*)server->h_addr,
          (char*)&server_addr.sin_addr.s_addr,
          server->h_length);
}

int client_socket::sconnect()
{
	int result = connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr));
	return result;
}

int client_socket::sread()
{
	int result = read(sockfd, buffer, 255);
	return result;
}

int client_socket::swrite(std::string data)
{
	int result = write(sockfd, data.c_str(), data.length());
	return result;
}


