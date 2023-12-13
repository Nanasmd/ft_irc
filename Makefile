# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbled <nbled@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 18:11:23 by nbled             #+#    #+#              #
#    Updated: 2023/09/07 18:15:26 by nbled            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##### Colors ####
GREEN 	= \033[0;32m
RED 	= \033[0;31m
BLUE 	= \033[0;34m
END		= \033[0m

### Names ###
NAME 		= ircserv
CC 			= c++
CFLAGS		= -Wall -Werror -Wextra -std=c++98

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

_SRC	= main.cpp \
		Channel.cpp \
		Client.cpp \
		Server.cpp

INCLUDES = Channel.hpp \
		Client.hpp \
		Server.hpp

SRC		= $(addprefix $(SRC_DIR)/, $(_SRC))
OBJ		= $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
HEADER	= $(addprefix $(INC_DIR)/, $(INCLUDES))

#### Makefile work ####
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER)
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) -I$(INC_DIR) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@echo "$(GREEN)Baking $(NAME)...$(END)"
	$(CC) -I$(INC_DIR) -o $@ $(OBJ) $(CFLAGS)
	@echo "$(BLUE)$(NAME) READY!$(END)"
		
clean:
	@echo "Removing objects..."
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Done!$(END)"
		
fclean: clean
	@echo "Cleaning everything..."
	@rm -f $(NAME)
	@echo "$(GREEN)Done!$(END)"
	@echo "$(BLUE)Everything is clean!$(END)"
		
re: fclean all

.PHONY: all clean fclean re
