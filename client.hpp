# ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <iostream>
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <fcntl.h>
#include <vector>
#include <iterator>

#include <sys/types.h>
#define _XOPEN_SOURCE_EXTENDED 1
#define _OE_SOCKETS
#define _USE_GNU
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>    //close 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
     
#define TRUE   1 
#define FALSE  0 
using namespace std;
class Client{

	public:
        Client();
		int		id;
		void	Set_nickname(std::string s);
		std::string Get_nickname() const;
        void	Set_username(std::string s);
		std::string Get_username() const;
        void	Set_clientsocket(int sd);
		int Get_clientsocket() const;
        ~Client();
	private:
		std::string	nickname;
        std::string	username;
        int client_socket;
};

#endif