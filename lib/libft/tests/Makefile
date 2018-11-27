# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 16:41:02 by hugo              #+#    #+#              #
#    Updated: 2018/11/11 16:12:53 by hugo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tests
INCS = tests.h
SRCS = $(wildcard *.c)

OTHER_INCDIR = ../includes/
OTHER_INCS = ../includes/libft.h ..includes/get_next_line.h
LIB_PATH = ../
LIB = ../libft.a

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror -g

all: $(LIB) $(NAME)

$(LIB):
	$(MAKE) -C ${LIB_PATH}

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) -lft -L.. -I$(OTHER_INCDIR) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(OTHER_INCDIR) -c -o $@ $< $(LDFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	$(MAKE) all