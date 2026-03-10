/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:15:14 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/11 01:31:36 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo_newline(char *cmd)
{
    int i;

    if (!cmd || cmd[0] != '-' || cmd[1] != 'n')
        return (0);
    i = 2;
    while (cmd[i])
    {
        if (cmd[i] != 'n' && cmd[i] != 'e' && cmd[i] != 'E')
            return (0);
        i++;
    }
    return (1);
}
int update_pwd(t_env *shell)
{
    int j;
    char    *old_path;
    char    new_path[4096];
    char    *full_old;
    char    *full_new;
    
    old_path = find_envp_value(shell->envp, "PWD");
    if (old_path)
    { 
        full_old = ft_strjoin("OLDPWD=", old_path);
        if (full_old)
        {
            j = envp_search(shell->envp,"OLDPWD");
            env_update(full_old, shell, j);
            free(full_old);
        }
    }
    if (getcwd(new_path, sizeof(new_path)) != NULL)
    {
        full_new = ft_strjoin("PWD=", new_path);
        if (full_new)
        {
            j = envp_search(shell->envp,"PWD");
            env_update(full_new, shell, j);
            free(full_new);
        }
    }
    return (1);
}
int cd_home(t_env *shell)
{
    char    *home;
    
    home = find_envp_value(shell->envp,"HOME");
    if (!home)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        return (1);
    }
    if (chdir(home) == -1)
        return (chdir_error(home));
    if (!update_pwd(shell))
        return (1);
    return (0);
}
int cd_old_path(t_env *shell)
{
    char    *prv_pwd;
 
    prv_pwd = find_envp_value(shell->envp,"OLDPWD");
    if (!prv_pwd)
    {
        ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
        return (1);
    }
    if (chdir(prv_pwd) == -1)
        return (chdir_error(prv_pwd));
    ft_putendl_fd(prv_pwd, 1);
    if (!update_pwd(shell))
        return (1);
    return (0);
}
