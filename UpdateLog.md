# Update documentation
This flie is used to see details of the tasks completed. The latest task will be in [README.md](/README.md)

## 21-04-2025

### Verify if the Ybus martices are correct.
- Used a textbook example detailed in [YbusTest.txt](/YbusTest.txt) to find the Y bus matrix.  
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


> Results are as expected. The Algorithm for gaussian elimination is **verified.**

