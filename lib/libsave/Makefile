# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/19 10:32:42 by hsabouri          #+#    #+#              #
#    Updated: 2019/02/04 11:38:53 by hugo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libsave.a
INCLUDES = -I./includes -I../libvec/includes -I../libft/includes -I../../includes -I../libtga/includes
CFLAGS = -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -g -O3 -fPIC
CC = clang

NO_COLOR=\x1b[0m
GREEN=\x1b[32;01m
YELLOW=\x1b[33;01m
BLUE=\x1b[36;01m
BLINK=\x1b[5;01m

SRCDIR = sources
OBJDIR = objs
INCDIR = includes
SRCNAM = open_file.c parse.c default.c write.c
INCNAM = structure_clone.h load_save.h

SRC=$(SRCNAM:%=$(SRCDIR)/%)
INC=$(INCNAM:%=$(INCDIR)/%)
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

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
	@$(MAKE) all
