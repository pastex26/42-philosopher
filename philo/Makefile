SRCS_FILES =	main \
				check_args \
				init_data \
				philo_action \
				philo_loop \
				monitoring \
				philo_utils \
				utils \
				free_data

#DIR---------------------
OBJ_DIR :=		.objs
DEP_DIR :=		.deps
SRC_DIR :=		src
INC_DIR :=		include
#------------------------

#FILES .C---------------------------------------------------------------------
SRCS :=			$(addsuffix .c, $(addprefix $(SRC_DIR)/, $(SRCS_FILES)))
#-----------------------------------------------------------------------------

#FILES .O .D------------------------------------------------------------------
OBJS =			$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
DEPS =			$(addprefix $(DEP_DIR)/, $(notdir $(SRCS:.c=.d)))
#-----------------------------------------------------------------------------

#NAMES---------------------
NAME := 		philo
#--------------------------

#PARAM----------------------------
CC := 			cc
CFLAGS :=		-Wall -Wextra -Werror
IFLAGS :=		-I$(INC_DIR)
DFLAGS :=		-MMD -MP
CF :=			$(CC) $(CFLAGS) $(IFLAGS)
#--------------------------------

#VPATH---------------------------
vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR)
vpath %.o $(OBJ_DIR)
vpath %.d $(DEP_DIR)

#style------------
GREEN := \033[0;32m
YELLOW :=\033[0;33m
RED := \033[0;31m
BLUE := \033[0;34m
END := \033[0m

GREENB := \033[1;32m
BLUEB := \033[1;34m
YELLOWB :=\033[1;33m
REDB := \033[1;31m
#-----------------

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOWB)🗃️  $@$(END)"
	@$(CF) $^ -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) $(DEP_DIR)
	@echo -n "$(BLUEB)🔨 $<"
	@echo " ->$(END) $@" | cut -b 1-8,15-
	@$(CF) $(DFLAGS) -c $< -o $@ -MF $(DEP_DIR)/$*.d

$(OBJ_DIR) $(DEP_DIR):
	@echo "$(GREENB)mkdir $(GREEN)$@$(END)"
	@mkdir -p $@

clean:
	@echo "$(REDB)🗑️  $(OBJ_DIR) $(DEP_DIR)$(END)"
	@echo "$(REDB)🗑️  $(NAME) $(END)"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)
	@rm -f $(NAME)

fclean: clean

re: fclean all

-include $(DEPS)

.PHONY: all re clean fclean