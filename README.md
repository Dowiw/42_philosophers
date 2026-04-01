# 42_philosophers
TODO

Few things to test:

Simple Even: ./philo 4 410 200 200
Very tight timing for 2 groups. Should never die.

Simple Odd: ./philo 5 800 200 200
Plenty of time for 3 groups.

Large Even: ./philo 10 410 200 200
Tests if your monitor_simulation can handle more threads.

Stress Test: ./philo 200 800 200 200
Tests system resource limits and mutex performance.

Even Number of Philosophers (N): They can eat in 2 groups. One philosopher only has to wait for one other "round" of eating to finish.

    Safe Condition: die_time > (eat_time×2)

Odd Number of Philosophers (N): This is harder because the circular table prevents simple 2-group synchronization. They effectively eat in 3 groups.

    Safe Condition: die_time > (eat_time×3)
