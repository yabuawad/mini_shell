#include "../minishell.h"

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	handle_last_token(char **str, t_tok *mytok)
{
	char	*token;

	if (mytok->j <= mytok->start)
		return (1);
	token = ft_substr(str[mytok->i], mytok->start, mytok->j - mytok->start);
	if (!token)
		return (0);
	mytok->tok[mytok->x++] = token;
	return (1);
}

static int	handle_token(char **str, t_tok *mytok)
{
	char	c;

	tok_init(mytok);
	while (str[mytok->i][mytok->j])
	{
		c = str[mytok->i][mytok->j];
		if (c == '\'' || c == '"')
			handle_quotes(c, mytok);
		else if (!mytok->in_sqt && !mytok->in_dqt && is_operator(c))
		{
			if (!handle_operator(str, mytok))
				return (0);
			continue ;
		}
		mytok->j++;
	}
	return (handle_last_token(str, mytok));
}

char	**handle_pr(char **str)
{
	t_tok	mytok;

	mytok.tok = malloc(sizeof(char *) * 1024);
	if (!mytok.tok)
		return (NULL);
	mytok.i = 0;
	mytok.x = 0;
	while (str[mytok.i])
	{
		if (!handle_token(str, &mytok))
		{
			mytok.tok[mytok.x] = NULL;
			freearr(mytok.tok);
			return (NULL);
		}
		mytok.i++;
	}
	mytok.tok[mytok.x] = NULL;
	return (mytok.tok);
}

char	**tokenise(char *line)
{
	char	**separated;
	char	**tokenised;
	int		has_dqt;

	has_dqt = check_quotes(line, '"');
	if (has_dqt < 0 || check_quotes(line, '\'') < 0)
		return (NULL);
	if (has_dqt > 0)
		separated = sep(line, ' ', '"');
	else
		separated = sep(line, ' ', '\'');
	if (!separated)
		return (NULL);
	tokenised = handle_pr(separated);
	freearr(separated);
	if (!tokenised)
		return (NULL);
	if (!handled_errors(tokenised, 0, 0, 0))
	{
		freearr(tokenised);
		return (NULL);
	}
	return (tokenised);
}
