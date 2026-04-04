#include "../minishell.h"

static int	parser_helper(char **tokens, t_parse **parse, char **argv_temp)
{
	while (tokens[(*parse)->i])
	{
		if (ft_strncmp(tokens[(*parse)->i], "|", 1) == 0)
		{
			argv_temp[(*parse)->tmpsize] = NULL;
			(*parse)->current->has_pipe = 1;
			(*parse)->current = end_cmd(parse, argv_temp);
			if (!(*parse)->current)
				return (0);
			(*parse)->tmpsize = 0;
			(*parse)->redir_head = NULL;
			(*parse)->i++;
		}
		else if (ft_strncmp(tokens[(*parse)->i], "<", 1) == 0
			|| ft_strncmp(tokens[(*parse)->i], ">", 1) == 0)
		{
			(*parse)->cmdredir = addredir();
			if (!fill_red(parse, tokens))
				return (0);
			(*parse)->i += 2;
		}
		else
			argv_temp[((*parse)->tmpsize)++] = tokens[(*parse)->i++];
	}
	return (1);
}

static void	init_parse(t_parse *parse)
{
	parse->tmpsize = 0;
	parse->i = 0;
	parse->redir_head = NULL;
	parse->cmdredir = NULL;
	parse->redtail = NULL;
	parse->current = parse->head;
}

static int	dotheparsing(t_parse **parse, char ***tokens, char **argv_temp)
{
	if (!(*parse)->head)
	{
		free(*parse);
		return (0);
	}
	init_parse(*parse);
	if (!parser_helper(*tokens, parse, argv_temp))
	{
		free_commands((*parse)->head);
		free(*parse);
		return (0);
	}
	argv_temp[(*parse)->tmpsize] = NULL;
	lastcmd((*parse)->current, argv_temp, (*parse)->redir_head,
		(*parse)->tmpsize);
	if (!(*parse)->current->argv)
	{
		free_commands((*parse)->head);
		free(*parse);
		return (0);
	}
	return (1);
}

t_cmd	*parse(char **tokens)
{
	t_parse	*parse;
	char	*argv_temp[1024];
	t_cmd	*head;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->head = addnode();
	if (!dotheparsing(&parse, &tokens, argv_temp))
		return (NULL);
	head = parse->head;
	free(parse);
	return (head);
}
