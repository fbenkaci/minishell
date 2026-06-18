/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:27:21 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/08 15:58:08 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../builtins/builtins.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

extern volatile sig_atomic_t	g_signal_status;

/*-------------------- ENUMS -----------------*/

typedef enum e_token
{
	NONE = -1,
	S_QUOTE,
	D_QUOTE,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	PARENTHESIS,
	SPACES,
	WORD_D_QUOTES,
	WORD_S_QUOTES,
	EMPTY_QUOTES,
}								t_token;

/*-------------------- STRUCTURES -----------------*/
typedef struct s_struct			t_struct;

typedef struct s_redir
{
	char						*filename;
	int							append;
	struct s_redir				*next;
}								t_redir;

typedef struct s_cmd
{
	char						**argv;
	char						*infile;
	t_redir						*infiles;
	char						*outfile;
	int							append;
	t_redir						*outfiles;
	int							heredoc;
	char						*heredoc_delim;
	int							heredoc_fd;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_exec
{
	int							pids;
	int							(*pipes)[2];
	int							nb_cmds;
	char						*path;
	int							last_status;
	t_cmd						*cmds;
}								t_exec;

typedef struct s_token_pool
{
	t_struct					*tokens;
	int							capacity;
	int							index;
}								t_token_pool;

typedef struct s_struct
{
	t_token						type;
	char						*str;
	char						**env;
	t_exec						*exec;
	t_token_pool				*token_pool;
	struct s_struct				*next;
}								t_struct;

/*-------------------- HEREDOC -----------------*/

int								handle_heredocs(t_struct **cur, t_cmd *cmd);
void							handle_sigint_heredoc(int sig);
int								init_heredoc_pipe(int *fd);
int								read_heredoc_line(char *delimiter, int line_nb,
									char *buffer);
void							check_heredoc_interrupts(int line_nb,
									char *delimiter, int *fd);

/*-------------------- EXPAND_HEREDOC -----------------*/

typedef struct s_expand_data
{
	char						*result;
	int							result_len;
	int							j;
}								t_expand_data;

int								process_variable_expansion(t_struct **cur,
									char *str, char **envp, int i);
int								handle_exit_status_expansion(t_struct **cur,
									char *current_str, int i);
int								handle_normal_variable_expansion(t_struct **cur,
									char *current_str, char **envp, int i);
int								process_exit_status_at_position(t_struct **cur,
									char *current_str, int *i);
int								process_char_expansion(t_struct **cur,
									char *current_str, char **envp, int *i);
int								expand_variable(t_struct **cur, char *str,
									char **envp);
int								process_variable_at_position(t_struct **cur,
									char *current_str, char **envp, int *i);
/*-------------------- FUNCTION PROTOTYPES -----------------*/

/* ========== SIGNAL HANDLING ========== */
void							handle_sigint(int sig);
void							handle_sigint_exec(int sig);
void							handle_sigint_heredoc(int sig);

/* ========== TOKEN POOL MANAGEMENT ========== */
t_token_pool					*init_token_pool(int initial_capacity);
t_struct						*get_token_from_pool(t_token_pool *pool);
void							reset_token_pool(t_token_pool *pool);
void							free_token_pool(t_token_pool *pool);
void							free_token_strings_only(t_token_pool *pool);
void							init_token(t_struct *token, t_token_pool *pool);

/* ========== VARIABLE EXPANSION ========== */
int								expand_variable(t_struct **cur, char *str,
									char **envp);
char							*replace_variable(char *str, int dollar_pos,
									char *var_name, char *var_value);
char							*extract_var_name(char *str, int start);
char							*get_env_value_2(char *var_name, char **envp);
char							*expand_variables_heredoc(t_struct **data,
									char *line);
char							*get_env_value_3(char *var_name);
char							*init_result_buffer(int line_len);
int								resize_buffer_if_needed(t_expand_data *data);
char							*ft_strncpy(char *dest, const char *src,
									size_t n);
int								update_current_string(t_struct **cur,
									char *original, char *new_str);

/* ========== EXECUTION ========== */
int								execution(t_cmd *cmd, t_exec *exec,
									t_struct **data);
int								open_all_heredocs(t_exec *exec, t_struct **data,
									t_cmd *cmd);
int								create_combined_input(t_cmd *cmd);
int								execute_single_builtin(t_exec *exec, t_cmd *cmd,
									t_struct **data);
void							setup_redirections(t_struct *data, t_cmd *cmd,
									t_exec *exec);
void							setup_pipe_redirections(t_exec *exec, int index,
									t_cmd *cmd);
void							run_command(t_struct **data, t_exec *exec,
									t_cmd *cmd);
void							complete_cleanup_and_exit(t_struct **data,
									t_exec *exec, t_cmd *cmd, int exit_code);
void							child_cleanup_and_exit(int exit_code);
void							close_pipes_and_wait(t_exec *exec);
int								fork_and_execute_commands(t_struct **data,
									t_exec *exec, t_cmd *cmd);
void							handle_cmd_error(char *cmd);
int								command_loc(t_struct *data, t_exec *exec,
									char *cmd);
void							add_infile_to_list(t_cmd *cmd,
									t_redir *new_redir, char *filename);
void							add_outfile_to_list(t_cmd *cmd,
									t_redir *new_redir, char *filename);
int								handle_variable_assignment(t_struct **cur,
									t_cmd *cmd, int *i, char **envp);
int								process_variable_expansion2(t_struct **cur,
									t_cmd *cmd, int *i, char **envp);
int								handle_append_redirection(t_struct **cur,
									t_cmd *cmd);
void							print_cmd_not_found(char *cmd);
int								is_path(char *cmd);
void							handle_exec_error(t_struct **data, t_exec *exec,
									t_cmd *cmd_list);
void							cleanup_line(t_struct *data);
void							handle_exit(t_struct *data);
void							handle_user_line(t_struct *data, t_exec *exec);
int								search_shlvl(t_struct *data);

/* ========== COMMAND CREATION ========== */
int								reorder_command_tokens(t_struct **cur);
t_cmd							*create_cmd_from_tokens(t_struct **cur,
									char **env, t_exec *exec);
int								handle_in(t_struct **cur, t_cmd *cmd);
int								handle_out_and_in(t_struct **cur, t_cmd *cmd);
int								handle_word_and_append(t_struct **cur,
									t_cmd *cmd, int *i, char **envp);

/* ========== PIPE MANAGEMENT ========== */
int								create_pipe(t_exec *data);
int								caculate_nb_cmd(t_exec *data, t_cmd *cmd);
int								ft_lstsize_bis(t_cmd *cmd);
void							close_unused_pipes(t_exec *data, int index);
void							close_pipes(t_exec *data, int index, int i,
									int j);

/* ========== HEREDOC ========== */
int								heredoc_input(t_struct **data, char *delimiter);

/* ========== MEMORY MANAGEMENT ========== */
void							free_all_cmd(t_cmd *cmd);
void							free_tokens(t_struct *tokens);
void							free_token_chain(t_struct *tokens);
void							free_all_shell(t_struct **data, t_exec *exec,
									t_cmd *cmd);
void							free_all_shell_parent(t_struct **data,
									t_exec *exec, t_cmd *cmd);

/* ========== UTILITIES ========== */
size_t							ft_strcat(char *dst, char *src);

/* ========== PARSING MAIN ========== */
int								parsing(t_struct *data);
void							is_token(t_struct *data);
int								identify_special_token(t_struct *data, int i);
int								identify_redirection(t_struct *data, int i);

/* ========== PARSING PIPES ========== */
int								utils_parse_pipe(t_struct *data, int i,
									int *found_pipe);
int								parse_error_pipe(t_struct *data);

/* ========== PARSING REDIRECTIONS ========== */
int								parse_redir(t_struct *data);
int								utils_parse_redir(t_struct *data, int i,
									int *found_redir);
int								handle_redir(t_struct *data, int i,
									int *found_redir);
int								get_error_type(t_struct *data);
int								handle_output_redir(t_struct *data, int i,
									int *found_redir);
int								handle_input_redir(t_struct *data, int i,
									int *found_redir);
int								handle_token_chars(t_struct *data, int i,
									int *found_redir);
int								process_char(t_struct *data, int i,
									int *found_redir);

/* ========== PARSING QUOTES ========== */
int								parsing_quote(t_struct *data);

/* ========== PATH UTILITIES ========== */
char							*find_path(char *cmd, char **paths);
void							free_paths(char **paths);

/* ========== TOKEN MANAGEMENT ========== */
void							free_token_list(t_struct *start);
t_struct						*create_token(const char *str, int len,
									t_token type, t_struct *new);
int								token_init(t_struct *data);
void							tokenize_string(t_struct *data, int i);
void							token_append(t_struct *data);

/* ========== TOKEN HANDLING ========== */
void							handle_space_token(char *s, int *i,
									t_struct **cur);
void							handle_word_token(char *s, int *i,
									t_struct **cur);
void							handle_special_tokens(char *s, int *i,
									t_struct **cur);
void							handle_redir_token(char *s, int *i,
									t_struct **cur);
void							handle_quotes(char *s, int *i, t_struct **cur);

/* ========== TOKEN HANDLING UTILITIES ========== */
int								handle_length_quotes(char *s, int *temp_i);
int								calculate_word_length(char *s, int start);
int								handle_extract_quotes(char *s, int *i);
int								extract_word_content(char *s, int *i,
									char *word_content);
void							append_and_advance(t_struct **cur,
									t_struct *new);

/* ========== WORD QUOTE HANDLING ========== */
void							word_quote(t_struct *data, int *i,
									t_struct **cur);
void							handle_word_d_quotes(t_struct *data, int *i,
									t_struct **cur);
void							handle_word_s_quotes(t_struct *data, int *i,
									t_struct **cur);

/* ========== TOKEN FUSION ========== */
void							echo_fusion(t_struct *data);

/* ========== QUOTE CLEANING ========== */
int								process_quote_chars(char *str, char *clean);
void							clean_quotes(t_struct *token);

/* ========== MULTIPLE REDIRECTIONS ========== */
int								handle_multiple_outfiles(t_struct *data,
									t_cmd *cmd, t_exec *exec);
int								handle_multiple_infiles(t_struct *data,
									t_cmd *cmd, t_exec *exec);
void							free_outfiles(t_redir *outfiles);
t_redir							*create_redir_node(char *filename, int append);
int								is_str_only_spaces(const char *str);

#endif