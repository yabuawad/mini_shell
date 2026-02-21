/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:59:52 by malhassa          #+#    #+#             */
/*   Updated: 2026/02/21 03:51:54 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int execute_builtin(t_cmd *cmd, t_env *env)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (1);
    if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
        return (execute_echo(cmd));
    else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
        return (execute_cd(cmd));
    else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
        return (execute_pwd());
    else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
        return (execute_env(cmd, env));
    else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
        return (execute_export(cmd, env));
    else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
        return (execute_unset(cmd, env));
    else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
        return (execute_exit(cmd, env));
    return (1);
}

int execute_command(t_cmd *cmd,t_env *env)
{
    char    *path;
    pid_t pid;
    int status;
    
    path = find_command_path(find_full_path(env->envp),cmd->argv[0]);
    if (!path)
    {
        ft_putstr_fd("Command not found\n",2);
        return (127);
    }
    pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd("Fork Error\n",2);
        return (1);//??
    }
    if (pid == 0)
    {
        execve(path,cmd->argv,env->envp);
        exit(127);
    }
    waitpid(pid,&status,0);
    free(path);
    return (WEXITSTATUS(status));
}
