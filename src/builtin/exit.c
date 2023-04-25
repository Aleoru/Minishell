#include "../../inc/minishell.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_mini(t_mini *mini)
{
	(void)mini;
	rl_clear_history();
}

int	built_exit(t_mini *mini)
{
	int	len;
	int	ret;

	len = 0;
	while (mini->options[len])
		len++;
	if (len > 2)
		write(2, "exit: to many arguments", 23);
	if (len == 2)
	{
		if (is_number(mini->options[1]))
		{
			ret = ft_atoi(mini->options[1]);
			free_mini(mini);
			exit(ret);
		}
		else
		{
			write(2, "exit: need numeric argument", 27);
			free_mini(mini);
			exit(2);
		}
	}
	if (len == 1)
	{
		free_mini(mini);
		exit(0);
	}
	return (1);
}
