# 🎨 Rendering Cub3D 🎮
#		by De Trappistinhos 🍻

NAME	=	cub3D

SRCS_DIR		= srcs
SRCS			:= $(shell find $(SRCS_DIR) -name *.c)

OBJS_DIR		= objs
OBJS			:= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Once we have subdirectories
#OBJS_SUB_DIR	:= $(shell find $(SRCS_DIR) -mindepth 1 -type d)
#OBJS_SUB_DIR	:= $(OBJS_SUB_DIR:$(SRCS_DIR)/%=$(OBJS_DIR)/%)

LIBFT_DIR		= libft

# Get OS name
UNAME = $(shell uname)

# MAC
ifeq ($(UNAME), Darwin)
OS			= Apple
MLX_DIR		= ./minilibx_mms
MLX_LIB		= -lmlx
GRAPH_LIB	= 

#LINUX
else
OS			= Linux
MLX_DIR		= ./minilibx-linux
MLX_LIB		= -lmlx_Linux $(MLX_DIR)/libmlx.a
GRAPH_LIB	= -lXext -lX11 -lm -lz
# In case we need it in the future
#INCLUDES	+= -I/usr/include 
#LIBRARIES	+= -L/usr/lib
endif

INCLUDES		= -Iincludes -Ilibft -I$(MLX_DIR)
LIBRARIES		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) $(MLX_LIB) $(GRAPH_LIB)

CC				= gcc
RM				= rm -f
RM_DIR			= rm -rf
MAKE			= make
CFLAGS 			= -Wall -Wextra -Werror
DFLAGS			= -fsanitize=address #-ggdb3 #for valgrind

# COLORS
GRAY			= \e[1;30m
GREEN 			= \e[1;32m
DARK_GREEN		= \e[0;32m
YELLOW			= \e[1;33m
BLUE			= \e[1;34m
PURPLE			= \e[1;35m
CYAN			= \e[1;36m
WHITE			= \e[1;37m
NORMAL			= \e[0;37m
END				= \e[0m

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
					@mkdir -p $(OBJS_DIR)
#					@mkdir -p $(OBJS_SUB_DIR)
					$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			@printf "\n"
			$(MAKE) bonus -C $(LIBFT_DIR)
			$(MAKE) -C $(MLX_DIR)
ifeq ($(UNAME), Darwin)
			cp $(MLX_DIR)/libmlx.dylib ./
endif
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBRARIES) -o $(NAME)
			@printf "	$(WHITE)[$(GREEN) Success. Compiled $(NAME).$(WHITE)]\
			$(END) \n\n"

all:	$(NAME)

clean:
			@printf "\n	$(WHITE)[$(BLUE)"
			@printf "Cleaning $(NAME) objects$(END)]\n"
			$(RM) $(OBJS)
			$(RM_DIR) $(OBJS_DIR)

deep_clean:	clean
			@printf "\n	$(WHITE)[$(BLUE)"
			@printf "Cleaning libft objects$(END)]\n"
			$(MAKE) clean -C $(LIBFT_DIR)
			@printf "\n	$(WHITE)[$(BLUE)"
			@printf "Cleaning minilibx objects$(END)]\n"
			$(MAKE) clean -C $(MLX_DIR)

fclean:		clean
			@printf "\n	$(WHITE)[$(BLUE)"
			@printf "Cleaning $(NAME) output files$(END)]\n"
			$(RM) $(NAME)

deep_fclean:	deep_clean
				@printf "\n	$(WHITE)[$(BLUE)"
				@printf "Cleaning libft library$(END)]\n"
				$(MAKE) fclean -C $(LIBFT_DIR)
ifeq ($(UNAME), Darwin)
				$(RM) libmlx.dylib
endif
				@printf "\n	$(WHITE)[$(BLUE)"
				@printf "Cleaning $(NAME) output files$(END)]\n"
				$(RM) $(NAME)

re:			fclean all

debug:		CFLAGS += $(DFLAGS)
debug:		all

.PHONY:		all clean deep_clean fclean deep_fclean re
