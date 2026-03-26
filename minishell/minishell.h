/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:45:18 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/20 05:59:45 by mohamed          ###   ########.fr       */
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
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
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
    int fd;
    char *target;
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
    char **envp;
    int last_exit_status;
    t_cmd   *cmd_head;
}t_env;

typedef struct s_pipes
{
    pid_t   *pids;
    int status;
    int fd[2];
    int last_read;
    int cmds_length;
}t_pipes;

int exec_error(char *cmd);
char	*find_command_path(char *path, char *cmd);
int cd_home(t_env *shell);
int update_pwd(t_env *shell);
int env_update(char *cmd, t_env *shell,int j);
int cd_old_path(t_env *shell);
int print_export(t_env *env);
int wait_for_all(t_pipes *pipes);
int decode_wait_status(int status);
int echo_newline(char *cmd);
int pipes_cleanup(t_pipes *pipes, int i);
int chdir_error(char *cmd);
int path_error(t_cmd *cmd);
char	*find_full_path(char *envp[]);
int run_command(t_cmd *cmd,t_env *shell);
void execve_handler(char *path,t_cmd *cmd, t_env *shell);
int apply_redirections(t_redir *redir);
int execute_builtin(t_cmd *cmd, t_env *shell);
int execute_cd(t_cmd *cmd, t_env *shell);
int is_builtin(const char *s);
int env_error(char *cmd);
int setup_fds(int i,t_pipes *pipes);
int execute_env(t_cmd *cmd , t_env *shell);
int  exit_value_validation(char *arg);
int execute_pwd(void);
int execute_echo(t_cmd *cmd);
void free_2d(char **array);
int execute_exit(t_cmd *cmd,t_env *shell);
int apply_pipe(t_cmd **cmd,t_env *shell);
int execute_with_redirections(t_cmd *cmd,t_env *shell);
void print_exit(char *message, int exit_value);
int ft_2dstrlen(char **str);
char **ft_envdup(char **envp,int is_new);
int ft_strcmp(char *str,char *str2);
int envp_search(char **envp, char *name);
char *find_envp_value(char **envp, char *name);
int export_error(char *cmd);
char *add_varible(char *str);
int execute_export(t_cmd *cmd, t_env *shell);
int execute_unset(t_cmd *cmd, t_env *shell);
void parser_set_last_status(int status);
void free_commands(t_cmd *cmd);
void perror_exit(char *message,int exit_code);
int heredocs_with_pipes(t_cmd *cmd);
int heredoc_redirection(t_redir *redir);
//parsing 
char	**sep(char const *s, char c,char quote);
void print_split(char **arr);
int check_quotes(char *str,char c);
char	**freearr(char **ptr);
char **tokenise(char *line);
char *removeqt(char *str);
int handled_errors(char **tokens,int i,int j,int dqt,int sqt);
t_cmd *parse(char **tokens,int i,int tmpsize);
t_cmd	*addnode(void);
t_redir	*addredir(void);
void print_argv(char **argv);
void print_cmdlist(t_cmd *cmd);
void print_redirs(t_redir *redir);
void fill_argv(t_cmd *cmd,char **tempargv,int tmpsize);
t_cmd *end_cmd(t_cmd *current,int tmpsize,char **argv_temp,t_redir *redir_head);
void set_redtype(t_redir *cmdredir,char **tokens,int i);
void fill_red(t_redir *cmdredir,t_redir **redtail,t_redir **redir_head,char **tokens,int i);
void lastcmd(t_cmd *current,char **argv_temp,t_redir *redir_head,int tmpsize);
t_env *expand(t_cmd *cmdlist,char **env);
int is_varchar(char c);
int get_length(char *str,int i);
char *get_var(char *str,int i,char *var);
char *find_env_val(t_env *myenv,char *var);
#endif