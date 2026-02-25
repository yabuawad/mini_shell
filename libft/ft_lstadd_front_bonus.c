/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:43:41 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/24 20:16:02 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
// int main(void)
// {
//     t_list *head;
//     t_list *node1;
//     t_list *node2;

//     head = NULL;
//     node1 = ft_lstnew("first");
//     node2 = ft_lstnew("second");
//     ft_lstadd_front(&head,node1);
//     ft_lstadd_front(&head,node2);
//     t_list *temp = head;
//     while(temp)
//     {
//         printf("%s\n",(char *)temp -> content);
//         temp = temp -> next;
//     }

// }