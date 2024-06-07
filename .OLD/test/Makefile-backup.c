INC=/usr/include


INCLIB=$(INC)/../lib

UNAME := $(shell uname)

CFLAGS= -I$(INC) -O3 -I.. -g

NAME= aureltest
SRC = aureltest.c
OBJ = $(SRC:%.c=%.o)

LFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lft

ifeq ($(UNAME), Darwin)
	# mac
	CC = clang
else ifeq ($(UNAME), FreeBSD)
	# FreeBSD
	CC = clang
else
	#Linux and others...
	CC	= gcc
	LFLAGS += -lbsd
endif

all: $(NAME)
	./$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		:\n	$(SRC)\n"
	@printf "OBJ		:\n	$(OBJ)\n"

clean:
	rm -f $(NAME) $(OBJ) *~ core *.core

re: clean all