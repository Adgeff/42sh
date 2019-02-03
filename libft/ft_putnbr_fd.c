/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geargenc <geargenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 19:10:31 by geargenc          #+#    #+#             */
/*   Updated: 2017/11/19 19:10:32 by geargenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void		ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (fd > 0)
	{
		if (n >= 10 || n <= -10)
			ft_putnbr_fd(n / 10, fd);
		else if (n < 0)
			write(fd, "-", 1);
		c = n % 10 * ((n < 0) ? -1 : 1) + '0';
		write(fd, &c, 1);
	}
}