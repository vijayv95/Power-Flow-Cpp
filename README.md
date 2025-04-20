# Power-Flow-Cpp
This is a repository that I use to study C++.

The aim is to create a piece of software to calculate the bus voltages in a power grid.

## Major issue
**Non convergence** 

## Latest completed Task
- Verify the gaussian elimination algorithm using example matrices.

| Test case  | Input  | Output  |
| ---------- | ------ | ------- |
| 1 | `2 3 : 6` <br> `1 -1 : 0.5` | `1.5 1` |
| 2 | `1 2 1 : 1` <br> `3 5 1 : 3` <br> `2 6 7 : 1` | `-2 2 1` |
| 3 | `1 2 -1  1 : 6` <br> `-1 1 2 -1 : 3` <br> `2 -1 2 2 : 14` <br> `1 1 -1 2 : 8` | `1 2 3 4` |

Results are as expected. The Algorithm for gaussian elimination is **verified.**

## Task in progress
- Verify if the Ybus martices are correct.
    - Optional: reduce space complexity by defining the size of the vector instead of continously using `push_back()`

## Next task
- Verify the equations for finding the residue.