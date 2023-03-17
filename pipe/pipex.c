#include "../../inc/minishell.h"

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*command;

	while (*paths)
	{
		command = ft_strjoin(*paths, cmd);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

/* version 2, comandos y ejecutables */
void	exe_command(t_mini *mini, char *cmd, char **envp)
{
	char	*cwd;

	//printf("check\n");
	cwd = NULL;
	//cwd = ft_strdup(getcwd(cwd, sizeof(1024)));
	cwd = ft_strdup("/home/fgalan-r/Minishell/PipexPlus");
	//printf("cwd: %s\n", cwd);
	mini->command_args = ft_split(cmd, ' ');
	if (ft_strchr(mini->command_args[0], '/'))
	{
		if (ft_strncmp(mini->command_args[0], "./", 2) == 0)
		{
			mini->command = ft_strjoin(cwd, mini->command_args[0] +1);
		}
		else if (ft_strncmp(mini->command_args[0], "..", 2) == 0)
		{
			mini->command = ft_strjoin(cwd, "/");
			mini->command = ft_strjoin(cwd, mini->command_args[0]);
		}
		else if (ft_strncmp(mini->command_args[0], "/", 1) == 0)
		{
			mini->command = ft_strdup(mini->command_args[0]);
		}
		mini->command_args[0] = ft_strdup(ft_strrchr(mini->command_args[0], '/') + 1);
	}
	else
		mini->command = get_cmd(mini->paths, mini->command_args[0]);
	execve(mini->command, mini->command_args, envp);
}

void	close_fd(t_mini *mini)
{
	int		i;

	i = 0;
	while (i < mini->n_cmd -1)
	{
		close(mini->fd[i][0]);
		close(mini->fd[i][1]);
		i++;
	}
}

void	dup_fd(t_mini *mini, int children)
{
	if (children == 0)
	{
		if (mini->in_fd != -2)
			dup2(mini->in_fd, STDIN_FILENO);
		if (mini->out_fd != -2 && mini->n_cmd == 1)
			dup2(mini->out_fd, STDOUT_FILENO);
		if (mini->n_cmd > 1)
			dup2(mini->fd[0][1], STDOUT_FILENO);
	}
	else if (children == mini->n_cmd -1)
	{
		if (mini->out_fd != -2)
			dup2(mini->out_fd, STDOUT_FILENO);
		dup2(mini->fd[children -1][0], STDIN_FILENO);
	}
	else
	{
		dup2(mini->fd[children][1], STDOUT_FILENO);
		dup2(mini->fd[children - 1][0], STDIN_FILENO);
	}
}

void	exe_pipex(t_mini *mini, char **argv, char **envp)
{
	int		i;

	i = 0;
	while (i < mini->n_cmd -1)
	{
		pipe(mini->fd[i]);
		i++;
	}
	i = 0;
	while (i < mini->n_cmd)
	{
		mini->pid[i] = fork();
		if (mini->pid[i] == 0)
		{
			dup_fd(mini, i);
			close_fd(mini);
			exe_command(mini, argv[i + 1], envp);
		}
		i++;
	}
	close_fd(mini);
	waitpid(-1, NULL, 0);
}

void	pipex(t_mini *mini)
{
	mini->in_fd = -2;
	mini->out_fd = -2;
	mini->double_out = 0; // ( 1 >> ) ( 0 > )
	//mini->outfile = ft_strdup("./file.txt");
	//mini->infile = ft_strdup("./infile.txt");
	mini->infile = NULL;
	mini->outfile = NULL;
	if (mini->infile != NULL)
		mini->in_fd = open(mini->infile, O_RDONLY);
	if (mini->outfile != NULL && mini->double_out)
		mini->out_fd = open(mini->outfile, O_APPEND | O_CREAT | O_RDWR, 0664); // O_APPEND escribe desde el final (redireccion >>)
	else
		mini->out_fd = open(mini->outfile, O_TRUNC | O_CREAT | O_RDWR, 0664); // O_TRUNC escribe desde el principio (redireccion >)
	exe_pipex(mini, argv, envp);
	if (mini->outfile != NULL)
		close(mini->out_fd);
	if (mini->infile != NULL)
		close(mini->in_fd);
	free_split(mini->paths);
	mini->in_fd = -2;
	mini->out_fd = -2;
}

	/* ejecutar programa */
	// char	cwd[PATH_MAX];
	// char	*path = NULL;
	// if (getcwd(cwd, sizeof(cwd)) != NULL)
	// 	printf("getcwd: %s\n", cwd);
	// char **test_cmd = ft_split("./my_prog hola holita adios", ' ');
	// if (test_cmd[0][0] == '.' && test_cmd[0][1] == '/')
	// 	path = ft_strjoin(cwd, test_cmd[0] +1);
	// else if (test_cmd[0][0] == '.' && test_cmd[0][1] == '.')
	// {
	// 	path = ft_strjoin(cwd, "/");
	// 	path = ft_strjoin(path, test_cmd[0]);
	// }
	// else if (test_cmd[0][0] == '/')
	// 	path = ft_strdup(test_cmd[0]);
	// printf("prog path: %s\n", path);
	// test_cmd[0] = ft_strdup(ft_strrchr(test_cmd[0], '/')+1);
	// printf("test_cmd[0]: %s\n", test_cmd[0]);
	// execve(path, test_cmd, envp);
	/* ejecutar programa  v1 */
	//char **test_cmd = ft_split("my_prog hola holita adios", ' ');
	//execve("/home/fgalan-r/Minishell/PipexPlus/../PipexPlus/my_prog", test_cmd, envp);