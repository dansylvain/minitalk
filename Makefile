NAME = server
CLIENT = client
MAKEFLAGS += --no-print-directory
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a

SRC_SERVER =	source_files/server.c \
				source_files/signals_server.c \
				source_files/server_utils.c \
				source_files/server_transmission.c \

SRC_CLIENT = 	source_files/client.c \
				source_files/signals_client.c \
				source_files/client_utils.c \
				source_files/client_transmission.c \
				

OBJ_SERVER = $(SRC_SERVER:.c=.o)

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(NAME) $(CLIENT)

$(NAME): $(OBJ_SERVER) $(LIBFT) $(FT_PRINTF)
	@$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME) -Llibft -lft -Lft_printf -lftprintf
	@echo "\033[0;32mServer Compilation successful\033[0m"

$(CLIENT): $(OBJ_CLIENT) $(LIBFT) $(FT_PRINTF)
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENT) -Llibft -lft -Lft_printf -lftprintf
	@echo "\033[0;32mClient Compilation successful\033[0m"

$(OBJ_SERVER): %.o: %.c
	@$(CC) $(CFLAGS) -Ilibft -Ift_printf -c $< -o $@

$(OBJ_CLIENT): %.o: %.c
	@$(CC) $(CFLAGS) -Ilibft -Ift_printf -c $< -o $@

$(LIBFT):
	@make -s bonus -C libft 
	@make -s -C libft 

$(FT_PRINTF):
	@make -s -C ft_printf 

clean:
	@rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	@make -C libft clean 
	@make -C ft_printf clean 

fclean: clean
	@rm -f $(NAME) $(CLIENT)
	@make -C libft fclean
	@make -C ft_printf fclean 

re: fclean all

# .PHONY: all clean fclean re bonus client