/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:15:59 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/09 06:07:12 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char    **new_environment(char **envp, char *cmd)
{
    char    **new_envp;
    int i;

    if (!envp || !cmd)
        return (NULL);
    i = 0;
    new_envp = ft_envdup(envp,1);  
    if (!new_envp)
        return (NULL);
    i = ft_2dstrlen(envp);
    new_envp[i] = ft_strdup(cmd);
    if (!new_envp[i])
    {
        free_2d(new_envp);
        return (NULL);
    }
    i++;
    new_envp[i] = NULL;
    return (new_envp);
}

static int  env_update(t_cmd *cmd, t_env *shell, int i ,int j)
{
    char **old_envp;
    
    if (j == -1)
    {
        old_envp = shell->envp;
        shell->envp = new_environment(shell->envp, cmd->argv[i]);
        if (!shell->envp)
        {
            shell->envp = old_envp;
            return (0);
        }
        free_2d(old_envp);
    }
    else
    {
        if (ft_strchr(cmd->argv[i],'='))
        {
            free(shell->envp[j]);
            shell->envp[j] = ft_strdup(cmd->argv[i]);
            if (!shell->envp[j])
                return (0);
        }
    }
    return (1);
}
static int export_validation(char  *cmd)
{
    int i;
    
    i = 0;
    if (!cmd[0] || !cmd)
        return (export_error(""));
    if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
        return (export_error(cmd));
    i = 1;
    while (cmd[i] && cmd[i] != '=')
    {
        if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
            return (export_error(cmd));
        i++;
    }
    return (0);
}
int execute_export(t_cmd *cmd, t_env *shell)
{
    int i;
    int j;
    int had_error;
    
    i = 1;
    had_error = 0;
    if (!cmd->argv[1])
        return (print_export(shell));
    while (cmd->argv[i])
    {
        if (export_validation(cmd->argv[i]))
            had_error = 1;
        else
        {
            j = envp_search(shell->envp,cmd->argv[i]);
            if (!env_update(cmd,shell,i,j))
                return (1);
        }
            i++;
    }    
    return (had_error);
}

int execute_unset(t_cmd *cmd, t_env *shell)
{
    int i;
    int index;
    int j;
    
    i = 1;
    while (cmd->argv[i])
    {
        index = envp_search(shell->envp, cmd->argv[i]);
        if (index != -1)
        {
            free(shell->envp[index]);
            j = index;
            while (shell->envp[j])
            {
                shell->envp[j] = shell->envp[j + 1];
                j++;
            }
        }
        i++;
    }
    return (0);
}
