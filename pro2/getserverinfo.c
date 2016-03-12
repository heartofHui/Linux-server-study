#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc,char ** argv)
{
	struct sockaddr_in addr;
	struct hosten *host;
	char **alias;
	
	if(argc<2)
	{
		fprintf(stderr,"Usage:%s hostname|ip\n",argv[0]);
		exit(1);
	}
	argv++;
	for(;*argv!=NULL;argv++)
	{
		//if is IP
		if(inet_aton(*argv,&addr.sin_addr)!=0)
		{
			host=gethostbyaddr((char *)&addr.sin_addr,4,AF_INET);
			printf("Address information of IP %s\n",*argv);
		}
		else
		{
			host=gethostbyname(*argv);
			printf("Address information of host %s\n",*argv);
		}
		if(host==NULL)
		{
			fprintf(stderr,"No address information of %s\n",*argv);
			continue;
		}
		printf("official host name %s\n",host->h_name);
		printf("name aliases:");
		for(alias=host->h_aliases;*alias!=NULL;alias++)
		{
			printf("%s",*alias);
		}
		
		printf("\nIp address:");
		for(alias=host->h_addr_list;*alias!=NULL;alias++)
		{
			printf("%s ",inet_ntoa(*(struct in_addr )(* alias)));
		}
	}
}