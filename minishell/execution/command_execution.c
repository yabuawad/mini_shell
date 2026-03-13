/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:59:52 by malhassa          #+#    #+#             */
/*   Updated: 2026/03/13 03:20:15 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int execute_builtin(t_cmd *cmd, t_env *shell)
{
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (1);
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return (execute_echo(cmd));
    else if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return (execute_cd(cmd, shell));
    else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        return (execute_pwd());
    else if (ft_strcmp(cmd->argv[0], "env") == 0)
        return (execute_env(cmd, shell));
    else if (ft_strcmp(cmd->argv[0], "export") == 0)
        return (execute_export(cmd, shell));
    else if (ft_strcmp(cmd->argv[0], "unset") == 0)
        return (execute_unset(cmd, shell));
    else if (ft_strcmp(cmd->argv[0], "exit") == 0)
        return (execute_exit(cmd, shell));
    return (1);
}

int run_command(t_cmd *cmd,t_env *shell)
{
    pid_t pid;
    int status;
    char    *path;
    char    *full_path;

    full_path = find_full_path(shell->envp);
    path = find_command_path(full_path, cmd->argv[0]);
    if (!path)
    {
        if (ft_strchr(cmd->argv[0], '/'))
            return (exec_error(cmd->argv[0]));
        if (!full_path)
            return (exec_error(cmd->argv[0]));
        return (path_error(cmd));
    }
    pid = fork();
    if (pid == -1)
    {
        perror("minishell: fork\n");
        return (1);
    }
    if (pid == 0)
        execve_handler(path,cmd,shell);
    waitpid(pid,&status,0);
    free(path);
    return (decode_wait_status(status));
}
