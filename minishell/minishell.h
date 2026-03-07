/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:45:18 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/05 22:30:26 by mohamed          ###   ########.fr       */
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
#include <errno.h>
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
    int has_pipe;
    struct s_cmd	*next;
}t_cmd;

typedef struct s_env
{
    char **envp; // i need it for access() and parser needs it for expanding
    int last_exit_status;
    t_cmd   *cmd_head;// the first command in the linked list
}t_env;

typedef struct s_pipes
{
    pid_t   *pids;
    int status;
    int fd[2];
    int last_read;
    int cmds_length;
}t_pipes;

char	*find_command_path(char *path, char *cmd);
int print_export(t_env *shell);
int    wait_for_all(t_pipes *pipes);
int echo_newline(t_cmd *cmd);
int pipes_cleanup(t_pipes *pipes);
int chdir_error(char *cmd);
int    exit_validation(t_cmd *cmd,long exit_c);
int path_error(t_cmd *cmd);
char	*find_full_path(char *envp[]);
int execute_command(t_cmd *cmd,t_env *shell);
void    apply_redirections(t_redir *redir);
int execute_builtin(t_cmd *cmd, t_env *shell);
int execute_cd(t_cmd *cmd, t_env *shell);
int is_builtin(const char *s);
int execute_env(t_cmd *cmd , t_env *shell);
int execute_pwd(void);
int execute_echo(t_cmd *cmd);
void    free_2d(char **array);
int execute_exit(t_cmd *cmd,t_env *shell);
int apply_pipe(t_cmd *cmd,t_env *shell);
int check_redirection(t_cmd *cmd,t_env *shell);
void print_exit(char *message, int exit_value);
int ft_2dstrlen(char **str);
char **ft_envdup(char **envp,int is_new);
int ft_strcmp(char *str,char *str2);
int envp_search(char **envp, char *name);
char    *find_envp_value(char **envp, char *name);
int export_error(char *cmd);
char    *add_varible(char *str);
int execute_export(t_cmd *cmd, t_env *shell);
int execute_unset(t_cmd *cmd, t_env *shell);
t_cmd *parse_input(char *input);
void free_commands(t_cmd *cmd);
void    perror_exit(char *message,int exit_code);
int	heredocs_with_pipes(t_cmd *cmd);
void    heredoc_redirection(t_redir *redir);
#endif