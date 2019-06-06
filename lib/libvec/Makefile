# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/19 10:32:42 by hsabouri          #+#    #+#              #
#    Updated: 2019/05/26 18:24:24 by hsabouri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libvec.a
INCLUDES = ./includes
CFLAGS = -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -g -fPIC
CFLAGS += -O3 -march=native
CC = clang

ifeq ($(SAN), yes)
ifeq ($(shell uname -s), Darwin) # remove _o
CFLAGS += -fsanitize=address
else
CFLAGS += -fsanitize=address
endif
endif

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
		float_vec_compare.c\
		fixed_convert.c\
		fixed_math.c\
		fixed_vec_new.c\
		fixed_vec_op.c\
		fixed_vec_prod.c\
		fixed_vec_convert.c\
		fixed_vec_ssize.c\
		fixed_vec_mult.c

INCNAM = fixed_math.h fixed_vec.h float_math.h float_vec.h vec.h

SRC=$(SRCNAM:%=$(SRCDIR)/%)
INC=$(INCNAM:%=$(INCDIR)/%)
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

NO_COLOR=\x1b[0m
GREEN=\x1b[32;01m
YELLOW=\x1b[33;01m
BLUE=\x1b[36;01m
BLINK=\x1b[5;01m

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	@echo -e "$(BLUE)" "[PACK]" "$(NO_COLOR)" $@
	@ar rcs $@ $^
	@ranlib $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	@echo -e "$(GREEN)" "[COMPILE]" "$(NO_COLOR)" $<
	@mkdir -p $(OBJDIR)
	@$(CC) -c -o $@ $< -I$(INCLUDES) $(CFLAGS)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean
