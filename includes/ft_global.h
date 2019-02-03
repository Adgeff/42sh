/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 01:51:22 by geargenc          #+#    #+#             */
/*   Updated: 2019/02/03 13:02:24 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOBAL_H

# define FT_GLOBAL_H

# include "ft_42sh.h"

char					*g_tokstr[] =
{
	"NONE",
	"WORD",
	"ASSIGNMENT_WORD",
	"NAME",
	"NEWLINE",
	"IO_NUMBER",
	"OPP",
	"PIPE",
	"AND",
	"SEMI",
	"GREAT",
	"LESS",
	"LPAR",
	"RPAR",
	"AND_IF",
	"OR_IF",
	"DLESS",
	"DGREAT",
	"LESSAND",
	"LESSANDDASH",
	"GREATAND",
	"GREATANDDASH",
	"LESSGREAT",
	"DLESSDASH",
	"CLOBBER",
	"LBRACE",
	"RBRACE",
	"COMMAND",
	"complete_command",
	"and_or",
	"pipeline",
	"pipe_sequence",
	"command",
	"compound_command",
	"subshell",
	"compound_list",
	"term",
	"brace_group",
	"simple_command",
	"cmd_name",
	"cmd_word",
	"cmd_prefix",
	"cmd_suffix",
	"redirect_list",
	"io_redirect",
	"io_file",
	"filename",
	"io_here",
	"here_end",
	"io_close",
	"newline_list",
	"linebreak",
	"separator_op",
	"separator"
};

t_toktab				g_toktab[] =
{
	{"|", PIPE},
	{"&", AND},
	{";", SEMI},
	{"<", LESS},
	{">", GREAT},
	{"(", LPAR},
	{")", RPAR},
	{"{", LBRACE},
	{"}", RBRACE},
	{"&&", AND_IF},
	{"||", OR_IF},
	{"<<", DLESS},
	{">>", DGREAT},
	{"<&", LESSAND},
	{"<&-", LESSANDDASH},
	{">&", GREATAND},
	{">&-", GREATANDDASH},
	{"<>", LESSGREAT},
	{"<<-", DLESSDASH},
	{">|", CLOBBER},
	{NULL, NONE}
};

t_tokcond				g_tokcond[] =
{
	{&ft_lex_operator, 0, 0},
	{&ft_lex_notoperator, 0, 0},
	{&ft_lex_newline, 0, 0},
	{&ft_lex_backslash, 1, 1},
	{&ft_lex_quote, 0, 1},
	{&ft_lex_dquote, 0, 1},
	{&ft_lex_dollar, 1, 1},
	{&ft_lex_bquote, 1, 1},
	{&ft_lex_ionumber, 0, 0},
	{&ft_lex_newoperator, 0, 0},
	{&ft_lex_blank, 0, 0},
	{&ft_lex_sharp, 0, 1},
	{&ft_lex_word, 1, 1},
	{&ft_lex_newword, 0, 0}
};

int						(*g_asttab[])(t_node **begin, t_node **current,
						t_node **list) =
{
	&ft_badtoken,
	&ft_ast_word,
	&ft_badtoken,
	&ft_badtoken,
	&ft_ast_newline,
	&ft_ast_io_number,
	&ft_badtoken,
	&ft_ast_pipe,
	&ft_ast_separator,
	&ft_ast_separator,
	&ft_ast_redir,
	&ft_ast_redir,
	&ft_ast_lpar,
	&ft_ast_rpar,
	&ft_ast_and_or,
	&ft_ast_and_or,
	&ft_ast_heredoc,
	&ft_ast_redir,
	&ft_ast_redir,
	&ft_ast_closefd,
	&ft_ast_redir,
	&ft_ast_closefd,
	&ft_ast_redir,
	&ft_ast_heredoc,
	&ft_ast_redir,
	&ft_ast_lbrace,
	&ft_ast_rbrace,
	&ft_badtoken
};

#endif
