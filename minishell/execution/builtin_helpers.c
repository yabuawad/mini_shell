/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:15:14 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/13 14:57:19 by mohamed          ###   ########.fr       */
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
int  exit_value_validation(char *arg, long long *value)
{
    int                 i;
    int                 sign;
    unsigned long long  result;
    unsigned long long  limit;

    if (!arg || !*arg)
        return (0);
    i = 0;
    sign = 1;
    if (arg[i] == '+' || arg[i] == '-')
    {
        if (arg[i] == '-')
            sign = -1;
        i++;
    }
    if (!ft_isdigit(arg[i]))
        return (0);
    result = 0;
    limit = (unsigned long long)LLONG_MAX;
    if (sign == -1)
        limit++;
    while (ft_isdigit(arg[i]))
    {
        if (result > (limit - (unsigned long long)(arg[i] - '0')) / 10)
            return (0);
        result = result * 10 + (unsigned long long)(arg[i] - '0');
        i++;
    }
    if (arg[i] != '\0')
        return (0);
    if (sign == -1 && result == (unsigned long long)LLONG_MAX + 1ULL)
        *value = LLONG_MIN;
    else
        *value = (long long)result * sign;
    return (1);
}

