NAME = philosopher

NAME_BONUS = philosopher_bonus

CC = cc
FLAGS = #-fsanitize=thread #-Wall -Wextra -Werror #-g -fsanitize=address #-fsanitize=thread  #-g -fsanitize=address
RM = rm -f

SRCS = ./rsc/init_data.c ./rsc/eating_routine.c ./rsc/print_data.c ./rsc/routine_philo.c \
		./rsc/sleeping_routine.c ./rsc/define_dead_philo.c \
		./rsc/algorithm.c ./rsc/list_operations.c ./rsc/exit.c ./rsc/parsing.c	\
		./rsc/manage_forks.c ./rsc/usleep.c ./rsc/monitoring.c ./main.c ./dbg/dbg_structures.c

SRCS_BONUS = ./rsc/algorithm.c ./rsc/list_operations.c ./rsc/exit.c ./rsc/parsing.c	\
		./main.c ./dbg/dbg_structures.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)
 
bonus:  $(NAME) $(NAME_BONUS)

$(NAME): $(OBJS)
	@ $(CC) $(FLAGS) -o $(NAME) $(OBJS) 

$(NAME_BONUS): $(OBJS_BONUS)
	@ $(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)

clean:
	@ $(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@ $(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus