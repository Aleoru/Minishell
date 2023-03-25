#include "../Libft/libft.h"
#include <stdio.h>

typedef struct s_mini
{
	char    **env;
	int     env_len;
} t_mini;

// void	free_split(char **split)
// {
// 	int		i;

// 	i = 0;
// 	while (split[i] != NULL)
// 		i++;
// 	i--;
// 	while (i >= 1)
// 	{
// 		free(split[i]);
// 		i--;
// 	}
// 	free(split);
// }

void free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		printf("pre free: %d\n", i);
		free(split[i]);
		printf("free: %d\n", i);
		i++;
	}
	free(split);
}

/* recive el nombre de una variable y devuelve su contenido */
char    *expand_env(char *env_var, char **envp)
{
	char    *var;
	char    *tmp;
	int     i;

	i = 0;
	tmp = ft_strjoin(env_var, "=");
	while (envp[i])
	{
		var = ft_strnstr(envp[i] + 1, tmp, ft_strlen(tmp));
		if (var)
		{
			var = ft_strdup(envp[i] + ft_strlen(tmp) + 1);
			break ;
		}
		free(var);
		i++;
	}
	free(tmp);
	return (var);
}

/* Crea una copia de **envp añadiendo el caracter 'e' al principio de la cadena para inciar que 
es una variable de entorno, las variables normales añadiran 'v'. La posición 0 corresponde a $? 
donde se almacenara el estado de terminación del ultimo proceso ejecutado */
void	init_env(t_mini *mini, char **envp)
{
	mini->env_len = 0;
	while (envp[mini->env_len])
		mini->env_len++;
	mini->env = malloc(sizeof(char *) * mini->env_len + 2);
	mini->env_len = 0;
	mini->env[0] = ft_strdup("v?=0");
	while (envp[mini->env_len])
	{
		mini->env[mini->env_len + 1] = ft_strjoin("e", envp[mini->env_len]);
		mini->env_len++;
	}
	mini->env[mini->env_len + 1] = '\0';
}

/* Imprime las variables de entorno (las que empiezan por 'e') que se crean con init_env o añadidas 
mas tarde con built-in export. El resoto de variables tienen 'v' como primer caracter y no se imprimen */
void	print_env(t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->env[i])
	{
		if (mini->env[i][0] == 'e') // || mini->env[i][0] == 'v')
			printf("%s\n", mini->env[i] + 1);
		i++;
	}
}

/* Añade una variable normal o variable de entorno a env */
void	add_env(t_mini *mini, char *env_var)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * mini->env_len + 2);
	while(mini->env[i])
	{
		new[i] = ft_strdup(mini->env[i]);
		i++;
	}
	new[i] = ft_strdup(env_var);
	i++;
	new[i] = '\0';
	free_split(mini->env);
	mini->env = new;
	mini->env_len++;
	print_env(mini);
}

/* Borra una  variable normal o de entorn en env */
void	del_env(t_mini *mini, char *env_var)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * mini->env_len);
}

int main(int argc, char **argv, char **envp)
{
	char    *str;
	int     *len;
	char    **split;
	t_mini	mini;

	init_env(&mini, envp);
	str = expand_env(argv[1], mini.env);
	if (str)
		printf("%s\n", str);
	//print_env(&mini);
	printf("len: %d\n", mini.env_len);
	add_env(&mini, "eVAAARRR=hola");
	printf("len: %d\n", mini.env_len);
	add_env(&mini, "eVAAARRRRR=hola");
	printf("len: %d\n", mini.env_len);
	// add_env(&mini, "eVAAARRR=hola");
	// printf("len: %d\n", mini.env_len);
	print_env(&mini);
	free(str);
	return (1);
}
