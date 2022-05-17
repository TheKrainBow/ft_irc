SRCS_CORE		=	srcs/Main.cpp							\
					srcs/Client.cpp							\
					srcs/Command.cpp						\
					srcs/Server.cpp							\
					srcs/Channel.cpp

INCLUDES		=	-Iincludes								\

NAME			=	ft_irc
SRCS			=	$(SRCS_CORE)



OBJS			=	$(SRCS:.cpp=.o)
CC				=	clang++
RM				=	@rm -f

FLAGS			=	-Wall -Werror -Wextra $(INCLUDES)

.cpp.o:
					@$(CC) -c $< -o $(<:.cpp=.o) $(FLAGS)

$(NAME):			start_message $(OBJS)
					@if [ "$?" = "" ]; then echo "\033[1A\033[30C\033[0;33mAlready done\033[15D\033[1B\033[1A\033[2D\033[1;32m✓\033[26D\033[0m";else echo "\033[1A\033[25C\033[1;32m✓\033[26D\033[0m"; fi
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME)

$(LIBFT):
					@make -s -C libft -f Makefile


all:				$(NAME)

bonus:				re

clean:
					@echo "\033[0;33mCleaning \033[1;31m$(NAME)\033[0;33m's objects\033[0m"
					$(RM) $(OBJS)

fclean:				clean
					@echo "\033[0;33mRemoving \033[1;31m$(NAME)\033[0;33m.\033[0m"
					$(RM) $(NAME)

start_message:
					@echo "\033[0;33mMaking \033[1;31m$(NAME)\033[0;33m\t\t\033[1;30m[\033[1;31mX\033[1;30m]\033[0m"

re:					fclean start_message $(OBJS)
					@echo "\033[1A\033[25C\033[1;32m✓\033[26D\033[0m"
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME)

.PHONY:				all clean fclean re