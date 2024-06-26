/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:49 by tmaillar          #+#    #+#             */
/*   Updated: 2024/04/02 14:08:38 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>

# define FORK 0
# define THINK 1
# define EAT 2
# define SLEEP 3
# define DIED 4
# define LEFT 5
# define RIGHT 6
# define MALLOC "Memory allocation failed"
# define TIME "ISSUE : Failed to get_time_on_day"
# define INIT_ERR "ISSUE : Failed to init mutex"
# define CREATE_ERR "ISSUE : Failed on create mutex"
# define JOIN_ERR "ISSUE : Failed on join mutex"
# define NB_ARGV "Argument must be only digit between 1 and INT_MAX\n"
# define USAGE "Usage :\n \
argv[1] : number_of_philosophers\n \
argv[2] : time_to_die\n \
argv[3] : time_to_eat\n \
argv[4] : time_to_sleep\n \
argv[5] (optional) : [number_of_times_each_philosopher_must_eat]"

/*------------------------Structure Philo-----------------------------------*/

typedef struct s_philo	t_philo;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}					t_fork;

typedef struct s_table
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_to_think;
	long				nb_meal;
	int					nb_philo;
	int					nb_fork;
	bool				someone_died;
	pthread_t			monitor;
	bool				thread_ready;
	long				nb_thread;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		write_mutex;
	long				starting_time;
	t_fork				*fork_mutex;
	bool				is_finish;
	t_philo				*philo;
}					t_table;

typedef struct s_philo
{
	int					philo_id;
	long				count_meal;
	long				last_meal_time;
	bool				is_full;
	pthread_t			thread;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_mutex_t		philo_mutex;
	t_table				*table;
}							t_philo;

/*----------------------------------Base------------------------------------*/

int					main(int argc, char **argv);

/*----------------------------------Init------------------------------------*/

int					init_argv(t_table *table, char **av);
int					ft_init(t_table *table);
int					init_alloc(t_table *table);
int					init_philo(t_table *table);
void				manage_fork(t_philo *philo, t_fork *forks, int i);
int					init_fork(t_table *table);
int					init_mutex(t_table *table);
int					init_write(t_table *table);
int					init_table(t_table *table);
int					init_death(t_table *table);

/*----------------------------------Secure----------------------------------*/

int					secure_create(pthread_t *thread,
						void *data, void *arg);
int					secure_join(pthread_t thread);
int					secure_init(pthread_mutex_t *mutex);

/*----------------------------------Philo-----------------------------------*/

int					philo(char **av);
void				*monitor(void *data);
int					start_simulation(t_table *table);
void				join_and_finish(t_table *table);
bool				simulation_ended(t_table *table);
bool				simulation_end_bc_die(t_table *table);
bool				is_died(t_philo *philo);

/*----------------------------------Thread----------------------------------*/

void				*thread_routine(void *data);
void				*thread_solo_routine(void *data);
int					solo_routine(t_table *table);
void				synchronize_thread(t_table *table);

/*----------------------------------State-----------------------------------*/

void				eat_sleep_routine(t_philo *philo);
void				think_routine(t_philo *philo);
void				print_status(t_philo *philo, int status);

/*----------------------------------Check-----------------------------------*/

int					check_argv(char **av);
void				increase_data(pthread_mutex_t *mutex,
						long *data);
void				assign_data(pthread_mutex_t *mutex,
						long *data, long value);
long				check_data(pthread_mutex_t *mutex,
						long *value);
void				assign_bool(pthread_mutex_t *mutex,
						bool *check, bool value);
bool				check_bool(pthread_mutex_t *mutex, bool *value);

/*----------------------------------Time-----------------------------------*/

long				get_time(void);
void				synchro_philo(long time);
void				wait_eat(t_table *table, long timing);
void				wait_sleep(t_table *table, long timing);
void				wait_think(t_table *table, t_philo *philo);
void				wait_die(t_table *table, long timing);

/*----------------------------------Error-----------------------------------*/

int					error_msg(char *str, char *str2);
void				destroy_all(t_table *table);
void				ft_free(t_philo *philo);
void				*free_table(t_table *table);
void				clean_fork_mutex(t_table *table);

/*----------------------------------Utils-----------------------------------*/

void				*ft_calloc(size_t nmemb, size_t size);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
long				ft_atol(char *str);
int					is_valid_digit(long nb);

#endif
