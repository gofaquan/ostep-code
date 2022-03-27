#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    //子进程我会从 main()函数开始执行（因此 hello world 信
    //息只输出了一次），而是直接从 fork()系统调用返回，就好像是它自己调用了 fork()
    //父进程获得的返回值是新创建子进程的 PID，而子进程获得的返回值是 0。
    //这个差别非常重要，因为这样就很容易编写代码处理两种我同的情况
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process) ,  rc = 0 为子进程
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else {
        // parent goes down this path (original process) ,而且 rc = 子进程 pid 29147
        printf("hello, I am parent of %d (pid:%d)\n",
               rc, (int) getpid());
    }
    return 0;
}
