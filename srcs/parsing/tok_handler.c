#include "../minishell.h"

void	tok_init(t_tok *mytok)
{
	mytok->j = 0;
	mytok->start = 0;
	mytok->in_sqt = 0;
	mytok->in_dqt = 0;
}

int	flush_pending(char **str, t_tok *mytok)
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

int	extract_operator(char **str, t_tok *mytok)
{
	char	*token;
	int		is_double;

	is_double = (str[mytok->i][mytok->j] == '<'
			|| str[mytok->i][mytok->j] == '>') && str[mytok->i][mytok->j
		+ 1] == str[mytok->i][mytok->j];
	if (is_double)
	{
		token = ft_substr(str[mytok->i], mytok->j, 2);
		if (!token)
			return (0);
		mytok->tok[mytok->x++] = token;
		mytok->j += 2;
	}
	else
	{
		token = ft_substr(str[mytok->i], mytok->j, 1);
		if (!token)
			return (0);
		mytok->tok[mytok->x++] = token;
		mytok->j += 1;
	}
	return (1);
}

int	handle_operator(char **str, t_tok *mytok)
{
	if (!flush_pending(str, mytok))
		return (0);
	if (!extract_operator(str, mytok))
		return (0);
	mytok->start = mytok->j;
	return (1);
}

void	handle_quotes(char c, t_tok *mytok)
{
	if (c == '\'' && !mytok->in_dqt)
		mytok->in_sqt = !mytok->in_sqt;
	else if (c == '"' && !mytok->in_sqt)
		mytok->in_dqt = !mytok->in_dqt;
}
