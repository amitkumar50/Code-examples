**Diameter of Binary Tree**
- [Approach-1, DFS. O(n)](#a1)
  - [CPP](#c)
  - [Java](#j)
  - [Python](#p)

### [Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)
- **Diameter?**	Number of nodes on longest path between 2 nodes of Tree
```c
 	      1
       / 
      2
     / \
    4   5
   / 	  \
  8  	   10
Diameter=4, between 8 & 10 only edges are calculated 8,4,2,5,10 -> 4
```
 
 <a name=a1></a>
 ### Depth 1st Search. O(n)
 #### Logic
 - _1._ Traverse to every node of tree, Find leftHeight, rightHeight of that node.
 - _2._ Diameter of that node = (leftHeight + rightHeight)
 - _3._ Return max(leftHeight, rightHeight) + 1 from child node to parent, so that parent can find it's own diameter
 - _4._ keep variable to track maximum diameter. on every node, check whether `diameter of node > maxDiameter`.
 #### Complexity
 - **Time:** O(n). Traverse every node once
 - **Space:** O(n). implicit call stack during DFS. if balanced tree = O(logn)
 #### Code
 <a name=c></a>
 **CPP**
 ```cpp
#include<iostream>
#include<algorithm>

struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}};
TreeNode* Create() {
  TreeNode* p4 = new TreeNode(4);
  TreeNode* p5 = new TreeNode(5);
  TreeNode* p3 = new TreeNode(3);
  TreeNode* p2 = new TreeNode(2, p4, p5);
  TreeNode* p1 = new TreeNode(1, p2, p3);
  return p1;
}

class Solution {
    // Variable to store maximum Diameter of any node in tree
    int maxDiameter;
public:
    int diameter (TreeNode* root) {
        if (!root)
            return 0;
        int leftHeight = 0, rightHeight = 0;
        
        // Traverse to deepest left, right nodes
        if (root->left)
            leftHeight += diameter(root->left);
        if (root->right)
            rightHeight += diameter(root->right);
            
        // Diameter of present node = leftHeight+rightHeight
        // keep node of maximum diameter of tree as in when encountered
        maxDiameter = max(maxDiameter, leftHeight+rightHeight);
        
        return max(leftHeight, rightHeight)+1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        maxDiameter = 0;
        if (!root)
            return 0;
        int a = diameter(root);       //ignore
        return maxDiameter;
    }
};

int main(){
  TreeNode* pRoot = Create();
  printf("Tree Created\n");
  Solution s;
  printf("Diameter=%d\n",s.diameterOfBinaryTree(pRoot));
}
```
<a name=j></a>
#### Java
```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    private int maxDiameter;
    public int diameter(TreeNode root){
        if (root == null)
            return 0;
        int lh = 0, rh = 0;
        if (root.left != null)
            lh += diameter(root.left);
        if (root.right != null)
            rh += diameter(root.right);
        maxDiameter = Math.max(maxDiameter, lh+rh);
        return Math.max(lh, rh) + 1;
    }
    public int diameterOfBinaryTree(TreeNode root) {
        maxDiameter = 0;
        diameter (root);
        return maxDiameter;
    }
}
```
<a name=p></a>
#### Python
```py
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        maxDiameter = 0

        def diameter (root: Optional[TreeNode]) -> int:
            if (root == None):
                return 0
            nonlocal maxDiameter
            lh = 0
            rh = 0
            if (root.left != None):
                lh = lh + diameter (root.left)
            if (root.right != None):
                rh = rh + diameter (root.right)
            maxDiameter = max(maxDiameter, lh+rh)
            return max(lh, rh) + 1

        diameter(root)
        return maxDiameter
```