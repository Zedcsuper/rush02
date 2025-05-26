/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:55:24 by zjamaien          #+#    #+#             */
/*   Updated: 2025/05/26 20:03:27 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*begin_meal(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		think_time(philo, philo->table->eat_time / 2);
	while (1)
	{
		if (philo->table->philonum == 1)
		{
			isolated_philosopher(philo->table);
			return (0);
		}
		if (is_time_to_finish(philo, NO))
			return (0);
		begin_feeding(philo);
		display_philosopher_status(philo, SLEEPING);
		think_time(philo, philo->table->sleep_time);
		display_philosopher_status(philo, THINKING);
		if (philo->table->philonum % 2 != 0)
			think_time(philo, philo->table->eat_time / 2);
	}
	return (0);
}

int	isolated_philosopher(t_table *table)
{
	display_philosopher_status(&table->philo[0], TAKING_FORK);
	think_time(&table->philo[0], table->die_time);
	display_philosopher_status(&table->philo[0], DIE);
	is_time_to_finish(&table->philo[0], YES);
	return (0);
}

void	begin_feeding(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left_fork]);
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->fork_mutex[philo->right_fork]);
		pthread_mutex_lock(&philo->table->fork_mutex[philo->left_fork]);
	}
	display_philosopher_status(philo, TAKING_FORK);
	display_philosopher_status(philo, TAKING_FORK);
	philo->last_eat = now();
	display_philosopher_status(philo, EAT);
	think_time(philo, philo->table->eat_time);
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->fork_mutex[philo->left_fork]);
}
