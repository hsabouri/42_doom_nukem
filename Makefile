BIN = doom-nukem
LIBFT_DIR = lib/libft
LIBSAVE_DIR = lib/libsave
LIBTGA_DIR = lib/libtga
LIBVEC_DIR = lib/libvec
ifeq ($(shell uname -s), Darwin)
	SDL2_DIR = $(HOME)/.brew/Cellar/sdl2/2.0.9/lib/
	SDL2_INC_DIR = $(HOME)/.brew/Cellar/sdl2/2.0.9/include/
	SDL2_TTF_DIR = $(HOME)/.brew/Cellar/sdl2_ttf/2.0.14/lib/
	SDL2_TTF_INC_DIR = $(HOME)/.brew/Cellar/sdl2_ttf/2.0.14/include/
else
	SDL2_DIR =.
	SDL2_INC_DIR =.
	SDL2_TTF_DIR =.
	SDL2_TTF_INC_DIR =.
endif

# -----------------
# SOURCE FILES (.c)
# -----------------

SRCS_FILES = $(shell find srcs -name "*.c")

# -----------------

SRCS_DIR = srcs
SRCS = $(SRCS_FILES:%=%)

# -----------------
# HEADER FILES (.h)
# -----------------

INCS_FILES = $(shell find srcs -name "*.c")

# -----------------

INCS_DIR = incs
INCS = $(INCS_FILES:%=%)

# -----------------

OBJS_DIR = objs
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC = clang
CFLAGS = -Wall -Wextra -Iincludes -I$(LIBFT_DIR)/includes -I$(LIBVEC_DIR)/includes -I$(SDL2_INC_DIR)/SDL2 -I$(SDL2_INC_DIR) -I$(LIBSAVE_DIR)/includes -I$(SDL2_TTF_INC_DIR) -I$(SDL2_TTF_INC_DIR)/SDL2 -I$(LIBTGA_DIR)/includes 
CFLAGS += -g
#CFLAGS += -Werror
LDFLAGS = -L$(LIBFT_DIR) -L$(LIBVEC_DIR) -L$(LIBSAVE_DIR) -L$(SDL2_DIR) -L$(SDL2_TTF_DIR) -L$(LIBTGA_DIR) -lsave -lm -lvec -lft -ltga -lSDL2 -lSDL2main -lSDL2_ttf -lpthread -ldl

all: libft libvec libsave libtga installSDL $(BIN)

ifeq ($(shell uname -s), Darwin_o) # remove _o
installSDL:
	@brew install sdl2
	@brew install sdl2_ttf
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

libtga:
	@$(MAKE) -j -C $(LIBTGA_DIR)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c #$(INCS)
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBVEC_DIR) clean
	$(MAKE) -C $(LIBSAVE_DIR) clean
	$(MAKE) -C $(LIBTGA_DIR) clean

fclean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBVEC_DIR) fclean
	$(MAKE) -C $(LIBSAVE_DIR) fclean
	$(MAKE) -C $(LIBTGA_DIR) fclean
	rm -rf $(BIN)

re: fclean
	$(MAKE) all

.PHONY: clean fclean libft libvec re all
