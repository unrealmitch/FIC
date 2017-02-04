import random

# PageRank v0.2
# Intelligent Information System
# Miguel Mosquera Pérez
# unrealmitch@gmail.com

PARM_ALPHA = 0.1
PARM_D = 0.15
PARM_TESTS = 10000


#Matrix = [[0, 1, 1], [0, 0, 1], [0, 0, 0]]

PageRank_values = [-1, -1, -1, -1, -1, -1, 1.6, 1.6, 1.6, 1.6, 1.6]

Matrix = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0], [0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0], [0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0], [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0],
        [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0], [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0], [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0]]



def have_links(page,matrix):
    num_pages = len(Matrix)

    pages_linked = []
    for i in range(num_pages):
        if matrix[page][i] == 1:
            pages_linked.append(i)
    return pages_linked

def getPageRank(matrix):
    num_pages = len(Matrix)
    actual_page = random.randint(0,num_pages-1)
    succession_page = []
    appears = [0] * num_pages

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
        print("S" + str(i) + ": " + str(appears[i]) + " - " + str(str(appears[i]*100/ PARM_TESTS) ) + "%")

# ---------------------------------------------------------------------------------------------------------#
# ---------------------------------------------------------------------------------------------------------#

def get_matrix_links(matrix, n):
    matrix_out = [[]] * (n)
    for i in range(n-1):
        for j in range (n):
            if matrix[j][i] == 1:
                matrix_out[i].append(j)

    return matrix_out

def get_page_rank_google(matrix_links, page_rank, page, n, stack):
    if page_rank[page] != -1:
        return page_rank[page]
    else:
        #if len(matrix_links[page]) == 0:
        #    return 1-PARM_D
        #else:
        sum_pr = 0
        for i in range(len(matrix_links[page])):
            if (page_rank[matrix_links[page][i]] == -1) and not (stack.__contains__(matrix_links[page][i])):
                stack.append(matrix_links[page][i])
                get_page_rank_google(matrix_links, page_rank, matrix_links[page][i],n, stack)
                sum_pr += page_rank[matrix_links[page][i]] / len(matrix_links[page])

        return  ((1-PARM_D) + PARM_D * sum_pr)

def get_page_rank2(matrix, page_rank):
    num_pages = len(matrix)
    matrix_links= get_matrix_links(matrix, num_pages)

    for i in range(num_pages):
        page_rank[i] = get_page_rank_google(matrix_links, page_rank, i, num_pages, [])
        print("S" + str(i) + ": " + str(page_rank[i]) + "%")

    return page_rank

get_page_rank2(Matrix, PageRank_values)