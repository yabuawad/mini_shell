/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:41:19 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/27 13:47:56 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
// void	print_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%s -> ", (char *)lst->content);
// 		lst = lst->next;
// 	}
// 	printf("NULL\n");
// }

// int	main(void)
// {
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	node1 = ft_lstnew(strdup("Hello"));
// 	node2 = ft_lstnew(strdup("World"));
// 	node3 = ft_lstnew(strdup("42"));

// 	node1->next = node2;
// 	node2->next = node3;
// 	printf("Before deletion:\n");
// 	print_list(node1);

// 	ft_lstdelone(node2, free);

// 	node1->next = node3;
// 	printf("After deletion of node2:\n");
// 	print_list(node1);

// 	ft_lstdelone(node3, free);
// 	node1->next = NULL;
// 	print_list(node1);
// 	return (0);
// }
