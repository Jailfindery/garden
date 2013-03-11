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

socket_base::socket_base(int portno)
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// Error-handling?

	bzero((char*)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	set_port(portno);

	for(int i = 0; i < 256; i++)
		buffer[i] = '\0';
}

socket_base::~socket_base()
{
	close(sockfd);
}

std::string socket_base::dump_buf()
{
	std::string result;
	for(int i = 0; i < 256; i++)
		result += buffer[i];
	return result;
}

void socket_base::set_port(int portno)
{
	server_addr.sin_port = htons(portno);
}

server::server(int portno) : socket_base(portno)
{
	server_addr.sin_addr.s_addr = INADDR_ANY;
	client_len = sizeof(client_addr);
}

int server::accept()
{
	confd = ::accept(sockfd, (sockaddr*)&client_addr, &client_len);
	if(confd < 0)
	{
		return -1;
	}
	return 0;
}

int server::bind()
{
	int result = ::bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr));
	return result;
}

void server::close_con()
{
	close(confd);
	return;
}

void server::listen()
{
	::listen(sockfd, QUEUE_LENGTH);
	return;
}

int server::read()
{
	int result = ::read(confd, buffer, 255);
	return result;
}

int server::write(std::string data)
{
	int result = ::write(confd, data.c_str(), (data.length() * 8));
	return result;
}

client::client(std::string host, int portno) : socket_base(portno)
{
	server = gethostbyname(host.c_str());
	bcopy((char*)server->h_addr,
          (char*)&server_addr.sin_addr.s_addr,
          server->h_length);
}

int client::connect()
{
	int result = ::connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr));
	return result;
}

int client::read()
{
	int result = ::read(sockfd, buffer, 255);
	return result;
}

int client::write(std::string data)
{
	int result = ::write(sockfd, data.c_str(), data.length());
	return result;
}


