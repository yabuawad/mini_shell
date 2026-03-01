/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:15:59 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/01 04:44:44 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **new_environment(char **envp, char *cmd)
{
    char    **new_envp;
    int i;

    if (!envp || !cmd)
        return (NULL);
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
    return (new_envp);
}

static int  env_update(t_cmd *cmd, t_env *env, int i ,int j)
{
    char **old_envp;
    
    if (j == -1)
    {
        old_envp = env->envp;
        env->envp = new_environment(env->envp, cmd->argv[i]);
        if (!env->envp)
        {
            env->envp = old_envp;
            return (0);
        }
        free_2d(old_envp);
    }
    else
    {
        free(env->envp[j]);
        env->envp[j] = ft_strdup(cmd->argv[i]);
        if (!env->envp[j])
            return (0);
    }
    return (1);
}
int execute_export(t_cmd *cmd, t_env *env)
{
    int i;
    int j;
    
    i = 1;
    if (!cmd->argv[1])
        return (print_export(env));
    while (cmd->argv[i])
    {
        if (!ft_isalpha(cmd->argv[i][0]))
            export_error(cmd->argv[i]);
        else
        {
            j = envp_search(env->envp,cmd->argv[i]);
            if (!env_update(cmd,env,i,j))
                return (1);
            i++;
        }
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
