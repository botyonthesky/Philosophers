void *count_to_100(void *arg)
{
    (void)arg;

    for(int i = 0; i < 100; i++);
    printf("The count has finished\n");
    return (NULL);
}

void *print_hello(void *arg)
{
    
    (void)arg;

    for(int i = 0; i < 100; i++)
    printf("Hello, world!\n");
    return (NULL);
}

int main()
{
    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1, NULL, count_to_100, NULL);
    pthread_create(&thread_2, NULL, print_hello, NULL);
    pthread_join(thread_1, NULL); 
    pthread_join(thread_2, NULL);
 return (0);
}



void    example()
{
    pthread_t   tid1;
    pthread_t   tid2;

    t_counter counter;

    counter.count = 0;
    pthread_mutex_init(&counter.count_mutex, NULL);
    
    printf("Main : count excepted is 42000\n");
    pthread_create(&tid1, NULL, thread_routine, &counter);
    printf("main : crea du first : %ld\n", tid1);
    
    pthread_create(&tid2, NULL, thread_routine, &counter);
    printf("main : crea du second : %ld\n", tid2);
    
    pthread_join(tid1, NULL);
    printf("main : uninon du first %ld\n", tid1);
    
    pthread_join(tid2, NULL);
    printf("main : uninon du first %ld\n", tid2);

    if (counter.count != 2 * 21000)
        printf("main : le compte est de %u\n", counter.count);
    else
        printf("main : le compte est de %u\n", counter.count);

    
    pthread_mutex_destroy(&counter.count_mutex);
}