/*
 * udpclient.c
 * 
 * Copyright 2020 Unknown <stack@host1>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char **argv)
{
	int sock;
	char message[30];
	int str_len;
	
	socklen_t adr_sz;
	
	struct sockaddr_in serv_adr, from_adr;
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n",argv[0]);
	}
	
	sock =socket(PF_INET, SOCK_DGRAM,0);
	if(sock==-1)
		error_handling("socket() error");
		
	memset(&serv_adr, 0, sizeof(serv_adr));

    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(atoi(argv[2]));
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); 
    
    while(1)
    {
		fputs("INSERT MESSAGE (q to quit) : ", stdout);
		fgets(message, sizeof(message),stdin);
		if(!strcmp(message,"q\n")|| !strcmp(message,"Q\n"))
			break;
		
		sendto(sock,message,strlen(message),0,(struct sockaddr*)&serv_adr, sizeof(serv_adr));
		adr_sz=sizeof(from_adr);
		str_len=recvfrom(sock,message,BUF_SIZE,0,(struct sockaddr*)&from_adr, &adr_sz);
		message[str_len]=0;
		printf("MESSAGE FROM SERVER : %s", message);
		
	}
	close(sock);
	
    
    
	return 0;
}


void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
