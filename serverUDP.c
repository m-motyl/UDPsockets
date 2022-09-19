#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define IP "127.0.0.1"
#define ROCK 1
#define PAPER 2
#define SCISSORS 3
#define FINISH 4
#define DRAW 5
#define LOSE 6
#define WIN 7


int p1 = -1, p2;

int main(){

        int sd,buff, buff1,clen;
	int player1, player2, draws;
	struct sockaddr_in sad, //server address
	                 cad, // client1 address
			 cad1;
      

	sd=socket(AF_INET,SOCK_DGRAM,0);
        memset((char *) &sad, 0,sizeof(sad));
        sad.sin_family=AF_INET;
        if( inet_pton( AF_INET, IP, & sad.sin_addr ) <= 0 ){
        	perror( "inet_pton() ERROR" );
        	exit( 1 );
      	}
      	sad.sin_port=htons((ushort) 5000);
     	bind(sd,(struct sockaddr *) &sad, sizeof(sad));
	player1 = player2 = draws = 0;
      	while (1){
		if(p1 == -1){
			printf("NEW GAME\n");
		}
		
        	recvfrom(sd,(char *) &buff, sizeof(int),0,
                  	(struct sockaddr *) &cad, &clen);
		recvfrom(sd, (char *) &buff1, sizeof(int),0,
			(struct sockaddr *) &cad1, &clen);

		if(p1 == -1){
			p1 = ntohs(cad.sin_port);
			p2 = ntohs(cad1.sin_port);	
		}

	        buff=ntohl(buff);
		buff1=ntohl(buff1);

		if(buff == ROCK && buff1 == PAPER){
			buff = LOSE;
			buff1 = WIN;
		}
		else if(buff == PAPER && buff1 == SCISSORS){
			buff = LOSE;
			buff1 = WIN;
		}
		else if(buff == SCISSORS && buff1 == ROCK){
			buff = LOSE;
			buff1 = WIN;
		}
		else if(buff == FINISH || buff1 == FINISH){
			printf("END OF THE GAME\n");
			if(player1 == player2){
				printf("DRAW\n");
			}
			else if(player1 > player2){
				printf("PLAYER[%d] WON\n",p1);
			}
			else{
				printf("PLAYER[%d] WON\n",p2);
			}
			buff = buff1 = FINISH;
			player1 = player2 = draws = 0;
			p1 = -1;
		}
		else if(buff == buff1){
			buff = buff1 = DRAW;
			draws++;
		}
		else{
			buff = WIN;
			buff1 = LOSE;
		}
		if(p1 == ntohs(cad.sin_port)){
			if(buff == WIN){
				player1++;
			}else if(buff == LOSE){
				player2++;
			}
		}else{
			if(buff == WIN){
				player2++;
			}
			else if(buff == LOSE){
				player1++;
			}
		}
		if(p1 != -1){
			printf("Player[%d] %d : %d Player[%d], draws(%d)\n", 
					p1, player1, player2, p2, draws);
		}

	        buff=htonl(buff);
		buff1=htonl(buff1);
	        if(sendto(sd,(char *) &buff, sizeof(int),
	                0,(struct sockaddr *) &cad, clen) < 0){
		 	perror("sendto() ERROR");
			exit(1);
		}
		if(sendto(sd,(char *) &buff1, sizeof(int),
			0,(struct sockaddr *) &cad1, clen) < 0){
			perror("sendto() ERROR");
			exit(1);
		}
      }
      return 0;
   }


