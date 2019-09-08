# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaddox <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/07 17:12:04 by smaddox           #+#    #+#              #
#    Updated: 2019/09/07 17:26:08 by smaddox          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
CFILES = \
		 src/md5.c \
		 src/ft_ssl.c \
		 src/utils.c \
		 src/md5_driver.c \
		 src/md5_driver_two.c \
		 src/sha256.c \
		 src/sha256_driver.c \
		 src/sha256_driver_two.c

OBJECTS = $(CFILES:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	gcc -o $(NAME) -I inc $(OBJECTS) src/libftprintf.a 

%.o : %.c
	gcc -I inc -Wall -Wextra -Werror -c $< -o $@

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all
