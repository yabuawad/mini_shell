/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:30:14 by mohamed           #+#    #+#             */
/*   Updated: 2026/02/20 17:16:32 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_envdup(char **envp)
{
    int i;
    char    **new_envp;
    
    i = ft_2dstrlen(envp);
    new_envp = malloc(sizeof (char *) * (i + 1));
    if (!new_envp)
        return (NULL);
    i = 0;
    while(envp[i])
    {
        new_envp[i] = ft_strdup(envp[i]);
        i++;
    }
    new_envp[i] = NULL;
    return (new_envp);
}

char    *variable_name(char **envp, int index)
{
    int i;
    char    *str;
    
    i = 0;
    while(envp[index][i] != '=')
        i++;
    str = malloc(sizeof(char) * (i + 1));
    if (!str)
        return (NULL);
    i = 0;
    while(envp[index][i] != '=')
    {
        str[i] = envp[index][i];
        i++;
    }
    str[i] = '\0';
    return (str);
}
int envp_search(char **envp, char *name)
{
    int i;
    int length;

    i = 0;
    length = ft_strlen(name);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, length) == 0 && envp[i][length] == '=')
            return (i);
        i++;
    }
    return (-1);
}

char    *find_envp_value(char **envp, char *name)
{
    int i;
    int length;
    
    i = envp_search(envp, name);
    if (i == -1)
        return (NULL);
    length = ft_strlen(name) + 1;
    return (envp[i] + length);
}

char    *add_varible(char *str)
{
    char    *new_var;
    
    if (ft_strchr(str,'='))
        new_var = malloc(ft_strlen(str) + 3);
    else
        new_var = malloc(ft_strlen(str) + 1);
    if (!new_var)
        return (NULL);
    return (new_var);
}
