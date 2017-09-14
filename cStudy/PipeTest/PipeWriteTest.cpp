#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include "../Includes/times.h"

int main(int argc, char ** argv)
{
    const char *fifo_name = "/tmp/my_fifo";
    int pipe_fd = -1;
    //int data_fd = -1;
    int res = 0;
    const int open_mode = O_WRONLY;
    int bytes_sent = 0;
    char buffer[PIPE_BUF + 1]={0};

    if(access(fifo_name, F_OK) == -1)
    {
        //管道文件不存在
        //创建命名管道
        res = mkfifo(fifo_name, 0777);
        if(res != 0)
        {
            fprintf(stderr, "Could not create fifo %s\n", fifo_name);
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d opening FIFO O_WRONLY\n", getpid());
    //以只写阻塞方式打开FIFO文件，以只读方式打开数据文件
    pipe_fd = open(fifo_name, open_mode);
    printf("Process %d result %d\n", getpid(), pipe_fd);

    if(pipe_fd != -1)
    {
        int bytes_read = 0;
        //向数据文件读取数据
        //bytes_read = read(data_fd, buffer, PIPE_BUF);
        //buffer = "hello pipe!\0";
		memset(buffer, 0, PIPE_BUF + 1);
        strncpy(buffer, "hello pipe!", PIPE_BUF);
        bytes_read = strlen(buffer);
        //buffer[bytes_read] = '\0';
        int64_t timeStart = getTimeMsec();
        int64_t timeEnd = 0;
        int32_t i = 0;
        while(bytes_read > 0)
        {
            //向FIFO文件写数据
            res = write(pipe_fd, buffer, bytes_read);
            if(res == -1)
            {
                fprintf(stderr, "Write error on pipe\n");
                exit(EXIT_FAILURE);
            }
            //累加写的字节数，并继续读取数据
            bytes_sent += res;
//            bytes_read = read(data_fd, buffer, PIPE_BUF);
//            buffer[bytes_read] = '\0';
            i++;
            timeEnd = getTimeMsec();
            if(timeEnd-timeStart>1000)
            {
            	printf("ending,num=%d\n",i);
            	break;
            }
        }
        close(pipe_fd);
        //close(data_fd);
    }
    else
        exit(EXIT_FAILURE);

    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
}
