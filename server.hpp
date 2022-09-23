# ifndef SERVER_H
#define SERVER_H

#include "client.hpp"

class Server{

	public:
        Server(int ac, char *av[]);
        void    init_client_socket(void);
        void    create_master_socket(void);
        void    set_master_socket(int opt);
        void    bind_socker(struct sockaddr_in address);
        int     Get_port() const;
        void	Set_port(int port);
        char*   Get_password(void) const;
        void	Set_password(char *);
        std::vector<Client> Get_clients(void);
        //void	Set_clients(void);
        int master_socket;
        ~Server();

        void addClient(Client client) 
        {
            std::cout << "client push back" << std::endl;
            new Client();
            client.Set_nickname("");
            client.Set_username("");
            client.Set_clientsocket(0);
            clients.push_back(client);
        }
	private:
        char *password;
        //int max_clients;
        //Client client[30];
        int PORT;
        std::vector<Client> clients;
};

#endif