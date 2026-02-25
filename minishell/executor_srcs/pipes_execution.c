/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:52:58 by mohamed           #+#    #+#             */
/*   Updated: 2026/02/25 16:58:06 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void last_process(t_cmd *cmd,t_env *pipeline, int last_read, t_pipes *pipes, int i)
{
    pipes->pids[i] = fork();
    if (pipes->pids[i] == 0)
    {
        dup2(last_read,0);
        if (is_builtin(cmd->argv[0]))
            exit(execute_builtin(cmd, pipeline));
        else
            exit(execute_command(cmd, pipeline));
    }
}

static void child_process(int fd[2],int i ,t_cmd *cmd, t_env *pipeline,int last_read)
{
    if (i > 0)
        dup2(last_read,0);
    dup2(fd[1],1);
    if (last_read != -1)
        close(last_read);
    close(fd[1]);
    close(fd[0]);
    if (is_builtin(cmd->argv[0]))
        exit(execute_builtin(cmd, pipeline));
    else
        exit(execute_command(cmd, pipeline));
}
void    before_execution(t_cmd *cmd,t_pipes *pipes)
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
        return ;
    pipes->last_read = -1;
 
}
int    wait_for_all(t_pipes *pipes)
{
    int status;
    int i;

    i = 0;
    while(i < pipes->cmds_length)
    {
        waitpid(pipes->pids[i],&status,0);
        i++;
    }
    free(pipes->pids);
    return (WEXITSTATUS(status));
}
int apply_pipe(t_cmd *cmd,t_env *pipeline)
{
    t_pipes pipes;
    int status;
    int fd[2];
    int i;
    
    before_execution(cmd,&pipes);
    i = 0;
    while (cmd->has_pipe)
    {
        if (pipe(fd) == -1)
            return (1);
        pipes.pids[i] = fork();
        if (pipes.pids[i] == 0)
            child_process(fd,i,cmd,pipeline,pipes.last_read);
        close(fd[1]);
        if (pipes.last_read != -1)
            close(pipes.last_read);
        pipes.last_read = fd[0];
        cmd = cmd->next;
        i++;
    }
    last_process(cmd,pipeline,pipes.last_read,&pipes,i);
    status = wait_for_all(&pipes);
    return (status);
}
