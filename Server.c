#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
void servicePlayers(int client1,int client2);
int main(int argc, char *argv[]){
        char *myTime;
        int sd, TOTO, TITI, port_no;
        socklen_t len;
        struct sockaddr_in servAdd;
        int points;
        int conv_points;
        int size = sizeof(conv_points);
        if(argc != 2){
                fprintf(stderr,"Call model: %s <Port Number>\n",argv[0]);
                exit(0);
        }
        if((sd = socket(AF_INET, SOCK_STREAM, 0))<0){
                fprintf(stderr, "Could not create socket\n");
                exit(1);
        }
        servAdd.sin_family = AF_INET;
        servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
        sscanf(argv[1], "%d", &port_no);
        servAdd.sin_port = htons((uint16_t)port_no);
        bind(sd, (struct sockaddr *) &servAdd,sizeof(servAdd));
        listen(sd, 6);
        while(1){
                TOTO=accept(sd,(struct sockaddr*)NULL,NULL);
                TITI=accept(sd,(struct sockaddr*)NULL,NULL);
                printf("Got a game request\n");
                if(fork()==0)
                        servicePlayers(TOTO,TITI);
        }
}
void servicePlayers(int TOTO,int TITI){
        int TOTO_points=0,TITI_points=0,size=sizeof(int);
        int c1_conv_points,c2_conv_points;
        while(1){
                sleep(1);
                write(TOTO,"You can now play",100);
                if(read(TOTO,&c1_conv_points,size)<0)
                        printf("Read Error from TOTO");
                TOTO_points+=ntohl(c1_conv_points);
                if(TOTO_points>=100){
                        write(TOTO,"Game over: You won the game",100);
                        write(TITI,"Game over: You lost the game",100);
                        break;
                }
                sleep(2);
                write(TITI,"You can now play",100);
                if(read(TITI,&c2_conv_points,size)<0)
                        printf("Read Error from TITI");
                TITI_points+=ntohl(c2_conv_points);
		if(TITI_points>=100){
                        write(TITI,"Game over: You won the game",100);
                        write(TOTO,"Game over: You lost the game",100);
                        break;
                }
                //sleep(1);
        }
        close(TOTO);
        close(TITI);

}