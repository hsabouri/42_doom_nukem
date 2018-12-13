NAME = doom-nukem

LIBFT_DIR = lib/libft

LIBVEC_DIR = lib/libvec
ifeq ($(shell uname -s), Darwin)
	SDL2_DIR = $(HOME)/.brew/Cellar/sdl2/2.0.9/lib/
	SDL2_INC_DIR = $(HOME)/.brew/Cellar/sdl2/2.0.9/includes/
else
	SDL2_DIR =.
	SDL2_INC_DIR =.
endif

# -----------------
# SOURCE FILES (.c)
# -----------------

SRCS_FILES = main.c

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
CFLAGS = -Wall -Wextra -Iincludes -I$(SDL2_SRCS_DIR)/includes -I$(LIBFT_DIR)/includes
CFLAGS += -g
#CFLAGS += -Werror
LDFLAGS = -L$(LIBFT_DIR) -L$(LIBVEC_DIR) -L$(SDL2_DIR) -lft -lvec -lSDL2 -lSDL2main -lpthread -ldl -lm

all: libft libvec installSDL $(NAME)

ifeq ($(shell uname -s), Darwin)
installSDL:
	@brew update
	@brew install sdl2
else
installSDL:
	@echo "Can't install SDL on Linux"
endif

libft:
	@$(MAKE) -C $(LIBFT_DIR)

libvec:
	@$(MAKE) -C $(LIBVEC_DIR)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c #$(INCS)
	mkdir -p $(OBJS_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -rf $(SDL2_SRCS_DIR)/CMakeCache.txt
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re: fclean
	$(MAKE) all
