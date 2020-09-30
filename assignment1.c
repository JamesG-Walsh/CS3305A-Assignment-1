#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	/************************************************** command line arguments ***********************************************
		For the purposes of this explanation, assume that "external_program.out" is located in /home/usr/A1/external_program.out

		When you are testing your program, replace "/home/usr/A1/external_program.out" with the path to the executable file
		generated when you compile "external_program.c"

		To compile assignment1.c: gcc assignment1.c -o assignment1
		To run your program: ./assignment1 /home/usr/A1/external_program.out
		argv[0] = "./assignment1"
		argv[1] = "/home/usr/A1/external_program.out"

		Number of arguments (argc) = 2

		In this assignment, the path to the external program is in argv[1]
	*************************************************************************************************************************/

	// If the path of external_program.out isn't provided by the user, the program will terminate

	if (argc != 2)
	{
		printf("Invalid arguments\n");
		exit(0);
	}

	// Hint: You might find snprintf() helpful in this assignment
	/***************************************************************************************************
	 * 										 YOUR CODE GOES HERE
	 James Walsh - jwalsh57 - 250481718
	 CS3305A - Assignment 1
	 ***************************************************************************************************/
	 pid_t forking_pid_1, forking_pid_2, forking_pid_3,  parent_pid, child_1_pid, child_1point1_pid, child_2_pid;

	 forking_pid_1 = fork(); //creates child_1

	 if (forking_pid_1<0) //fork unsuccessful
	 {
		 printf("fork unsuccessful");
		 exit(1);
	 }

	 if(forking_pid_1>0) //parent
	 {
		 parent_pid = getpid();
		 child_1_pid = forking_pid_1;
		 printf("parent process (PID %d) created child_1 (PID %d) \n", parent_pid, child_1_pid);

		 printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", parent_pid, child_1_pid);
		 wait(NULL);

		forking_pid_3 = fork(); //creates child_2 from parent

		if (forking_pid_3 < 0) //fork unsuccesful
		 {
			printf("fork unsuccessful");
		 	exit(1);
		 }
		 if (forking_pid_3 > 0) //still parent
		 {
			 printf("parent (PID %d) created child_2 (PID %d)\n", getpid(), forking_pid_3);
		 }
		 if (forking_pid_3 == 0) // new process child 2
		 {
			child_2_pid = getpid();
			char child_2_pid_str[12];
			sprintf(child_2_pid_str,"%d",child_2_pid);

			printf("child_2 (PID %d) is calling an external program external_program.out and leaving child_2..\n", child_2_pid);
			int status = execl("./external_program.out", "external_program.out", child_2_pid_str, NULL);
			if (status < 0)
			{
				printf("execl() failed. status: %d\n", status);
			}
		 }
	 }

	 if(forking_pid_1==0) //new process child_1
	 {
		 forking_pid_2 = fork(); //creates child_1.1 from child_1

		 if (forking_pid_2 < 0) //fork unsuccesful
		 {
			printf("fork unsuccessful");
		 	exit(1);
		 }
		 if (forking_pid_2 > 0) //still child_1
		 {
			 printf("child_1 (PID %d) created child_1.1 (PID %d)\n", getpid(), forking_pid_2);
			 
			 wait(NULL); //wait for child_1.1 to finish
			 printf("child_1 (PID %d) is now complete\n", getpid());
		 }
		 if (forking_pid_2 == 0) //new process child_1.1
		 {
			 //printf("From child_1.1: my parent is child_1 (PID %d).  My PID is %d.\n", getppid(), getpid());
		 }
	 }
	return 0;
}