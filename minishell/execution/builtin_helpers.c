/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:15:14 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/24 22:44:00 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

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
static void    update_variable(t_env *shell, char *variable, char *path)
{
    int j;
    char    *full;
    
    full = ft_strjoin(variable,path);
    if (full)
    {
        j = envp_search(shell->envp, variable);
        env_update(full,shell,j);
        free(full);
    }
}
int update_pwd(t_env *shell)
{
    char    *old_path;
    char    new_path[4096];
    
    old_path = find_envp_value(shell->envp, "PWD");
    if (old_path)
        update_variable(shell,"OLDPWD",old_path);
    if (getcwd(new_path, sizeof(new_path)) != NULL)
        update_variable(shell,"PWD",new_path);
    else
        ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",2);
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
int  exit_value_validation(char *arg)
{
    int                 i;
    int                 sign;
    long long  result;

    if (!*arg || !arg)
        return (0);
    i = 0;
    sign = 1;
    while (arg[i] == ' ' || (arg[i] >= 9 && arg[i] <= 13))
        i++;
    if (arg[i] == '+' || arg[i] == '-')
    {
        if (arg[i] == '-')
            sign = -1;
        i++;
    }
    if (!ft_isdigit(arg[i]))
        return (0);
    result = 0;
    while (ft_isdigit(arg[i]))
    {
        result = result * 10 + (arg[i] - '0');
        i++;
    }
    return (result * sign);
}
