NAME = doom-nukem

LIBFT_DIR = lib/libft
SDL2_DIR = lib/sdl2_build
SDL2_SRCS_DIR = lib/sdl2_srcs

SRCS_FILES = main.c
SRCS_DIR = srcs
SRCS = $(SRCS_FILES:%=$(SRCS_DIR)/%)

INCS_FILES = doom.h
INCS_DIR = incs
INCS = $(INCS_FILES:%=$(INCS_DIR)/%)

OBJS_DIR = objs
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC = clang
CFLAGS = -Wall -Wextra -Iincludes -I$(SDL2_SRCS_DIR)/include -I$(LIBFT_DIR)/includes
CFLAGS += -g
#CFLAGS += -Werror
LDFLAGS = -L$(LIBFT_DIR) -L$(SDL2_DIR) -lft -lSDL2 -lSDL2main -lpthread -ldl -lm

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

sdl2:
	#$(SDL2_SRCS_DIR)/configure
	@mkdir -p $(SDL2_SRCS_DIR)
	@cmake -B$(SDL2_DIR) -H$(SDL2_SRCS_DIR)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c #$(INCS_FILES)
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
