/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:59:16 by mde-sa--          #+#    #+#             */
/*   Updated: 2023/10/03 11:59:51 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Includes
# include "../src/libft/libft.h"
# include <unistd.h>
# include <pthread.h>

// Error Codes
# define SUCCESS 0
# define ARG_ERROR 1
# define MALLOC_ERROR 2
# define THREAD_ERROR 3

// Philosopher States
# define EATING 0
# define THINKING 1
# define SLEEPING 2

// Fork states
# define AVAILABLE 0
# define TAKEN 1

// Argument struct
typedef struct s_args {
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
} t_args;

// Philosopher Struct
typedef struct s_philo {
    int number;
    int state;
    int last_meal;
} t_philo;

// Global struct
typedef struct s_global {
    t_args          *args;
    pthread_t*		philo;
    pthread_mutex_t *print_mutex;
} t_global;

// Function declarations
/// main.c
int     main(int argc, char **argv);
void	*routine(void *arg);

/// arg_check.c
int     check_args(int argc, char **argv);
void    init_args(t_args *args, int argc, char **argv);
void    print_args(t_args *args);

/// thread_management.c
int     create_threads(t_args *args, pthread_t *philo);
int     join_threads(t_args *args, pthread_t *philo);

#endif