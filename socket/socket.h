#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#include <iostream>
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
		
