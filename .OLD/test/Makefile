# Paths
INC = ./libft/includes
LIBFT_DIR = ./libft
MINILIBX_DIR = ../lib
X11_LIB_DIR = /usr/X11/lib

# Compiler and Flags
UNAME := $(shell uname)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC) -I$(LIBFT_DIR) -I$(MINILIBX_DIR) -O3 -g
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -L$(X11_LIB_DIR) -lXext -lX11 -lm

# Adjust LFLAGS for non-macOS systems
ifeq ($(UNAME), Darwin)
    CC = clang
else ifeq ($(UNAME), FreeBSD)
    CC = clang
else
    LFLAGS += -lbsd
endif

# Project Files
NAME = aureltest
SRC = aureltest.c
OBJ = $(SRC:.c=.o)

# Targets
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(OBJ) -o $@ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(NAME)

fclean: clean
	rm -f $(LIBFT_DIR)/*.o

re: fclean all

.PHONY: all clean fclean re
