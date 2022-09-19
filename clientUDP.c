#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#define IP "127.0.0.1"
#define FINISH 4
#define DRAW 5
#define LOSE 6
#define WIN 7
int main(){
     int sd,buff,clen,slen;
     int wins, losses, draws;
      struct sockaddr_in sad, //server address
	                 cad; //client address

      sd=socket(AF_INET,SOCK_DGRAM,0);
      if (sd < 0){
	  perror( "socket() ERROR" );
	  exit(1);
      }    
      memset((char *) &sad, 0,sizeof(sad));
      sad.sin_family=AF_INET;
       if( inet_pton( AF_INET, IP, & sad.sin_addr ) <= 0 ){
        perror( "inet_pton() ERROR" );
        exit( 1 );
      }
      sad.sin_port=htons((ushort) 5000);
      cad.sin_family=AF_INET;

      if( inet_pton( AF_INET, IP, & cad.sin_addr ) <= 0 ){
        perror( "inet_pton() ERROR" );
      	 exit( 1 );
      }    
      bind(sd,(struct sockaddr *) &cad, sizeof(cad));
      
      printf("1 - ROCK\n");
      printf("2 - PAPER\n");
      printf("3 - SCISSORS\n");
      printf("[4 - FINISH]\n");
      slen=sizeof(sad);
      wins = losses = draws = 0;
      printf("YOU ARE PLAYING AS PLAYER[%d]\n", ntohs(cad.sin_port));
      while(1){
	     	printf("SCORE (w)%d, (p)%d, (r)%d\n", wins, losses, draws);
		scanf("%d", &buff);
		buff=ntohl(buff);
		if (sendto(sd,(char *) &buff,sizeof(int),0,
			(struct sockaddr *) &sad,slen)<0){
	 		perror( "sendto() ERROR" );
	 		exit( 1 );
       		}
       		recvfrom(sd,(char *) &buff,sizeof(int),0,
                 	(struct sockaddr *) &sad,&slen);
       		buff=htonl(buff);
		switch(buff){
			case FINISH:
				printf("END OF THE GAME\n");
				exit(0);
			case LOSE:
				printf("LOSE\n");
				losses++;
				break;
			case WIN:
				printf("WIN\n");
				wins++;
				break;
			case DRAW:
				printf("DRAW\n");
				draws++;
				break;	
		}
      }
      return 0;
}
