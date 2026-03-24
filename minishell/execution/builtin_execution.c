/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 19:09:18 by malhassa          #+#    #+#             */
/*   Updated: 2026/03/24 22:23:34 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/readline.h>

int execute_cd(t_cmd *cmd, t_env *shell)
{
    if (!cmd || !cmd->argv)
        return (1);
    if (!cmd->argv[1] || (cmd->argv[1][0] == '~' && cmd->argv[1][1] == '\0')) 
        return (cd_home(shell));
    if (cmd->argv[2])
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        return (1);
    }
    if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == '\0')
        return (cd_old_path(shell));
    if (chdir(cmd->argv[1]) == -1)
        return (chdir_error(cmd->argv[1]));
    if (!update_pwd(shell))
        return (1);
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
        write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
        if (cmd->argv[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (newline)
        write(1, "\n", 1);
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
    write(1, pwd, ft_strlen(pwd));
    write(1, "\n", 1);
    return (0);
}
int execute_env(t_cmd *cmd , t_env *shell)
{
    int i;
    
    if (cmd->argv[1])
    {   
        i = 1;
        while (cmd->argv[i])
        {
            if (ft_strcmp(cmd->argv[i],"env") != 0)
                return (env_error(cmd->argv[i]));
            i++;
        }
    }
    i = 0;
    while(shell->envp[i])
    {
        if (ft_strchr(shell->envp[i],'='))
        {
            write (1,shell->envp[i],ft_strlen(shell->envp[i]));
            write(1,"\n",1);
        }
        i++;
    }
    return (0);
}
int is_zero(char *num)
{
    int i;

    i = 0;
    while (num[i])
    {
        if (num[i] != '0')
            return (0);
        i++;
    }
    return (1);
}
int execute_exit(t_cmd *cmd, t_env *shell)
{
    int   exit_c;
    
    exit_c = 0;
    ft_putendl_fd("exit", 1);
    if (cmd->argv[1])
    {
        exit_c = exit_value_validation(cmd->argv[1]);
        if (!exit_c && !is_zero(cmd->argv[1]))
        {
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(cmd->argv[1], 2);
            ft_putendl_fd(": numeric argument required", 2);
            exit(2);
        }
        if (cmd->argv[2])
        {
            ft_putstr_fd("exit: ", 2);
            ft_putendl_fd("too many arguments", 2);
            return (1);
        }
    }
    else if (shell)
        exit_c = shell->last_exit_status;
    exit((unsigned char)exit_c);
}
