#include "../minishell.h"

int	check_word(char *tokens, int i)
{
	char	c;

	while (tokens[i] && tokens[i] == ' ')
		i++;
	if (!tokens[i])
		return (0);
	if (tokens[i] == '|')
		return (0);
	if (tokens[i] == '"' || tokens[i] == '\'')
	{
		c = tokens[i++];
		while (tokens[i] && tokens[i] != c)
			i++;
		return (tokens[i] == c);
	}
	return (1);
}

int	check_red(char *tokens, int i)
{
	if (!tokens)
		return (0);
	while (tokens[i] == ' ')
		i++;
	if (!tokens[i])
		return (0);
	if (tokens[i] == '>' || tokens[i] == '<' || tokens[i] == '|')
		return (0);
	else
		return (1);
}

int	print_err(char *err_msg)
{
	ft_putendl_fd(err_msg, 2);
	return (0);
}

int	handled_errors(char **tokens, int i, int dqt, int sqt)
{
	int	j;

	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			if (tokens[i][j] == '"')
				dqt = !dqt;
			else if (tokens[i][j] == '\'')
				sqt = !sqt;
			else if (!dqt && !sqt)
			{
				if ((tokens[i][j] == '|' && (i == 0 || !tokens[i + 1]))
					|| (tokens[i][j] == '|' && !check_word(tokens[i + 1], 0)))
					return (print_err("syntax error near unexpected token |"));
				if ((tokens[i][j] == '>' || tokens[i][j] == '<')
					&& !check_red(tokens[i + 1], 0))
					return (print_err("syntax error near unexpected token"));
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	free_var(char *old, char *newstr, char *value)
{
	free(old);
	free(newstr);
	free(value);
}
