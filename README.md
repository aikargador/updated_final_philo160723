# philo_phinal

5 800 200 200
10 10000 200 200 1
2 10000 200 200 1
1 800 200 200
5 800 200 200
4 410 200 200
4 310 200 200
4 310 200 100
4 1000 500 600
3 1000 500 600
5 200 100 60
4 500 400 300
3 700 200 200
3 610 200 200
2 700 200 200


valgrind --leak-check=full --show-leak-kinds=all ./philo 3 310 100 100 4




valgrind --leak-check=full --show-leak-kinds=all ./philo 3 310 100 100 3



valgrind --tool=helgrind ./philo 3 310 100 100 3