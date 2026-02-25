/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:52:53 by malhassa          #+#    #+#             */
/*   Updated: 2026/02/24 17:25:19 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*find_full_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*access_checker(char **str, char *cmd)
{
	char	*tmp;
	char	*temp;
	int		i;

	i = 0;
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		if (!tmp)
			return (NULL);
		temp = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!temp)
			return (NULL);
		if (!access(temp, X_OK))
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *path, char *cmd)
{
	char	**str;
	char	*temp;

	if (!path || !cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		return (NULL);
	}
	str = ft_split(path, ':');
	if (!str)
		return (NULL);
	temp = access_checker(str, cmd);
	free_2d(str);
	if (!temp)
		return (NULL);
	return (temp);
}
