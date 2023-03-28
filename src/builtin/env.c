#include "../Libft/libft.h"
#include <stdio.h>

typedef struct s_mini
{
	char    **env;
	int     env_len;
} t_mini;

void free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		//printf("pre free: %d\n", i);
		free(split[i]);
		//printf("free: %d\n", i);
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
		i++;
	}
	free(tmp);
	return (var);
}

/* Devuelve el nombre de la variable dentro de la string */
char	*name_var(char *env_var)
{
	char	*name;
	int		i;

	i = 0;
	while (env_var[i] != '=')
		i++;
	name = malloc(sizeof(char) * i);
	i = 0;
	while (env_var[i + 1] != '=')
	{
		name[i] = env_var[i + 1];
		i++;
	}
	name[i] = '\0';
	return (name);
}

/* Crea una copia de **envp añadiendo el caracter 'e' al principio de la cadena para inciar que 
es una variable de entorno, las variables normales añadiran 'v'. La posición 0 corresponde a $? 
donde se almacenara el estado de terminación del ultimo proceso ejecutado */
void	init_env(t_mini *mini, char **envp)
{
	mini->env_len = 0;
	while (envp[mini->env_len])
		mini->env_len++;
	mini->env = malloc(sizeof(char *) * (mini->env_len + 2) + 1);
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
mas tarde con built-in export. El resto de variables tienen 'v' como primer caracter y no se imprimen */
void	print_env(t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->env[i])
	{
		if (mini->env[i][0] == 'e' || mini->env[i][0] == 'v')
			printf("var[%d]: %s\n", i, mini->env[i] + 1);
		i++;
	}
}

/* Añade una variable normal o variable de entorno a env */
void	add_env(t_mini *mini, char *env_var)
{
	char	**new;
	char	*name;
	int		i;

	i = 0;
	name = name_var(env_var);
	if (expand_env(name, mini->env) == NULL)
	{
		new = malloc(sizeof(char *) * (mini->env_len + 2) + 1);
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
		mini->env_len += 1;
	}
	free(name);
}

int	contain_var(t_mini *mini, char *env_var ,int i)
{
	char	*name;
	char	*tmp;

	tmp = name_var(mini->env[i]);
	name = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = ft_strjoin(env_var, "=");
	if (ft_strnstr(name, tmp, ft_strlen(tmp)) == NULL)
	{
		free(tmp);
		free(name);
		return (0);
	}
	free(tmp);
	free(name);
	return (1);
}

/* Borra una  variable normal o de entorn0 en env (env_var sera el solo nombre de la variable)*/
void	del_env(t_mini *mini, char *env_var_name)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (expand_env(env_var_name, mini->env))
	{
		new = malloc((sizeof(char *) * mini->env_len) + 1);
		while (mini->env[i])
		{
			if (!contain_var(mini, env_var_name, i))
			{
				new[j] = ft_strdup(mini->env[i]);
				j++;
				i++;
			}
			else
				i++;
		}
		new[j] = '\0';
		free(mini->env);
		mini->env = new;
	}
}

/* Cambia el contenido de una  variable */
void	change_value(t_mini *mini, char *new_value)
{	
	int		i;
	char	*name;

	i = 0;
	name = name_var(new_value);
	if (expand_env(name, mini->env))
	{
		while (mini->env[i])
		{
			if (contain_var(mini, name, i))
			{
				free(mini->env[i]);
				mini->env[i] = ft_strdup(new_value);
			}
			i++;
		}
		free(name);
	}
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
	add_env(&mini, "eVAARR=hola");
	change_value(&mini, "eVAAARRR=adios");
	//del_env(&mini, "VAAARRR");
	//del_env(&mini, "USER");
	//del_env(&mini, "HOME");
	//del_env(&mini, "_");
	print_env(&mini);
	free(str);
	// str = expand_env("USER", mini.env);
	// if (str)
	// 	printf("%s\n", str);
	return (1);
}
