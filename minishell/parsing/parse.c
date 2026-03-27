#include "../minishell.h"

static void	parser_helper(char **tokens, t_parse **parse,
					char *argv_temp[1024])
{
    // parse->i = 0;
    while (tokens[(*parse)->i])
    {
        if (ft_strncmp(tokens[(*parse)->i], "|", 1) == 0)
        {
            argv_temp[(*parse)->tmpsize] = NULL;
            (*parse)->current->has_pipe = 1;
            (*parse)->current = end_cmd(parse, argv_temp);
            (*parse)->tmpsize = 0;
            (*parse)->redir_head = NULL;
            (*parse)->i++;
        }
        else if (ft_strncmp(tokens[(*parse)->i], "<", 1) == 0 || ft_strncmp(tokens[(*parse)->i], ">", 1) == 0)
        {
            (*parse)->cmdredir = addredir();
            fill_red(parse, tokens);
            (*parse)->i += 2;
        }
        else
			argv_temp[((*parse)->tmpsize)++] = tokens[(*parse)->i++];
    }
}

t_cmd *parse(char **tokens)
{
    t_parse *parse; 
    char    *argv_temp[1024];
    t_cmd	*head;

    parse = malloc(sizeof(t_parse));
    if (!parse)
        return (NULL);
    parse->tmpsize = 0;
    parse->i = 0;
    parse->head = addnode();
    if (!parse->head) 
	{
		free(parse);
		return (NULL);
	}
    parse->current = parse->head;
    parse->redir_head = NULL;
    parse->cmdredir = NULL;
    parse->redtail = NULL;
    parser_helper(tokens, &parse, argv_temp);    
    argv_temp[parse->tmpsize] = NULL;
    lastcmd(parse->current, argv_temp, parse->redir_head, parse->tmpsize);
    head = parse->head;
    free(parse);
    return (head);
}

