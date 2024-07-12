MANDATORY_DIR	=	sources
HEADERS_DIR		=	includes
OBJ_DIR			=	.objs

SRCS			=	$(shell find $(MANDATORY_DIR) -name "*.c")
# SRCS_ASM		=	$(shell find $(MANDATORY_DIR) -name "*.asm")

OBJS			=	$(patsubst $(MANDATORY_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
# OBJS_ASM		=	$(patsubst $(MANDATORY_DIR)%.asm, $(OBJ_DIR)%.o, $(SRCS_ASM))

HEADERS			=	$(shell find $(HEADERS_DIR) -name "*.h") $(shell find $(MANDATORY_DIR) -name "*.h")

CC				=	gcc
ASM				=	nasm
RM				=	rm -f
CFLAGS			=	-I$(HEADERS_DIR) -I$(MANDATORY_DIR) -g3 -O0  # -Wall -Wextra -Werror

ifeq ($(shell uname), Darwin)
	ASMFLAGS	=	-f macho64
else
	ASMFLAGS	=	-f elf64
endif

NAME			=	woody_woodpacker

GREEN			=	\033[1;32m
BLUE			=	\033[1;34m
RED				=	\033[1;31m
YELLOW			=	\033[1;33m
DEFAULT			=	\033[0m
UP				=	"\033[A"
CUT				=	"\033[K"

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf ${UP}${CUT}

# $(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.asm $(HEADERS)
# 	@mkdir -p $(@D)
# 	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
# 	@$(ASM) $(ASMFLAGS) $< -o $@
# 	@printf ${UP}${CUT}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

clean:
	@echo "$(RED)Cleaning build folder$(DEFAULT)"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all lib clean fclean re
