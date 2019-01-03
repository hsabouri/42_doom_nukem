NAME = doom-nukem
LIBFT_DIR = lib/libft
LIBSAVE_DIR = lib/libsave
LIBVEC_DIR = lib/libvec
ifeq ($(shell uname -s), Darwin)
	SDL2_DIR = $(HOME)/.brew/Cellar/sdl2/2.0.9/lib/
	SDL2_INC_DIR = $(HOME)/.brew/Cellar/sdl2/2.0.9/include/
else
	SDL2_DIR =.
	SDL2_INC_DIR =.
endif

# -----------------
# SOURCE FILES (.c)
# -----------------

SRCS_FILES = main.c\
			event.c \
			test_map.c\
			graphic_polygon.c\
			graphic_utils.c\
			graphic_display.c\
			bresenham.c\
			physic.c\
			player_physic.c\
			collision.c

# -----------------

SRCS_DIR = srcs
SRCS = $(SRCS_FILES:%=$(SRCS_DIR)/%)

# -----------------
# HEADER FILES (.h)
# -----------------

INCS_DIR = incs
INCS = $(INCS_FILES:%=$(INCS_DIR)/%)

# -----------------

OBJS_DIR = objs
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC = clang
CFLAGS = -Wall -Wextra -Iincludes -I$(LIBFT_DIR)/includes -I$(LIBVEC_DIR)/includes -I$(SDL2_INC_DIR) -I$(LIBSAVE_DIR)/includes
CFLAGS += -g
#CFLAGS += -Werror
LDFLAGS = -L$(LIBFT_DIR) -L$(LIBVEC_DIR) -L$(LIBSAVE_DIR) -L$(SDL2_DIR) -lsave -lm -lvec -lft -lSDL2 -lSDL2main -lpthread -ldl

all: libft libvec libsave installSDL $(NAME)

ifeq ($(shell uname -s), Darwin)
installSDL:
	@brew install sdl2
else
installSDL:
	@echo "Can't install SDL on Linux"
endif

libft:
	@$(MAKE) -j -C $(LIBFT_DIR)

libvec:
	@$(MAKE) -j -C $(LIBVEC_DIR)

libsave:
	@$(MAKE) -j -C $(LIBSAVE_DIR)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c #$(INCS)
	mkdir -p $(OBJS_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBVEC_DIR) clean
	$(MAKE) -C $(LIBSAVE_DIR) clean

fclean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBVEC_DIR) fclean
	$(MAKE) -C $(LIBSAVE_DIR) fclean
	rm -rf $(NAME)

re: fclean
	$(MAKE) all

.PHONY: clean fclean libft libvec re all
