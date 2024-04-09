/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/09 12:43:02 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Includes
# include "../src/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

// Error Codes
typedef enum e_ErrorCode
{
	SUCCESS,
	ARG_ERROR,
	MUTEX_ERROR,
	MALLOC_ERROR,
	THREAD_ERROR
}	t_ErrorCode;

// Error Messages
# define ARG_MESSAGE "Usage: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat] \
(optional)\n"
# define MUTEX_MESSAGE "Mutex error\n"
# define MALLOC_MESSAGE "Malloc error\n"
# define THREAD_MESSAGE "Thread error\n"
# define PHILO_NO_MESSAGE "(Evaluation sheet states: \
'Do not test with more than 200 philosophers.')\n\n"
# define TIME_ERROR_MESSAGE "(Evaluation sheet states: \
'Do not test time_to_die or time_to_eat or time_to_sleep \
set to values lower than 60ms')\n\n"

// Philosopher actions
typedef enum e_PhiloAction
{
	TOOK_A_FORK,
	IS_EATING,
	IS_THINKING,
	IS_SLEEPING,
	DIED
}	t_PhiloAction;

// Philo Messages
# define FORK_MESSAGE "has taken a fork"
# define EATING_MESSAGE "is eating"
# define SLEEPING_MESSAGE "is sleeping"
# define THINKING_MESSAGE "is thinking"
# define DEATH_MESSAGE "died"

// Constants
# define NUMBER_OF_PHILOSOPHERS 1
# define TIME_TO_DIE 2
# define TIME_TO_EAT 3
# define TIME_TO_SLEEP 4
# define NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT 5
# define PHILO_NO_WAIT_TIME 25
# define LIST_WAIT_TIME 20

// Structs
typedef struct s_table	t_table;

typedef struct s_forks
{
	int					fork_id;
	pthread_mutex_t		fork_mutex;
}	t_forks;

typedef struct s_philos
{
	pthread_t			thread;
	int					philo_id;

	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				time_to_think;
	size_t				time_last_meal;
	int					times_each_philosopher_must_eat;

	t_forks				*first_fork;
	t_forks				*second_fork;

	int					eat_count;
	size_t				start_time;

	t_table				*table;
}	t_philos;

typedef struct s_message
{
	size_t				time_stamp;
	int					philo_id;
	t_PhiloAction		action;
	struct s_message	*next;
}	t_message;

struct s_table
{
	int					number_of_philos;
	pthread_mutex_t		number_mutex;

	int					success_count;

	bool				success_flag;
	pthread_mutex_t		success_mutex;

	bool				death_flag;
	pthread_mutex_t		death_mutex;

	bool				simulation_run;
	pthread_mutex_t		simulation_mutex;

	t_forks				*forks;

	t_philos			*philos;

	size_t				table_start_time;

	t_message			*message_head;
	t_message			*message_end;
	pthread_mutex_t		message_mutex;

};

// Function declarations
/// main.c
int					main(int argc, char **argv);

/// arg_check.c
t_ErrorCode			check_args(int argc, char **argv);
bool				is_argc_inadequate(int argc);
bool				arg_has_non_digit_chars(char **argv);
bool				is_arg_larger_than_int(char **argv);
bool				is_special_case(int argc, char **argv);

/// arg_init.c
t_ErrorCode			init_table(t_table *table, int argc, char **argv);
void				init_philo_data(t_table *table, int argc, char **argv);
void				init_fork_data(t_table *table);
void				setup_philo_times(t_philos *philo, int argc, char **argv);
void				assign_forks(t_philos *philo, t_table *table, int i);

/// mutexes_init.c
t_ErrorCode			init_mutexes(t_table *table);

/// manage_threads.c
t_ErrorCode			init_threads(t_table *table);
t_ErrorCode			end_threads(t_table *table);
void				wait_for_threads(t_table *table);
void				sync_threads(t_table *table);
t_ErrorCode			one_philo_simulation(int time_to_die);

/// routines.c
void				*routine(void *current_philo);
void				philo_thread(t_philos *philo);
void				*one_philo_routine(void *time_to_die);

/// fork_eat_think_sleep.c
void				take_first_fork_routine(t_philos *philo);
void				take_second_fork_routine(t_philos *philo);
void				eat_routine(t_philos *philo,
						size_t current_time);
void				think_routine(t_philos *philo,
						size_t current_time);
void				sleep_routine(t_philos *philo,
						size_t current_time);

/// monitoring_printing_thread.c
void				monitoring_and_printing_thread(t_table *table);
void				update_simstate(t_table *table, t_philos *philo,
						t_PhiloAction action, bool *simulation_stop);
void				wait_for_element(t_message **current, t_message **target,
						t_table *table);
void				print_philo_action(t_message current);

/// printing_buffer.c
void				add_message(t_philos *philo, t_table *table,
						t_PhiloAction action);
void				add_node_to_list(t_philos *philo, t_table *table,
						t_PhiloAction action);

/// end_conditions.c
bool				stop_simulation(t_table *table);
bool				someone_died(t_table *table);
void				set_death(t_philos *philo, size_t wait_time);

/// time_utils.c
size_t				get_abs_time(void);
size_t				get_current_time(t_philos *philo);
void				ft_usleep(size_t milliseconds);

/// clean_data.c
void				clean_data(t_table *table);
void				clean_mutexes(t_table *table);
void				clean_mallocs(t_table *table);
void				list_clear(t_message *message_head);

/// mutex_utils_getter.c
bool				get_bool(pthread_mutex_t *mutex, bool *value);
int					get_int(pthread_mutex_t *mutex, int *value);
size_t				get_size_t(pthread_mutex_t *mutex, size_t *value);
t_message			get_t_msg(pthread_mutex_t *mutex, t_message *message);

/// mutex_utils_setter.c
void				set_bool(pthread_mutex_t *mutex, bool *target,
						bool value);
void				set_int(pthread_mutex_t *mutex, int *target,
						int value);
void				set_size_t(pthread_mutex_t *mutex,
						size_t *target, size_t value);

/// warning.c
void				warning(char **argv);

#endif