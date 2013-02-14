/*
 *
 *  Socket implementation class header for garden.
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

#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#include <string>
#include <sys/types.h>
#include <netinet/in.h>

/* NB! Functions named ss* exist to
 *     prevent name collisions.
 * It stands for "socket_server."
 */
namespace tcp
{
	class socket_server
	{
	public:
		socket_server(int portno);
		~socket_server();
		int ssaccept();
		int ssbind();
		void close_con();
		std::string dump_buf();
		void sslisten();
		int ssread();
		int sswrite(std::string data);

	private:
		char buffer[256];
		sockaddr_in client_addr;
		socklen_t client_len;
		int confd;
		sockaddr_in server_addr;
		void set_port(int portno);
		int sockfd;
	};
}

#endif

