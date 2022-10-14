#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>  
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#define PORT 8080
#define _OPEN_SYS_SOCK_IPV6
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{   
    int loop = 1;
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    while (loop > 0){
        char input[100];
        printf("C: ");
        gets(input);
        char *msg = input;

        send(sock , msg , strlen(msg) , 0 );
        //printf("C: Mensaje Enviado\n");

        char buffer[1024] = {0};
        valread = read( sock , buffer, 1024);
        printf("S: %s\n",buffer );
    }
    return 0;
}
