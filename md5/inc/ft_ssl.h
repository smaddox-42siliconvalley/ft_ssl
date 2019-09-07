/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 20:26:37 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/06 19:49:19 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "ft_printf.h"
# include "utils.h"

# define TABLE_LENGTH 2
# define MD5 { "Message Digest command", "md5", &md5_driver }
# define SHA256 { "Message Digest command", "sha256", &sha256_driver }
# define SSL_FUNCTS { MD5, SHA256 }
# define INIT_SSL_TABLE(x) t_dis_table x = { SSL_FUNCTS }

typedef struct			s_dispatch_func
{
	const char			designation[100];
	const char			key[100];
	int					(*func)(int, char**);
}						t_dispatch_func;

typedef struct			s_dis_table
{
	t_dispatch_func		table[TABLE_LENGTH];
}						t_dis_table;

int						md5_driver(int ac, char** av);
int						sha256_driver(int ac, char** av);

#endif
