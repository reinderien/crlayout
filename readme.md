Problem
-------

A popular textbook with Part 2 "Designing Operations", chapter 9 "Layout
Decisions", has a homework question 9.5 that has a lot of traffic on various
tutor and homework help sites on the internet:

> **9.5** Roy Creasey [sometimes shown as Ted Post] Enterprises, a machine shop, 
> is planning to move to a new, larger location. The new building will be 60 
> feet long by 40 feet wide. Creasey envisions the building as having six 
> distinct production areas, roughly equal in size. He feels strongly about 
> safety and intends to have marked pathways throughout the building to 
> facilitate the movement of people and materials. See the following building 
> schematic.
>
> **Building Schematic (with work areas 1-6)**
>
>     1--2--3
>     |  |  |
>     4--5--6
>
> His foreman has completed a month-long study of the number of loads of 
> material that have moved from one process to another in the current building. 
> This information is contained in the following flow matrix.
>
>                Materials Welding Drills Lathes Grinders Benders
>     Materials          0     100     50      0        0      50 
>     Welding           25       0      0     50        0       0 
>     Drills            25       0      0      0       50       0 
>     Lathes             0      25      0      0       20       0 
>     Grinders          50       0    100      0        0       0 
>     Benders           10       0     20      0        0       0
>
> Finally, Creasey has developed the following matrix to indicate distances 
> between the work areas shown in the building schematic.
>
> **Distance Between Work Areas**
>
>     20 40 20 40 60
>        20 40 20 40
>           60 40 20
>              20 40
>                 20
>
> What is the appropriate layout of the new building?

Analysis
--------

This is a discrete optimization problem. Given that there are only 6! = 720
permutations of the process placement this is trivially solvable by brute force:

- Fill out the lower triangle of the `distances` matrix such that it's
  symmetrical
- Represent the design as an array of six integers, where each index is an
  area and each value is a process
- Generate all permutations of that array
- For each area-area source-destination pair, calculate the sum of the product 
  of the distance and the flow. This total is the cost.
- Find the minimum cost.
- Print all solutions that have the minimum cost.

Solution
--------

As it turns out, the four optimal solutions are all reflections of a single
solution about one or both axes.

The output is:

```
Number of processes to locate: 6
The smallest total rate-distance product cost found is 13000
The best area arrangements at this cost are:

        1         2         3 
   Lathes  Grinders    Drills 
        4         5         6 
  Welding Materials   Benders 

        1         2         3 
   Drills  Grinders    Lathes 
        4         5         6 
  Benders Materials   Welding 

        1         2         3 
  Welding Materials   Benders 
        4         5         6 
   Lathes  Grinders    Drills 

        1         2         3 
  Benders Materials   Welding 
        4         5         6 
   Drills  Grinders    Lathes 
```
