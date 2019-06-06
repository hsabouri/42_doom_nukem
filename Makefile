BIN = doom-nukem
LIBFT_DIR = lib/libft
LIBTGA_DIR = lib/libtga
LIBVEC_DIR = lib/libvec
ifeq ($(shell uname -s), Darwin)
	SDL2_DIR = $(HOME)/.brew/Cellar/sdl2/2.0.9_1/lib/
	SDL2_INC_DIR = $(HOME)/.brew/Cellar/sdl2/2.0.9_1/include/
	SDL2_TTF_DIR = $(HOME)/.brew/Cellar/sdl2_ttf/2.0.14/lib/
	SDL2_TTF_INC_DIR = $(HOME)/.brew/Cellar/sdl2_ttf/2.0.14/include/
	SDL2_MIXER_DIR = $(HOME)/.brew/Cellar/sdl2_mixer/2.0.4/lib/
	SDL2_MIXER_INC_DIR = $(HOME)/.brew/Cellar/sdl2_mixer/2.0.4/include/
else
	SDL2_DIR =.
	SDL2_INC_DIR =.
	SDL2_TTF_DIR =.
	SDL2_TTF_INC_DIR =.
	SDL2_MIXER_DIR = .
	SDL2_MIXER_INC_DIR = .
endif

NO_COLOR=\x1b[0m
GREEN=\x1b[32;01m
YELLOW=\x1b[33;01m
BLUE=\x1b[36;01m
BLINK=\x1b[5;01m

# -----------------
# SOURCE FILES (.c)
# Don't forget to list files at the end of the project
# -----------------

SRCS_FILES = $(shell find srcs -name "*.c")

# -----------------

SRCS_DIR = srcs
SRCS = $(SRCS_FILES:%=%)

# -----------------
# HEADER FILES (.h)
# Don't forget to list files at the end of the project
# -----------------

INCS_FILES = $(shell find includes -name "*.h")

# -----------------

INCS_DIR = includes
INCS = $(INCS_FILES:%=%)

# -----------------

OBJS_DIR = objs
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# -----------------

CC = clang
CFLAGS = -Wall -Wextra -Iincludes
CFLAGS += -g
#CFLAGS += -O3 -march=native
#CFLAGS += -Werror

ifeq ($(SAN), yes)
ifeq ($(shell uname -s), Darwin) # remove _o
LDFLAGS = -fsanitize=address
CFLAGS += -fsanitize=address
else
LDFLAGS = -lasan
CFLAGS += -fsanitize=address
endif
endif

ifeq ($(OPT), yes)
CFLAGS += -O3 -march=native
endif

CFLAGS += -I$(LIBFT_DIR)/includes
CFLAGS += -I$(LIBVEC_DIR)/includes
CFLAGS += -I$(SDL2_INC_DIR)/SDL2 -I$(SDL2_INC_DIR)
CFLAGS += -I$(SDL2_TTF_INC_DIR) -I$(SDL2_TTF_INC_DIR)/SDL2
CFLAGS += -I$(SDL2_MIXER_INC_DIR) -I$(SDL2_MIXER_INC_DIR)/SDL2
CFLAGS += -I$(LIBTGA_DIR)/includes
CFLAGS += -I.

LDFLAGS += -L$(LIBFT_DIR) -lft
LDFLAGS += -lpthread -ldl -lm
LDFLAGS += -L$(LIBVEC_DIR) -lvec
LDFLAGS += -L$(SDL2_DIR) -lSDL2 -lSDL2main
LDFLAGS += -L$(SDL2_TTF_DIR) -lSDL2_ttf
LDFLAGS += -L$(SDL2_MIXER_DIR) -lSDL2_mixer
LDFLAGS += -L$(LIBTGA_DIR) -ltga

all: message libft libvec libtga $(BIN)

message:
	@echo -e "$(YELLOW)" "[BUILD]" "$(NO_COLOR)" $(BIN)

libft:
	@echo -e "$(YELLOW)" "[BUILD]" "$(NO_COLOR)" $@
	@$(MAKE) -j -s -C $(LIBFT_DIR) SAN=$(SAN) OPT=$(OPT)

libvec:
	@echo -e "$(YELLOW)" "[BUILD]" "$(NO_COLOR)" $@
	@$(MAKE) -j -s -C $(LIBVEC_DIR) SAN=$(SAN) OPT=$(OPT)

libtga:
	@echo -e "$(YELLOW)" "[BUILD]" "$(NO_COLOR)" $@
	@$(MAKE) -j -s -C $(LIBTGA_DIR) SAN=$(SAN) OPT=$(OPT)

$(BIN): $(OBJS)
	@echo -e "$(BLUE)" "[LINK]" "$(NO_COLOR)" $@
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo -e "$(BLINK)" "FINISHED !" "$(NO_COLOR)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCS)
	@echo -e "$(GREEN)" "[COMPILE]" "$(NO_COLOR)" $<
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(LIBVEC_DIR) clean
	@$(MAKE) -s -C $(LIBTGA_DIR) clean

fclean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(LIBVEC_DIR) fclean
	@$(MAKE) -s -C $(LIBTGA_DIR) fclean
	rm -rf $(BIN)

re: fclean
	@$(MAKE) all

.PHONY: clean fclean libft libvec libtga re all

.SILENT: clean fclean libft libvec libtga re all
