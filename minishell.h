#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_HEREDOC,
	R_APPEND
}					redir_type;

typedef struct s_redir
{
	int				fd;
	char			*target;
	redir_type		type;
	struct s_redir	*next_redirection;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	int				has_pipe;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			**envp;
	int				last_exit_status;
	t_cmd			*cmd_head;
}					t_env;

typedef struct s_pipes
{
	pid_t			*pids;
	int				status;
	int				fd[2];
	int				last_read;
	int				cmds_length;
}					t_pipes;

typedef struct s_parse
{
	int				tmpsize;
	int				i;
	t_cmd			*head;
	t_cmd			*current;
	t_redir			*redir_head;
	t_redir			*redtail;
	t_redir			*cmdredir;
}					t_parse;

typedef struct s_tok
{
	int				j;
	int				i;
	int				start;
	int				in_sqt;
	int				in_dqt;
	int				x;
	char			**tok;
}					t_tok;

typedef struct s_exp
{
     int     old_len;
    int     exp_len;
    int     new_len;
    char    **new_argv;
    int     i;
    int     j;
}t_exp;


extern volatile sig_atomic_t	g_sig_status;

int					exec_error(char *cmd);
char				*find_command_path(char *path, char *cmd);
int					cd_home(t_env *shell);
int					update_pwd(t_env *shell);
int					dup2_error(int fd);
int					env_update(char *cmd, t_env *shell, int j);
int					cd_oldpwd(t_env *shell);
int					print_export(t_env *env);
int					wait_for_all(t_pipes *pipes);
int					decode_wait_status(int status);
int					echo_newline(char *cmd);
int					apply_parse(char *line, t_env *shell);
int					pipes_cleanup(t_pipes *pipes, int i);
int					chdir_error(char *cmd);
int					path_error(t_cmd *cmd);
void				path_handler(t_cmd *cmd, char *full_path);
char				*find_full_path(char *envp[]);
int					run_exe_command(t_cmd *cmd, t_env *shell);
void				execve_handler(char *path, t_cmd *cmd, t_env *shell);
int					apply_redirections(t_redir *redir, t_env *env);
int					execute_builtin(t_cmd *cmd, t_env *shell);
int					execute_cd(t_cmd *cmd, t_env *shell);
int					is_builtin(const char *s);
int					env_error(char *cmd);
int					setup_fds(int i, t_pipes *pipes);
void				memory_cleanup(char *line, t_env *shell);
int					execute_env(t_cmd *cmd, t_env *shell);
int					exit_value_validation(char *arg);
int					execute_pwd(void);
int					execute_echo(t_cmd *cmd);
void				free_2d(char **array);
int					execute_exit(t_cmd *cmd, t_env *shell);
int					apply_pipe(t_cmd **cmd, t_env *shell);
void				free_var(char *old, char *newstr, char *value);
int					execute_with_redirections(t_cmd *cmd, t_env *shell);
void				print_exit(char *message, int exit_value);
int					ft_2dstrlen(char **str);
char				**ft_envdup(char **envp, int is_new);
int					ft_strcmp(char *str, char *str2);
int					envp_search(char **envp, char *name);
char				*find_envp_value(char **envp, char *name);
int					export_error(char *cmd);
char				*add_varible(char *str);
int					execute_export(t_cmd *cmd, t_env *shell);
int					execute_unset(t_cmd *cmd, t_env *shell);
void				sigint_handler(int sig);
void				init_signals(void);
void				parser_set_last_status(int status);
void				parent_signals(void);
void				free_commands(t_cmd *cmd);
void				perror_exit(char *message, int exit_code);
int					heredocs_with_pipes(t_cmd *cmd, t_env **shell);
int					heredoc_redirection(t_redir *redir, t_env *env);
// parsing
int	delimiter_has_quote(char *s);
char	**sep(char const *s, char c,char quote);
void print_split(char **arr);
int check_quotes(char *str,char c);
char	**freearr(char **ptr);
char **tokenise(char *line);
char *removeqt(char *str,int j,size_t i);
int handled_errors(char **tokens,int i,int dqt,int sqt);
t_cmd *parse(char **tokens);
t_cmd	*addnode(void);
t_redir	*addredir(void);
void print_argv(char **argv);
int	heredoc_input(t_redir *redir, int fd[2], t_env *env);
int fill_argv(t_cmd *cmd,char **tempargv,int tmpsize);
t_cmd *end_cmd(t_parse **parse,char **argv_temp);
void set_redtype(t_redir *cmdredir,char **tokens,int i);
int fill_red(t_parse **parse,char **tokens);
void lastcmd(t_cmd *current,char **argv_temp,t_redir *redir_head,int tmpsize);
t_env *expand(t_cmd *cmdlist,char **env, int last_exit_status);
int is_varchar(char c);
int get_length(char *str,int i);
char *get_var(char *str,int i,char *var);
void clean_qts(t_cmd *cmdlist,int i,t_redir *r);
char *find_env_val(t_env *myenv,char *var);
t_env *addenv(void);
int  count_tokens(char **arr);
char **split_argv(char **argv, int pos, char **expanded);
int  is_pure_var(char *str);
void check_tok(t_cmd *curnt, t_env *myenv, char ***split, int *i);
void expand_this(char **str, t_env *myenv, int i,int state);
void	free_partial_argv(char **argv, int size);
void	init(t_tok *mytok);


#endif