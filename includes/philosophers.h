/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/12/21 22:52:52 by mde-sa--         ###   ########.fr       */
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
	MUTEX_ERROR,
	MALLOC_ERROR,
	THREAD_ERROR
};

// Philosopher States
enum e_PhiloState {
	START_STATE,
	AVAILABLE_FOR_EATING_2_FORK_LEFT,
	AVAILABLE_FOR_EATING_1_FORK_LEFT,
	EATING,
	THINKING,
	SLEEPING,
	DEAD
};


// Error Messages
# define ARG_MESSAGE "Usage: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat] \
(optional)\n"
# define MUTEX_MESSAGE "Mutex error\n"
# define MALLOC_MESSAGE "Malloc error\n"
# define THREAD_MESSAGE "Thread error\n"

// Argument struct
typedef struct s_args {
	int					number_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					times_each_philosopher_must_eat;

	pthread_mutex_t		print_mutex;

	int					*success_array;
	int					success_count;
	pthread_mutex_t		success_count_mutex;

	int					death_flag;
	pthread_mutex_t		death_mutex;

	int					philo_id;
	enum e_PhiloState	*philo_state;
	pthread_t			*threads;
	pthread_mutex_t		philo_id_mutex;

	pthread_mutex_t		*forks;



}	t_args;

// Function declarations
/// main.c
int					main(int argc, char **argv);

/// arg_check.c
int					check_args(int argc, char **argv);
int					init_args(t_args *arg, int argc, char **argv);
int					init_arrays(t_args *arg);
int					init_mutexes(t_args *arg);


/// clean_memory.c
void				clear_args(t_args *arg);
void				clear_memory(t_args *arg);
void				clear_mutexes(t_args *arg);

/// thread_management.c
int					create_threads(t_args *arg);
int					join_threads(t_args *arg);

/// routine.c
void				*routine(void *arg);
void				simulation_stop_at_success_or_death(t_args *arg,
						int thread_id, size_t start_time, size_t epoch_time);
void				simulation_stop_at_death(t_args *arg,
						int thread_id, size_t start_time, size_t epoch_time);

/// eat_think_sleep.c
void				eat_routine(t_args *arg, int thread_id,
						size_t time_last_meal, size_t start_time);
void				take_left_fork(t_args *arg, int thread_id,
						size_t time_last_meal, size_t start_time);
void				take_right_fork(t_args *arg, int thread_id,
						size_t time_last_meal, size_t start_time);
void				sleep_routine(t_args *arg, int thread_id,
						size_t time_last_meal, size_t start_time);
void				think_routine(t_args *arg, int thread_id,
						size_t time_last_meal, size_t start_time);

/// update_mutex.c
void				update_success(t_args *arg, int thread_id);
void				update_count(int *count, pthread_mutex_t *count_mutex);
int					update_philo_state(t_args *arg, int thread_id,
						size_t time_last_meal, size_t epoch_time);
int					check_death(t_args *arg, int thread_id,
						size_t time_last_meal, size_t epoch_time);

/// time_functions.c
size_t				get_current_time(void);
size_t				get_time_diff(size_t start_time, size_t end_time);
int					ft_usleep(size_t milliseconds);
/* int					get_timestamp(t_args *arg); */

/// print_message.c
void				print_message(t_args *arg, int thread_id,
						size_t current_time, size_t epoch_time);
char				*get_full_philo_message(t_args *arg, int thread_id,
						size_t current_time, size_t epoch_time);
char				*left_side_of_str(int thread_id, size_t current_time,
						size_t epoch_time);
char				*right_side_of_str(t_args *arg,
						int thread_id);
char				*concatenate_str_with_space(char *left_string,
						char *right_string);

/// helper_functions.c
void				print_args(t_args *arg);
void				print_message_helper(t_args *arg, int thread_id,
						char *message);
void				print_state(t_args *arg, int thread_id);
char				*size_t_to_str(size_t value);

#endif