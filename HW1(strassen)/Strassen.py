import numpy as np
import time
import matplotlib.pyplot as plt
import math
from random import *

def genMatrix(n):
    newMarix = []
    for i in range(0,n):
        dataline = []
        for j in range(0,n):
            dataline.append(randint(0,10))

        for j in range(0, n):
            Vals = list(map(float, dataline))

        newMarix.append(Vals)
    return newMarix

def partitionMatrix(matrix):
    length = len(matrix)
    if(length % 2 is not 0):
        stack = []
        for x in range(length + 1):
            stack.append(float(0))
        length += 1
        matrix = np.insert(matrix, len(matrix), values=0, axis=1)
        matrix = np.vstack([matrix, stack])
    d = (length // 2)
    matrix = matrix.reshape(length, length)
    completedPartition = [matrix[:d, :d], matrix[d:, :d], matrix[:d, d:], matrix[d:, d:]]
    return completedPartition

def strassen(mA, mB,aN):
    n1 = len(mA)
    n2 = len(mB)
    # global aN
    if(n1 and n2 <= aN):
        return (mA * mB)
    else:
        print(mA)
        A = partitionMatrix(mA)
        B = partitionMatrix(mB)
        mc = np.matrix([0 for i in range(len(mA))]for j in range(len(mB)))
        C = partitionMatrix(mc)

        a11 = np.array(A[0])
        a12 = np.array(A[2])
        a21 = np.array(A[1])
        a22 = np.array(A[3])

        b11 = np.array(B[0])
        b12 = np.array(B[2])
        b21 = np.array(B[1])
        b22 = np.array(B[3])

        mone = np.array(strassen((a11 + a22), (b11 + b22)))
        mtwo = np.array(strassen((a21 + a22), b11))
        mthree = np.array(strassen(a11, (b12 - b22)))
        mfour = np.array(strassen(a22, (b21 - b11)))
        mfive = np.array(strassen((a11 + a12), b22))
        msix = np.array(strassen((a21 - a11), (b11 + b12)))
        mseven = np.array(strassen((a12 - a22), (b21 + b22)))

        C[0] = np.array((mone + mfour - mfive + mseven))
        C[2] = np.array((mthree + mfive))
        C[1] = np.array((mtwo + mfour))
        C[3] = np.array((mone - mtwo + mthree + msix))

        return np.array(C)

#단순행렬곱
def matrixMul(mA, mB):
    resMatirx = []
    A = np.array(mA)
    B = np.array(mB)
    n = len(A)

    for i in range(0,n):
        dataline = []
        for j in range(0,n):
            sum = 0
            for k in range(0,n):
                sum += A[i][k]*B[k][j]
            dataline.append(sum)
        resMatirx.append(dataline)

    return resMatirx

#strassen 시간측정
def strassenTimeFunction(N):
    aN = bN = N

    matrixA = genMatrix(aN)
    matrixB = genMatrix(bN)
    matrixA = np.matrix(matrixA)
    matrixB = np.matrix(matrixB)

    startStrassen = time.time()
    matrixC = [[0 for i in range(len(matrixA))] for j in range(len(matrixA))]
    matrixC = strassen(matrixA, matrixB,N)
    endStrassen = time.time()
    strassenTime = endStrassen - startStrassen

    return strassenTime

#단순곱 시간측정
def mulTimeFunction(N):
    aN = bN = N

    matrixA = genMatrix(aN)
    matrixB = genMatrix(bN)
    matrixA = np.matrix(matrixA)
    matrixB = np.matrix(matrixB)

    startMul = time.time()
    matrixD = matrixMul(matrixA, matrixB)
    endMul = time.time()
    mulTime = endMul - startMul

    return mulTime


# Time Check Code
# N = int(input('N = '))
# N = pow(2, N)
# strassenTime = strassenTimeFunction(N)
# mulTime = mulTimeFunction(N)
# print("strassen time = %lf" %strassenTime)
# print("mul time = %lf" %mulTime)

#TEST CODE
def cubic(x):
    x = pow(2,x)
    return 2*pow(x,3)-pow(x,2)
def exp281(x):
    x = pow(2, x)
    return 7*pow(x,math.log2(7))-6*pow(x,2)

def test():
    i= 0
    while(True):
        i += 1
        x = cubic(i)
        y = exp281(i)
        if x>=y:
            break;
    return i

x1 = np.arange(8.0, 11.0, 0.2)
x2 = np.arange(8.0, 11.0, 0.2)
plt.plot(x1,cubic(x1),label="cubic")
plt.plot(x2,exp281(x2), linestyle="--", label="exp2.81")
plt.grid()
plt.show()

print("thresholds = %d" %test())