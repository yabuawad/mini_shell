/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_setup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:59:45 by malhassa          #+#    #+#             */
/*   Updated: 2026/02/26 04:38:47 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    infile_redirection(t_redir *redir)
{
    int infile_fd;

    infile_fd = open(redir->target, O_RDONLY);
    if (infile_fd < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(redir->target, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        exit(1);
    }
    if (dup2(infile_fd,0) == -1)
        perror_exit("minishell: dup2",1);
    if (close(infile_fd) == -1)
        perror_exit("minishell: close",1);
}

static void    outfile_redirection(t_redir *redir)
{
    int outfile_fd;

    outfile_fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(redir->target, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        exit(1);
    }
    if (dup2(outfile_fd, 1) == -1)
        perror_exit("minishell: dup2",1);
    if (close(outfile_fd) == -1)
        perror_exit("minishell: close",1);
}
static void    append_redirection(t_redir *redir)
{
    int append_fd;
    
    append_fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (append_fd < 0)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(redir->target, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        exit(1);
    }
    if (dup2(append_fd, 1) == -1)
        perror_exit("minishell: dup2",1);
    if (close(append_fd) == -1)
        perror_exit("minishell: close",1);
}
static void    heredoc_redirection(t_redir *redir)
{
    int fd[2];
    char    *str;

    if (pipe(fd) == -1)
        perror_exit("minishell: pipe",1);
    while (1)
    {
        str = readline("> ");
        if(!str)
            break;
        if (strcmp(str,redir->target) == 0)
        //     break;
        // write(fd[1], str, ft_strlen(str));
        // write(fd[1],"\n",1);
        // free(str);
    }
    close(fd[1]);
    if (str)
        free(str);
    if (dup2(fd[0],0) == -1)
        perror_exit("minishell: dup2",1);
    close(fd[0]);
}
void    apply_redirections(t_redir *redir)
{
    while (redir)
    {
        if (redir->type == R_IN)
            infile_redirection(redir);
        else if (redir->type == R_OUT)
            outfile_redirection(redir);
        else if (redir->type == R_APPEND)
            append_redirection(redir);
        else if (redir->type == R_HEREDOC)
            heredoc_redirection(redir);
        redir = redir->next_redirection;
    }
}

static void    child_execution(t_cmd *cmd, t_env *env)
{
    int status;
    char    *path;
    
    apply_redirections(cmd->redirs);
    if (!cmd->argv || !cmd->argv[0])
        exit(0);
    if (is_builtin(cmd->argv[0]))
    {
        status = execute_builtin(cmd, env);
        exit(status);
    }
    path = find_command_path(find_full_path(env->envp), cmd->argv[0]);
    if (!path)
        path_error(cmd);
    execve(path, cmd->argv, env->envp);
    perror("execve");
    free(path);
    exit(127);
}
int check_redirection(t_cmd *cmd,t_env *env)
{
    int status;
    pid_t pid;
    
    if (!cmd || !cmd->redirs)
        return (0);
    pid = fork();
    if (pid == -1)
    {
        perror("minishell: fork");
        return (1);
    }
    if (pid == 0)
        child_execution(cmd, env);
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}
