# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/19 10:32:42 by hsabouri          #+#    #+#              #
#    Updated: 2018/12/21 18:16:52 by hsabouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libvec.a
INCLUDES = ./includes
CFLAGS = -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -g -O3 -fPIC
CC = clang

SRCDIR = sources
OBJDIR = objs
INCDIR = includes
SRCNAM = float_math.c\
		float_vec_new.c\
		float_vec_op.c\
		float_vec_prod.c\
		float_vec_mult.c\
		float_vec_rot.c\
		float_vec_convert.c\
		fixed_convert.c\
		fixed_math.c\
		fixed_vec_new.c\
		fixed_vec_op.c\
		fixed_vec_prod.c\
		fixed_vec_mult.c
INCNAM = fixed_math.h fixed_vec.h float_math.h float_vec.h vec.h

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
