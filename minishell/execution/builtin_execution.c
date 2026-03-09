/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:09:18 by malhassa          #+#    #+#             */
/*   Updated: 2026/03/09 06:07:15 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_cd(t_cmd *cmd, t_env *shell)
{
    char *home;
    
    if (!cmd || !cmd->argv)
        return (1);
    if (!cmd->argv[1])
    {
        home = find_envp_value(shell->envp,"HOME");
        if (!home)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
        if (chdir(home) == -1)
            return (chdir_error(home));
        return (0);
    }
    if (cmd->argv[2])
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        return (1);
    }
    if (chdir(cmd->argv[1]) == -1)
        return (chdir_error(cmd->argv[1]));
    return (0);
}

int execute_echo(t_cmd *cmd)
{
    int i;
    int newline;
    
    i = 1;
    newline = 1;
    while (cmd->argv[i] && echo_newline(cmd->argv[i]))
    {
        newline = 0;
        i++;
    }
    while (cmd->argv[i])
    {
        printf("%s", cmd->argv[i]);
        if (cmd->argv[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
    return (0);
}
int execute_pwd(void)
{
    char    pwd[4096];

    if (getcwd(pwd,sizeof(pwd)) == NULL)
    {
        perror("minishell: pwd");
        return (1);
    }
    printf("%s\n",pwd);
    return (0);
}
int execute_env(t_cmd *cmd , t_env *shell)
{
    int i;
    
    if (cmd->argv[1])
    {
        ft_putstr_fd("env: '", 2);
        ft_putstr_fd(cmd->argv[1], 2);
        ft_putstr_fd("': No such file or directory\n", 2);
        return (127);
    }
    i = 0;
    while(shell->envp[i])
    {
        write (1,shell->envp[i],ft_strlen(shell->envp[i]));
        write(1,"\n",1);
        i++;
    }
    return (0);
}
int execute_exit(t_cmd *cmd, t_env *shell)
{
    long exit_c;
    
    exit_c = 0;
    ft_putendl_fd("exit", 1);
    if (cmd->argv[1])
    {
        exit_c = (long)ft_atoi(cmd->argv[1]);
        if (cmd->argv[2])
        {
            ft_putstr_fd("exit: ", 2);
            ft_putendl_fd("too many arguments", 2);
            return (1);
        }
        if (exit_c == 0 && cmd->argv[1][0] != '0')
        {
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(cmd->argv[1], 2);
            ft_putendl_fd(": numeric argument required", 2);
            exit(2);
        }
    }
    else if (shell)
        exit_c = shell->last_exit_status;
    exit(exit_c % 256);
}
