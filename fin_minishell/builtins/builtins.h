/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:38:28 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/07/05 19:49:02 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../parsing/minishell.h"

typedef struct s_redir			t_redir;
typedef struct s_cmd			t_cmd;
typedef struct s_exec			t_exec;
typedef struct s_struct			t_struct;
typedef struct s_token_pool		t_token_pool;
typedef struct s_gc_node		t_gc_node;
typedef struct s_garbage		t_garbage;
typedef struct s_expand_data	t_expand_data;

/*------------------builtin-----------------*/
char							*add_env_var(t_struct *data, char *var,
									char *new_val_var);
int								ft_export(t_exec *exec, t_struct *data,
									char **cmd);
int								ft_unset(t_exec *exec, t_struct *data,
									char **cmd);
int								ft_env(t_exec *exec, t_struct *data,
									char **cmd);
int								ft_cd(t_exec *exec, t_struct *data, char **cmd);
int								ft_echo(t_exec *exec, char **cmd);
int								ft_pwd(t_exec *exec);
int								exec_builtin(t_exec *exec, t_struct *data,
									t_cmd *cmd);
int								is_builtin(char *cmd);

/*------------------export functions-----------------*/

void							print_export(t_exec *exec, char **cpy_env);
void							print_after_equal(char **cpy_env, int i, int j,
									int *flag);
void							sorted_export(char **cpy_env);
int								is_valid_identifier(char *cmd);
int								is_likely_parsing_fragment(char *arg,
									char **cmd, int current_index);
int								should_process_export_arg(char *arg);
int								is_valid_export(char *cmd);

/*------------------env functions-----------------*/

int								add_or_replace_env_var(t_struct *data,
									char *cmd);
int								add_in_env(t_struct *data, char *cmd);
int								cpy_env(t_struct *data, char **envp);
char							*update_env(t_struct *data, char *var,
									char *new_val_var);
int								update_pwd_vars(t_struct *data, char *oldpwd);
int								cd_path(t_struct *data, const char *path);
void							free_all(char *new_pwd, char *oldpwd,
									char *env_old, char *env_new);
void							actualize_last_status(t_exec *exec, int *flag);

/*------------------exit functions-----------------*/
int								ft_exit(t_exec *exec, t_struct *data,
									t_cmd *cmd);

#endif