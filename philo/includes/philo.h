/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjamaien <zjamaien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:38:59 by zjamaien          #+#    #+#             */
/*   Updated: 2025/05/26 16:14:30 by zjamaien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				meal_count;
	int				left_fork;
	int				right_fork;
	long long		last_eat;
	struct s_table	*table;
	pthread_t		thrd;
}					t_philo;

typedef struct s_table
{
	int				philonum;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meal_limit;
	int				ate_enough;
	int				finish_flag;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	finish_mutex;
}					t_table;

#define TAKING_FORK "has taken a fork"
#define EAT "is eating"
#define SLEEPING "is sleeping"
#define THINKING "is thinking"
#define DIE "died"
#define FINISH "f"
#define FINISH_MSG "All philosophers ate enough"
#define YES 1
#define NO 0

void				think_time(t_philo *philo, long long ms);
void				display_philosopher_status(t_philo *philo,
						const char *status);
long long			now(void);
int					terminate_on_error(t_table *table, int n);
int					ft_atoi(const char *s);
int					isolated_philosopher(t_table *table);
int					start_locks(t_table *table);
int					call_philosophers(t_table *table);
int					set_table(t_table *table, int ac, char **av);
int					is_time_to_finish(t_philo *philo, int order);
int					check_philo_status(t_philo *philo);
void				begin_feeding(t_philo *philo);
void				*begin_meal(void *arg);
int					turn_philosophers_in_threads(t_table *table);
void				clean_table(t_table *table);
void				destroy_padlocks(t_table *table);
void				terminate_dinner(t_table *table);
void				begin_dinner_monitor(t_table *table);