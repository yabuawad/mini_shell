#include "../minishell.h"

static int	delimiter_has_quote(char *s)
{
    int	i;

    i = 0;
    if (!s)
        return (0);
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '"')
            return (1);
        i++;
    }
    return (0);
}

static int	delimiter_match(char *str, t_redir *redir, int skip_expand)
{
    char	*delim;
    int		match;

    delim = redir->target;
    if (skip_expand)
        delim = removeqt(redir->target, 0, 0);
    if (!delim)
        return (-1);
    match = (ft_strcmp(str, delim) == 0);
    if (skip_expand)
        free(delim);
    return (match);
}

static char	*expand_heredoc(char *str, t_env *env, int skip_expand)
{
    char	*expanded;
    int		i;

    if (skip_expand || !env)
        return (str);
    expanded = ft_strdup(str);
    if (!expanded)
        return (NULL);
    i = 0;
    while (expanded[i])
    {
        if (expanded[i] == '\'')
            expanded[i] = '\a';
        i++;
    }
    expand_this(&expanded, env, 0);
    i = 0;
    while (expanded[i])
    {
        if (expanded[i] == '\a')
            expanded[i] = '\'';
        i++;
    }
    return (expanded);
}

static int  heredoc_terminate(char *str,int return_value)
{
    free(str);
    return (return_value);
}
static void  write_heredoc_line(int fd,char *str, char *expanded)
{
    write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	if (expanded != str)
		free(expanded);
	free(str);
}
int	heredoc_input(t_redir *redir, int fd[2], t_env *env)
{
    char	*str;
    char	*expanded;
    int		skip_expand;
    int		match;

    str = readline("> ");
    if (global_signal == SIGINT)
        return (heredoc_terminate(str,-1));
    if (!str)
        return (0);
    skip_expand = delimiter_has_quote(redir->target);
    match = delimiter_match(str, redir, skip_expand);
    if (match == -1)
        return (heredoc_terminate(str, -1));
    if (match == 1)
        return (heredoc_terminate(str, 0));
    expanded = expand_heredoc(str, env, skip_expand);
    if (!expanded)
        return (heredoc_terminate(str,-1));
    write_heredoc_line(fd[1],str,expanded);
	return (1);
}
