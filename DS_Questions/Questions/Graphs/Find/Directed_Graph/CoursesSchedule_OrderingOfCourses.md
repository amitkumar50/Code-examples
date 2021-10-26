**[Course Schedule II](#p)**
- [Approach-1, Directed Cyclic Graph](#a1)

<a name=p></a>
## [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
- There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
- You are given an array prerequisites where `prerequisites[i] = [a, b]` indicates that you must take course b first if you want to take course a.
- Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.
```c
Example-1
Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
//0 is prerequisite of 1,2.
//1,2 are prerequisites of 3
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

Example-2
Input: numCourses = 1, prerequisites = []
Output: [0]
```

### Approach-1, Directed Cyclic Graph
- We can represent course relationships with directed, cyclic graph, where 
  - Each course would represent a vertex in the graph
  - Edges are modeled after the prerequisite relationship between courses. For pair `[a, b]` means the course b is a prerequisite for the course a. `b ➔ a`.
```c
[[1,0],[2,0],[3,1],[3,2]]

  0 ------> 1 -----> 3
  |                  /\
  --------> 2 -------|
```