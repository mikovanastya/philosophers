NAME 	= philo

SRCS = 	init.c \
		philo.c \
		utils.c \
		print.c \
		death.c

HEADER = philo.h

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