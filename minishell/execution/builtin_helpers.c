/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:15:14 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/09 06:07:20 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo_newline(char *cmd)
{
    int i;
    int j;
    
    if (!cmd || cmd[1] != 'n' || cmd[0] != '-')
        return (0);
    i = 2;
    while (cmd[i])
    {
        if (cmd[i] != 'n')
        {
            j = i+1;
            while (cmd[j] && (cmd[j] == 'n' || cmd[j] == 'e'))
                j++;
            if (cmd[j] != '\0')
                return (0);          
        }
        i++;
    }
    return (1);
}
