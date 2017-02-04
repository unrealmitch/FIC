import random

# PageRank v0.1
# Intelligent Information System
# Miguel Mosquera Pérez
# unrealmitch@gmail.com

PARM_ALPHA = 0.1
PARM_TESTS = 10000

num_pages = 3
Matrix = [[0, 1, 1], [0, 0, 1], [0, 0, 0]]


def have_links(page,matrix):
    pages_linked = []
    for i in range(num_pages):
        if matrix[page][i] == 1:
            pages_linked.append(i)
    return pages_linked

def main(matrix):
    actual_page = random.randint(0,num_pages-1)
    succession_page = []
    appears = [0,0,0]

    for i in range(PARM_TESTS):
        succession_page.append(actual_page)
        appears[actual_page] = int(appears[actual_page]) + 1

        pages_linked = have_links(actual_page, matrix)
        if len(pages_linked) != 0:
            if random.random() <= 1-PARM_ALPHA:
                actual_page = random.choice(pages_linked)
                #actual_page = pages_linked[random.randint(0,len(pages_linked)-1)]
                continue

        actual_page = random.randint(0,num_pages-1)

    for i in range(num_pages):
        print("S" + str(i) + ": " + str(appears[i]) + " - " + str(str(appears[i]/ PARM_TESTS) ) + "%")

main(Matrix)