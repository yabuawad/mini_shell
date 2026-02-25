/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:08:18 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/24 20:18:10 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = lst;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

// int main(void)
// {
//  t_list *head = NULL;
//     t_list *node1;
//     t_list *node2;
//     t_list *node3;

//     // Create nodes
//     node1 = ft_lstnew("A");
//     node2 = ft_lstnew("B");
//     node3 = ft_lstnew("C");

//     // Build the list
//     ft_lstadd_front(&head, node1);  // List: A
//     ft_lstadd_front(&head, node2);  // List: A -> B
//     ft_lstadd_front(&head, node3);  // List: A -> B -> C

//     // Count the nodes
//     int size = ft_lstsize(head);
//     printf("List size: %d\n", size);  // Should print 3}
// }
