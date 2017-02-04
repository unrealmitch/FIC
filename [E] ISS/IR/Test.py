# Tf-Idf Test
# Intelligent Information System
# Miguel Mosquera Pérez
# unrealmitch@gmail.com


import TfIdf
import os
from collections import OrderedDict
from operator import itemgetter

DEFAULT_IDF_UNITTEST = 1.0

def main():
    my_tfidf = TfIdf.TfIdf("tfidf_corpus.txt", DEFAULT_IDF=DEFAULT_IDF_UNITTEST)

    files = os.listdir("txt")
    n_files = len(files) - 150

    print("initializing information retrieval!\n")

    for i in range(n_files):
        print("Proccesing[" + str(int (i* 100/n_files) ) + "%]: (" + str(i) + ") " + files[i])
        file_act = open(".\\txt\\" + files[i], "r")
        string_act = ""
        for line in file_act.readlines():
            string_act += line

        my_tfidf.add_input_document(string_act)

    print("Process Finish!")
    my_tfidf.save_corpus_to_file("out_tfidf.txt", "out_stopword.txt")

    print("Starting Query Input!")

    while True:

        '''
        n = int(input("Choose nº document [Number of document]:"))
        if n >= 0 and n<n_files:
            print("File choosed: " + str(files[n]))
            file_act = open(".\\txt\\" + files[n], "r")
            string_act = ""
            for line in file_act.readlines():
                string_act += line

            q = input("Choose you query:")
            print(str(my_tfidf.get_tfipc(string_act,q)))
        '''
        q = input("Choose you query (#q to exit):")
        if q == "#q":
            break

        dic_tfipf = {}

        for i in range(n_files):
            print("Proccesing query[" + str(int(i * 100 / n_files)) + "%]: (" + str(i) + ") " + files[i])
            file_act = open(".\\txt\\" + files[i], "r")
            string_act = ""
            for line in file_act.readlines():
                string_act += line
            dic_tfipf[files[i]] = my_tfidf.get_tfipc(string_act,q)
            print(dic_tfipf[files[i]])

        sorted_dic_tfipf = OrderedDict(sorted(dic_tfipf.items(), key=itemgetter(1), reverse=True))

        print("\nSorted list of files with TF-IDF:\n")

        for file, tfipf_value in sorted_dic_tfipf.items():
            print("#" + str(tfipf_value) + " :->: " + file)

main()