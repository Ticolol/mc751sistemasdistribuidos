#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

//SERVER

int main(int argc , char *argv[])
{
    int socket_desc , new_socket;
    struct sockaddr_in server_addr , client;
    char *message;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        perror("Could not create socket");
        return -1;
    }

    int reuse = 1;
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, (const void*)&reuse, sizeof(reuse)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
    }

    //Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    
    //server_addr.sin_addr.s_addr = INADDR_ANY; // accept connections in all IPs in this machine
    
    inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr.s_addr));
    
    server_addr.sin_port = htons( 8888 );

    //char str[INET_ADDRSTRLEN];
    //inet_ntop(AF_INET, &(server_addr.sin_addr.s_addr), str, INET_ADDRSTRLEN);

    //printf("%d, %s\n", server_addr.sin_addr.s_addr, str);


    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server_addr , sizeof(server_addr)) < 0)
    {
        perror("bind failed");
        return -1;
    }
    printf("bind done\n");

    //Listen
    listen(socket_desc , 10);  // queue up to 10

    while(1) {

    socklen_t c;
    //Accept and incoming connection
    printf("Waiting for incoming connections...");
    fflush(stdout);
    c = sizeof(struct sockaddr_in);
    new_socket = accept(socket_desc, (struct sockaddr *)&client, &c);
    if (new_socket<0)
    {
        perror("accept failed");
        return 1;
    }

    char client_addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client.sin_addr.s_addr), client_addr, INET_ADDRSTRLEN);

    //printf("%d, %s\n", server_addr.sin_addr.s_addr, str);


    printf("Connection accepted from %s\n", client_addr);

    char buffer[1024];

    int readResult = recv(new_socket, buffer, 1024, 0);

    printf("%s:%d sent: %s\n", client_addr, ntohs(client.sin_port), buffer);

    //Reply to the client
    message = "Falou, cliente otário";
    send(new_socket , message , strlen(message),0);

    //if (shutdown(new_socket, 2)) {
    //  perror("shutdown");
    //}

    if (close(new_socket)) {
      perror("close");
    }

  }

    return 0;
}
