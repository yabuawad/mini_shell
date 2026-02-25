/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:49:26 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/27 13:44:35 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	temp = *lst;
	if (!(*lst) || !del)
		return ;
	while (temp)
	{
		del(temp->content);
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
	*lst = NULL;
}
