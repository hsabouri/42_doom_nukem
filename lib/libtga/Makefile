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

NAME = libtga.a
INCLUDES = -I./includes -I../libvec/includes -I../libft/includes -I../../includes -I../libsave/includes
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
SRCNAM = tga.c
INCNAM = tga.h

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
	@$(CC) -c -o $@ $< $(INCLUDES) $(CFLAGS)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	
