/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:45:18 by mohamed           #+#    #+#             */
/*   Updated: 2026/02/16 15:11:06 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

// #include <typeinfo>
#include<unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef enum e_redir_type
{
    R_IN,
    R_OUT,
    R_HEREDOC,
    R_APPEND
}redir_type;

typedef struct s_redir
{
    int fd; // -1 default
    char *target; // name of file
    redir_type type;
    struct s_redir *next_redirection;
}t_redir;

typedef struct s_cmd
{
    char			**argv;
    t_redir		*redirs;
    int has_pipe;
    struct s_cmd	*next;
}t_cmd;

typedef struct s_env
{
    char **envp; // i need it for access() and parser needs it for expanding
    int last_exit_status;
    t_cmd   *cmd_head;// the first command in the linked list
}t_env;

// typedef struct s_token
// {
//     char *value;
//     int     dqt;
//     int     sqt;
//     struct s_token *next;
// }t_token;

char	**sep(char const *s, char c,char quote);
void print_split(char **arr);
int check_quotes(char *str,char c);
char	**freearr(char **ptr);
char **tokenise(char *line);
char *removeqt(char *str);
int handled_errors(char **tokens,int i,int j,int dqt,int sqt);
t_cmd *parse(char **tokens,int i);
t_cmd	*addnode(void);
t_redir	*addredir(void);
void print_argv(char **argv);
void print_cmdlist(t_cmd *cmd);
void print_redirs(t_redir *redir);
#endif
