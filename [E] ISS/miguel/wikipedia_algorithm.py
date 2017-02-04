import sys

'''
Miguel Caballero
Page Rank Graph from Wikipedia using wikipedia algorithm
'''
#Constant d
D = 0.85
N = 11
# --------------

#Variables
_ady_list = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
             [0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
             [0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
             [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
             [0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0],
             [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0],
             [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0],
             [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0],
             [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0],
             [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
             [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0]]
_page_rank_value = [D,D,D,D,D,D,D,D,D,D,D]
_pages = ['A','B','C','D','E','F','X1','X2','X3','X4','X5']
_m = {0: [], 1: [], 2: [], 3: [], 4: [], 5: [], 6: [], 7: [], 8: [], 9: [], 10: []}
_c = {0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0, 8: 0, 9: 0, 10: 0}
# --------------

#Functions

#PageRank of page A (Recursive)
def pr_func(A):
    if _m[A] == False:
        return _page_rank_value[A]
    else:
        sum_PR_C = 0
        if _m[A]:
            val = _m[A].pop()
            if _c[A] > 0:
                sum_PR_C += (pr_func(val) / _c[A])
            else:
                sum_PR_C += (pr_func(val))

        return ((1-D)/N)+(D*sum_PR_C)

#Count of outgoing links from page A
def c_func(A):
    num = 0
    for x in range(0, N):
        if _ady_list[A][x] == 1:
            num += 1
    return num

#Incoming links to page A
def m_func(A):
    for x in range(0, N):
        if _ady_list[x][A] == 1:
            _m[A].append(x)

# --------------

#Body

for A in range(0, N):
    m_func(A)
    _c[A] = c_func(A)

print("Incoming links for each page A:\n", str(_m), "\nTotal outgoing links for each page A:\n", str(_c))

for A in range(0, N):
    _page_rank_value[A] = pr_func(A)

zipped = zip(_pages,_page_rank_value)#Zip for page rank output

print("Page Rank")
for i in zipped:
    print(i)

# --------------