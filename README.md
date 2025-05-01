# Power-Flow-Cpp
This is a repository that I use to study C++.

The aim is to create a piece of software to calculate the bus voltages in a power grid.

Check [UpdateLog.md](/UpdateLog.md) for details on previous tasks.

## Latest completed Task 

> ***Bug Fix:*** changed `bus[i].deltaf = var[size + i-1];` to `bus[i].deltaf = var[size + i-2];`

## Task in progress

- Write code to normalize Jacobian matrix before Gaussian elimination

## Next task
- Verify convergence
- Write code to output to a file in the standard format.