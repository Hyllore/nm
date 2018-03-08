/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 19:17:09 by droly             #+#    #+#             */
/*   Updated: 2015/12/11 11:15:22 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp3;
	t_list	*tmp2;
	void	*tmp;

	tmp3 = (*f)(lst);
	if ((tmp = ft_lstnew(tmp3->content, tmp3->content_size)))
	{
		tmp2 = (t_list *)tmp;
		lst = lst->next;
		while (lst)
		{
			tmp3 = (*f)(lst);
			if (!(tmp2->next = ft_lstnew(tmp3->content, tmp3->content_size)))
				return (NULL);
			tmp2 = tmp2->next;
			lst = lst->next;
		}
	}
	return ((t_list *)tmp);
}
