/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:30:14 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/02 21:29:18 by malhassa         ###   ########.fr       */
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
        if (!new_envp[i])
        {
            free_2d(new_envp);
            return (NULL);
        }
        i++;
    }
    new_envp[i] = NULL;
    return (new_envp);
}

static char    *variable_name(char *var)
{
    int i;
    char    *str;
    
    i = 0;
    
    while(var[i] && var[i] != '=')
        i++;
    str = malloc(sizeof(char) * (i + 1));
    if (!str)
        return (NULL);
    i = 0;
    while(var[i] && var[i] != '=')
    {
        str[i] = var[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}
int     envp_search(char **envp, char *name)
{
    int i;
    int length;
    char    *variable;

    i = 0;
    while (envp[i])
    {
        variable = variable_name(name);
        if (!variable)
            return (-1);
        length = ft_strlen(variable);
        if (ft_strncmp(envp[i],variable,length) == 0)
        {
            if (variable)
                free(variable);
            return (i);
        }
        i++;
        if (variable)
            free(variable);
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

