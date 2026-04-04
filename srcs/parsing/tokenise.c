#include "../minishell.h"

static int	handler_helper(char ***str, t_tok **mytok, char **token)
{
	if ((*mytok)->j > (*mytok)->start)
	{
		*token = ft_substr((*str)[(*mytok)->i], (*mytok)->start, (*mytok)->j
				- (*mytok)->start);
		if (!*token)
			return (0);
		(*mytok)->tok[(*mytok)->x++] = *token;
	}
	if (((*str)[(*mytok)->i][(*mytok)->j] == '<'
			|| (*str)[(*mytok)->i][(*mytok)->j] == '>')
		&& (*str)[(*mytok)->i][(*mytok)->j
		+ 1] == (*str)[(*mytok)->i][(*mytok)->j])
	{
		*token = ft_substr((*str)[(*mytok)->i], (*mytok)->j, 2);
		if (!*token)
			return (0);
		(*mytok)->tok[(*mytok)->x++] = *token;
		(*mytok)->j += 2;
	}
	return (1);
}

static int	handle_operator(char **str, t_tok *mytok)
{
	char	*token;
	int		old_j;

	old_j = mytok->j;
	if (!handler_helper(&str, &mytok, &token))
		return (0);
	if (mytok->j == old_j)
	{
		token = ft_substr(str[mytok->i], mytok->j, 1);
		if (!token)
			return (0);
		mytok->tok[mytok->x++] = token;
		mytok->j += 1;
	}
	mytok->start = mytok->j;
	return (1);
}

static int	handle_token(char **str, t_tok *mytok, char *token)
{
	init(mytok);
	while (str[mytok->i][mytok->j])
	{
		if (str[mytok->i][mytok->j] == '\'' && !mytok->in_dqt)
			mytok->in_sqt = !mytok->in_sqt;
		else if (str[mytok->i][mytok->j] == '"' && !mytok->in_sqt)
			mytok->in_dqt = !mytok->in_dqt;
		else if (!mytok->in_sqt && !mytok->in_dqt
			&& (str[mytok->i][mytok->j] == '|' || str[mytok->i][mytok->j] == '<'
				|| str[mytok->i][mytok->j] == '>'))
		{
			if (!handle_operator(str, mytok))
				return (0);
			continue ;
		}
		mytok->j++;
	}
	if (mytok->j > mytok->start)
	{
		token = ft_substr(str[mytok->i], mytok->start, mytok->j - mytok->start);
		if (!token)
			return (0);
		mytok->tok[mytok->x++] = token;
	}
	return (1);
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
		if (!handle_token(str, &mytok, NULL))
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
	char	**seperated;
	char	**tokenised;
	int		has_dqt;

	has_dqt = check_quotes(line, '"');
	if (has_dqt < 0 || (check_quotes(line, '\'') < 0))
		return (NULL);
	if (has_dqt > 0)
		seperated = sep(line, ' ', '"');
	else
		seperated = sep(line, ' ', '\'');
	if (!seperated)
		return (NULL);
	tokenised = handle_pr(seperated);
	freearr(seperated);
	if (!tokenised)
		return (NULL);
	if (!handled_errors(tokenised, 0, 0, 0))
	{
		freearr(tokenised);
		return (NULL);
	}
	return (tokenised);
}
