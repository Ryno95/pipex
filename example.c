#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define PIPE_STANDARD_ARRAY_SIZE 2
#define READ_FD 0
#define WRITE_FD 1
#define CHILD_PROCESS_ID 0
#define SYSTEM_ERR -1

// int sum_of_part_of_array(int *array, int start, int end)
// {
// 	int i;
// 	int sum;

// 	if (!array)
// 		return (-1);
// 	i = start;
// 	sum = 0;
// 	while (i < end)
// 	{
// 		sum += array[i]; 
// 		i++;
// 	}
// 	return (sum);
// }

// static void close_multiple(int *multi_fd)
// {
// 	close(multi_fd[READ_FD]);
// 	close(multi_fd[WRITE_FD]);
// }
// static int get_sum_of_child(int *fd)
// {
// 	int sum_of_child;

// 	sum_of_child = 0;
// 	if (read(fd[READ_FD], &sum_of_child, sizeof(int)) == SYSTEM_ERR)
// 		return (-1);
// 	return(sum_of_child);
// }

int execute_command(const char *path, const char *argv[])
{
	return (execve(path, (char *const *)argv, NULL));
}

int child_process(const char *argv[])
{
	int fd;
	int fd2;

	fd = open("results.txt", O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		exit(3);
		
	fd2 = dup2(fd, STDOUT_FILENO);
	if (fd2 != STDOUT_FILENO)
		return (4);

	if (execute_command(argv[0], argv) == -1)
		return (-1);
	close(fd);
	close(fd2);
	return (1);
}

int parent_process()
{
	int wstatus;
	wait(&wstatus);
	int status_code = WEXITSTATUS(wstatus);
	if (status_code == 0)
		printf("SUCCESS!");
	else
		printf("Failure code with status code: %d\n", WEXITSTATUS(wstatus));
	return (1);
}

int main(void)
{
	const char *argv[] = {"/sbin/ping", "-c", "1", "google.com", NULL};
	const int pid = fork();

	if (pid == SYSTEM_ERR)
		return (2);
	else if (pid == CHILD_PROCESS_ID)
		child_process(argv);
	else
		parent_process();
}

// int main(void)
// {
//     int pipe_one[PIPE_STANDARD_ARRAY_SIZE]; // child to parent
//     int pipe_two[PIPE_STANDARD_ARRAY_SIZE]; // parent to child
//     int pid;
//     int x;
//     int y;

//     if (pipe(pipe_one) == SYSTEM_ERR)
//         return (1);
//     if (pipe(pipe_two) == SYSTEM_ERR)
//         return (1);   
//     pid = fork();
//     if (pid == SYSTEM_ERR)
//         return (2);
//     if (pid == CHILD_PROCESS_ID)
//     {
//         if (read(pipe_one[READ_FD], &x, sizeof(x)) == SYSTEM_ERR)
//             return (3);
//         printf("Child received: %d\n", x);
//         x *= 4;
//         if (write(pipe_one[WRITE_FD], &x, sizeof(x)) == SYSTEM_ERR)
//             return (4);
//         printf("Child wrote: %d\n", x);
//     }
//     else
//     {
//         srand(time(NULL));
//         y = rand() % 10;
//         if (write(pipe_one[WRITE_FD], &y, sizeof(y)) == SYSTEM_ERR)
//             return (5);
//         printf("Parent wrote: %d\n", y);
//         sleep(1);
//         if (read(pipe_one[READ_FD], &y, sizeof(y)) == SYSTEM_ERR)
//             return (6);
//         printf("Result received by parent: %d\n", y);
//     }
//     close_multiple(pipe_one);
//     return (0);
// }

// int main(void)
// {
//     int arr[] = {1, 2, 3, 8, 9, 10};
//     const int array_size = sizeof(arr) / sizeof(int);
// ;   int fd[PIPE_STANDARD_ARRAY_SIZE];
//     int pid;
//     int start, end;

//     if (pipe(fd) == SYSTEM_ERR)
//         return (1);
	
//     pid = fork();
//     if (pid == SYSTEM_ERR)
//         return (2);
	
//     if (pid == CHILD_PROCESS_ID)
//         assign_start_end_vals(&start, &end, 0, (start + (array_size / 2)));
//     else
//         assign_start_end_vals(&start, &end, array_size / 2, array_size);
 
//     int sum = sum_of_part_of_array(arr, start, end);

//     printf("Partial sum: %d\n", sum);

//     if (pid == CHILD_PROCESS_ID)
//     {
//         close(READ_FD);
//         if (write(fd[WRITE_FD], &sum, sizeof(int)) == SYSTEM_ERR)
//             return (4);
//         close_multiple(fd);
//     }
//     else
//     {
//         sum += get_sum_of_child(fd);
//         close_multiple(fd);
//         printf("Total sum: %d\n", sum);
//         waitpid(-1, NULL, 0);
//     }
	
//     return (0);
// }