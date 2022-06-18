#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>  
#include <unistd.h> 
#include <netdb.h> 
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
//https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
//http://puremonkey2010.blogspot.com/2012/07/networkprg-tcp-clientserver.html
  
int main()  
{  
  struct sockaddr_in server;  
  int socketfd;  
  char buffer[255];
  char message[255];  
  int n;  
  
  /* 製作 socket */  
  socketfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (socketfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
  //initialize
  bzero((char *) &server, sizeof(server));
  /* 準備連線端指定用的 struct 資料 */  
  server.sin_family = AF_INET;  
  server.sin_port = htons(1234);  
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* 127.0.0.1 是 localhost 本機位址 */  
  //inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);  
  
  /* 與 server 端連線 */  
  n = connect(socketfd, (struct sockaddr *)&server, sizeof(server));  
  if(n < 0){
    perror("ERROR connecting");
    exit(1);
  }
  /* 從伺服器接受資料 */  
  while (1)
  {
    memset(buffer, 0, sizeof(buffer));
    memset(message, 0, sizeof(message));  
    n = read(socketfd, buffer, sizeof(buffer));
    printf("%s", buffer);
    scanf("%s", message);
    //send message to server
    write(socketfd, message, strlen(message));
    if(message[0] == '1'){
        memset(buffer, 0, sizeof(buffer));
        memset(message, 0, sizeof(message));
        read(socketfd, buffer, strlen(buffer));
        printf("%s", buffer);

        scanf("%s", message);
        write(socketfd, message, strlen(message));

        memset(buffer, 0, sizeof(buffer));
        read(socketfd, buffer, strlen(buffer));
        printf("address get from domain name : %s\n\n", buffer);
    }
    else if(message[0] == '2'){
        memset(buffer, 0, sizeof(buffer));
        memset(message, 0, sizeof(message));
        read(socketfd, buffer, strlen(buffer));
        printf("%s", buffer);

        scanf("%s", message);
        write(socketfd, message, strlen(message));

        memset(buffer, 0, sizeof(buffer));
        read(socketfd, buffer, strlen(buffer));
        printf("Email get from domain name : %s\n\n", buffer);
    }
    else{
        memset(message, 0, sizeof(message));
        break;
    }

  }
  
   
  
  //printf("\t[Info] Receive %d bytes: %s\n", n, buffer);  
  
  /* 結束 socket */  
  close(socketfd);  
  return 0;  
} 