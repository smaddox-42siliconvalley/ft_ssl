/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 00:21:26 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/06 18:39:50 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

# define P_FLAG 0xc0
# define Q_FLAG 0x30
# define R_FLAG 0xc
# define S_FLAG 0x3
# define TOGGLE_P(x) ((x) ^= (P_FLAG))
# define TOGGLE_Q(x) ((x) ^= (Q_FLAG))
# define TOGGLE_R(x) ((x) ^= (R_FLAG))
# define TOGGLE_S(x) ((x) ^= (S_FLAG))
# define CHECK_P(x) ((x) & (P_FLAG))
# define CHECK_Q(x) ((x) & (Q_FLAG))
# define CHECK_R(x) ((x) & (R_FLAG))
# define CHECK_S(x) ((x) & (S_FLAG))

typedef struct					s_file
{
	char						*name;
	unsigned long long int		size;
	uint8_t						*data;
	int							error;
}								t_file;

t_file							file_reader(char *file);
t_file							stdin_reader(void);
#endif
