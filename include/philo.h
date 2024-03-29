/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:49 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 09:41:05 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>

#define FORK 0
#define THINK 1
#define EAT 2
#define SLEEP 3
#define DIED 4
#define LEFT 5
#define RIGHT 6
#define MALLOC "Memory allocation failed"
#define TIME "ISSUE : Failed to get_time_on_day"
#define INIT_ERR "ISSUE : Failed to init mutex"
#define CREATE_ERR "ISSUE : Failed on create mutex"
#define JOIN_ERR "ISSUE : Failed on join mutex"
#define NB_ARGV "Argument must be only digit between 1 and INT_MAX\n \
and/or the numbers of philosophers cant be more than 200"
#define USAGE "Usage :\n \
argv[1] : number_of_philosophers\n \
argv[2] : time_to_die\n \
argv[3] : time_to_eat\n \
argv[4] : time_to_sleep\n \
argv[5] (optional) : [number_of_times_each_philosopher_must_eat]"

/*------------------------Structure Philo-----------------------------------*/

typedef struct s_philo t_philo;

typedef		struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}					t_fork;


typedef	struct 			s_table
{
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	unsigned long		time_to_think;
	long				nb_meal;
	int					nb_philo;
	int					nb_fork;
	bool				someone_died;
	pthread_t			monitor;
	bool				thread_ready;
	long				nb_thread;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		write_mutex;
	unsigned long		starting_time;
	t_fork				*fork_mutex;
	bool				is_finish;
	t_philo				*philo;
}					t_table;



typedef struct				s_philo
{
	int					philo_id;
	long				count_meal;
	long				last_meal;
	bool				is_full;
	pthread_t			thread;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_mutex_t		philo_mutex;
	t_table				*table;
}							t_philo;

/*----------------------------------Base------------------------------------*/

int     main(int argc, char **argv);

/*----------------------------------Init------------------------------------*/

int   				ft_init(t_table *table, char **av);
int					init_argv(t_table *table, char **av);
int					init_alloc(t_table *table);
int					init_philo(t_table *table);
int				    init_fork(t_table *table);
int					init_mutex(t_table *table);
int 				init_write(t_table *table);
int 				init_meal(t_table *table);
// int					init_death(t_table *table);
// pthread_t    		*init_thread(t_philo *philo);

/*----------------------------------Philo-----------------------------------*/

int    				philo(char **av);
void				manage_fork(t_philo *philo, t_fork *forks, int i);
void    			start_simulation(t_table *table);
void			    *monitor(void *data);
long			 	get_time(void);
void    			*thread_routine(void *data);


/*----------------------------------Thread----------------------------------*/

void    			*thread_routine(void *data);
void				*thread_solo_routine(void *data);
void				solo_routine(t_table *table);
void				eat_routine(t_philo *philo);
void				wait_philo(size_t timing);
void				stop_simulation(t_table *table);
void				print_status(t_philo *philo, int status, int side, int debug);
// void				print_status_debug(t_philo *philo, int status, int side);
void			    synchronize_thread(t_table *table);
bool				is_all_thread(pthread_mutex_t *mutex, long *thread, long nb_philo);

/*----------------------------------Check-----------------------------------*/

int 				check_argv(char **av);
void    			increase_data(pthread_mutex_t *mutex, long *data);
void    			assign_data(pthread_mutex_t *mutex,long *data, long value);
long				check_data(pthread_mutex_t *mutex, long *value);
void    			assign_bool(pthread_mutex_t *mutex, bool *check, bool value);
bool    			check_bool(pthread_mutex_t *mutex, bool *value);
bool				philo_died(t_philo *philo);
bool     			philo_full(t_philo *philo);


/*----------------------------------Error-----------------------------------*/

int    				error_msg(char *str, char *str2);
void    			destroy_all(t_table *table);
void				ft_free(t_philo *philo);
/*----------------------------------Utils-----------------------------------*/

void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
long	ft_atol(char *str);
int 	is_valid_digit(long nb);

#endif