/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/20 21:50:23 by mde-sa--         ###   ########.fr       */
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

// Error Codes
enum e_ErrorCode {
	SUCCESS,
	ARG_ERROR,
	MALLOC_ERROR,
	THREAD_ERROR
};

// Philosopher States
enum e_PhiloState {
	START_STATE,
	AVAILABLE_FOR_EATING_2_FORK_LEFT,
	AVAILABLE_FOR_EATING_1_FORK_LEFT,
	EATING,
	AVAILABLE_FOR_THINKING,
	THINKING,
	AVAILABLE_FOR_SLEEPING,
	SLEEPING,
	DEAD
};

enum e_ForkState {
	TAKEN,
	AVAILABLE
};

// Error Messages
# define ARG_MESSAGE "Usage: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat] \
(optional)\n"
# define MALLOC_MESSAGE "Malloc error\n"
# define THREAD_MESSAGE "Thread error\n"

// Argument struct
typedef struct s_args {
	// Data from Command Line Input
	int					number_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;

	// Threads.
	// Philosopher #philo_id is "threads[philo_id]"" and is in state "philo_state[philo_id]""
	// There are "number_of_philos" threads.
	// Philo_id will be unique to each thread.
	pthread_t			*threads;
	enum e_PhiloState	*philo_state;
	int					philo_id;
	pthread_mutex_t		philo_id_mutex;

	// Forks.
	// Each fork to the left and to the right of each philosopher is protected by a mutex and can change state
	// There are "number_of_philos" Forks.
	enum e_ForkState	*forks;						// Forks array (N of Philosophers + 1)
	pthread_mutex_t		*forks_mutex;				// Forks mutex array (N of Philososphers + 1)

	// Data to keep track of events
	int					death_count;
	pthread_mutex_t		death_count_mutex;
	int					success_count;
	pthread_mutex_t		success_count_mutex;

	// Print mutex
	pthread_mutex_t		print_mutex;

}	t_args;

// Function declarations
/// main.c
int					main(int argc, char **argv);

/// arg_check.c
int					check_args(int argc, char **argv);
int					init_args(t_args *args, int argc, char **argv);
void				init_mutexes(t_args *args);
void				clear_args(t_args *args);

/// thread_management.c
int					create_threads(t_args *args);
int					join_threads(t_args *args);

/// routine.c
void				*routine(void *arg);
void				simulation_stop_at_success(t_args *arg,
						int thread_id, int start_time);
void				simulation_stop_at_death(t_args *arg,
						int thread_id, int start_time);

/// eat_think_sleep.c
void				eat_routine(t_args *arg, int thread_id,
						int time_last_meal, int start_time);
void				take_left_fork(t_args *arg, int thread_id,
						int time_last_meal, int start_time);
void				take_right_fork(t_args *arg, int thread_id,
						int time_last_meal, int start_time);
void				sleep_routine(t_args *arg, int thread_id,
						int time_last_meal, int start_time);
void				think_routine(t_args *arg, int thread_id,
						int time_last_meal, int start_time);

/// update_mutex.c
void				update_count(int *count, pthread_mutex_t *count_mutex);
int					update_philo_state(t_args *arg, int thread_id,
						int time_last_meal, int current_time);
int					check_death(t_args *arg, int thread_id,
						int time_last_meal, int current_time);

/// time_functions.c
long long			get_current_time(void);
long long			get_time_diff(long long start_time, long long end_time);

/// print_message.c
enum e_ErrorCode	print_message(t_args *arg, int thread_id,
						long current_time);
char				*get_full_philo_message(t_args *arg, int thread_id,
						long current_time);
char				*left_side_of_str(int thread_id,
						long current_time);
char				*right_side_of_str(t_args *arg,
						int thread_id);
char				*concatenate_str_with_space(char *left_string,
						char *right_string);

/// helper_functions.c
void				print_args(t_args *args);
void				print_message_helper(t_args *args, int thread_id,
						char *message);

#endif