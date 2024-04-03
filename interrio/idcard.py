
def mod(S1):
    mod = S1%11
    return mod

def check(Y1):
    
    checklist = [1, 0, 'X', 9, 8, 7, 6, 5, 4, 3, 2]
    return checklist[Y1]

def getY(Alist1):
    A = [int(Alist1[i]) for i in range(len(Alist))]
    W = [1,2,4,8,5,10,9,7,3,6,1,2,4,8,5,10,9,7]
    W.reverse()
    S = 0
    for i in range(0, 17):
        S = S + A[i] * W[i]
    
    Y1 = mod(S)
    return Y1


ID = input("Please input ID number: ")
Alist = list(ID)
Y = getY(Alist) 
lastnum = check(Y)
if len(Alist) == 17:
    ID = ID + str(lastnum)
    print("Complete ID number: ", ID)

if len(Alist) == 18:
    if Alist[17] == str(lastnum):
        print("The ID number is valid")
    else:
        print("The ID number is invalid")
                 


