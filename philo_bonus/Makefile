NAME 	= philo_bonus

SRCS = 	philo_bonus.c \
		init_bonus.c \
		utils_bonus.c \
		print_bonus.c \
		death_bonus.c


HEADER = philo_bonus.h

OBJ 	= $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -g -I.
		
all : $(NAME) 

$(NAME) : $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME) 

	
%.o : %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)
	

re : fclean all

.PHONY : all clean fclean re