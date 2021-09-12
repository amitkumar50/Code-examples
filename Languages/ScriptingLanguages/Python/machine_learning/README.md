- [Artificial Intelligence, Machine Learning, Deep Learning](#vs)
- **Tensorflow**
  - [Tensor](#t)
  - [Code](#c1)
- **Opencv**
  - [How it works?](#how)
  - [Source Code](#c2)

<a name=vs></a>
## Artificial Intelligence, Machine Learning, Deep Learning
```c
           |       AI                          |       ML                 |      DL 
-----------|-----------------------------------|--------------------------|-------------------------
Originated |     1950                          |       1960               |   1970
What       | Simulated Intelligence in Machines| Machine making decisions | Using Neural networks to solve complex problems
                                                 without being programmed |
Objective  | Building machines which can       | Algo which can learn thru |Neural n/w to identify patterns 
             think like humans                 | data
```

## Tensorflow
- This is ML Open source library(EXPOSING APIs) for numerical computation and large-scale ML supports CPUs & GPUs. 
- Python Front-end APIs & backend written in c++ for high performance.

<a name=t></a>
**Tensor?**
- Multi-dimensional arrays used to store numbers during computation.
- String tensors don’t exist in Numpy (or in most other libraries), because tensors are preallocated contiguous memory segments, and strings, being variable length. 

<a name=c1></a>
### Code
1. [Creating Tensors](Code)
2. [Supervised Learning using imdb Dataset](Code)

## opencv
opensource library(written in C++,python,java) for image processing, recognizance. OpenCV uses ML algorithms to search for faces within a picture. It matches thousands of small patterns and features.
```c
////Ubuntu Installation///
# sudo apt update
# sudo apt install python3-pip
# sudo apt install python3-opencv
```
<a name=how></a>
### How it works?
#### 1. Breaking task into smaller tasks=classifiers
- Task of image recognization is broken into smaller tasks called **Classifiers.** For a face, we can have 6000+ Classifiers.
- The algorithm starts at the top left of a picture and moves down across small blocks of data, looking at each block and matching, constantly asking, “Is this a face?”
  
#### 2. Breaking problem in Multiple Stages=Casades
- Cascade dictionary meaning is waterfall. In ML Cascade is breaking the problem of detecting faces into multiple stages. There canbe 30-50 cascades.
- The cascades themselves are **a bunch of XML files** that contain OpenCV data used to detect objects.

#### Haar Cascade
- Haar is a supervised learning where ascade function is trained from a lot of positive and negative images. It is then used to detect objects in other images.
- Lets take face detection as an example. Initially, the algorithm needs a lot of positive images of faces and negative images without faces to train the classifier
- Cascade classifier training requires a set of positive samples and a set of negative images. You must provide a set of positive images with regions of interest specified to be used as positive samples.

**How it works??** The algorithm has four stages:
  1. **Haar Feature Selection**
  2. **Creating  Integral Images**
  3. **Adaboost Training**: selects the best features and trains the classifiers that use them
  4. **Cascading Classifiers**

<a name=c2></a>
### Code
1. [Take a image file(abba.png), Draw rectangle around faces on the image](Code/opencv_Draw-Rectangles-around-face.md)
