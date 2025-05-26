/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:02:28 by zjamaien          #+#    #+#             */
/*   Updated: 2025/05/26 19:15:56 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	turn_philosophers_in_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philonum)
	{
		if (pthread_create(&table->philo[i].thrd, NULL, begin_meal,
				&table->philo[i]))
			return (terminate_on_error(table, 3));
	}
	return (1);
}

int	call_philosophers(t_table *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->philonum);
	table->fork_mutex = malloc(sizeof(pthread_mutex_t) * table->philonum);
	if (!table->philo || !table->fork_mutex)
		return (terminate_on_error(table, 1));
	table->start_time = now();
	while (++i < table->philonum)
	{
		table->philo[i].id = i + 1;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->philonum;
		table->philo[i].meal_count = 0;
		table->philo[i].last_eat = table->start_time;
		table->philo[i].table = table;
	}
	return (1);
}

int	set_table(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (terminate_on_error(NULL, 0));
	table->philonum = ft_atoi(av[1]);
	table->die_time = ft_atoi(av[2]);
	table->eat_time = ft_atoi(av[3]);
	table->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		table->meal_limit = ft_atoi(av[5]);
	else
		table->meal_limit = -1;
	if (table->philonum < 1 || table->die_time < 1 || table->eat_time < 1
		|| table->sleep_time < 1 || (ac == 6 && table->meal_limit < 1))
		return (terminate_on_error(NULL, 0));
	table->finish_flag = 0;
	return (1);
}
