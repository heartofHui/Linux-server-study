#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis.h>

int main(int argc, char **argv) {
    unsigned int j;
    redisContext *c;
    redisReply *reply;
    const char *hostname = (argc > 1) ? argv[1] : "192.168.100.172";
    int port = (argc > 2) ? atoi(argv[2]) : 6379;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    c = redisConnectWithTimeout(hostname, port, timeout);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    /* PING server */
    reply = redisCommand(c,"PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);

    /* Set a key */
    reply = redisCommand(c,"SET %s %s", "foo:chenhui:test:redis", "hello world");
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);
	
	reply = redisCommand(c,"get foo:chenhui:test:redis");
	printf("get foo:chenhui:test:redis -->\n",reply->str);
	freeReplyObject(reply);


	reply=redisCommand(c,"incr counter:chen");
	printf("incr counter:%lld\n",reply->integer);
	
	freeReplyObject(reply);
	for(j=0;j<10;j++)
	{
		char buf[64];
		snprintf(buf,64,"%u",j);
		reply=redisCommand(c,"lpush mylist:chen element-%s",buf);
		
		freeReplyObject(reply);
		
	}
	reply=redisCommand(c,"lrange mylist:chen 0 -1");
	if(reply->type==REDIS_REPLY_ARRAY)
	{
		for(j=0;j<reply->elements;j++)
		{
			printf("%u) %s\n",j,reply->element[j]->str);
		}
	}

	freeReplyObject(reply);
	
	reply=redisCommand(c,"zadd myzset:chen mysql %d",12);
	freeReplyObject(reply);
	reply=redisCommand(c,"zrange myzset:chen 0 -1 withscores");
	if(reply->type==REDIS_REPLY_ARRAY)
	{
		printf("ss\n");
		for(j=0;j<reply->elements;j++)
		{
			printf("%s\n",reply->element[j]->str);
		}
	}
	freeReplyObject(reply);


    /* Disconnects and frees the context */
    redisFree(c);
	
    return 0;
}

