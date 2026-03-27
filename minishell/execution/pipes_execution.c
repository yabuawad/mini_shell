/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:52:58 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/26 16:51:59 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void execute_final_process(t_cmd *cmd, t_env *shell)
{
    char    *path;
    char    *full_path;
    
    if (!cmd || !cmd->argv || !cmd->argv[0])
        exit(0);
    if (cmd->redirs)
    {
        if (!apply_redirections(cmd->redirs))
            exit(1);
    }
    if (is_builtin(cmd->argv[0]))
        exit(execute_builtin(cmd, shell));
    full_path = find_full_path(shell->envp);
    path = find_command_path(full_path, cmd->argv[0]);
    if (!path)
    {
        if (ft_strchr(cmd->argv[0], '/'))
            exit(exec_error(cmd->argv[0]));
        if (!full_path)
            exit(exec_error(cmd->argv[0]));
        exit(path_error(cmd));
    }
    execve_handler(path,cmd,shell);
}
static int final_process(t_cmd *cmd,t_env *shell, t_pipes *pipes, int i)
{
    int status;
    
    if (!cmd)
        return (pipes_cleanup(pipes,i));
    pipes->pids[i] = fork();
    if (pipes->pids[i] < 0)
        return (pipes_cleanup(pipes,i));
    if (pipes->pids[i] == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (pipes->last_read != -1)
        {
            if (dup2(pipes->last_read,0) == -1)
            {
                perror("minishell: dup2");
                close(pipes->last_read);
                exit(1);
            }
        }
        if (pipes->last_read != -1)
            close(pipes->last_read);
		execute_final_process(cmd, shell);
    }
    if (pipes->last_read != -1)
        close(pipes->last_read);
    status = wait_for_all(pipes);
    pipes_cleanup(pipes,0);
    return (status);
}

static void piped_command(t_pipes *pipes,int i ,t_cmd *cmd, t_env *shell)
{
    char    *path;
    char    *full_path;

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (setup_fds(i,pipes) == -1)
        exit(1);
    if (cmd->redirs)
    {
        if (!apply_redirections(cmd->redirs))
            exit(1);
    }
    if (!cmd || !cmd->argv || !cmd->argv[0])
        exit(0);
    if (is_builtin(cmd->argv[0]))
        exit(execute_builtin(cmd, shell));
    full_path = find_full_path(shell->envp);
    path = find_command_path(full_path, cmd->argv[0]);
    if (!path)  
    {
        if (ft_strchr(cmd->argv[0], '/'))
            exit(exec_error(cmd->argv[0]));
        if (!full_path)
            exit(exec_error(cmd->argv[0]));
        exit(path_error(cmd));
    }
    execve_handler(path,cmd,shell);
}
static int    before_execution(t_cmd *cmd,t_pipes *pipes)
{
    int i;
    t_cmd   *temp;
    
    temp = cmd;
    i = 1;
    while(temp && temp->has_pipe == 1)
    {
        i++;
        temp = temp->next;
    }
    pipes->cmds_length = i;
    pipes->pids = malloc(sizeof(pid_t) * pipes->cmds_length);
    if (!pipes->pids)
        return (0);
    pipes->last_read = -1;
    pipes->fd[0] = -1;
    pipes->fd[1] = -1;
    return (1);
}
int apply_pipe(t_cmd **cmd,t_env *shell)
{
    t_pipes pipes;
    int status;
    int i;
    
    if (!before_execution((*cmd),&pipes))
        return (1);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    i = 0;
    while ((*cmd) && (*cmd)->has_pipe)
    {
        if (pipe(pipes.fd) == -1)
            return (pipes_cleanup(&pipes,i));
        pipes.pids[i] = fork(); 
        if (pipes.pids[i] < 0)
            return (pipes_cleanup(&pipes,i));
        if (pipes.pids[i] == 0)
            piped_command(&pipes,i,(*cmd),shell);
        close(pipes.fd[1]);
        if (pipes.last_read != -1)
            close(pipes.last_read);
        pipes.last_read = pipes.fd[0];
        (*cmd) = (*cmd)->next;
        i++;
    }
    status = final_process((*cmd),shell,&pipes,i);
    init_signals();
    return (status);
}

