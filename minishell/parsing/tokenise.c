#include "../minishell.h"

static void init(t_tok *mytok)
{
    mytok->j = 0;
    mytok->start = 0;
    mytok->in_sqt = 0;
    mytok->in_dqt = 0;
}
static void	handle_operator(char **str, t_tok *mytok)
{
	if (mytok->j > mytok->start)
		mytok->tok[mytok->x++] = ft_substr(str[mytok->i], mytok->start, mytok->j - mytok->start);
	if ((str[mytok->i][mytok->j] == '<' || str[mytok->i][mytok->j] == '>')
		&& str[mytok->i][mytok->j + 1] == str[mytok->i][mytok->j])
	{
		mytok->tok[mytok->x++] = ft_substr(str[mytok->i], mytok->j, 2);
		mytok->j += 2;
	}
	else
	{
		mytok->tok[mytok->x++] = ft_substr(str[mytok->i], mytok->j, 1);
		mytok->j += 1;
	}
	mytok->start = mytok->j;
}

static void	handle_token(char **str, t_tok *mytok)
{
	init(mytok);
	while (str[mytok->i][mytok->j])
	{
		if (str[mytok->i][mytok->j] == '\'' && !mytok->in_dqt)
			mytok->in_sqt = !mytok->in_sqt;
		else if (str[mytok->i][mytok->j] == '"' && !mytok->in_sqt)
			mytok->in_dqt = !mytok->in_dqt;
		else if (!mytok->in_sqt && !mytok->in_dqt
			&& (str[mytok->i][mytok->j] == '|' || str[mytok->i][mytok->j] == '<' || str[mytok->i][mytok->j] == '>'))
		{
			handle_operator(str, mytok);
			continue;
		}
		mytok->j++;
	}
	if (mytok->j > mytok->start)
		mytok->tok[mytok->x++] = ft_substr(str[mytok->i], mytok->start, mytok->j - mytok->start);
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
		handle_token(str, &mytok);
		mytok.i++;
	}
	mytok.tok[mytok.x] = NULL;
	return (mytok.tok);
}
char **tokenise(char *line)
{
    char  **seperated;
    char **tokenised;

    if(check_quotes(line,'"') < 0 || check_quotes(line,'\'') < 0)
        return NULL;
    if(check_quotes(line,'"') > 0)
        seperated = sep(line,' ','"');
    else
        seperated = sep(line,' ','\'');
    if(!seperated)
        return NULL;
    tokenised = handle_pr(seperated);
    freearr(seperated);
    if(!tokenised)
        return NULL;
    if (handled_errors(tokenised,0,0,0))
            print_split(tokenised);
    else
    {
        printf("error\n");
        freearr(tokenised);
        return NULL;
    }
    return(tokenised);
}
