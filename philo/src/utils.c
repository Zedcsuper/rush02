/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:58:27 by zjamaien          #+#    #+#             */
/*   Updated: 2025/05/26 17:36:49 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *s)
{
	int	ret;
	int	signal;
	int	i;

	ret = 0;
	signal = 1;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			signal *= -1;
		i++;
	}
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		else if (s[i] >= '0' || s[i] <= '9')
			ret = (ret * 10) + (s[i] - '0');
		i++;
	}
	return (signal * ret);
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar_fd(*(s++), fd);
}

int	terminate_on_error(t_table *table, int n)
{
	ft_putstr_fd("Error\n", 2);
	if (n == 1)
		clean_table(table);
	if (n == 2)
		destroy_padlocks(table);
	if (n == 3)
		terminate_dinner(table);
	return (0);
}

void	think_time(t_philo *philo, long long stop)
{
	long long	begin;

	begin = now();
	while (!is_time_to_finish(philo, NO) && (now() - begin) < stop)
		usleep(100);
}
