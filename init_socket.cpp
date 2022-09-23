#include "server.hpp"

void    Server::init_client_socket(void)
{
    int i;
    for (i = 0; i < (int)this->clients.size(); i++)  
    {  
        this->clients[i].Set_clientsocket(0);
        //this->client[i]->client_socket = 0;
    }
}

   //create a master socket
void    Server::create_master_socket(void)
{
    if( (this->master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }
}    

    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
void    Server::set_master_socket(int opt)
{
    if( setsockopt(this->master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
}    
         
    //bind the socket to localhost port 8888
void    Server::bind_socker(struct sockaddr_in address)
{
    if (bind(this->master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }
}

