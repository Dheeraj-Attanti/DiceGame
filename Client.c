#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>


int main(int argc, char *argv[])
{
  srand(time(NULL));
  signal(SIGINT, SIG_IGN);
  char msg[100];
  int server, port_no;
  socklen_t len;
  struct sockaddr_in servAdd;     // server socket address

 if(argc != 3){
    printf("Call model: %s <IP Address> <Port Number>\n", argv[0]);
    exit(0);
  }

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0){
     fprintf(stderr, "Cannot create socket\n");
     exit(1);
  }

  servAdd.sin_family = AF_INET;
  sscanf(argv[2], "%d", &port_no);
  servAdd.sin_port = htons((uint16_t)port_no);
   if(inet_pton(AF_INET, argv[1], &servAdd.sin_addr) < 0){
  fprintf(stderr, " inet_pton() has failed\n");
  exit(2);
  }

 if(connect(server, (struct sockaddr *) &servAdd, sizeof(servAdd))<0){
  fprintf(stderr, "connect() has failed, exiting\n");
  exit(3);
 }

  int Client_points[2], server_points[2];
  Client_points[0]=0;
  Client_points[1]=0;
  server_points[0]=0;
  server_points[1]=0;
  char c, play[50], won[50], lost[50];
 // won[50] = "Game over: you won the game";
 // lost[50] = "Game over: you lost the game";
 // play[50] = "You can now play";

  while(1)
  {
        //Read operation//
    if (read(server, &msg, 100)<0){
      fprintf(stderr, "read() error\n");
      exit(3);
    }

    printf("\n\n Message From server :: %s \n",msg);
    //Read operation finished//

        if(strcmp(msg, "You can now play") ==0)
        {
               
        Client_points[0] = (rand() % 6)+1;
        Client_points[1]+=Client_points[0];
        break;
          
         printf("\nClient score :-\n");
         printf("Dice : %d\n", Client_points[0]);
         printf("Total score : %d\n", Client_points[1]);
         printf("\n\n\n");
         write(server, &Client_points, sizeof(Client_points));
	 }
	else if(strcmp(msg, "Game over: you won the game") ==0)
	{

	printf("\n\n I won the game \n\n");

	exit(0);

	}

	else if(strcmp(msg, "Game over: you lost the game") ==0)
	{

	printf("\n\n I lost the game \n\n");

	exit(0);

	}

	}
}