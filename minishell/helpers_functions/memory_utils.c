/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 21:43:19 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/19 23:08:50 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_2d(char **array)
{
    int i;

    if (!array)
        return ;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
    
}

static void free_redirections(t_redir *redirs)
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

static void free_argv(char **argv)
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
