#include "client.hpp"

int check_if_in_nick(char *buffer, client client, int i)
{
    for (i = 0; i < max_clients; i++)  
    {  
        if(buffer + 4 = this->client[i]->getnickname())
            return (1);
    }
    return (0);
}

int check_if_in_user(char *buffer, client client, int i)
{
    for (i = 0; i < max_clients; i++)  
    {  
        if(buffer + 4 = this->client[i]->getusername())
            return (1);
    }
    return (0);
}
