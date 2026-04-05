/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuawad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 11:30:55 by yabuawad          #+#    #+#             */
/*   Updated: 2026/04/05 11:30:58 by yabuawad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_parse(char *line, t_env *shell)
{
	char	**tokens;
	t_env	*expanded;

	tokens = tokenise(line);
	if (!tokens)
	{
		shell->last_exit_status = 2;
		return (0);
	}
	shell->cmd_head = parse(tokens);
	freearr(tokens);
	if (!shell->cmd_head)
	{
		shell->last_exit_status = 2;
		return (0);
	}
	expanded = expand(shell->cmd_head, shell->envp, shell->last_exit_status);
	clean_qts(shell->cmd_head, 0, NULL);
	if (expanded)
		free(expanded);
	return (1);
}
