#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_philo
{
        int id;
        int d;
        pthread_mutex_t *mutex;

}       t_philo;

typedef struct s_ret
{
        int d;
}       t_ret;

void    *table(void *val)
{
    t_philo *t;

    t = (t_philo *)val;
    if (t->id % 2)
        usleep(200);
    pthread_mutex_lock(&t->mutex[t->id]);
    printf("%d has taken a fork\n", t->id + 1);
    pthread_mutex_lock(&(t->mutex[(t->id + 1) % 3]));
    printf("%d has taken a fork\n", t->id + 1);
    printf("%d is eating\n", t->id + 1);
    usleep(200 * 1000);
    pthread_mutex_unlock(&t->mutex[t->id]);
    pthread_mutex_unlock(&(t->mutex[(t->id + 1) % 3]));
    printf("%d is sleeping\n", t->id + 1);
    usleep(200 * 1000);
    printf("%d is thinking\n", t->id + 1);
    t->d = t->id + 10;
    return (void *)t;
}


int main(int ac, char **av)
{
    pthread_t *philo;
    pthread_mutex_t *mutex;
    t_philo *p;
    void *r;
    int         k;

    if (ac != 5 && ac != 6)
    {
        printf("waa wa waaa wa waa wa \n");
        return 1;
    }
    
    // int n_philo = atoi(av[1]);
    // printf("%d\n\n", n_philo);
    p = malloc(sizeof(t_philo) * atoi(av[1]));
    // r = malloc(sizeof(t_ret) * 3);
    philo = malloc(sizeof(pthread_t) * atoi(av[1]));
    mutex = malloc(sizeof(pthread_mutex_t) * atoi(av[1]));
    for (int i = 0; i < atoi(av[1]); i++)
    {
        pthread_mutex_init(&mutex[i], NULL);
    }
    for (int i = 0; i < atoi(av[1]); i++)
    {
        p[i].id = i;
        p[i].mutex = mutex;
    }
    for (int i = 0; i < atoi(av[1]); i++)
    {
        pthread_create(&philo[i], NULL, table, &p[i]);
    }
    for (int i = 0; i < atoi(av[1]); i++)
    {
        pthread_join(philo[i], &r);
        // printf("philo->%d\n", i + 1);
    }
}