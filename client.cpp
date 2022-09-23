#include "client.hpp"

///constructeur
Client::Client()
{
	////orders
}

/////get

std::string 	Client::Get_nickname() const
{
	return(this->nickname);
}

std::string 	Client::Get_username() const
{
	return(this->username);
}

int 	Client::Get_clientsocket() const
{
	return(this->client_socket);
}


///set

void	Client::Set_nickname(std::string s)
{
	nickname = s;
}

void	Client::Set_username(std::string s)
{
	username = s;
}

void	Client::Set_clientsocket(int sd)
{
	this->client_socket = sd;
}

//////destructeur

Client::~Client()
{
	std::cout << "\e[0;31mDestructor called \e[0m" << std::endl;
}