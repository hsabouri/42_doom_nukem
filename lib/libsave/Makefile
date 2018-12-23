# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/19 10:32:42 by hsabouri          #+#    #+#              #
#    Updated: 2018/12/23 17:31:59 by hsabouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libsave.a
INCLUDES = ./includes
CFLAGS = -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -g -O3 -fPIC
CC = clang

SRCDIR = sources
OBJDIR = objs
INCDIR = includes
SRCNAM = open_file.c parse.c default.c
INCNAM = structure_clone.h

SRC=$(SRCNAM:%=$(SRCDIR)/%)
INC=$(INCNAM:%=$(INCDIR)/%)
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	ar rcs $@ $^
	ranlib $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $< -I$(INCLUDES) $(CFLAGS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean
	@$(MAKE) all
