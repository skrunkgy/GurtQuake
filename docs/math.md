# MATH

I know, very scary. But most of the math we use in GurtQuake graphics are linear algebra principles. We will go over
- [Vectors](##Vectors)
- [Matrices](##Matrices)
- [Transforms](##Transforms)
- [C++ Features](##Features)

## Vectors

Vectors are simply ordered elements of n size (or dimension). The most common sizes are 2, 3 and 4. These are used to store some important properties, for example:
- 2D UV coordinates
- 3D spaces
- 4D rows of matrices

We can access these 3 types of vectors by their axis name or their index. For their axis names, they go by
x, y, z, w
r, g, b, a
s, t, u, v

A vector of size 3 will only be able to access the first 3 axis names, understandably.

### Operations

We can perform some math operations on these, such as:
scalar * vector
vector * scalar
vector + vector
vector - vector
vector / scalar

We can perform some programming stuff too, like:
vector\[index\]
vector == vector
vector != vector
vector = vector
vector = {...}
vector(...)

There are some free functions (functions that dont belong to a class):
normalize(vector)
dot(vector, vector)
cross(vec3, vec3)
length(vector)

If you haven't noticed, these list of operations do not specify a kind of vector * vector. Although TECHNICALLY it is in the OpenGL specification to allow this (simply multiply each vectors component with each other), we do not provide this as it is not in our use case. If you want to write that, I don't care, be my guest. Vector multiplication comes in two flavors: dots and crosses.

### Dot Product

The dot product between two vectors of any size produces a scalar value. The magnitude (or just simply the result) can be written as |A||B|cos(t), where A and B are the magnitudes of the vectors, and t is the angle between them. When t gets smaller, the magnitude of the dot product increases. This is helpful for comparing two vectors. The way to compute these without getting angles between vectors and magnitudes is by multiplying each component of one vector with another, and adding them. In C++, this looks like:

```cpp
float dot = 0;
for (int i = 0; i < n; i++)
{
	dot += A[i] * B[i];
}
```

### Cross Product

The cross product can only be performed between two 3D vectors, and produces an orthogonal 3D vector, meaning it makes a right angle with both of the multiplicants. The magnitude of the cross product is given as |A||B|sin(t). We usually don't care about the magnitude, as the use case of this usually involves normalized vectors (vectors whos magntitude is of 1). Think of normals on a triangle, where we can take two of the triangles sides and produce a normal for it for lighting information. This is also useful for when we get to the Transform class.


## Matrices

Matrices are like a 2 dimensional array, or a vector of vectors. They are represented as an array of vectors in our engine.

The use case of matrices is primarily for transformations. Almost any transformation (all, for what I know) can be represented as a matrix. We can apply matrices to other matrices, and matrices to vectors. These things are powerful.

Matrices have both "row" size and "column" size. In this engine, we utilize row-major order, which means rows are stored next to each other in memory. For example, a 4x4 matrix may look like this in memory:

r0c0, r0c1, r0c2, r0c3, r1c0, ...

This is because in GurtQuake, rows are reresented as vectors. It makes it more simple this way, but we will need to keep this in mind when we do certain operations.

Matrix can have math operations too, such as:
matrix * scalar
scalar * matrix
matrix * matrix
vector * matrix
matrix * vector
matrix + matrix
matrix - matrix
matrix / scalar

As well as programming:
matrix = matrix
matrix == matrix
matrix != matrix
matrix\[index\]
matrix({...})

You may have noticed that we are able to multiply matrices with each other, unlike the vector. We are also able to multiply them with vectors, very strange!

### Matrix Multiplication

Matrix multiplation is where the magic happens, but under some strict conditions. Matrix multiplication can only take place when the left matrix's row size is equal to the right matrix's column size. An example of this would be:
`			  | d  e  f  g |
| a  b  c | * | h  i  j  k |
			  | l  m  n  o |`
a 1x3 and 3x4 matrix. For simplicitly, let's say the left matrix is of size AxN, and right matrix is of NxB. The resulting matrix would be of size AxB.

In terms of performing the multiplication, we go by each row in the left matrix and do a dot product of it with each column in the right matrix. We store this dot product in the resulting matrix in the number row we used on the left and number column we used on the right. There is probably an image better explaining this.

Using our example, we would get a resulting 1x4 matrix. To demonstrate, the resulting matrix would look like this:
`| (a*d + b*h + c*l)  (a*e + b*i + c*m)  (a*f + b*j + c*n)  (a*g + b*k + c*o) |`
Notice we only used one row for the left column, and each of the letters in each dot product came from their respective column from the right matrix.

This is also where we get vector and matrix multiplication. We just assume a vector of size N is a 1xN matrix if were doing vector * matrix, or a Nx1 matrix if were doing matrix * vector. The engine handles both cases.

Matrix multiplication is VERY useful for transformations. We are now ready to get into the Transform class.

## Transforms

First, we need to go over the basics of transformations with matrices. We start with a demonstration.

`
| x  y |  *  |  0  1  |
			 | -1  0  |
`
We take a 2D vector and apply this mystery matrix. When we do, our resulting vector is
`| y  -x |`
which is just our point rotated by 90 degrees around the origin counter-clockwise. Fascinating!

`
| x  y |  *  | s  0 |
			 | 0  s |`
This matrix results in
`| sx  sy |`
which is a simple scale matrix. We could have splitted the two s's and scaled each component separately.

These are all nice, but what about translation? For this, we must add a another component to our vector, and subsequently another row to our matrix:
`
			    | 1  0 |
| x  y  1 |  *  | 0  1 |
			    | 3  2 |
`
The resulting vector is
`| x+3  y+2 |`
We add the 1 so that our dot product adds only the translation part of the matrix without touching our x or y.

Now that we have the basic understandings of transformations, we can look at engine implementation.

### The Transform Class

The engine provides a Transform class, which holds three properties:
- Position (3D vector)
- Basis (3x3 matrix)

These represent basic translations responsible for position, rotation, and scale. Usually, engines interface the rotation part as either an euler angle (3D vector of angles) or a quaternion. GurtQuake does not do either because:
- Euler angles are subject to "Gimbal lock". This means that some configuration of these makes it impossible to represent others.
- Quaternions are too scary, and are really only useful for some things we do not care for at the moment.

The basis simply holds the local axis. This means that it is also a orthonormalized matrix (orthogonal and normalized, remember!). We can get a transformation matrix if we apply these three properties like this:

`
| b00 b01 b02 0 |	  | 1  0  0  0 |
| b10 b11 b12 0 |  *  | 0  1  0  0 |
| b20 b21 b22 0 |     | 0  0  1  0 |
| 0   0   0   1 |     | px py pz 1 |
`

The engine provides a `Transform::get_matrix()` method to provide the resulting matrix. This matrix can be applied to any vector4D (or a position vector with a 1 as the w component) and it will transform the point from local space to world space. Later, you will see that this will be our "model" matrix.


## Summary

This sums up math stuff, and we are ready to go over [graphics](./graphics.md).
