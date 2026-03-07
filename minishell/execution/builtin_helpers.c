/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:15:14 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/07 03:40:31 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo_newline(t_cmd *cmd)
{
    int j;
    
    j = 1;
    while (cmd->argv[1][j])
    {
        if (cmd->argv[1][j] != 'n')
            return (0);
        j++;
    }
    return (1);
}
// int    exit_validation(t_cmd *cmd,long exit_c)
// {
//     int exit_value;

//     if (cmd->argv[1] && cmd->argv[2])
//     {
//         ft_putstr_fd("exit: '", 2);
//         ft_putstr_fd(cmd->argv[1], 2);
//         ft_putstr_fd("': too many arguments \n", 2);
//         return (1);
//     }
    
// }