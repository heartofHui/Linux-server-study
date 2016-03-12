#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFLEN 1024

int main(int argc,char ** argv)
{
    int sockfd,newfd;
    struct sockaddr_in s_addr,c_addr;
    char buf[BUFLEN];
    socklen_t len;
    unsigned int port,listnum;
    fd_set rfds;
    struct timeval tv;
    int retval,maxfd;
    ///create socket
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("socket");
        exit(errno);
    }
    else
    {
        printf("socket create success!\n");
    }
    //set port
    if(argv[2])
        port=atoi(argv[2]);
    else
        port=4567;
    //set listen length
    if(argv[3])
        listnum=atoi(argv[3]);
    else
        listnum=3;
    //set server ip
    bzero(&s_addr,sizeof(s_addr));
    s_addr.sin_family=AF_INET;
    s_addr.sin_port=htons(port);

    if(argv[1])
        s_addr.sin_addr.s_addr=inet_addr(argv[1]);
    else
        s_addr.sin_addr.s_addr=INADDR_ANY;
    ///bind address and port on socket
    if((bind(sockfd,(struct sockaddr*) &s_addr,sizeof(struct sockaddr)))==-1)
    {
        perror("bind");
        exit(errno);
    }
    else
        printf("bind sucecss!\n");
    ///listen self
    if(listen(sockfd,listnum)==-1)
    {
        perror("listen");
        exit(errno);
    }
    else
        printf("the server is listening!\n");
    while(1)
    {
        printf("----chat beginning----\n");
        len=sizeof(struct sockaddr);
        if((newfd=accept(sockfd,(struct sockaddr*) &c_addr,&len))==-1)
        {
            perror("accept");
            exit(errno);
        }
        else
        {
            printf("the chatting client is:%s %d\n",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));

        }
        while(1)
        {
            ///clean the fd into set
            FD_ZERO(&rfds);
            //add standard fd into set
            FD_SET(0,&rfds);
            maxfd=0;
            //add now connecting fd into set
            FD_SET(newfd,&rfds);

            if(maxfd<newfd)
            {
                maxfd=newfd;
            }
            tv.tv_sec=5;
            tv.tv_usec=0;
            ///wait chatting
            retval=select(maxfd+1,&rfds,NULL,NULL,&tv);
            if(retval==-1)
            {
                printf("select error,exit\n");
                break;
            }
            else if(retval==0)
            {
                printf("server hasnt input info\n");
                continue;
            }
            else
            {
                //input info
                if(FD_ISSET(0,&rfds))
                {

                    _retry:
                    bzero(buf,BUFLEN);


                    fgets(buf,BUFLEN,stdin);
                    if(!strncasecmp(buf,"quit",4))
                    {
                        printf("server wants to end\n");
                        break;
                    }
                    if(!strncasecmp(buf,"\n",1))
                    {
                        printf("there is only ENTER\n");;
                        goto _retry;
                    }
                    if(strchr(buf,'\n'))
                    {
                        len=send(newfd,buf,strlen(buf)-1,0);
                    }
                    else
                        len=send(newfd,buf,strlen(buf),0);
                    if(len>0)
                        printf("\tinfo send success,length is:%d\n",len);
                    else
                    {
                        printf("send false\n");
                        break;
                    }

                }
                ///client info coming
                if(FD_ISSET(newfd,&rfds))
                {
                    ///receive
                    bzero(buf,BUFLEN);
                    len=recv(newfd,buf,BUFLEN,0);
                    if(len>0)
                        printf("client's info is:%s,length:%d\n",buf,len);
                    else
                    {
                        if(len<0)
                            printf("receive false\n");
                        else
                            printf("client quit\n");
                        break;
                    }
                }
            }
        }
        ///
        close(newfd);
        printf("server quit?y/n");
        bzero(buf,BUFLEN);
        fgets(buf,BUFLEN,stdin);
        if(!strncasecmp(buf,"y",1))
        {
            printf("server quit\n");
            break;
        }

    }
    close(sockfd);
    return 0;
}
