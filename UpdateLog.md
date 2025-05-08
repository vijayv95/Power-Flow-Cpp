# Update documentation
This flie is used to see details of the tasks completed. The latest task will be in [README.md](/README.md)

## 08-05-2025

### Verify Convergence  

> ***Bug Fix:*** changed `bus[i].deltaf = var[size + i-1];` to `bus[i].deltaf = var[size + i-2];`

Convergence is observed in test case 3, but not in tet case 1 and 2. The interations tend to repeat after a few itterations. 


## 01-05-2025

### Use textbook example to verify Residual matrix formation.

#### Test case 1:

Used textbook example detailed in [JacobianTest1.txt](/Data/JacobianTest1.txt).

Expected output:  

```
| 0.275 |
|-0.3   |
| 0.225 |
| 0.65  |
```

Recieved output:  

```
| 0.2750 |
|-0.3000 |
| 0.2250 |
| 0.6500 |
```

#### Test case 2:

Used textbook example detailed in [JacobianTest2.txt](/Data/JacobianTest2.txt).

Expected output:  

```
| 0.3  |
|-0.3  |
| 0.36 |
| 0.7  |
```

Recieved output:  

```
| 0.3000 |
|-0.3000 |
| 0.2000 |
| 0.5400 |
```
> ***Bug Fix:*** `sus += b.lineCharging;` is changed to `sus += -b.lineCharging/2;`

Ouptup after change

```
| 0.3000 |
|-0.3000 |
| 0.3500 |
| 0.7050 |
```

#### Test case 3:

Used textbook example detailed in [JacobianTest3.txt](/Data/JacobianTest3.txt).

Expected output:  

```
|-0.0236 |
|-0.4412 |
|-0.4    |
| 0.6956 |
| 0.1052 |
|-0.01   |
```

Recieved output:  

```
|-0.0235 |
|-0.4412 |
|-0.4000 |
| 0.6959 |
| 0.1053 |
|-0.0100 |
```
Residual Mtrix formation is ***Verified***

## 27-04-2025

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

## 22-04-2025

### Verify the equations for finding the residue.

> ***Bug Found:*** When the calculatd Q `bus[i].Q` exceeds the limits, The Q specified is to be replaced with the limit and the bus should be treated as load bus. I replaced the calculated Q rather than the specified Q.  

following changes are made to rectify this mistake.   
`bus[i].deltaQ = (bus[i].generationMVAR - bus[i].loadMVAR) - bus[i].Q;`  
is changed to:  
`bus[i].deltaQ = bus[i].minLimit - bus[i].Q;`  
or  
`bus[i].deltaQ = bus[i].maxLimit - bus[i].Q;`  
according to the conditions.


The following code is **verified** according to the textbook equations.
```
bus[i].P += (bus[i].e * (bus[j].e * G[i][j] + bus[j].f * B[i][j]) + bus[i].f * (bus[j].f * G[i][j] - bus[j].e * B[i][j]));

bus[i].Q += (bus[i].f * (bus[j].e * G[i][j] + bus[j].f * B[i][j]) - bus[i].e * (bus[j].f * G[i][j] - bus[j].e * B[i][j]));

bus[i].deltaP = (bus[i].generationMW - bus[i].loadMW) - bus[i].P;

bus[i].deltaQ = (bus[i].generationMVAR - bus[i].loadMVAR) - bus[i].Q;

bus[i].deltaV2 = bus[i].finalVoltage*bus[i].finalVoltage - (bus[i].e * bus[i].e + bus[i].f * bus[i].f);
```

## 21-04-2025

### Verify if the Ybus martices are correct.
- Used a textbook example detailed in [YbusTest.txt](/Data/YbusTest.txt) to find the Y bus matrix.  
- Vector sizes were decleared which avoided all `push_back()` commands

> ***Bug Fix:*** added a -ve sign in the calculation for Susceptance `Matrix B`  

Both `Matrix G` and `Matrix B` are **Verified**.

## 20-04-2025

### Verify the gaussian elimination algorithm using example matrices.

| Test case  | Input  | Output  |
| ---------- | ------ | ------- |
| 1 | `2 3 : 6` <br> `1 -1 : 0.5` | `1.5 1` |
| 2 | `1 2 1 : 1` <br> `3 5 1 : 3` <br> `2 6 7 : 1` | `-2 2 1` |
| 3 | `1 2 -1  1 : 6` <br> `-1 1 2 -1 : 3` <br> `2 -1 2 2 : 14` <br> `1 1 -1 2 : 8` | `1 2 3 4` |


Results are as expected. The Algorithm for gaussian elimination is **verified.**

