MANDATORY_DIR	=	sources
HEADERS_DIR		=	includes
OBJ_DIR			=	.objs

# fonts
SRCS			=	$(shell find $(MANDATORY_DIR) -name "*.c")

# objects
OBJS			=	$(patsubst $(MANDATORY_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

CC				=	gcc
RM				=	rm -f
CFLAGS			=	-I$(HEADERS_DIR) -I$(MANDATORY_DIR) -g3 -O0 #-Wall -Wextra -Werror

NAME			=	woody_woodpacker

GREEN			=	\033[1;32m
BLUE			=	\033[1;34m
RED				=	\033[1;31m
YELLOW			=	\033[1;33m
DEFAULT			=	\033[0m
UP				=	"\033[A"
CUT				=	"\033[K"

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c Makefile
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf ${UP}${CUT}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

clean:
	@echo "$(RED)Cleaning build folder$(DEFAULT)"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all lib clean fclean re
