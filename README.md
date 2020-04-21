# Simple-Relational-Data-Model
Simple relational data models with CRUD operations and supported features for interactions among relations (querying/joining). Sample data was taken from the book ["The Foundations of Computer Science"](http://infolab.stanford.edu/~ullman/focs.html)

## Relation Schema
#### 1. Table A
```
StudentId | Name | Address | Phone
```
#### 2. Table B
```
Course | Prerequisite
```
#### 3. Table C
```
Course | Day | Hour
```
#### 4. Table D
```
Course | Room
```
#### 5. Table CSG
```
Course | StudentId | Grade
```

## Operations
#### 1. Insert, Lookup, Delete Data (Part 1)
- Supported for table A, B, C, D, and CSG
#### 2. Retrieve Data (Part 2)
- Question 1: What grade did [StudentName] get in [CourseName]? (Sample Input: C.Brown / CS101)
- Question 2: Where is [StudentName] at [Time] on [Day]? (Sample Input: C. Brown / M / 9AM)
#### 3. Selection, Projection, Join Relations (Part 3)
- Joining table C and D (table CD) 
- Data structures QueryCSG and QueryCD for querying data from joined table CD and table CSG
#### 4. Check for memory leak
- Tool: [Valgrind](https://valgrind.org/) for detection and debugging

## Running Instructions
#### 1. Install [Make](https://www.gnu.org/software/make/) and [Valgrind](https://valgrind.org/)
#### 2. Part 1 (Insert, Lookup, Delete operations)
```
$ make part1
$ ./part1
```
#### 3. Part 2 (Retrieve Data)
```
$ make part2
$ ./part2
```
#### 4. Part 3 (Selection, Projection, Join Relations)
```
$ make part 3
$ ./part3
```

## Contributors
1. [Hoang Le](https://github.com/Soos99)
2. [Loc Bui](https://github.com/hekl0)
