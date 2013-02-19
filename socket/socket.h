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
//#include <sys/types.h>
//#include <netinet/in.h>
#include <netdb.h>

/* NB! Functions named s* exist to
 *     prevent name collisions.
 */

/* TODO:
*/

namespace tcp
{
	class base_socket
	{
	public:
		base_socket(int portno);
		virtual ~base_socket();
		std::string dump_buf();
		virtual int sread() = 0;
		virtual int swrite(std::string data) = 0;
	protected:
		char buffer[256];
		sockaddr_in server_addr;
		void set_port(int portno);
		int sockfd;
	};

	class server_socket : public base_socket
	{
	public:
		server_socket(int portno);
		void close_con();
		int saccept();
		int sbind();
		void slisten();
		int sread();
		int swrite(std::string data);
	private:
		sockaddr_in client_addr;
		socklen_t client_len;
		int confd;
	};

	class client_socket : public base_socket
	{
	public:
		client_socket(std::string host, int portno);
		int sconnect();
		int sread();
		int swrite(std::string data);
	private:
		hostent* get_host(std::string name);
		hostent* server;
	};
}

#endif
