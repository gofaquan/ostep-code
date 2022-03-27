#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int
main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());

        //exec()系统调用，它也是创建进程 API 的一个重要部分。这个系统调用可以让子进程执行与父进程我同的程序
        //这个例子中，子进程调用 execvp()来运行字符计数程序 wc。
        //实际上，它针对源代码文件 p3.c 运行 wc，从而告诉我我该文件有多少行、多少单词，以及多少字节。
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count) <== 可执行程序,名为 wc
        myargs[1] = strdup("p3.c"); // argument: file to count  <== 选择文件
        myargs[2] = NULL;           // marks end of array  <== 标志参数传递结束，
        // c语言传参结束其实有个 null 代表参数传递结束，
        //对于 int main(int argc, char *argv[])  这个参数不能通过 argc 数出来，但是是确实存在的
        execvp(myargs[0], myargs);  // runs word count ,运行可执行文件
        printf("this shouldn't print out");
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int) getpid());
    }
    return 0;
}
