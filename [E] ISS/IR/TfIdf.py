# Tf-Idf v0.2
# Intelligent Information System
# Miguel Mosquera Pérez
# unrealmitch@gmail.com


import math
import re
from operator import itemgetter
from collections import OrderedDict
from collections import Counter

class TfIdf:

  def __init__(self, corpus_filename = None, stopword_filename = None,
               DEFAULT_IDF = 1.5):

    """Initialize the idf dictionary.

       If a corpus file is supplied, reads the idf dictionary from it, in the
       format of:
        HEAD [# of total documents]
        term: # of documents containing the term #IDF

       If a stopword file is specified, reads the stopword list from it, in
       the format of one stopword per line.

       The DEFAULT_IDF value is returned when a query term is not found in the
       idf corpus.
    """

    self.num_docs = 0
    self.term_num_docs = {}     # term : num_docs_containing_term
    self.stopwords = []
    self.idf_default = DEFAULT_IDF

    if corpus_filename:
      corpus_file = open(corpus_filename, "r")

      line = corpus_file.readline()
      self.num_docs = len(line.strip())

      # Reads "term:frequency" from each subsequent line in the file.
      for line in corpus_file:
       tokens = line.split(":")
       term = tokens[0].strip()
       frequency = int(tokens[1].strip())
       self.term_num_docs[term] = frequency

    if stopword_filename:
      stopword_file = open(stopword_filename, "r")
      self.stopwords = [line.strip() for line in stopword_file]

  def get_tokens(self, str):
    #Tokenizedr and normalizer.

    return re.findall(r"<a.*?/a>|<[^\>]*>|[\w'@#]+", str.lower())

  def add_input_document(self, input):
    #Add terms in the specified document to the idf dictionary.

    self.num_docs += 1
    words = set(self.get_tokens(input))
    for word in words:
      if word in self.term_num_docs:
        self.term_num_docs[word] += 1
      else:
        self.term_num_docs[word] = 1

  def save_corpus_to_file(self, idf_filename, stopword_filename,
                          STOPWORD_PERCENTAGE_THRESHOLD = 0.01):
    #Save the idf dictionary and stopword list to the specified file.

    output_file = open(idf_filename, "w")

    sorted_term_num_docs = OrderedDict(sorted(self.term_num_docs.items(), key=itemgetter(1), reverse =True))

    sorted_terms = sorted(self.term_num_docs.items(), key=itemgetter(1),
                          reverse=True)

    output_file.write(str("Term [T: " + str(self.num_docs) + "]").ljust(25, " ") +
                      "T in Docs  " + "IDF" "\n\n")

    for term, num_docs  in sorted_term_num_docs.items():
      output_file.write(  term.ljust(25, " ") +
                          str(num_docs).ljust(11, " ") +
                          str(self.get_idf(term)) + "\n")

    stopword_file = open(stopword_filename, "w")
    for term, num_docs in sorted_terms:
      if num_docs < STOPWORD_PERCENTAGE_THRESHOLD * self.num_docs:
        break

      stopword_file.write(term + "\n")

  def get_num_docs(self):
    return self.num_docs

  def get_idf(self, term):
    if term in self.stopwords:
      return 0

    if not term in self.term_num_docs:
      return self.idf_default

    return math.log(float(1 + self.get_num_docs()) /
      (1 + self.term_num_docs[term]))

  def get_tfipc(self, doc, query):
    words = set(self.get_tokens(query))
    sum = 0.0

    words2 = doc.split()
    wordCount = Counter(words2)

    for word in words:
      #sum += float (doc.count(word)) * self.get_idf(word)
      sum += float(wordCount[word]) * self.get_idf(word)

    return sum

  def get_doc_keywords(self, curr_doc):
    tfidf = {}
    tokens = self.get_tokens(curr_doc)
    tokens_set = set(tokens)
    for word in tokens_set:
      mytf = float(tokens.count(word)) / len(tokens_set)
      myidf = self.get_idf(word)
      tfidf[word] = mytf * myidf

    return sorted(tfidf.items(), key=itemgetter(1), reverse=True)
