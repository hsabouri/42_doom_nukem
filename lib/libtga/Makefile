# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/19 10:32:42 by hsabouri          #+#    #+#              #
#    Updated: 2019/01/16 18:05:55 by hsabouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libtga.a
INCLUDES = -I./includes -I../libvec/includes -I../libft/includes -I../../includes -I../libsave/includes
CFLAGS = -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -g -O3 -fPIC
CC = clang

SRCDIR = sources
OBJDIR = objs
INCDIR = includes
SRCNAM = tga.c
INCNAM = tga.h

SRC=$(SRCNAM:%=$(SRCDIR)/%)
INC=$(INCNAM:%=$(INCDIR)/%)
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	ar rcs $@ $^
	ranlib $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $< $(INCLUDES) $(CFLAGS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean
	@$(MAKE) all
