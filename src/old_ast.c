/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 09:28:08 by geargenc          #+#    #+#             */
/*   Updated: 2019/01/30 09:29:51 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void			ft_unexpected_token(char *token)
{
	char		*chr;

	ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
	while ((chr = ft_strchr(token, '\n')))
	{
		write(2, token, chr - token);
		ft_putstr_fd("\\n", 2);
		token = chr + 1;
	}
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

void			ft_ast_push_one_back(t_node **from, t_node **to)
{
	if (*from)
	{
		while (*to)
			to = &((*to)->next);
		*to = *from;
		*from = (*from)->next;
		(*to)->next = NULL;
	}
}

void			ft_ast_del(t_node *ast)
{
	if (ast)
	{
		ft_ast_del(ast->next);
		ft_ast_del(ast->content);
		if (ast->data)
			free(ast->data);
		free(ast);
	}
}

void			ft_ast_del_one(t_node **ast)
{
	t_node		*tmp;

	if (*ast)
	{
		tmp = *ast;
		*ast = (*ast)->next;
		tmp->next = NULL;
		ft_ast_del(tmp);
	}
}

int				ft_ast_linebreak(t_node **ast)
{
	t_node		*new;

	while (!(*ast) || (*ast)->token == NEWLINE)
	{
		if (!(*ast))
		{
			if (!(new = ft_next_tokens()))
				return (-1);
			*ast = new;
		}
		else
			ft_ast_del_one(ast);
	}
	return (1);
}

int				ft_ast_simple_command_prefix(t_node **ast)
{
	t_node		*new;
	int			ret;

	if ((ret = ft_ast_cmd_prefix(ast)) != 1)
		return (ret);
	if (!(new = ft_new_node()))
		return (-1);
	new->token = simple_command;
	ft_ast_push_one_back(ast, &(new->content));
	if ((ret = ft_ast_cmd_word(ast)) == -1)
		return (-1);
	if (ret == 1)
	{
		ft_ast_push_one_back(ast, &(new->content));
		if ((ret = ft_ast_cmd_suffix(ast)) == -1)
			return (-1);
		if (ret == 1)
			ft_ast_push_one_back(ast, &(new->content));
	}
	return (1);
}

int				ft_ast_simple_command_noprefix(t_node **node)
{
	
}

int				ft_ast_simple_command(t_node **ast)
{
	if ((ret = ft_ast_simple_command_prefix(ast)) == -1)
		return (-1);
	if (ret == 0)
		ret = ft_ast_simple_command_noprefix(ast);
	return (ret);
	if (ret == 1)
	{
		if (!(new = ft_new_node()))
			return (-1);
		new->token = simple_command;
		ft_ast_push_one_back(ast, &(new->content));
		if ((ret = ft_ast_cmd_word(ast)) == -1)
			return (-1);
		if (ret == 1)
		{
			ft_ast_push_one_back(ast, &(new->content));
			if ((ret = ft_ast_cmd_suffix(ast)) == -1)
				return (-1);
			if (ret == 1)
				ft_ast_push_one_back(ast, &(new->content));
		}
	}
}

int				ft_ast_command_compound(t_node **ast)
{
	t_node		*new;
	int			ret;

	if ((ret = ft_ast_compound_command(ast)) != 1)
		return (ret);
	if (!(new = ft_new_node()))
		return (-1);
	new->token = command;
	ft_ast_push_one_back(ast, &(new->content));
	if ((ret = ft_ast_redirect_list(ast)) == -1)
		return (-1);
	if (ret == 1);
		ft_ast_push_one_back(ast, &(new->content));
	new->next = *ast;
	*ast = new;
}

int				ft_ast_command(t_node **ast)
{
	t_node		*new;
	int			ret;

	if ((ret = ft_ast_simple_command(ast)) == -1)
		return (-1);
	if (ret == 1)
	{
		if (!(new = ft_new_node()))
			return (-1);
		ft_ast_push_one_back(ast, &(new->content));
		new->token = command;
		new->next = *ast;
		*ast = new;
	}
	else if ((ret = ft_ast_command_compound(ast)) != 1)
		return (ret);
	return (1);
}

int				ft_ast_pipe_sequence_end(t_node **ast)
{
	t_node		*new;
	int			ret;

	if ((*ast)->token != pipe_sequence || !(*ast)->next
		|| (*ast)->next->token != PIPE)
		return (0);
	if (!(ft_ast_linebreak(&((*ast)->next->next))))
		return (-1);
	if ((ret = ft_ast_command(&((*ast)->next->next))) == -1)
		return (ret);
	if (ret == 0)
	{
		ft_unexpected_token_error((*ast)->next->next->data);
		return (-1);
	}
	if (!(new = ft_new_node()))
		return (-1);
	new->token = pipe_sequence;
	ft_ast_push_one_back(ast, &(new->content));
	ft_ast_push_one_back(ast, &(new->content));
	ft_ast_push_one_back(ast, &(new->content));
	new->next = *ast;
	*ast = new;
	return (1);
}

int				ft_ast_pipe_sequence(t_node **ast)
{
	t_node		*new;
	int			ret;

	if ((ret = ft_ast_command(ast)) != 1)
		return (ret);
	if (!(new = ft_new_node()))
		return (-1);
	new->token = pipe_sequence;
	ft_ast_push_one_back(ast, &(new->content));
	new->next = *ast;
	*ast = new;
	while (ret == 1)
		ret = ft_ast_pipe_sequence_end(ast);
	if (ret == -1)
		return (-1);
	return (1);
}

int				ft_ast_pipeline(t_node **ast)
{
	t_node		*new;
	int			ret;

	if ((ret = ft_ast_pipe_sequence(ast)) != -1)
		return (ret);
	if (!(new = ft_new_node()))
		return (-1);
	new->token = pipeline;
	ft_ast_push_one_back(ast, &(new->content));
	new->next = *ast;
	*ast = new;
	return (1);
}

int				ft_ast_and_or_end(t_node **ast)
{
	t_node		*new;
	int			ret;

	if ((*ast)->token != and_or || !(*ast)->next
		|| ((*ast)->next->token != AND_IF && (*ast)->next->token != OR_IF))
		return (0);
	if (ft_ast_linebreak(&((*ast)->next->next)) == -1)
		return (-1);
	if ((ret = ft_ast_pipeline(&((*ast)->next->next))) == -1)
		return (ret);
	if (ret == 0)
	{
		ft_unexpected_token_error((*ast)->next->next->data);
		return (-1);
	}
	if (!(new = ft_new_node()))
		return (-1);
	new->token = and_or;
	ft_ast_push_one_back(ast, &(new->content));
	ft_ast_push_one_back(ast, &(new->content));
	ft_ast_push_one_back(ast, &(new->content));
	new->next = *ast;
	*ast = new;
	return (1);
}

int				ft_ast_and_or(t_node **ast)
{
	t_node		*new;
	int			ret;

	if ((ret = ft_ast_pipeline(ast)) != 1)
		return (ret);
	if (!(new = ft_new_node()))
		return (-1);
	new->token = and_or;
	ft_ast_push_one_back(ast, &(new->content));
	new->next = *ast;
	*ast = new;
	while (ret == 1)
		ret = ft_ast_and_or_end(ast);
	if (ret == -1)
		return (-1);
	return (1);
}

int				ft_ast_list(t_node **ast)
{
	t_node		*new;
	int			ret;

	if ((ret = ft_ast_and_or(ast)) != 1)
		return (ret);
	if (!(new = ft_new_node()))
		return (-1);
	new->token = list;
	ft_ast_push_one_back(ast, &(new->content));
	if ((ret = ft_ast_separator_op(&((*ast)->next))) == -1)
		return (-1);
	if (ret == 1)
	{
		if ((ret = ft_ast_list(&((*ast)->next->next))) == -1)
			return (-1);
		if (ret == 1)
		{
			ft_ast_push_one_back(ast, &(new->content));
			ft_ast_push_one_back(ast, &(new->content));
		}
	}
	new->next = *ast;
	*ast = new;
	return (1);
}

int				ft_ast_complete_command(t_node **ast)
{
	t_node		*new;
	int			ret;

	if ((ret = ft_ast_list(ast)) != 1)
		return (ret);
	if (!(new = ft_new_node()))
		return (-1);
	new->token = complete_command;
	ft_ast_push_one_back(ast, &(new->content));
	if ((ret = ft_ast_separator(&((*ast)->next))) == -1)
		return (-1);
	if (ret == 1)
		ft_ast_push_one_back(ast, &(new->content));
	new->next = *ast;
	*ast = new;
	return (1);
}
