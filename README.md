# Power-Flow-Cpp
This is a repository that I use to study C++.

The aim is to create a piece of software to calculate the bus voltages in a power grid.

Check [UpdateLog.md](/UpdateLog.md) for details on previous tasks.

## Latest completed Task 

### Verify the equations for finding the residue.

***Bug Found:*** When the calculatd Q `bus[i].Q` exceeds the limits, The Q specified is to be replaced with the limit and the bus should be treated as load bus. I replaced the calculated Q rather than the specified Q. following changes are made to rectify this mistake.   
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

## Task in progress
- Use textbook example to verify Jacobian matrix formation.

## Next task
- Verify convergence
- Write code to output to a file in the standard format.