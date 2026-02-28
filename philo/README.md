*This project has been created as part of the 42 curriculum by julauren*

# **Description**

In this project, you will learn the basics of threading a process.
You will learn how to create threads and explore the use of mutexes in order not to have *data race*.

# **Instructions**

Your Programm must take this following arguments :
- <u>number of philosophers</u> : the number of philosophers and also the number of forks.

- <u>time to die</u> **(in milliseconds)** : if a philosopher has not started eating within *time_to_die* milliseconds since the start of their last meal or the start of the simulation, he dies.

- <u>time to eat</u> **(in milliseconds)** : the time it takes for a philosopher to eat. During that time, they will need to hold two fork.

- <u>time to sleep</u> **(in milliseconds)** : the time a philosopher will spend sleeping.

- <u>number of times each philosopher must eat</u> (optional argument) : if all philosophers have eaten at least *number_of_times_each_philosopher_must_eat* times, the simulation stop. If no specified, the simulation stops when a philosopher dies.

# **Ressources**

- Threads & mutex : https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/

- liste circulaire doublement chaînées : http://sdz.tdct.org/sdz/les-listes-circulaires-doublement-chainees-en-c.html
