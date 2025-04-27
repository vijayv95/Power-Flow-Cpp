# Power-Flow-Cpp
This is a repository that I use to study C++.

The aim is to create a piece of software to calculate the bus voltages in a power grid.

Check [UpdateLog.md](/UpdateLog.md) for details on previous tasks.

## Latest completed Task 

### Use textbook example to verify Jacobian matrix formation.

#### Test Case 1
Used textbook example detailed in [JacobianTest1.txt](/Data/JacobianTest1.txt).

Expected output:  

```
| 2.846 -1.666   8.975   -5.0 |
|-1.666  6.366  -5.0     20.9 |
| 8.525   -5.0  -2.991  1.666 |
| -5.0   19.1   1.666  -6.966 |
```

Recieved output:  

```
| 4.166 -1.666  -5.0     5.0 |
|-1.666  13.33   5.0     0.0 |
| 5.0   -40.0   1.666    0.0 |
| 2.0    0.0     0.0     0.0 |
```

Summary of changes made:
- second itterator `j` for the `GtempVector` loop used to begin at `1`, now changed to `0`.
- array index used for Jacobian matrix calculation was wrong. Used to be `GtempVector[i]`. Now `GtempVector[i-1]`

With these changes the output is now the expected output.  

Output after changes:

```
| 2.8467  -1.6667   8.9750  -5.0000  |
|-1.6667   6.3667  -5.0000   20.9000 |
| 8.5250  -5.0000  -2.9917   1.6667  |
|-5.0000   19.1000  1.6667  -6.9667  |
```

#### Test case 2

Used textbook example detailed in [JacobianTest2.txt](/Data/JacobianTest2.txt).

Expected output:  

```
| 4.0667 -2.5   12.8   -7.5  |
|-2.5     7.2  -7.5     23.4 |
| 12.08  -7.5  -4.2667  2.5  |
|-7.5     21.5  2.5    -7.8  |
```

Recieved output:  

```
| 4.0667 -2.5    12.8   -7.5  |
|-2.5     7.2   -7.5     23.4 |
| 12.4   -7.5   -4.2667  2.5  |
|-7.5     21.82  2.5    -7.8  |
```

#### Test case 3

Used textbook example detailed in [JacobianTest3.txt](/Data/JacobianTest3.txt).

Expected output:  

```
| 5.7036    -1.47    -1.47    24.2256  -5.88    -5.88  |
|-1.47       8.2712  -5.88   -5.88      33.56   -23.53 |
|-1.47      -5.88     7.35   -5.88     -23.53    29.41 |
| 22.63     -5.88    -5.88   -6.056     1.47     1.47  |
|-5.88       32.95   -23.53   1.47     -8.4      5.88  |
|-5.88      -23.53    29.33   1.47      5.88    -7.35  |
```

Recieved output:  

```
| 5.7059  -1.4706  -1.4706    24.2353  -5.8824  -5.8824  |
|-1.4706   8.2745  -5.8824   -5.8824    33.5686 -23.5294 |
|-1.4706  -5.8824   7.3529   -5.8824   -23.5294  29.4118 |
| 23.0035 -5.8824  -5.8824   -6.0588    1.4706   1.4706  |
|-5.8824   33.2380 -23.5294   1.4706   -8.3922   5.8824  |
|-5.8824  -23.5294  29.4918   1.4706    5.8824   -7.3529 |
```

Jacobian matrix formation is ***Verified***

## Task in progress
- Use textbook example to verify Residual matrix formation.

## Next task
- Verify convergence
- Write code to output to a file in the standard format.