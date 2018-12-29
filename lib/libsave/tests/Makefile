# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/09 16:41:02 by hugo              #+#    #+#              #
#    Updated: 2018/11/29 13:47:33 by hugo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = tests
INCS = tests.h
SRCS = $(wildcard *.c)

OTHER_INCDIR = ../includes/
OTHER_INCS = ../includes/fixed_math.h ../includes/float_math.h
LIB_PATH = ../
LIB = ../libvec.a

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror -g

all: $(LIB) $(NAME)

$(LIB):
	$(MAKE) -C ${LIB_PATH}

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) -lvec -lm -L.. -I$(OTHER_INCDIR) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(OTHER_INCDIR) -c -o $@ $< $(LDFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean
	$(MAKE) all