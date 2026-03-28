/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:15:59 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/28 00:19:06 by mohamed          ###   ########.fr       */
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

int  env_update(char *cmd, t_env *shell,int j)
{
    char **old_envp;
    char *new_value;
    
    if (j == -1)
    {
        old_envp = shell->envp;
        shell->envp = new_environment(shell->envp, cmd);
        if (!shell->envp)
        {
            shell->envp = old_envp;
            return (0);
        }
        free_2d(old_envp);
        return (1);
    }
    if (ft_strchr(cmd,'='))
    {
        new_value = ft_strdup(cmd);
        if (!new_value)
            return (0);
        free(shell->envp[j]);
        shell->envp[j] = new_value;
    }
    return (1);
}
static int export_validation(char  *cmd)
{
    int i;
    
    i = 0;
    if (!cmd || !cmd[0])
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
            if (!env_update(cmd->argv[i],shell,j))
                return (1);
        }
            i++;
    }    
    return (had_error);
}

static int  unset_validation(char *cmd)
{
    int i;

    if (!cmd || !cmd[0])
        return (1);
    if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
        return (1);
    i = 1;
    while (cmd[i])
    {
        if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
            return (1);
        i++;
    }
    return (0);
}
static void unset_env(t_env *shell,int index)
{
    int j;

    j = 0;
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
}
int execute_unset(t_cmd *cmd, t_env *shell)
{
    int i;
    int index;
    int had_error;
    
    i = 1;
    had_error = 0;
    while (cmd->argv[i])
    {
        if (unset_validation(cmd->argv[i]))
        {
            ft_putstr_fd("minishell: unset: ", 2);
            ft_putstr_fd(cmd->argv[i], 2);
            ft_putendl_fd(": not a valid identifier", 2);
            had_error = 1;
            i++;
            continue;
        }
        index = envp_search(shell->envp,cmd->argv[i]);
        unset_env(shell,index);
        i++;
    }
    return (had_error);
}
