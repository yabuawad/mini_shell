/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:00:00 by parser            #+#    #+#             */
/*   Updated: 2026/03/02 16:17:58 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_token
{
    char *value;
    int type; // 0=word, 1=redirect_in, 2=redirect_out, 3=redirect_append
    struct s_token *next;
} t_token;

// ============================================================================
// TOKEN UTILITIES
// ============================================================================

t_token *token_new(char *value, int type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->value = ft_strdup(value);
    if (!token->value)
    {
        free(token);
        return (NULL);
    }
    token->type = type;
    token->next = NULL;
    return (token);
}

void token_add_back(t_token **head, t_token *new_token)
{
    t_token *current;

    if (!head || !new_token)
        return;
    if (!*head)
    {
        *head = new_token;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

void token_clear(t_token **head)
{
    t_token *current;
    t_token *temp;

    if (!head)
        return;
    current = *head;
    while (current)
    {
        temp = current->next;
        free(current->value);
        free(current);
        current = temp;
    }
    *head = NULL;
}

int token_list_size(t_token *head)
{
    int size;

    size = 0;
    while (head)
    {
        size++;
        head = head->next;
    }
    return (size);
}

// ============================================================================
// TOKENIZER
// ============================================================================

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int is_quote(char c)
{
    return (c == '"' || c == '\'');
}

static void syntax_error(char *token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    ft_putstr_fd(token, 2);
    ft_putstr_fd("'\n", 2);
}

static int validate_syntax(t_token *tokens)
{
    int prev_type;

    prev_type = -1;
    while (tokens)
    {
        if (tokens->type == 4 || tokens->type == 5)
        {
            if (prev_type == -1 || prev_type == 4 || prev_type == 5)
            {
                syntax_error(tokens->value);
                return (0);
            }
            if (tokens->type == 4 && (!tokens->next || tokens->next->type == 4 || tokens->next->type == 5))
            {
                syntax_error(!tokens->next ? "newline" : tokens->next->value);
                return (0);
            }
        }
        if (tokens->type == 1 || tokens->type == 2 || tokens->type == 3 || tokens->type == 6)
        {
            if (!tokens->next || tokens->next->type != 0)
            {
                syntax_error(!tokens->next ? "newline" : tokens->next->value);
                return (0);
            }
        }
        prev_type = tokens->type;
        tokens = tokens->next;
    }
    return (1);
}

char *extract_quoted_string(char *str, int *i, char quote)
{
    char *result;
    int start;
    int len;

    (*i)++; // skip opening quote
    start = *i;
    while (str[*i] && str[*i] != quote)
        (*i)++;
    len = *i - start;
    result = ft_substr(str, start, len);
    if (str[*i] == quote)
        (*i)++; // skip closing quote
    return (result);
}

char *extract_word(char *str, int *i)
{
    char *result;
    char *temp;
    char *joined;
    char *word_part;
    int start;
    int len;
    char quote;

    result = ft_strdup("");
    if (!result)
        return (NULL);

    while (str[*i] && !is_whitespace(str[*i]) && str[*i] != '<' && str[*i] != '>' && str[*i] != '|' && str[*i] != ';')
    {
        if (is_quote(str[*i]))
        {
            quote = str[*i];
            temp = extract_quoted_string(str, i, quote);
            if (temp)
            {
                joined = ft_strjoin(result, temp);
                free(temp);
                if (!joined)
                {
                    free(result);
                    return (NULL);
                }
                free(result);
                result = joined;
            }
        }
        else
        {
            start = *i;
            while (str[*i] && !is_whitespace(str[*i]) && str[*i] != '<' &&
                   str[*i] != '>' && str[*i] != '|' && str[*i] != ';' && !is_quote(str[*i]))
                (*i)++;
            len = *i - start;
            word_part = ft_substr(str, start, len);
            if (word_part)
            {
                joined = ft_strjoin(result, word_part);
                free(word_part);
                if (!joined)
                {
                    free(result);
                    return (NULL);
                }
                free(result);
                result = joined;
            }
        }
    }
    return (result);
}

t_token *tokenize(char *input)
{
    t_token *tokens;
    t_token *new_token;
    int i;
    char *word;

    tokens = NULL;
    i = 0;

    while (input[i])
    {
        // Skip whitespace
        while (input[i] && is_whitespace(input[i]))
            i++;

        if (!input[i])
            break;

        new_token = NULL;
        // Check for redirections
        if (input[i] == '<')
        {
            if (input[i + 1] == '<')
            {
                new_token = token_new("<<", 6);
                i += 2;
            }
            else
            {
                new_token = token_new("<", 1);
                i++;
            }
        }
        else if (input[i] == '>')
        {
            if (input[i + 1] == '>')
            {
                new_token = token_new(">>", 3);
                i += 2;
            }
            else
            {
                new_token = token_new(">", 2);
                i++;
            }
        }
        else if (input[i] == '|')
        {
            new_token = token_new("|", 4);
            i++;
        }
        else if (input[i] == ';')
        {
            new_token = token_new(";", 5);
            i++;
        }
        else
        {
            // Extract word (handles quotes)
            word = extract_word(input, &i);
            if (!word)
            {
                token_clear(&tokens);
                return (NULL);
            }
            if (*word)
            {
                new_token = token_new(word, 0);
            }
            free(word);
        }
        
        if (!new_token)
        {
            token_clear(&tokens);
            return (NULL);
        }
        token_add_back(&tokens, new_token);
    }

    return (tokens);
}

// ============================================================================
// REDIRECTION BUILDING
// ============================================================================

t_redir *redir_new(char *target, int type)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->fd = -1;
    redir->target = ft_strdup(target);
    if (!redir->target)
    {
        free(redir);
        return (NULL);
    }
    if (type == 1)
        redir->type = R_IN;
    else if (type == 2)
        redir->type = R_OUT;
    else if (type == 3)
        redir->type = R_APPEND;
    else if (type == 6)
        redir->type = R_HEREDOC;
    redir->next_redirection = NULL;
    return (redir);
}

void redir_add_back(t_redir **head, t_redir *new_redir)
{
    t_redir *current;

    if (!head || !new_redir)
        return;
    if (!*head)
    {
        *head = new_redir;
        return;
    }
    current = *head;
    while (current->next_redirection)
        current = current->next_redirection;
    current->next_redirection = new_redir;
}

// ============================================================================
// COMMAND BUILDING
// ============================================================================

t_cmd *cmd_new(void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->redirs = NULL;
    cmd->has_pipe = 0;
    cmd->next = NULL;
    return (cmd);
}

void cmd_add_back(t_cmd **head, t_cmd *new_cmd)
{
    t_cmd *current;

    if (!head || !new_cmd)
        return;
    if (!*head)
    {
        *head = new_cmd;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_cmd;
}

int count_argv(t_token *tokens)
{
    int count;

    count = 0;
    while (tokens && tokens->type == 0)
    {
        count++;
        tokens = tokens->next;
    }
    return (count);
}
void free_argv(char **argv)
{
    int i;

    if (!argv)
        return;
    i = 0;
    while (argv[i])
    {
        free(argv[i]);
        i++;
    }
    free(argv);
}

char **build_argv(t_token *tokens)
{
    char **argv;
    int argc;
    int i;

    argc = count_argv(tokens);
    if (argc == 0)
        return (NULL);

    argv = malloc(sizeof(char *) * (argc + 1));
    if (!argv)
        return (NULL);

    i = 0;
    while (tokens && tokens->type == 0)
    {
        argv[i] = ft_strdup(tokens->value);
        if (!argv[i])
        {
            free_argv(argv);
            return (NULL);
        }
        i++;
        tokens = tokens->next;
    }
    argv[i] = NULL;

    return (argv);
}

// ============================================================================
// MAIN PARSER
// ============================================================================

t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd *commands;
    t_cmd *current_cmd;
    t_redir *new_redir;
    int redir_type;

    commands = NULL;
    current_cmd = NULL;

    while (tokens)
    {
        // Skip empty/null tokens
        if (!tokens->value)
        {
            tokens = tokens->next;
            continue;
        }

        // Start new command
        if (current_cmd == NULL || tokens->type == 4 || tokens->type == 5)
        {
            if (current_cmd && (current_cmd->argv || current_cmd->redirs))
            {
                if (tokens->type == 4) // If pipe follows this command
                    current_cmd->has_pipe = 1;
                cmd_add_back(&commands, current_cmd);
            }
            else if (current_cmd)
            {
                free_commands(current_cmd);
            }
            current_cmd = cmd_new();
            if (!current_cmd)
            {
                free_commands(commands);
                return (NULL);
            }

            if (tokens->type == 4 || tokens->type == 5) // pipe or semicolon
            {
                tokens = tokens->next;
                continue;
            }
        }

        // Handle redirections
        if (tokens->type == 1 || tokens->type == 2 || tokens->type == 3 || tokens->type == 6)
        {
            redir_type = tokens->type;
            tokens = tokens->next;

            // Skip whitespace
            while (tokens && !tokens->value)
                tokens = tokens->next;

            if (tokens && tokens->type == 0)
            {
                new_redir = redir_new(tokens->value, redir_type);
                if (!new_redir)
                {
                    free_commands(commands);
                    free_commands(current_cmd);
                    return (NULL);
                }
                redir_add_back(&current_cmd->redirs, new_redir);
                tokens = tokens->next;
            }
        }
        else if (tokens->type == 0) // word token
        {
            // Build argv from consecutive words
            if (!current_cmd->argv)
            {
                current_cmd->argv = build_argv(tokens);
                if (!current_cmd->argv)
                {
                    free_commands(commands);
                    free_commands(current_cmd);
                    return (NULL);
                }

                // Skip tokens we already processed
                int word_count = count_argv(tokens);
                for (int i = 0; i < word_count; i++)
                    tokens = tokens->next;
            }
            else
            {
                tokens = tokens->next;
            }
        }
        else
        {
            tokens = tokens->next;
        }
    }

    // Add last command
    if (current_cmd && (current_cmd->argv || current_cmd->redirs))
        cmd_add_back(&commands, current_cmd);
    else if (current_cmd)
        free_commands(current_cmd);

    return (commands);
}

// ============================================================================
// PUBLIC PARSER API
// ============================================================================

t_cmd *parse_input(char *input)
{
    t_token *tokens;
    t_cmd *commands;

    if (!input || !*input)
        return (NULL);

    tokens = tokenize(input);
    if (!tokens)
        return (NULL);

    if (!validate_syntax(tokens))
    {
        token_clear(&tokens);
        return (NULL);
    }
    commands = parse_tokens(tokens);
    token_clear(&tokens);

    return (commands);
}

void free_redirections(t_redir *redirs)
{
    t_redir *current;
    t_redir *temp;

    current = redirs;
    while (current)
    {
        temp = current->next_redirection;
		if (current->fd != -1)
			close(current->fd);
        if (current->target)
            free(current->target);
        free(current);
        current = temp;
    }
}

void free_commands(t_cmd *cmd)
{
    t_cmd *current;
    t_cmd *temp;

    current = cmd;
    while (current)
    {
        temp = current->next;
        if (current->argv)
            free_argv(current->argv);
        if (current->redirs)
            free_redirections(current->redirs);
        free(current);
        current = temp;
    }
}
