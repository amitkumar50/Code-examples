- **ML Learning Types**
  - [1. Supervised Learning](#sl)
    - [a. Classification](#c)
    - [b. Regression](#r)
    - [c. Logisitic Regression](#lr)
  - [2. Unsupervised Learning](#ul)
    - [a. Clustering](#cl)
    - [b. Visualization and dimensionality reduction](#v)
    - [c. Association rule learning](#arl)
  - [3. Semisupervised learning](#ssl)
  - [4. Reinforcement learning](#rl)
- **[Modes of Learning](#mol)**
  - _1._ Batch
  - _2._ Online Mode
- **[Instance-Based, Model-based Learning](#im)**

<a name=sl></a>
## 1. Supervised Learning
- The training data feed to the algorithm includes the desired solutions, called labels.
- Supervised learning algorithms: k-Nearest Neighbors, Linear Regression, Logistic Regression, Support Vector Machines (SVMs), Decision Trees & Random Forests, Neural networks

### Types of Supervised learning
<a name=c></a>
**1a. Classification (give yes/no)**
- _a. Spam Filterning:_ Algo is trained with many example emails along with their class (spam or ham), and it must learn how to classify new emails. Each email has a label.

<a name=r></a>
**1b. Regression: (give % or numeric value)**
- _Predictors(Predict something):_
  - Predict whether based on inputs.
  - Predict price of car provided with some inputs((mileage, age, brand, etc.)

<a name=lr></a>
**1c. Logistic Regression (yes/no with %)**
- Mix of classfication & Regression.
- Example: 20% of chances being a spam.

<a name=ul></a>
## 2. Unsupervised Learning
- Dataset does not have labels. ML model tries to learn without teacher.
### Types of Unsupervised learning
<a name=cl></a>
**2a. Clustering:**
- Algorithms used: (k-Means, Hierarchical Cluster Analysis (HCA), Expectation Maximization)

<a name=v></a>
**2b. Visualization and dimensionality reduction**
- With unlabelled data this algorithm provides ouput which can be plotted on 2-D, 3-D plane.
- Algorithms used: Principal Component Analysis (PCA), Kernel PCA, Locally-Linear Embedding (LLE), t-distributed Stochastic Neighbor Embedding (t-SNE)

<a name=v></a>
**2c. Association rule learning:**
- This provides output as relations between attributes.
- Algorithms used: Apriori, Eclat
- Examples:
  - _1. Supermarket data analysis:_ suppose you own a supermarket. Sales logs may reveal that people who purchase sauce, potato chips also buy bread. Thus, you may want to place these items close to each other.

<a name=ssl></a>
## 3. Semisupervised learning
- lot of unlabeled data and a little bit of labeled data
- Algorithms: Deep belief networks (DBNs), 
- Examples:
  - _1. FB Photos:_ When we load photos, we provide labels to few and leave others. AI identifies photos.

<a name=rl></a>
### 4. Reinforcement learning
- Agent(AI Program) can observe the environment, select and perform actions, and get rewards in return

<a name=mol></a>
## Modes of Learning
### 1. Online Mode
- As data comes, data is fed.
- Examples: Stock prices
### 2. Batch Mode
Model is be trained using all the available data

 <a name=im></a>
### Instance-Based, Model-based Learning
#### Instance Based Learning
- Learning based on number of instances of particular word.
- Examples
  - _1. Spam Filtering:_ Model measures similarity between two emails (by coutning number of similar words in 2 emails).
 
#### Modelbased Learning
