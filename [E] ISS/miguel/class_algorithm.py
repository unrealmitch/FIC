import random
import operator
'''
Miguel Caballero
Page Rank Graph from Wikipedia using class algorithm
'''
#Variables
nodes = ['A', 'B', 'C', 'D', 'E', 'F', 'X1', 'X2', 'X3', 'X4', 'X5']
ady_list = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0], [0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0], [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0],
            [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0], [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0], [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0]]
nodes_count = {'A': 0, 'B': 0, 'C': 0, 'D': 0, 'E': 0, 'F': 0, 'X1': 0, 'X2': 0, 'X3': 0, 'X4': 0, 'X5': 0}
node = -1
# --------------

#Constants
PRECISION = 100
N = 11
ALPHA = 0.1
# --------------

#Functions
def are_outgoing_links(node):
    ady = []
    for x in range(0,N):
        if ady_list[node][x] == 1:
            ady.append(x)
    return ady

def round_values():
    for x in range(0,N):
        node_selected = nodes[x]
        nodes_count[node_selected] = round(nodes_count[node_selected],2)
# --------------

#Body
for x in range(0,PRECISION):
    if node == -1:
        node = random.randint(0,N-1)
    #we add to node
    node_selected = nodes[node]
    node_add = nodes_count[node_selected]
    nodes_count[node_selected] = node_add + 1/PRECISION
    ady = are_outgoing_links(node)

    #is there any outgoing link?
    if len(ady) > 0:
        #1-alpha
        if random.random()> ALPHA:
            link = random.randint(0,len(ady)-1)
            node = ady[link]
        else:
            node = -1
    else:
        node = -1

round_values()

print(sorted(nodes_count.items(), key=operator.itemgetter(1), reverse=True))
# --------------