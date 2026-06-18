SOURCE =parsing/minishell.c parsing/minishell_1.c parsing/minishell_2.c parsing/parsing.c  parsing/parsing_pipe.c  parsing/parsing_redir.c parsing/parsing_redir_utils.c parsing/fusion_token.c parsing/clean_quotes.c \
		parsing/parsing_quote.c parsing/special_tokens.c parsing/token_pool.c parsing/handle.c parsing/handle_utils.c parsing/word_quote.c parsing/signal.c\
		builtins/builtins.c  builtins/cd.c builtins/exit.c builtins/cd_path.c builtins/env.c builtins/pwd.c builtins/export_utils.c builtins/unset.c builtins/echo.c builtins/export.c builtins/export_print.c builtins/export_validation.c \
		execution/exec_utils.c execution/exec_utils_1.c execution/exec_utils_2.c execution/exec_utils_3.c execution/exec_utils_4.c execution/exec_utils_5.c execution/exec_utils_6.c execution/exec_utils_7.c execution/exec_utils_8.c execution/minishell_exec.c execution/multiple_redirections.c \
		execution/token_to_cmd_1.c execution/token_to_cmd_2.c execution/token_to_cmd_3.c execution/token_to_cmd_4.c execution/token_to_cmd_5.c execution/expand.c execution/expand2.c execution/expand_utils.c execution/expand_utils_1.c\
		heredoc/heredoc.c heredoc/heredoc_utils.c heredoc/heredoc_utils_1.c heredoc/heredoc_utils_2.c

OBJ = ${SOURCE:.c=.o}
CC = cc
NAME = minishell
CFLAGS = -g3 -Wall -Wextra -Werror 

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ -lreadline libft/ft_printf/libftprintf.a  libft/libft.a

clean:
	@rm -f $(OBJ)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re