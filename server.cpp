#include "server.hpp" 



///constructeur
Server::Server(int ac, char *av[])
{
    (void)ac;
    std::vector<Client>::iterator it;
    this->master_socket = 0;
    //this->Set_maxclient(30);
    //check port
    this->Set_port(atoi(av[1]));
    //check password ??
    this->Set_password(av[2]);

    for (it = this->clients.begin(); it != this->clients.end(); ++it)
    {
        (*it).Set_nickname("");
        (*it).Set_username("");
        (*it).Set_clientsocket(0);
    }
    // for ( i = 0 ; i < (int)this->clients.size() ; i++)  
    // {
    //     Get_clients().find().Set_nickname("\0");
    //     Get_clients()[i].Set_username("\0");
    //     Get_clients()[i].Set_clientsocket(0);
    // } 
}

////get
int Server::Get_port() const
{
	return(this->PORT);
}

char*  Server::Get_password(void) const
{
    return(this->password);
}
        
std::vector<Client> Server::Get_clients(void)
{
	return(this->clients);
}
////set
void	Server::Set_port(int port)
{
	this->PORT = port;
}

void	Server::Set_password(char *password)
{
    this->password = password;
}

//void	Server::Set_clients(Client client, int i)
//{
//	this->clients[i] = client;
//}
//////destructor
Server::~Server()
{
    //delete *server;
	std::cout << "\e[0;31mDestructor called \e[0m" << std::endl;
}

int main(int ac , char *av[])  
{ 
    (void)ac;
    if (ac != 2)
        return (1);
    //(void)argv;
    Server *server = new Server(ac,av);
    //server.Set_port(atoi(av[1]));
    int opt = TRUE; 
    // bool isExit = false;
    //int master_socket ;
    int addrlen ;
    int new_socket ;
    //int client_socket[30] ;
    //int max_clients = 30 ;
    int activity;
    //int i ;
    int valread;
    int sd = 0;  
    int max_sd = 0;  
    struct sockaddr_in address;  
    int bufsize = 1024;
    char buffer[1025];  //data buffer of 1K 
    memset(buffer, 0, bufsize);
         
    //set of socket descriptors 
    fd_set readfds;  
         
    //a message 
    char message[] = "ECHO Daemon v1.0 \r\n";  
     
    //initialise all client_socket[] to 0 so not checked
    server->init_client_socket();
    //for (i = 0; i < max_clients; i++)  
    //{  
    //    client_socket[i] = 0;
    //    //this->client[i]->client_socket = 0;
    //}  
         
    //create a master socket 
    server->create_master_socket();
    //if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    //{  
    //    perror("socket failed");  
    //    exit(EXIT_FAILURE);  
    //}  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    server->set_master_socket(opt);
    //if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )  
    //{  
    //    perror("setsockopt");  
    //    exit(EXIT_FAILURE);  
    //}  
     
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons(server->Get_port());  
         
    //bind the socket to localhost port 8888 
    server->bind_socker(address);
    //if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    //{  
    //    perror("bind failed");  
    //    exit(EXIT_FAILURE);  
    //} 
    //    /* ------------- LISTENING CALL ------------- */
    //    /* ---------------- listen() ---------------- */
    std::cout << "Listener on port " << server->Get_port() << std::endl;  
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(server->master_socket, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection 
    addrlen = sizeof(address);  
    puts("Waiting for connections ...");  
    std::vector<Client>::iterator it; 
    while(TRUE)  
    {  
        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(server->master_socket, &readfds);  
        max_sd = server->master_socket;  
             
        //add child sockets to set 
        for (it = server->Get_clients().begin(); it != server->Get_clients().end(); ++it)  
        {  
            //socket descriptor 
            //sd = client_socket[i];
            
            //server->Get_client(i).Set_clientsocket(sd);
                
            sd = (*it).Get_clientsocket();
                 
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                 
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
             
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(server->master_socket, &readfds))  
        {  
            if ((new_socket = accept(server->master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  

            // set non-blocking socket
            if (fcntl(new_socket, F_SETFL, O_NONBLOCK) < 0) {
                // handle error
                std::cerr << "Cannot set state on socket" << std::endl;
                exit(EXIT_FAILURE);
            }


             //
            //inform user of socket number - used in send and receive commands 
            std::cout << "New connection , socket fd is " << new_socket << ", ip is : "<< inet_ntoa(address.sin_addr) << " , port : "<< ntohs(address.sin_port) << std::endl;

            //send new connection greeting message 
            if( send(new_socket, message, strlen(message), 0) != (ssize_t)strlen(message))  
            {  
                perror("send"); 
                return (1);
            }  
                 
            puts("Welcome message sent successfully");  
            server->addClient((Client)(*it));
            //std::vector<Client>::iterator it; 
            //add new socket to array of sockets
            for (it = server->Get_clients().begin(); it != server->Get_clients().end(); ++it)
            {  
                //if position is empty;
                std::cout << "check soket" << std::endl;//(*it).Get_clientsocket() << std::endl;
                //if(server->.Get_client().clientsocket() == 0)  
                //{
                std::cout << "newsocket" << (*it).Get_clientsocket() << std::endl;
                
                //(*it).end().Set_clientsocket(new_socket);
                //client_socket[i] = new_socket;
        
                //this->client[i]->client_socket = new_socket
                (*it).Set_clientsocket(new_socket);
                std::cout << "Adding to list of sockets as " << std::endl;  
                //break;  
            }
            //}  
        }  
        /////////////////////////////MSG CLIENT//////////////////////////////
        //else its some IO operation on some other socket
        //int j = 0;
        std::vector<Client>::iterator jt; 
        //int i = 0;
        std::vector<Client>::iterator it; 
        int len = 0;
        std::cout << "maxclient "<< server->Get_clients().size() << std::endl;
        //for (i = 0; i < server->Get_clients().size(); i++) 
        for (it = server->Get_clients().begin(); it != server->Get_clients().end(); ++it) 
        {  
            //sd = client_socket[i]; 
            sd = (*it).Get_clientsocket();
            //sd = this->client[i]->client_socket;   
            if (FD_ISSET(sd, &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                if ((valread = read(sd, buffer, bufsize)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);  
                    std::cout << "Host disconnected , ip " << inet_ntoa(address.sin_addr) << " , port " << ntohs(address.sin_port) << std::endl;  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    //client_socket[i] = 0;
                    //server->Get_client(i).Set_clientsocket(0);
                    (*it).Set_clientsocket(0); 
                }  
                     
                //Echo back the message that came in 
                else 
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read
                    std::cout << "check"<< std::endl;
                    for (jt = server->Get_clients().begin(); jt != server->Get_clients().end(); ++jt)
                    { 
                           
                        buffer[valread] = '\0';
                        while (valread > 0) 
                        {
                            std::cout << "1len: " << (len = strlen(buffer)) << std::endl;
                            std::cout << "1buffer:" << buffer << std::endl;
                            valread = recv((*jt).Get_clientsocket(), buffer, bufsize, 0);
                            //for (i = 0; i < server->Get_maxclient(); i++) 
                            for (it = server->Get_clients().begin(); it != server->Get_clients().end(); ++it)
                            {
                                buffer[len] = '\0';
                                std::cout << "2len: " << strlen(buffer) << std::endl;
                                std::cout << "2buffer:" << buffer << std::endl;
                                send((*it).Get_clientsocket(), buffer,bufsize, 0);
                                
                            }

                        }                            
                    }
                }
            }   
        }

    }  
    return (0);  
} 
