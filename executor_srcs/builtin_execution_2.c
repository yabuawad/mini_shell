/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:15:59 by mohamed           #+#    #+#             */
/*   Updated: 2026/02/26 04:28:49 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **new_environment(char **envp, char *cmd)
{
    char    **new_envp;
    int i;

    i = 0;
    new_envp = malloc(sizeof(char *) * (ft_2dstrlen(envp) + 2));  
    
    while (envp[i])
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
    i++;
    new_envp[i] = NULL;
    free_2d(envp);
    return (new_envp);
}
int execute_export(t_cmd *cmd, t_env *env)
{
    int i;
    int j;
    
    i = 1;
    if (!cmd->argv[1]) // only export command with no args
        return (print_export(env));
    while (cmd->argv[i])
    {
        j = envp_search(env->envp,cmd->argv[i]);
        if (j == -1) // new variable
            env->envp = new_environment(env->envp,cmd->argv[i]);
        else
        {
            free(env->envp[j]);
            env->envp[j] = ft_strdup(cmd->argv[i]);
            if (!env->envp[j])
                return (0);
        } 
        i++;
    }    
    return (1);
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
        if (index != -1)
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
