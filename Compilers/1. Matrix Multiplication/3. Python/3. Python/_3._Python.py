#!/usr/bin/python2
# -*- coding: UTF-8 -*-

import time

startTime = 0
#endTime = 0
#useTime = 0
firstMatrixM = 0
firstMatrixN = 0
secondMatrixM = 0
secondMatrixN = 0
firstMatrix = []
secondMatrix = []
resultMatrix = []

def Init():
    global firstMatrixM
    global firstMatrixN
    global secondMatrixM
    global secondMatrixN
    global firstMatrix
    global secondMatrix

    tempInput = ""
    print("Please input M and N of the first matrix.")
    tempInput = input()
    firstMatrixM = int(tempInput.split()[0])
    firstMatrixN = int(tempInput.split()[1])
    print("Please input M and N of the second matrix.")
    tempInput = input()
    secondMatrixM = int(tempInput.split()[0])
    secondMatrixN = int(tempInput.split()[1])

    temp0 = 0
    print("Please input the first matrix. End with a blank Line.")
    while temp0 < firstMatrixM:
        tempInput = input()
        tempLine = [int(x) for x in tempInput.split()]
        firstMatrix.append(tempLine)
        temp0 = temp0 + 1
    tempInput = input()

    temp0 = 0
    print("Please input the second matrix. End with a blank Line.")
    while temp0 < secondMatrixM:
        tempInput = input()
        tempLine = [int(x) for x in tempInput.split()]
        secondMatrix.append(tempLine)
        temp0 = temp0 + 1
    tempInput = input()

def Calc():
    temp0 = 0
    while temp0 < firstMatrixM:
        tempLine = []
        temp1 = 0
        while temp1 < secondMatrixN:
            temp2 = 0
            temp3 = 0
            while temp2 < firstMatrixN:
                temp3 = temp3 + firstMatrix[temp0][temp2] * secondMatrix[temp2][temp1]
                temp2 = temp2 + 1
            tempLine.append(temp3)
            temp1 = temp1 + 1
        resultMatrix.append(tempLine)
        temp0 = temp0 + 1

def Output():
    temp0 = 0

    print("The result matrix after multiplication is:")
    while temp0 < firstMatrixM:
        temp1 = 0
        while temp1 < secondMatrixN:
            print(resultMatrix[temp0][temp1], end = "")
            if temp1 == secondMatrixN - 1:
                print("")
            else:
                print(" ", end = "")
            temp1 = temp1 + 1
        temp0 = temp0 + 1

Init()
startTime = time.clock()
Calc()
Output()
print("Calculation used %d ms." %((time.clock() - startTime)*1000))