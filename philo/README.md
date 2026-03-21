*This project has been created as part of the 42 curriculum by julauren*

# **Description**

In this project, you will create a basic multithreaded processing system.
This is a simulation of philosophers eating spaghetti.
Incredible, isn't it ?

# **Instructions**

First, you need to run the makefile in your terminal with the make command. This will compile all your files into a single executable.

Your Programm must take this following arguments in this order separated by a space :
- <u>number of philosophers</u> : the number of philosophers and also the number of forks.

- <u>time to die</u> **(in milliseconds)** : if a philosopher has not started eating within *time_to_die* milliseconds since the start of their last meal or the start of the simulation, he dies.

- <u>time to eat</u> **(in milliseconds)** : the time it takes for a philosopher to eat.

- <u>time to sleep</u> **(in milliseconds)** : the time a philosopher will spend sleeping.

- <u>number of times each philosopher must eat</u> (optional argument) : if all philosophers have eaten at least *number_of_times_each_philosopher_must_eat* times, the simulation stop. If no specified, the simulation stops when a philosopher dies.

# **Ressources**

- Threads & mutex : https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/
