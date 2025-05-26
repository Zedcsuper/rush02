CC = cc

CFLAGS = -Wall -Wextra -Werror

INCLUDE = -I./includes

OBJ_DIR = obj_dir


RM = rm -rf

NAME = philo

OUTPUTFLAG = -o

NORELINKFLAG = -c

MKDIR = mkdir -p

SRCS =\
	src/main.c \
	src/finish_clean.c \
	src/init_thread.c \
	src/locks.c \
	src/routine.c \
	src/utils.c

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(OUTPUTFLAG) $(NAME)

$(OBJ_DIR)/%.o: src/%.c  ./includes/philo.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) $(NORELINKFLAG) $< $(OUTPUTFLAG) $@

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
