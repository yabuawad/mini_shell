/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_setup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:59:45 by malhassa          #+#    #+#             */
/*   Updated: 2026/02/21 03:42:35 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    infile_redirection(t_cmd *cmd)
{
    int infile_fd;

    infile_fd = open(cmd->redirs->target,O_RDONLY);
    if (infile_fd < 0)
        print_exit("failed to open a file",1);
    if (dup2(infile_fd,0) == -1)
        print_exit("dup2 failed",1);
    if (close(infile_fd) == -1)
        print_exit("close failed",1);
}

void    outfile_redirection(t_cmd *cmd)
{
    int outfile_fd;

    outfile_fd = open(cmd->redirs->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd < 0)
        print_exit("failed to open a file",1);
    if (dup2(outfile_fd, 1) == -1)
        print_exit("dup2 failed",1);
    if (close(outfile_fd) == -1)
        print_exit("close failed",1);
}
void    append_redirection(t_cmd *cmd)
{
    int append_fd;
    
    append_fd = open(cmd->redirs->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (append_fd < 0)
        print_exit("failed to open a file", 1);
    if (dup2(append_fd, 1) == -1)
        print_exit("dup2 failed", 1);
    if (close(append_fd) == -1)
        print_exit("close failed", 1);
}

// void    heredoc_redirection(t_cmd *cmd)
// {
       
// }
int check_redirection(t_cmd *cmd,t_env *env)
{
    char    *cmd_path;
    int status;
    pid_t pid;
    
    if (!cmd || !cmd->redirs)
        return (0);
    cmd_path = find_command_path(find_full_path(env->envp), cmd->argv[0]);
    if (!cmd_path)
    {
        ft_putstr_fd("Command not found\n", 2);
        return (127);
    }
    pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd("Fork Error\n", 2);
        return (1);
    }
    if (pid == 0)
    {
        if (cmd->redirs->type == R_IN)
            infile_redirection(cmd);
        else if (cmd->redirs->type == R_OUT)
            outfile_redirection(cmd);
        else if (cmd->redirs->type == R_APPEND)
            append_redirection(cmd);
        execve(cmd_path, cmd->argv, env->envp);
        perror("execve");
        exit(127);
    }
    waitpid(pid, &status, 0);
    free(cmd_path);
    return (WEXITSTATUS(status));
}
