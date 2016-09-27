#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write, readResult

//CLIENT

int main(int argc , char *argv[])
{
  int socketfd;
  struct sockaddr_in serv_addr;

  //Create socket
  socketfd = socket(AF_INET , SOCK_STREAM , 0);
  if (socketfd == -1)
  {
      perror("Could not create socket");
      return -1;
  }

  //Prepare the sockaddr_in structure
  serv_addr.sin_family = AF_INET;
  //server.sin_addr.s_addr = INADDR_ANY; // accept connections in all IPs in this machine
  if (inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr.s_addr))< 0) {
    perror("inet_pton");
    return -1;
  }
  // server.sin_addr.s_addr = inet_addr("127.0.0.1"); // deprecated
  serv_addr.sin_port = htons( 8888 );

  if( connect(socketfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
     perror("Connect Failed");
     return 1;
  }

  char *message = "E ai servidor mané\n";
  int writeResult = send(socketfd , message , strlen(message), 0);
  char buffer[1024];
  int readResult = recv(socketfd, buffer, 1024, 0);
  printf("Servidor enviou: %s\n", buffer);
  close(socketfd);




}
