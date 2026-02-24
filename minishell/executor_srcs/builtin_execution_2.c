/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:15:59 by mohamed           #+#    #+#             */
/*   Updated: 2026/02/23 03:49:46 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char    **new_environment(char **envp, char *cmd)
{
    char    **new_envp;
    int size_of_envp;
    int i;
    
    size_of_envp = ft_2dstrlen(envp);
    new_envp = malloc(sizeof(char *) * (size_of_envp + 2));
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
    new_envp[i] = ft_strdup(cmd);
    if (!new_envp[i])
    {
        free_2d(new_envp);
        return (NULL);
    }
    i++;
    new_envp[i] = NULL;
    free_2d(envp);
    return (new_envp);
}
int execute_export(t_cmd *cmd, t_env *env)
{
    int i;
    int index;
    
    if (!cmd->argv[1])
    {
        i = 0;
        while (env->envp[i])
        {
            printf("declare -x %s\n", env->envp[i]);
            i++;
        }
        return (0);
    }
    i = 1;
    while (cmd->argv[i])
    {
        index = envp_search(env->envp, cmd->argv[i]);
        if (index >= 0)
        {
            free(env->envp[index]);
            env->envp[index] = ft_strdup(cmd->argv[i]);
            if (!env->envp[index])
                return (1);
        }
        else
        {
            env->envp = new_environment(env->envp,cmd->argv[i]);
            if (!env->envp)
                return (1);
        }
        i++;
    }
    return (0);
}

int execute_unset(t_cmd *cmd, t_env *env)
{
    int i;
    int index;
    int j;
    
    i = 1;
    while (cmd->argv[i])
    {
        index = envp_search(env->envp, cmd->argv[i]);
        if (index >= 0)
        {
            free(env->envp[index]);
            j = index;
            while (env->envp[j])
            {
                env->envp[j] = env->envp[j + 1];
                j++;
            }
        }
        i++;
    }
    return (0);
}
