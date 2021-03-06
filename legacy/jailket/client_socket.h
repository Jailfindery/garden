/*
 *
 * Client socket class definition for garden.
 * Copyright (C) 2013 Joshua Schell (joshua.g.schell@gmail.com)
 *
 * garden is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * garden is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with garden. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CLIENT_SOCKET_H_INCLUDED
#define CLIENT_SOCKET_H_INCLUDED

#include <string>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "server_address.h"

/* Exceptions:
 * connect_error	connect()
 * not_connected	send(), recv()
 * socket_error		client_socket(), set_server()
 */

using namespace std;

namespace jailket {

class client_socket
{
  private:
	int socket_fd;
	addrinfo* server;
  public:
	client_socket(server_address& s);
	virtual ~client_socket();
	void connect();
	int send(string mes);
	string recv();
	void set_server(server_address& s);
	void close();
};

}

#endif /* CLIENT_H_INCLUDED */

