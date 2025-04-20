# Power-Flow-Cpp
This is a repository that I use to study C++.

The aim is to create a piece of software to calculate the bus voltages in a power grid.

Check [UpdateLog.md](/UpdateLog.md) for details on previous tasks.

## Latest completed Task 

### Verify if the Ybus martices are correct.
- Used a textbook example detailed in [YbusTest.txt](/YbusTest.txt) to find the Y bus matrix.  
- Vector sizes were decleared which avoided all `push_back()` commands

> ***Bug Fix:*** added a -ve sign in the calculation for Susceptance `Matrix B`  

Both `Matrix G` and `Matrix B` are **Verified**.


## Task in progress
- Verify the equations for finding the residue.


## Next task
- Verify convergence
- Write code to output to a file in the standard format.