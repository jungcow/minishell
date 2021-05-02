#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	clear_envset(char **envset)
{
	int		i;

	i = 0;
	while (envset[i])
	{
		free(envset[i]);
		i++;
	}
	free(envset);
}

int		dup_envset(char **env, char *str)
{
	free(*env);
	*env = ft_strdup(str);
	if (*env == NULL)
		return (0);
	return (1);
}

int		count_envset(char *arg)
{
	int		i;
	int		num;

	i = 0;
	num = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && (arg[i + 1] != '$' && arg[i + 1] != '\0'))
			num++;
		i++;
	}
	if (*arg != '$')
		num++;
	return (num);
}

int		create_envset(char ***envset, char *arg, int *flag)
{
	int		i;
	int		j;

	printf("create start\n");
	i = count_envset(arg);
	if (arg[ft_strlen(arg) - 1] == '$')
		*flag = 1;
	*envset = (char **)malloc(sizeof(char *) * (i + (*flag) + 1));
	if (*envset == NULL)
		return (0);
	j = -1;
	while (++j < i + *flag)
		(*envset)[j] = NULL;
	(*envset)[j] = NULL;
	printf("create done\n");
	return (1);
}

int		init_envset(char **envset, char *arg, int flag)
{
	char	**strs;
	int		num;
	int		i;

	printf("init start\n");
	strs = ft_split(arg, '$');
	if (strs == NULL)
		return (0);
	num = count_envset(arg);
	i = -1;
	while (++i < num)
		if (!dup_envset(&envset[i], strs[i]))
		{
			clear_envset(strs);
			clear_envset(envset);
			return (0);
		}
	if (flag && !dup_envset(&envset[i], "$"))
	{
		clear_envset(strs);
		clear_envset(envset);
		return (0);
	}
	envset[i + flag] = NULL;
	clear_envset(strs);
	printf("init done\n");
	return (1);
}

int		replace_envset(char **envset, char *arg)
{
	char	*value;
	int		i;
	int		num;

	printf("replace start\n");
	i = -1;
	printf("replace arg: %s\n", arg);
	printf("replace first: %c\n", *arg);
	if (*arg != '$')
		i = 0;
	num = count_envset(arg);
	printf("num: %d\n", num);
	printf("i: %d\n", i);
	while (envset[++i] && i < num )
	{
		value = getenv(envset[i]);
		printf("value: %s\n", value);
		if (!value && !dup_envset(&envset[i], ""))
		{
			clear_envset(envset);
			return (0);
		}
		else if (value && !dup_envset(&envset[i], value))
		{
			clear_envset(envset);
			return (0);
		}
	}
	printf("replace done\n");
	return (1);
}

int		join_envset(char **envset, char **arg)
{
	int		i;
	int		len;
	char	*str;

	printf("join start\n");
	i = -1;
	len = 0;
	while (envset[++i])
		len += ft_strlen(envset[i]);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
	{
		clear_envset(envset);
		return (0);
	}
	i = -1;
	len = 0;
	while (envset[++i])
	{
		ft_strncpy(str + len, envset[i], ft_strlen(envset[i]));
		len += ft_strlen(envset[i]);
	}
	str[len] = '\0';
//	free(*arg);
	*arg = str;
	printf("join done\n");
	return (1);
}

int main(int argc, char *argv[])
{
	char	 **envset;
	char	*arg[3];
	int		flag;
	int		j;

	printf("%s\n", argv[1]);
	envset = NULL;
	j = 1;
	while (j < argc)
	{
		flag = 0;
		if (!create_envset(&envset, argv[j], &flag))
			return (0);
		if (!init_envset(envset, argv[j], flag))
			return (0);
		if (!replace_envset(envset, argv[j]))
			return (0);
		if (!join_envset(envset, &argv[j]))
			return (0);
		j++;
	}
	j = 1;
	while (j < argc)
	{
		printf("arg[%d]: %s\n", j, argv[j]);
		j++;
	}
	clear_envset(envset);
	return (0);
}

// gcc main.c -I../../libft ../../libft/*.c -fsanitize=address
