/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/26 18:41:09 by mde-sa--         ###   ########.fr       */
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
enum e_ErrorCode
{
	SUCCESS,
	ARG_ERROR,
	MUTEX_ERROR,
	MALLOC_ERROR,
	THREAD_ERROR
};

// State of simulation
enum e_SimState
{
	CONTINUE,
	STOP_SIMULATION
};

// Philosopher States
enum e_PhiloState
{
	START_STATE,
	AVAILABLE_FOR_EATING_2_FORK_LEFT,
	AVAILABLE_FOR_EATING_1_FORK_LEFT,
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
	ALIVE
};

enum e_ForkStatus
{
	AVAILABLE,
	TAKEN
};

// Error Messages
# define ARG_MESSAGE "Usage: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat] \
(optional)\n"
# define MUTEX_MESSAGE "Mutex error\n"
# define MALLOC_MESSAGE "Malloc error\n"
# define THREAD_MESSAGE "Thread error\n"

// Argument struct
typedef struct s_args
{
	int					number_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					times_each_philosopher_must_eat;

	size_t				epoch_time;

	int					*success_array;
	int					success_count;
	pthread_mutex_t		success_count_mutex;

	int					death_flag;
	pthread_mutex_t		death_mutex;

	int					philo_id;
	enum e_PhiloState	*philo_state;
	pthread_t			*threads;
	pthread_mutex_t		philo_id_mutex;

	enum e_ForkStatus	*fork_status;
	int					*fork_holder;
	pthread_mutex_t		*fork_status_mutex;

	pthread_mutex_t		*forks;

	t_list				*output;
	t_list				*output_head;
	t_list				*output_end;
	pthread_mutex_t		linked_list_mutex;

	t_list				*next_to_eat;
	t_list				*next_to_eat_head;
	t_list				*next_to_eat_end;
	pthread_mutex_t		next_to_eat_mutex;

	pthread_mutex_t		cleanup_mutex;
}	t_args;

// Function declarations
/// main.c
int					main(int argc, char **argv);

/// arg_check.c
int					check_args(int argc, char **argv);
bool				is_argc_inadequate(int argc);
bool				arg_has_non_digit_chars(char **argv);
bool				is_arg_larger_than_int(char **argv);

/// arg_init.c
int					init_args(t_args *arg, int argc, char **argv);
int					init_mem_alloc(t_args *arg);
void				fill_in_args_arrays(t_args *arg);
int					init_mutexes(t_args *arg);

/// clean_memory.c
void				clear_args(t_args *arg);
void				clear_mallocs(t_args *arg);
void				clear_mutexes(t_args *arg);
void				clear_linkedlists(t_args *arg);

/// thread_management.c
int					create_threads(t_args *arg);
int					join_threads(t_args *arg);

/// routine.c
void				*routine(void *arg);
void				simulation(t_args *arg, int thread_id, size_t start_time,
						size_t epoch_time);
void				printing_thread(t_args *arg);
enum e_SimState		check_end_of_simulation(t_args *arg);
void				wait_for_print_buffer(t_args *arg, t_list **print);

/// update_forks.c
void				take_left_fork(t_args *arg, int thread_id,
						size_t time_last_meal, size_t start_time);
void				take_right_fork(t_args *arg, int thread_id,
						size_t time_last_meal, size_t start_time);
enum e_ForkStatus	check_fork(t_args *arg, int fork_position);
void				update_fork(t_args **arg, int fork_position, int thread_id);
void				cleanup_forks(t_args *arg, int thread_id);

/// eat_think_sleep.c
void				take_forks(t_args *arg, int thread_id,
						size_t time_last_meal, size_t epoch_time);
void				eat_routine(t_args *arg, int thread_id,
						size_t time_last_meal, size_t start_time);
void				sleep_routine(t_args *arg, int thread_id,
						size_t time_last_meal, size_t start_time);
void				think_routine(t_args *arg, int thread_id,
						size_t time_last_meal, size_t start_time);

/// update_mutex.c
void				update_success(t_args *arg, int thread_id);
void				update_count(int *count, pthread_mutex_t *count_mutex);
void				update_philo_state(t_args *arg, int thread_id,
						size_t time_last_meal, size_t epoch_time);
enum e_PhiloState	check_death(t_args *arg, int thread_id,
						size_t time_last_meal, size_t epoch_time);

/// time_functions.c
size_t				get_current_time(void);
size_t				get_time_diff(size_t start_time, size_t end_time);
int					ft_usleep(size_t milliseconds);

/// print_message.c
enum e_ErrorCode	create_print_message(t_args *arg, int thread_id,
						size_t current_time, size_t epoch_time);
char				*get_full_philo_message(t_args *arg, int thread_id,
						size_t current_time, size_t epoch_time);
char				*left_side_of_str(int thread_id, size_t current_time,
						size_t epoch_time);
char				*right_side_of_str(t_args *arg, int thread_id);
char				*concatenate_str_with_space(char *left_string,
						char *right_string);

/// buffered_output.c
enum e_ErrorCode	add_to_buffered_output(t_args *arg, char *string);
void				print_output(t_args *arg);

#endif