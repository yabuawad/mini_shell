/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:36:09 by yabuawad          #+#    #+#             */
/*   Updated: 2026/04/05 11:36:12 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_2dstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_builtin(const char *s)
{
	if (!s || !*s)
		return (0);
	return (ft_strcmp((char *)s, "echo") == 0 || ft_strcmp((char *)s, "cd") == 0
		|| ft_strcmp((char *)s, "pwd") == 0 || ft_strcmp((char *)s,
			"export") == 0 || ft_strcmp((char *)s, "unset") == 0
		|| ft_strcmp((char *)s, "env") == 0 || ft_strcmp((char *)s,
			"exit") == 0);
}

int	ft_strcmp(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i] && str[i] == str2[i])
		i++;
	return ((unsigned char)str[i] - (unsigned char)str2[i]);
}

int	delimiter_has_quote(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}
