/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trashcan.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:27:24 by smaddox           #+#    #+#             */
/*   Updated: 2019/07/20 16:42:54 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRASHCAN_H
# define TRASHCAN_H

# include "libft.h"

# define DEFAULT_TRASH_SIZE 100

typedef enum		e_type
{
	T_CHAR, T_INT, T_FLOAT
}					t_my_type;
typedef struct		s_trash
{
	t_my_type		type;
	union			u_name
	{
		char		*cp;
		int			*ip;
		float		*fp;
	}				u_piece;
}					t_rash;
typedef struct		s_trashcan
{
	t_rash			can[DEFAULT_TRASH_SIZE];
	int				top;
}					t_rash_can;

void				new_trash_bag(t_rash_can *my_trashcan);
void				mom(t_rash_can *my_trashcan, t_my_type tp, ...);
int					trash_overflow(t_rash_can *my_trashcan);
int					trashcan_empty(t_rash_can *my_trashcan);
void				garbage_day(t_rash_can *my_trashcan);
#endif
