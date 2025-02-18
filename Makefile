NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -pthread #-fsanitize=thread
INCLUDES = ./inc
INCLUDEFLAGS = -I$(INCLUDES)

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

SRC_DIR = ./src
OBJ_DIR = ./bin

SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/free_data.c \
	$(SRC_DIR)/init_data.c \
	$(SRC_DIR)/eat_routine.c \
	$(SRC_DIR)/sleep_think_routines.c \
	$(SRC_DIR)/philo_routine.c \
	$(SRC_DIR)/time_utils.c \
	$(SRC_DIR)/str_utils.c \
	$(SRC_DIR)/valid_args.c \
	$(SRC_DIR)/death_monitor_routine.c \
#	$(SRC_DIR)/.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME) $(OBJ_DIR)

$(OBJ_DIR):
	@echo "${YELLOW}Creating object directory $(OBJ_DIR)...${NC}"
	@mkdir -p $(OBJ_DIR)
	@echo "${GREEN}Object directory $(OBJ_DIR) created.${NC}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDEFLAGS) -c $< -o $@

${NAME}: $(OBJS)
	@echo "${YELLOW}Creating $(NAME) executable...${NC}"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "${GREEN}$(NAME) executable created.${NC}"

#all: $(NAME) $(OBJ_DIR)

clean:
	@echo "${YELLOW}Removing object files...${NC}"
	@rm -rf $(OBJ_DIR)
	@echo "${GREEN}Object files removed.${NC}"

fclean:
	@echo "${YELLOW}Removing object files...${NC}"
	@rm -rf $(OBJ_DIR)
	@echo "${GREEN}Object files removed.${NC}"
	@echo "${YELLOW}Removing $(Name) executable...${NC}"
	@rm -f $(NAME)
	@echo "${GREEN}$(NAME) executable removed.${NC}"

re: fclean all

.PHONY: all clean fclean re philo
