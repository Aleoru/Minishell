#include "../../inc/minishell.h"

void	split_cmd_line(t_mini *mini)
{
	int		i;
	int		y;
	char	*str;

	i = 0;
	y = 0;
	str = malloc(ft_strlen(mini->input) * sizeof(char));
	mini->cmd_pipe = malloc(mini->n_cmd * sizeof(char *));
	printf("%s\n", mini->input);
	while (mini->input[i])
	{
		while (mini->input[i] == ' ' && mini->input[i] != '\0')
			i++;
		while (mini->input[i] != ' ' && mini->input[i] != '\0')
		{
			str[y] = mini->input[i];
			y++;
			i++;
			if (mini->input[i] == ' ')
			{
				str[y] = mini->input[i];
				y++;
				i++;
			}
			printf("%s\n", str);
		}
	}
	free(mini->input);
	printf("%s\n", str);
	free(str);
}

void	interpreter(t_mini *mini)
{
	int	i;

	i = 0;
	mini->n_cmd = 0;
	while(mini->input[i])
	{
		if (mini->input[i] == '|')
			mini->n_cmd++;
		i++;
	}
	mini->n_cmd++;
	printf("Nº cmd: %d\n", mini->n_cmd);
	split_cmd_line(mini);
/* 	mini->fd = ft_calloc(mini->n_cmd, 2 * sizeof(int));
	mini->pid = malloc(mini->n_cmd * sizeof(pid_t)); */
	//pipex(mini);
}