/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/31 18:16:04 by mde-sa--         ###   ########.fr       */
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

typedef enum e_ForkStatus
{
	AVAILABLE,
	TAKEN
}	t_ForkStatus;

// Error Messages
# define ARG_MESSAGE "Usage: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat] \
(optional)\n"
# define MUTEX_MESSAGE "Mutex error\n"
# define MALLOC_MESSAGE "Malloc error\n"
# define THREAD_MESSAGE "Thread error\n"

// Struct
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
	t_forks				*first_fork;
	t_forks				*second_fork;
	t_PhiloState		state;
	bool				full;
}	t_philos;

typedef struct s_message
{
	int						time_stamp;
	int						philo_id;
	t_PhiloState			philo_state;
	struct s_message		*next;
}	t_message;

typedef struct s_table
{
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					times_each_philosopher_must_eat;

	size_t				epoch_time;

	int					success_count;
	pthread_mutex_t		success_mutex;

	bool				death_flag;
	pthread_mutex_t		death_mutex;

	t_forks				*forks;

	t_philos			*philos;

	t_message			*message_head;
	t_message			*message_end;
	pthread_mutex_t		message_mutex;

}	t_table;

// Function declarations
/// main.c
int					main(int argc, char **argv);

/// arg_check.c
int					check_args(int argc, char **argv);
bool				is_argc_inadequate(int argc);
bool				arg_has_non_digit_chars(char **argv);
bool				is_arg_larger_than_int(char **argv);

/// arg_init.c
int					init_table(t_table *table, int argc, char **argv);
int					malloc_table_data(t_table *table);
void				init_malloc_data(t_table *table);
int					init_mutexes(t_table *table);

/// manage_threads.c
int					init_threads(t_table *table);

/// routines.c
void				*routine(void *table);

/// time.c
int					get_current_time();

/// clean_data.c
void				clean_data(t_table *table);
void				clean_mutexes(t_table *table);
void				clean_mallocs(t_table *table);
void				list_clear(t_message *message_head);


////// Helpers
void	print_philo(t_philos philo);


#endif