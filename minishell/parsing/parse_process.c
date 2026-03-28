/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:59:23 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/28 02:58:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    apply_parse(char *line, t_env *shell)
{
    char    **tokens;
    t_env    *expanded;
    
    tokens = tokenise(line);
    if (!tokens)
    {
        shell->last_exit_status = 2;
        free(line);
        return (0);
    }
    shell->cmd_head = parse(tokens);
    freearr(tokens);
    if (shell->cmd_head)
    {
        expanded = expand(shell->cmd_head, shell->envp,
                shell->last_exit_status);
    clean_qts(shell->cmd_head,0);   
        if (expanded)
            free(expanded);
    }
    return (1);
}
