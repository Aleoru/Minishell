#include "../../inc/minishell.h"

char	*del_spaces(t_mini *mini)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = ft_calloc(1, ft_strlen(mini->input) * sizeof(char));
	while (mini->input[i])
	{
		while (mini->input[i] == ' ' && mini->input[i] != '\0')
			i++;
		while (mini->input[i] != ' ' && mini->input[i] != '\0')
		{
			if ((mini->input[i] == '|' || mini->input[i] == '<'
				|| mini->input[i] == '>') && mini->input[i - 1] == ' ')
			{
				str[j - 1] = mini->input[i];
				i++;
				break ;
			}
			else if ((mini->input[i] == '|' || mini->input[i] == '<'
				|| mini->input[i] == '>') && mini->input[i + 1] == ' ')
			{
				str[j] = mini->input[i];
				j++;
				i++;
				break ;				
			}
			str[j] = mini->input[i];
			j++;
			i++;
			if (mini->input[i] == ' ')
			{
				str[j] = mini->input[i];
				j++;
				i++;
			}
		}
	}
	if (str[j - 1] == ' ')
		str[j - 1] = '\0';
	else
		str[j] = '\0';
	free(mini->input);
	return (str);
}
 
void	split_cmd_line(t_mini *mini)
{
	int		start;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	start = 0;
	mini->cmd_pipe = malloc(mini->n_cmd * sizeof(char *));
	str = del_spaces(mini);
	printf("%s\n", str);
	while (str[i])
	{
		if ((str[i] == '|' && str[i + 1] == '|') || (str[i] == '<'
			&& str[i + 1] == '<') || (str[i] == '>'
			&& str[i + 1] == '>'))
		{
			mini->cmd_pipe[j] = ft_substr(str, start, (i - start));
			printf("%d: %s\n", j, mini->cmd_pipe[j]);
			i++;
			j++;
			start = i + 1;
		}
		else if (str[i] == '|' || str[i] == '<'
			|| str[i] == '>')
		{
			mini->cmd_pipe[j] = ft_substr(str, start, (i - start));
			printf("%d: %s\n", j, mini->cmd_pipe[j]);
			j++;
			start = i + 1;
		}
		i++;
	}
	if (j < mini->n_cmd)
	{
		mini->cmd_pipe[j] = ft_substr(str, start, (i - start));
		printf("%d: %s\n", j, mini->cmd_pipe[j]);
	}
}

void	interpreter(t_mini *mini, char **envp)
{
	int	i;

	i = 0;
	mini->n_cmd = 0;
	while(mini->input[i])
	{
		if (mini->input[i] == '|' || mini->input[i] == '<'
			|| mini->input[i] == '>')
		{
			if (mini->input[i - 1] == '<'|| mini->input[i - 1] == '>')
				i++;
			else
				mini->n_cmd++;
		}
		i++;
	}
	mini->n_cmd++;
	printf("Nº cmd: %d\n", mini->n_cmd);
	split_cmd_line(mini);
	if (envp)
		printf("\n");
/* 	mini->fd = ft_calloc(mini->n_cmd, 2 * sizeof(int));
	mini->pid = malloc(mini->n_cmd * sizeof(pid_t)); */
	//pipex(mini, envp);
}