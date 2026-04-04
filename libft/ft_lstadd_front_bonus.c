/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:43:41 by malhassa          #+#    #+#             */
/*   Updated: 2026/03/02 15:42:46 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *lst_new)
{
	lst_new->next = *lst;
	*lst = lst_new;
}
// int main(void)
// {
//     t_list *head;
//     t_list *node1;
//     t_list *node2;

//     head = NULL;
//     node1 = ft_lstlst_new("first");
//     node2 = ft_lstlst_new("second");
//     ft_lstadd_front(&head,node1);
//     ft_lstadd_front(&head,node2);
//     t_list *temp = head;
//     while(temp)
//     {
//         printf("%s\n",(char *)temp -> content);
//         temp = temp -> next;
//     }

// }