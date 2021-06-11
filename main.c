#include "pipex.h"

void	exec_child(char **paths, char **cmd, int *fd, bool first_child)
{
	int		i;

	if (!first_child)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	i = -1;
	while (paths[++i])
		execve(paths[i], cmd, NULL);
}

void	ft_exit(char *err)
{
	if (err)
		printf("%s\n", err);
	exit(0);
}

int	main(int argc, char *argv[], char **envp)
{
	char	**paths;
	char	***commands;
	int		i;
	int		fd[2];
	pid_t	pid;

	paths = NULL;
	if (argc < 5)
		ft_exit("Insufficient arguments");
	commands = parse_commands(argc, argv);
	if (pipe(fd) == -1)
		ft_exit("Unable to open pipe file descriptors");
	i = 2;
	while (i < argc - 1)
	{
		pid = fork();
		if (pid == -1)
			ft_exit("Unable to fork new process");
		if (pid == 0)
		{
			paths = get_paths(envp, argv, i);
			if (i == 2)
				exec_child(paths, commands[i - 2], fd, true);
			else if (i == argc - 2)
				write_to_file(argv[4], fd, paths, commands[i - 2]);
			else
				exec_child(paths, commands[i - 2], fd, false);
		}
		i++;
	}
	ft_free_arr_arrs(commands);
	return (0);
}
