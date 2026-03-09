/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_setup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:59:45 by malhassa          #+#    #+#             */
/*   Updated: 2026/03/09 06:08:53 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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