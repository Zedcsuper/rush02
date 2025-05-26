/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:07:45 by zjamaien          #+#    #+#             */
/*   Updated: 2025/05/26 19:24:14 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_time_to_finish(t_philo *philo, int finish_order)
{
	pthread_mutex_lock(&philo->table->finish_mutex);
	if (finish_order || philo->table->finish_flag)
	{
		if (finish_order)
			philo->table->finish_flag = 1;
		pthread_mutex_unlock(&philo->table->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->finish_mutex);
	return (0);
}

void	clean_table(t_table *table)
{
	free(table->philo);
	free(table->fork_mutex);
}

void	terminate_dinner(t_table *table)
{
	int	i;
	i = -1;
	while (++i < table->philonum && table->finish_flag)
		pthread_join(table->philo[i].thrd, NULL);
	destroy_padlocks(table);
}
