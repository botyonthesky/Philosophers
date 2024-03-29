/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaillar <tmaillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 07:34:35 by tmaillar          #+#    #+#             */
/*   Updated: 2024/03/29 09:53:26 by tmaillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    print_status(t_philo *philo, int status, int side, int debug)
{
    long time;
    bool    is_finish;

    is_finish = philo->table->is_finish;
    
    time = get_time() - philo->table->starting_time;
    if (philo->is_full == true)
        return ;
    
    if (debug == 0)
    {
        pthread_mutex_lock(&philo->table->write_mutex);
        if (status == FORK && !is_finish)
            printf("%ld %d has taken a fork\n", time, philo->philo_id);
        if (status == FORK && !is_finish)
            printf("%ld %d has taken a fork\n", time, philo->philo_id);    
        if (status == THINK && !is_finish)
            printf("%ld %d is thinking\n", time, philo->philo_id);
        if (status == EAT && !is_finish)
            printf("%ld %d is eating\n", time, philo->philo_id);
        if (status == SLEEP && !is_finish)
            printf("%ld %d is sleeping\n", time, philo->philo_id);
        if (status == DIED && !is_finish)
            printf("%ld %d is died\n", time, philo->philo_id);
        pthread_mutex_unlock(&philo->table->write_mutex);
    }
    else
    {
        pthread_mutex_lock(&philo->table->write_mutex);
        if (status == FORK && side == LEFT && !is_finish)
            printf("%ld philo %d has taken the left fork n%d\n", time, philo->philo_id, philo->left_fork->fork_id);
        if (status == FORK && side == RIGHT && !is_finish)
            printf("%ld philo %d has taken the right fork n%d\n", time, philo->philo_id, philo->right_fork->fork_id);    
        if (status == EAT && !is_finish)
            printf("%ld philo %d is eating his %lu meal whith fork %d and %d\n", time, philo->philo_id,
            philo->count_meal, philo->left_fork->fork_id, philo->right_fork->fork_id);
        if (status == SLEEP && !is_finish)
            printf("%ld philo %d is sleeping\n", time, philo->philo_id);
        if (status == THINK && !is_finish)
            printf("%ld philo %d is thinking\n", time, philo->philo_id);
        if (status == DIED && !is_finish)
            printf("%ld philo %d is died\n", time, philo->philo_id);
        pthread_mutex_unlock(&philo->table->write_mutex);
    }
}



void    wait_philo(size_t timing)
{
    //EST-ce que qqun est mort ? philo->table->someone_dead?
    //SI OUI return exit val;
    long    time;

    time = get_time() + timing;

    while (get_time() < time)
    {
        usleep(1000);
    }
}

void    stop_simulation(t_table *table)
{
    destroy_all(table);
    return ;
}
void    *thread_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    synchronize_thread(philo->table);
    assign_data(&philo->philo_mutex, &philo->last_meal, get_time());
    increase_data(&philo->table->meal_mutex, &philo->table->nb_thread);
    if (philo->table->nb_philo % 2 == 0)
        wait_philo(50);
    while (philo->table->is_finish == false)
    {

        if (check_bool(&philo->philo_mutex, &philo->is_full) == true)
            break ; 
        eat_routine(philo);
        print_status(philo, SLEEP, -1, 0);
        wait_philo(philo->table->time_to_sleep);
        
        print_status(philo, THINK, -1, 0);
        wait_philo(philo->table->time_to_think);
    }
    return (NULL);
}
void    eat_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork->fork);
    print_status(philo, FORK, LEFT, 0);
    pthread_mutex_lock(&philo->right_fork->fork);
    print_status(philo, FORK, RIGHT, 0);
    assign_data(&philo->philo_mutex, &philo->last_meal, get_time());
    increase_data(&philo->table->meal_mutex, &philo->count_meal);
    print_status(philo, EAT, -1, 0);
    wait_philo(philo->table->time_to_eat);
    if (philo_full(philo) == true)
    {
        assign_bool(&philo->table->meal_mutex, &philo->is_full, true);    
        assign_bool(&philo->table->meal_mutex, &philo->table->is_finish, true);
    }
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_unlock(&philo->left_fork->fork);
}

void    *thread_solo_routine(void *data)
{
    t_philo *philo;
    
    philo = (t_philo *)data;
    pthread_mutex_lock(&philo->left_fork->fork);
    print_status(philo, FORK, LEFT, 1);
    wait_philo(philo->table->time_to_die);
    print_status(philo, DIED, -1, 1);
    pthread_mutex_unlock(&philo->left_fork->fork);
    return (NULL);
}



// void    *thread_routine(void *data)
// {
//     t_philo *philo;
//     int i;
//     size_t dinner_start;
//     size_t time_to_die;
    
//     philo = (t_philo *)data;
//     i = 0;
//     dinner_start = philo->table->starting_time;
//     time_to_die = philo->table->time_to_die;
//     printf("philo %d is thinking\n", philo->philo_id);
    
//     philo->last_meal_time = dinner_start;

//     while (i < philo->table->nb_meal || philo->table->nb_meal == -1)
//     {
//         if (philo->table->nb_philo % 2 == 1)
//         {
//             pthread_mutex_lock(&philo->table->fork_mutex[philo->fork_id[0]]);
//             printf("philo %d has taken a fork %d\n", philo->philo_id, philo->fork_id[0]);
//             pthread_mutex_lock(&philo->table->fork_mutex[philo->fork_id[1]]);
//             printf("philo %d has taken a second fork %d\n", philo->philo_id, philo->fork_id[1]);
//         }
//         else
//         {     
//             pthread_mutex_lock(&philo->table->fork_mutex[philo->fork_id[1]]);
//             printf("philo %d has taken a fork %d\n", philo->philo_id, philo->fork_id[1]);
//             pthread_mutex_lock(&philo->table->fork_mutex[philo->fork_id[0]]);
//             printf("philo %d has taken a second fork %d\n", philo->philo_id, philo->fork_id[0]);
//         }
//         if ((get_time() + time_to_die) < dinner_start)
//         {
//             pthread_mutex_lock(&philo->meal_mutex);
//             printf("philo %d is eating\n", philo->philo_id);
//             wait_philo(philo->table->time_to_eat);
//             pthread_mutex_unlock(&philo->meal_mutex);
//             pthread_mutex_unlock(&philo->table->fork_mutex[philo->fork_id[0]]);
//             pthread_mutex_unlock(&philo->table->fork_mutex[philo->fork_id[1]]);
//         }
//         else
//         {
//             pthread_mutex_lock(&philo->death_mutex);
//             printf("philo %d is died\n", philo->philo_id);
//             pthread_mutex_unlock(&philo->death_mutex);
//             philo->is_dead = true;
//         }
//         if (philo->is_dead == true)
//             stop_simulation(philo->table);
//         pthread_mutex_lock(&philo->philo_mutex);
//         printf("philo %d is sleeping\n", philo->philo_id);
//         wait_philo(philo->table->time_to_sleep);
//         pthread_mutex_unlock(&philo->philo_mutex);
//         i++;
//     }
//     return (NULL);
// }