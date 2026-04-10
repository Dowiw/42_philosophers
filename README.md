*This project has been created as part of the 42 curriculum by kmonjard*
# 42_philosophers

## Description
The project is a program that is similar to the [Dining_philosophers_problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

`philo` is program that acts as **a scenario of philosophers dining in one round table** by parsing the philosopher count, how long it takes for them to die without eating, how long it takes to eat and sleep, and an optional how many times should they eat.

Each philosopher has 2 forks on the right and left which they share with other philosophers. The first philosopher shares its left fork with the last. In order to eat, they must hold both forks. Then they can sleep, and then wait for both forks to be available.

*If there is only one philosopher, there is only one fork. If the optional argument is passed, once every philospher has eaten that amount of times, the simulation ends.*

## Instructions
To compile `./philo`, use make inside `/philo`.
```sh
cd philo
make
```

To use the program:
```sh
./philo <no. of philosophers> <death ms> <eat ms> <sleep ms> <optional: max eat count>
```

For example:
```sh
./philo 4 410 200 200
```

```sh
./philo 5 700 200 200 10
```

**Note:** During testing, setting the `<death ms>` variable more than double the `<eat ms>` value allows any even number of philosophers to live forever.

Setting it more than triple, allows any odd number of philosophers to live forever.

This is because the philosophers are eating in 2 groups for even, and 3 groups for odd.

**Other tests:**
- Large Even: `./philo 10 410 200 200`
- Stress Test: `./philo 200 800 200 200`

## Resources

[pthread_create(3)](https://man7.org/linux/man-pages/man3/pthread_create.3.html), [pthread_mutex_init(3)](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html).
As always, it is important to read the manual and learn what each posix thread function does.

The aforementioned [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) wikipedia for a grasp on the concept.

This [long medium article by Dean Ruina](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2) that details about the project, it is technically a walkthrough but was used as an idea pool.

**AI Use:** Used very often to spot problems that hit a wall while looking through the code. It acted as a peer to run to when things became difficult to comprehend.
