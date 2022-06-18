#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
//https://linuxhint.com/gethostbyname-function-c/
typedef struct _student
{
    char student_ID[255];
    char student_email[255];
}student;

int main( int argc, char *argv[] ) {
   // read in the data in query.txt
   FILE *fp;
   int student_amount = 0;
   student Data[255];
   //read data
   fp = fopen("query.txt", "r");
   while (fscanf(fp, "%s %s", Data[student_amount].student_ID
   , Data[student_amount].student_email) != EOF)
   {
       student_amount++;
   }
   

   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 1234;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
      
   while(1){
        /* Now start listening for the clients, here process will
           go in sleep mode and will wait for the incoming connection
        */
        //if there are many new clients, we have to listen to new connection
        //request continuously.
        listen(sockfd,10);
        clilen = sizeof(cli_addr);

        /* Accept actual connection from the client */
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        
        //if there isn't any new connection
        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        
        //the communication might continue 
        while (1)
        {
            char message[255];
            char response[255];

            //initialize
            memset(buffer, 0, sizeof(buffer));
            memset(message, 0, sizeof(message));
            memset(response, 0, sizeof(response));
            
            strcpy(message, "What's your requirement? 1.DNS 2.QUERY 3.QUIT : ");
            write(newsockfd, message, strlen(message));
            memset(message, 0, sizeof(message));
            /* If connection is established then start communicating */
            
            n = read( newsockfd,buffer,255 );
            
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            // client's reaponse
            if(buffer[0] == '1'){
                //initialize
                memset(buffer, 0, sizeof(buffer));
                /* Write a response to the client */
                strcpy(message, "Input URL address : ");
                write(newsockfd, message, strlen(message));
                memset(message, 0, sizeof(message));
                //read client's response
                n = read( newsockfd,response,255 );
            
                if (n < 0) {
                    perror("ERROR reading from socket");
                    exit(1);
                }
                // start to find out DNS
                struct hostent *H;
                struct in_addr **Addrlist;
                H = gethostbyname(response);
                Addrlist = (struct in_addr**) H ->h_addr_list;
                if(H == NULL){
                    strcpy(message, "No such URL address");
                }
                else{
                    
                    strcpy(message, inet_ntoa(*Addrlist[0]));
                    break;
                }
                write(newsockfd, message, strlen(message));
                memset(message, 0, sizeof(message));
                
            }
            else if(buffer[0] == '2'){

                memset(buffer, 0, sizeof(buffer));
                strcpy(message, "Input student ID : ");
                write(newsockfd, message, strlen(message));
                memset(message, 0, sizeof(message));
                //read client's response
                n = read( newsockfd,response,255 );
            
                if (n < 0) {
                    perror("ERROR reading from socket");
                    exit(1);
                }
                int find = 0;
                for(int i = 0;i < student_amount;i ++){
                    if(strcmp(response, Data[i].student_ID) == 0){
                        strcpy(message, Data[i].student_email);
                        find = 1;
                        if(find)
                            break;
                    }
                }
                if(find){
                    write(newsockfd, message, strlen(message));
                    memset(message, 0, sizeof(message));
                }
                else{
                    strcpy(message, "No such student ID");
                    write(newsockfd, message, strlen(message));
                    memset(message, 0, sizeof(message));

                }
            }
            else if(buffer[0] == '3'){

                memset(buffer, 0, sizeof(buffer));
                break;
            }
            else{

                memset(buffer, 0, sizeof(buffer));
                break;
            }
            //printf("Here is the message: %s\n",buffer);
            
            
           
        }
        
        
   }
   
      
   return 0;
}
