NAME = phylosopher

NAME_BONUS = phylosopher_bonus

CC = cc
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
RM = rm -f

SRCS = ./rsc/algorithm.c ./rsc/list_operations.c ./rsc/exit.c ./rsc/parsing.c ./main.c

SRCS_BONUS = ./rsc/algorithm.c ./rsc/list_operations.c ./rsc/exit.c ./rsc/parsing.c ./main.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT:= libft/libft.a

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)
 
bonus:  $(NAME) $(NAME_BONUS)

$(NAME): $(LIBFT) $(OBJS)
	@ $(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(NAME_BONUS): $(OBJS_BONUS)
	@ $(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT)

$(LIBFT):
	@ make -C libft/ >/dev/null

clean:
	@ $(RM) $(OBJS) $(OBJS_BONUS)
	@ make -C libft/ clean >/dev/null

fclean: clean
	@ $(RM) $(NAME) $(NAME_BONUS)
	@ make -C libft/

re: fclean all

.PHONY: all libft clean fclean re bonus