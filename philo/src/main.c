/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:39:24 by zjamaien          #+#    #+#             */
/*   Updated: 2025/05/26 19:01:44 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	if (now() - philo->last_eat >= philo->table->die_time)
	{
		display_philosopher_status(philo, DIE);
		is_time_to_finish(philo, YES);
		//philo->table->finish_flag = 1;
		pthread_mutex_unlock(&philo->table->meal_mutex);
		return (1);
	}
	else if (philo->table->meal_limit > 0
		&& philo->meal_count >= philo->table->meal_limit)
	{
		philo->table->ate_enough++;
		if (philo->table->ate_enough >= philo->table->philonum)
		{
			is_time_to_finish(philo, YES);
			display_philosopher_status(philo, FINISH);
			pthread_mutex_unlock(&philo->table->meal_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->table->meal_mutex);
	return (0);
}

void	begin_dinner_monitor(t_table *table)
{
	int	i;
	int	continue_flag;

	continue_flag = 1;
	while (continue_flag)
	{
		i = -1;
		table->ate_enough = 0;
		{
			while (++i < table->philonum)
			{
				if (continue_flag && check_philo_status(&table->philo[i]))
					continue_flag = 0;
			}
			usleep(100);
		}
	}
	terminate_dinner(table);
}

void	display_philosopher_status(t_philo *philo, const char *status)
{
	long long	time;

	pthread_mutex_lock(&philo->table->print_mutex);
	if (!is_time_to_finish(philo, NO))
	{
		time = now() - philo->table->start_time;
		printf("%lld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
	if (status[0] == 'f')
		printf("%s\n", FINISH_MSG);
}

long long	now(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

int	main(int ac, char **av)
{
	t_table	table;

	memset(&table, 0, sizeof(table));
	if (!set_table(&table, ac, av))
		return (1);
	if (!call_philosophers(&table))
		return (1);
	if (!start_locks(&table))
		return (1);
	if (!turn_philosophers_in_threads(&table))
		return (1);
	begin_dinner_monitor(&table);
	return (0);
}
