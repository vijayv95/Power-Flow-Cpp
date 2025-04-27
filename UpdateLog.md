# Update documentation
This flie is used to see details of the tasks completed. The latest task will be in [README.md](/README.md)

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

