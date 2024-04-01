/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/04/01 12:27:38 by mde-sa--         ###   ########.fr       */
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

// State of simulation
typedef enum e_SimState
{
	CONTINUE,
	STOP_SIMULATION
}	t_SimState;

// Philosopher States
typedef enum e_PhiloState
{
	MISSING_2_FORK,
	MISSING_1_FORK,
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
}	t_PhiloState;

// Fork Status
typedef enum e_ForkStatus
{
	AVAILABLE,
	TAKEN
}	t_ForkStatus;

// Mutex actions
typedef enum e_MutexAction
{
	LOCK,
	UNLOCK
}	t_MutexAction;

// Error Messages
# define ARG_MESSAGE "Usage: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat] \
(optional)\n"
# define MUTEX_MESSAGE "Mutex error\n"
# define MALLOC_MESSAGE "Malloc error\n"
# define THREAD_MESSAGE "Thread error\n"

// String outputs
# define TOOK_A_FORK " has taken a fork\n"
# define IS_EATING " is eating\n"
# define IS_THINKING " is thinking\n"
# define IS_SLEEPING " is sleeping\n"
# define DIED " died\n"

// Struct

typedef struct s_table	t_table;

typedef struct s_forks
{
	int					fork_id;
	t_ForkStatus		fork_status;
	pthread_mutex_t		fork_mutex;
}	t_forks;

typedef struct s_philos
{
	pthread_t			thread;
	int					philo_id;
	size_t				time_since_last_meal;
	t_forks				*first_fork;
	t_forks				*second_fork;
	t_PhiloState		state;
	bool				full;
	t_table				*table;
}	t_philos;

typedef struct s_message
{
	int						time_stamp;
	int						philo_id;
	t_PhiloState			philo_state;
	struct s_message		*next;
}	t_message;

struct s_table
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_each_philosopher_must_eat;

	int					success_count;
	bool				success_flag;
	pthread_mutex_t		success_mutex;

	bool				death_flag;
	pthread_mutex_t		death_mutex;

	bool				simulation_run;
	pthread_mutex_t		simulation_mutex;

	t_forks				*forks;

	t_philos			*philos;

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
t_ErrorCode			malloc_table_data(t_table *table);
void				init_philo_data(t_table *table);
void				init_fork_data(t_table *table);
t_ErrorCode			init_mutexes(t_table *table);

/// manage_threads.c
t_ErrorCode			init_threads(t_table *table);
void				sync_threads(t_table *table);
void				wait_for_threads(t_table *table);
t_ErrorCode			end_threads(t_table *table);

/// routines.c
void				*routine(void *current_philo);
void				printing_thread(t_philos *philo);
void				philo_thread(t_philos *philo);

/// fork_eat_think_sleep.c
void				take_first_fork_routine(t_philos *philo, int current_time);
void				take_second_fork_routine(t_philos *philo, int current_time);
void				eat_routine(t_philos *philo, int current_time);
void				think_routine(t_philos *philo, int current_time);
void				sleep_routine(t_philos *philo, int current_time);

/// monitor_print_thread.c
bool				stop_simulation(t_table *table);

/// time_utils.c
size_t				get_current_time(void);
size_t				get_time_diff(size_t start_time, size_t now);
void				ft_usleep(size_t milliseconds);

/// special_cases.c

/// clean_data.c
void				clean_data(t_table *table);
void				clean_mutexes(t_table *table);
void				clean_mallocs(t_table *table);
void				list_clear(t_message *message_head);

/// mutex_utils_getter.c
bool				get_bool(pthread_mutex_t *mutex, bool *value);
int					get_int(pthread_mutex_t *mutex, int *value);
size_t				get_size_t(pthread_mutex_t *mutex, size_t *value);

/// mutex_utils_setter.c
void				set_bool(pthread_mutex_t *mutex, bool *target,
						bool value);
void				set_int(pthread_mutex_t *mutex, int *target,
						int value);
void				set_size_t(pthread_mutex_t *mutex,
						size_t *target, size_t value);

/// Helpers
void				print_philo(t_philos philo);

#endif