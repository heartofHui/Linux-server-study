#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return (void *)1;
}
void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}
void *thr_fn3(void *arg)
{
    while(1) {
        printf("thread 3 writing\n");
        sleep(1);
    }
}
int main(void)
{
    pthread_t tid;
    void *tret;
    pthread_create(&tid, NULL, thr_fn1, NULL);
    pthread_join(tid, &tret);
    printf("thread 1 exit code %d\n", (int)tret);
    pthread_create(&tid, NULL, thr_fn2, NULL);
    pthread_join(tid, &tret);
    printf("thread 2 exit code %d\n", (int)tret);
    pthread_create(&tid, NULL, thr_fn3, NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid, &tret);
    printf("thread 3 exit code %d\n", (int)tret);
    return 0;
}

/*
  一个线程可以调用 pthread_cancel 终止同一进程中的另一个线程。
  线程可以调用 pthread_exit 终止自己。
*/
/*pthread_join()
  调用该函数的线程将挂起等待，直到 id 为 thread 的线程终止。thread 线程以不
  同的方法终止，通过 pthread_join 得到的终止状态是不同的，总结如下：
    如果 thread 线程通过 return 返回，value_ptr 所指向的单元里存放的是
  thread 线程函数的返回值。
    如果thread线程被别的线程调用pthread_cancel异常终止掉，value_ptr
  所指向的单元里存放的是常数 PTHREAD_CANCELED。
    如果 thread 线程是自己调用 pthread_exit 终止的，value_ptr 所指向的
  单元存放的是传给 pthread_exit 的参数。*/