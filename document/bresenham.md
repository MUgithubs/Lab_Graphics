# How to get all the octants of Bresenham's Algorithm

As we know, a Bresenham's Algorithm must work for 8 octants together. 

Starts from 12 o' clock, I named the first
octant as 1, then 2; the 3'o clock's as 3, 4, until 8.

Obviously, Case 2 and Case 1 is the basis of all the cases. Case 2 could generate 3, 7, 6 and Case 1 will do the rest.

Case 2's code is the most discussed in website, but the rest parts are hard to find in Internet. So I wrote this tutorial.

## First 4 based on Case 2

* case 2 - Beautiful, right?:

```pseudocode
Oct_2(x1, x2, y1, y2){
    dx = x2 - x1
    dy = y2 - y1
    e = 0 //e is error
    i = x1
    j = y1

    // "access condition"
    if 0 < dy < dx: // 0 < m < 1
    for i = x1 to x2:
        plot(i, j)
        e = e + dy
        if 2*e > dx:
            e = e - dx
            j = j + 1
}
```

* case 3:
  * `dy -> -dy`
  * `j = j + 1 -> -1`
  * Change "access condition"

    Think about it: Why?

Case 2 -> 3 represent a kind of transformation: Along the x-axis. That is, change the dy's sign, and don't touch the error-acceleration system, then change the step of y.

* case 6:
  * Simply call o2 again, but swift the begining point and the end point.

* case 7:
  * Simply call o3 again, but swift the begining point and the end point.

Case 2 -> 6, 7 are elegant.

## Rest 4 based on Case 1

O1 is the most amazing one: Because it's just change any x1 <-> y1,x2 <-> y2, but keep plot(x,y) unchanged. That's all!


Charles H
Feb, 22, 2019 1:41 A.M. in MC325

