NAME = fdf
LIBFT = libft.a

SRC_DIR = ./src
SRC_FILES =	bresenham_line.c \
			initiate_matrix.c \
			map_parser.c \
			utils.c \
			utils_2.c \
			utils_3.c \
			main.c

			
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

LIBMLX = ./lib/MLX42
LIBMLX_BUILD = $(LIBMLX)/build
LIBFT_PATH = ./lib/libft

CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -rf
OBJ = $(SRC:.c=.o)
HEADER = ./header

HEADERS = -I $(HEADER) -I $(LIBMLX)/include
LIBS = $(LIBMLX_BUILD)/libmlx42.a -ldl -lglfw -pthread -lm -L $(LIBFT_PATH) -lft -fsanitize=address

all: libmlx $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX_BUILD)/libmlx42.a
	@$(CC) -o $(NAME) $(OBJ) $(LIBS)
	@echo "Compilation done"

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@echo "LIBFT created"

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX_BUILD) && make -C $(LIBMLX_BUILD) -j4
	@echo "MLX42 built"

%.o: %.c
	@$(CC) $(FLAGS) -I $(HEADER) -I $(LIBMLX)/include -c -o $@ $<
	@echo "compiling: $<"

clean: 
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@$(RM) $(OBJ) > /dev/null 2>&1
	@$(RM) $(LIBMLX_BUILD) > /dev/null 2>&1
	@echo "Clean done"

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@$(RM) $(NAME) > /dev/null 2>&1
	@echo "Fclean done"

re: fclean all

.PHONY: clean all re fclean libmlx

