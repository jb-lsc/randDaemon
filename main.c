/* 
 * File:   main.c
 * Author: jb
 *
 * Created on 23 April 2014, 20:58
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/*
 * 
 */
int main(int argc, char** argv) 
{
    FILE *fp = NULL;
    pid_t process_id = 0;
    pid_t sid = 0;
    
    // Create child process
    process_id = fork();
    
    // Indication of fork() failure
    if (process_id < 0) 
    {
        printf("Fork Failed!\n");
        exit(1);
    }
    
    // Kill the parent process.
    if (process_id > 0)
    {
        printf("Child process created, ID: %d \n", process_id);
        exit(0);
    }
    
    // unmask the file mode.
    umask(0);
    
    // set the new session
    sid = setsid();
    if (sid < 0)
    {
        // Failure
        exit(1);
    }
    
    // Change the current working directory to the root.
    chdir("/tmp");
    
    // Close the connections to the terminal.
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    // open the log file in write mode.
    fp = fopen("Log.txt", "w+");
    while (1)
    {
        // Don't block context switches, let the process sleep for some time.
        sleep(1);
        fprintf(fp, "Logging info... \n");
        fflush(fp);
        
        // Implement the core work for this daemon.
    }
    fclose(fp);
    return (0);
}

