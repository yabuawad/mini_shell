/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 22:31:05 by mohamed           #+#    #+#             */
/*   Updated: 2026/03/28 03:55:55 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  is_zero(char *num)
{
    int i;

    i = 0;
    if (num[i] == '+' || num[i] == '-')
        i++;
    while (num[i])
    {
        if (num[i] != '0')
            return (0);
        i++;
    }
    return (1);
}

int  exit_value_validation(char *arg)
{
    int                 i;
    int                 sign;
    long long  result;

    sign = 1;
    i = 0;
    if (arg[i] == '+' || arg[i] == '-')
    {
        if (arg[i] == '-')
            sign = -1;
        i++;
    }
    result = 0;
    while (ft_isdigit(arg[i]))
    {
        if (sign == 1 && (result > (LLONG_MAX - (arg[i] - '0')) / 10))
			return (0);
		if (sign == -1 && (-result < (LLONG_MIN + (arg[i] - '0')) / 10))
			return (0);
		result = result * 10 + (arg[i++] - '0');
    }
    if (arg[i] != '\0')
        return (0);
    return (result * sign);
}

int execute_exit(t_cmd *cmd, t_env *shell)
{
    long long   exit_c;
    
    exit_c = 0;
    ft_putendl_fd("exit", 1);
    if (cmd->argv[1])
    {
        exit_c = exit_value_validation(cmd->argv[1]);
        if (!exit_c && !is_zero(cmd->argv[1]))
        {
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(cmd->argv[1], 2);
            ft_putendl_fd(": numeric argument required", 2);
            exit(2);
        }
        if (cmd->argv[2])
        {
            ft_putstr_fd("exit: ", 2);
            ft_putendl_fd("too many arguments", 2);
            return (1);
        }
    }
    else if (shell)
        exit_c = shell->last_exit_status;
    exit((unsigned char)exit_c);
}
