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

NAME = libft.a
INCLUDES = ./includes
CFLAGS = -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -g -fPIC

ifeq ($(SAN), yes)
ifeq ($(shell uname -s), Darwin) # remove _o
CFLAGS += -fsanitize=address
else
CFLAGS += -fsanitize=address
endif
endif

ifeq ($(OPT), yes)
CFLAGS += -O3 -march=native
endif

CC = clang

SRCDIR = sources
OBJDIR = objs
INCDIR = includes
SRCNAM	= ft_atoi.c\
		  ft_bzero.c\
		  ft_isalnum.c\
		  ft_amap.c\
		  ft_isalpha.c\
		  ft_isascii.c\
		  ft_isblank.c\
		  ft_isblankn.c\
		  ft_isdigit.c\
		  ft_isprint.c\
		  ft_isspace.c\
		  ft_itoa.c\
		  ft_memalloc.c\
		  ft_memccpy.c\
		  ft_memchr.c\
		  ft_memcmp.c\
		  ft_memcpy.c\
		  ft_memdel.c\
		  ft_memmove.c\
		  ft_memrchr.c\
		  ft_memset.c\
		  ft_putchar.c\
		  ft_putchar_fd.c\
		  ft_putendl.c\
		  ft_putendl_fd.c\
		  ft_putnbr.c\
		  ft_putnbr_fd.c\
		  ft_putstr.c\
		  ft_putstr_fd.c\
		  ft_strcat.c\
		  ft_strchr.c\
		  ft_strclr.c\
		  ft_strcmp.c\
		  ft_strcpy.c\
		  ft_strdel.c\
		  ft_strdup.c\
		  ft_strequ.c\
		  ft_striter.c\
		  ft_striteri.c\
		  ft_strjoin.c\
		  ft_strlen.c\
		  ft_strmap.c\
		  ft_strmapi.c\
		  ft_strncat.c\
		  ft_strncmp.c\
		  ft_strncpy.c\
		  ft_strnequ.c\
		  ft_strnew.c\
		  ft_strnstr.c\
		  ft_strrchr.c\
		  ft_strsplit.c\
		  ft_strstr.c\
		  ft_strsub.c\
		  ft_strtrim.c\
		  ft_tolower.c\
		  ft_listbrowse.c\
		  ft_listfold.c\
		  ft_listforeach.c\
		  ft_listinsert.c\
		  ft_listjoin.c\
		  ft_listnew.c\
		  ft_listpop.c\
		  ft_listshift.c\
		  ft_listpush.c\
		  ft_listmap.c\
		  ft_anew.c\
		  ft_anth.c\
		  ft_apop.c\
		  ft_ashift.c\
		  ft_ainsert.c\
		  ft_apush.c\
		  ft_aforeach.c\
		  ft_toupper.c\
		  ft_memjoin.c\
		  get_next_line.c\
		  ft_array_inner_op.c\
		  console.c

INCNAM = libft.h get_next_line.h


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
	@$(MAKE) all
