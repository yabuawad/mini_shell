/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:45:18 by mohamed           #+#    #+#             */
/*   Updated: 2026/02/19 22:15:30 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include<unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>   
#include <stdlib.h>
#include <fcntl.h>
#include "../libft/libft.h"

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
    struct s_cmd	*next;
}t_cmd;

typedef struct s_env
{
    char **envp; // i need it for access() and parser needs it for expanding
    int last_exit_status;
    t_cmd   *cmd_head;// the first command in the linked list
}t_env;

char	*find_command_path(char *path, char *cmd);
char	*find_full_path(char *envp[]);
int execute_command(t_cmd *cmd,char **envp);
int execute_builtin(t_cmd *cmd, t_env *env);
int execute_cd(t_cmd *cmd);
int is_builtin(const char *s);
int execute_env(t_cmd *cmd , t_env *env);
int execute_pwd(void);
int execute_echo(t_cmd *cmd);
void    free_2d(char **array);
int execute_exit(t_cmd *cmd,t_env *env);
int check_redirection(t_cmd *cmd,t_env *env);
void print_exit(char *message, int exit_value);
#endif