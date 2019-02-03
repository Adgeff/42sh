/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_42sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:10:16 by geargenc          #+#    #+#             */
/*   Updated: 2019/02/03 13:01:55 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_42SH_H

# define FT_42SH_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <signal.h>

# include "../libft/libft.h"

typedef enum			e_tok
{
	NONE = 0,
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER,
	OPP,
	PIPE,
	AND,
	SEMI,
	GREAT,
	LESS,
	LPAR,
	RPAR,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESSAND,
	LESSANDDASH,
	GREATAND,
	GREATANDDASH,
	LESSGREAT,
	DLESSDASH,
	CLOBBER,
	LBRACE,
	RBRACE,
	COMMAND,
	complete_command,
	list,
	and_or,
	pipeline,
	pipe_sequence,
	command,
	compound_command,
	subshell,
	compound_list,
	term,
	brace_group,
	simple_command,
	cmd_name,
	cmd_word,
	cmd_prefix,
	cmd_suffix,
	redirect_list,
	io_redirect,
	io_file,
	filename,
	io_here,
	here_end,
	io_close,
	newline_list,
	linebreak,
	separator_op,
	separator
}						t_tok;

typedef struct			s_toktab
{
	char				*str;
	t_tok				token;
}						t_toktab;

typedef struct			s_toklist
{
	t_tok				token;
	size_t				start;
	size_t				len;
	struct s_toklist	*next;
}						t_toklist;

typedef struct			s_node
{
	t_tok				token;
	char				*data;
	struct s_node		*left;
	struct s_node		*right;
	struct s_node		*parent;
	struct s_node		*redir;
}						t_node;

typedef struct			s_main
{
	char				*ttyname;
	struct winsize		winsize;
}						t_main;

/*
**						lexer
*/

int						ft_lex_operator(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_notoperator(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_newline(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_backslash(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_quote(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_dquote(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_dollar(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_bquote(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_ionumber(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_newoperator(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_blank(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_sharp(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_word(char **input, size_t *index,
						t_toklist **current);
int						ft_lex_newword(char **input, size_t *index,
						t_toklist **current);
t_toklist				*ft_lexer(char **input);
void					ft_print_toklist(char *input, t_toklist *list);

/*
**						ast
*/

int						ft_ast_word(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_newline(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_io_number(t_node **begin, t_node **current,
						t_node **list);
int						ft_badtoken(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_pipe(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_separator(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_redir(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_lpar(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_rpar(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_and_or(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_heredoc(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_closefd(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_lbrace(t_node **begin, t_node **current,
						t_node **list);
int						ft_ast_rbrace(t_node **begin, t_node **current,
						t_node **list);

typedef struct			s_tokcond
{
	int					(*cond)(char **, size_t *, t_toklist **);
	int					dquote_mode;
	int					sub_mode;
}						t_tokcond;

extern char				*g_tokstr[];
extern t_toktab			g_toktab[];
extern t_tokcond		g_tokcond[];

#endif
