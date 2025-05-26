/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:05:54 by zjamaien          #+#    #+#             */
/*   Updated: 2025/05/26 16:14:16 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_locks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philonum)
	{
		if (pthread_mutex_init(&table->fork_mutex[i], NULL))
			return (terminate_on_error(table, 2));
	}
	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (terminate_on_error(table, 2));
	if (pthread_mutex_init(&table->meal_mutex, NULL))
		return (terminate_on_error(table, 2));
	if (pthread_mutex_init(&table->finish_mutex, NULL))
		return (terminate_on_error(table, 2));
	return (1);
}

void	destroy_padlocks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philonum)
		pthread_mutex_destroy(&table->fork_mutex[i]);
	clean_table(table);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->finish_mutex);
}
