/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:30:41 by malhassa          #+#    #+#             */
/*   Updated: 2026/03/02 15:42:30 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *lst_new)
{
	t_list	*temp;

	if (!lst_new)
		return ;
	if (*lst == NULL)
	{
		*lst = lst_new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = lst_new;
}

// // ====== test case ======
// int main(void)
// {
//     t_list *list = NULL;
//     t_list *node1;
//     t_list *node2;
//     t_list *node3;

//     int a = 10;
//     int b = 20;
//     int c = 30;

//     node1 = ft_lstlst_new(&a);
//     node2 = ft_lstlst_new(&b);
//     node3 = ft_lstlst_new(&c);

//     ft_lstadd_back(&list, node1);
//     ft_lstadd_back(&list, node2);
//     ft_lstadd_back(&list, node3);

//     t_list *tmp = list;
//     while (tmp)
//     {
//         printf("%d\n", *(int *)tmp->content);
//         tmp = tmp->next;
//     }
//     return (0);
// }
