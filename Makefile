NAME            := woody_woodpacker

MANDATORY_DIR   := sources
HEADERS_DIR     := includes
OBJ_DIR         := .objs

CC              := gcc
ASM             := nasm
RM              := rm -rf

ifeq ($(shell uname), Darwin)
    ASMFLAGS    := -f macho64 -D __APPLE__
else
    ASMFLAGS    := -f elf64 -D __LINUX__
endif

CFLAGS          := -Wall -Wextra -Werror -g3 -O0
DEPSFLAGS       := -MMD -MP
INCLUDES        := -I $(HEADERS_DIR) -I $(MANDATORY_DIR)

ALL_CFLAGS      := $(CFLAGS) $(DEPSFLAGS) $(INCLUDES)

SRCS_C          := $(shell find $(MANDATORY_DIR) -name "*.c" 2>/dev/null)
SRCS_ASM        := $(shell find $(MANDATORY_DIR) -name "*.asm" 2>/dev/null)

OBJS_C          := $(patsubst $(MANDATORY_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_C))
OBJS_ASM        := $(patsubst $(MANDATORY_DIR)/%.asm, $(OBJ_DIR)/%.o, $(SRCS_ASM))

ALL_OBJS        := $(sort $(OBJS_C) $(OBJS_ASM))
ALL_DEPS        := $(OBJS_C:.o=.d)

TOTAL_FILES     := $(words $(ALL_OBJS))
CURRENT_FILE    := 0

BOLD            := \033[1m
DIM             := \033[2m
CYAN            := \033[36m
GREEN           := \033[32m
YELLOW          := \033[33m
BLUE            := \033[34m
MAGENTA         := \033[35m
RED             := \033[31m
RESET           := \033[0m

define update_progress
	$(eval CURRENT_FILE=$(shell expr $(CURRENT_FILE) + 1))
	$(eval PERCENT=$(shell expr $(CURRENT_FILE) \* 100 / $(TOTAL_FILES)))
	$(eval PROGRESS=$(shell expr $(CURRENT_FILE) \* 20 / $(TOTAL_FILES)))
	$(eval REMAINING=$(shell expr 20 - $(PROGRESS)))
	@printf "\r\033[K   $(GREEN)✔$(RESET) %b %-50s$(RESET)\n" "$(1)" "$(2)"
	@printf "   [$(GREEN)%s$(DIM)%s$(RESET)] %3d%%" \
		"$(shell printf '%0.s#' $$(seq 1 $(PROGRESS) 2>/dev/null))" \
		"$(shell printf '%0.s-' $$(seq 1 $(REMAINING) 2>/dev/null))" \
		"$(PERCENT)"
endef

define get_file_size
$$(du -h $(1) 2>/dev/null | awk '{print $$1}')
endef

all: $(NAME)

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c Makefile
	@mkdir -p $(@D)
	$(call update_progress,$(YELLOW)Compiling C  $(RESET), $<)
	@$(CC) $(ALL_CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.asm Makefile
	@mkdir -p $(@D)
	$(call update_progress,$(MAGENTA)Compiling ASM$(RESET), $<)
	@$(ASM) $(ASMFLAGS) $< -o $@

$(NAME): $(ALL_OBJS)
	@printf "\r\033[K\n   $(BOLD)$(BLUE)Linking $(NAME)...$(RESET)\n"
	@$(CC) $(ALL_CFLAGS) $(ALL_OBJS) -o $(NAME)
	@if [ -f $(NAME) ]; then \
		printf "   $(GREEN)✔ $(NAME) compiled successfully!$(RESET) $(DIM)(%s)$(RESET)\n\n" "$(call get_file_size,$(NAME))"; \
	else \
		printf "   $(RED)✖ Failed to create $(NAME)$(RESET)\n\n"; \
		exit 1; \
	fi

-include $(ALL_DEPS)

clean:
	@printf "   $(RED)➤ Cleaning objects...$(RESET)\n"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@printf "   $(RED)➤ Removing executable...$(RESET)\n"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re