/* 
 * File:   main.c
 * Author: jb
 *
 * Created on 23 April 2014, 20:58
 */

#define DAE_NAME "randDaemon"
#define DAE_PID "/var/run/dae.pid"
#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

//#include "bool.h"
#include "signalHandler.h"

bool d_terminated = false;

/*
 * 
 */
int main(int argc, char** argv) 
{
    FILE *fp = NULL;
    pid_t process_id = 0;
    pid_t sid = 0;
    //d_terminated = false;
    bool daemonise = true;
    int count = 0;
    
#ifdef DEBUG
    daemonise = false;
#endif
    printf("Value of daemonise: %d\n", daemonise);
    
    if (daemonise)
    {
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

		// Close the connections to the terminal.
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
    }
    
    // Change the current working directory to the root.
    if (chdir("/tmp") < 0)
    {
    	return (EXIT_FAILURE);
    }
    
    printf("Debugging Daemon: %s \n", DAE_NAME);


    // open the log file in write mode.
    fp = fopen("Log.txt", "w+");

    fprintf(fp, "d_terminated: %d... \n", d_terminated);
    fflush(fp);

    while (!d_terminated)
    {
        // Don't block context switches, let the process sleep for some time.
        sleep(1);
        fprintf(fp, "Logging info... \n");
        fflush(fp);
        
        // Implement the core work for this daemon.
    }
    fclose(fp);

    return (EXIT_SUCCESS);
}

