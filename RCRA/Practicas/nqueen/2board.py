
# NQUEEN 2 BOARD
# RCRA - UDC - 03-02-17
# Miguel Mosuera
# miguel.mosuera.perez@udc.es
# github.com/unrealmitch

import sys
import subprocess
import time
import math
import os
def main():
	if len(sys.argv) < 2:
		print("Error: How many queens? [Missing arg1: command n_queens file_output]")
		sys.exit(0)
	else:
		fout = "output"

		print("#Generating Clasp File of NQUEEN...")
		bashCommand = "./nqueen.py " + sys.argv[1] + " temp.cnf"
		output = subprocess.check_output(['bash','-c', bashCommand])

		print("#Runing CLASP...")

		if int(sys.argv[1]) > 13:
			print("		...better go for a cofee!")

		if os.path.isfile(fout):
			os.remove(fout)

		bashCommand = "/usr/bin/clasp 0 temp.cnf > " + fout
		#subprocess.Popen(['bash','-c', bashCommand])
		os.popen(bashCommand)

		clasp = open(fout, 'r').read()
		pointer = int(clasp.find("v ", 1)) 
		ans=1

		#print(clasp)

		print("\n")
		while (pointer != -1):
			clasp2 = clasp[clasp.find("v ", pointer)+2:clasp.find(" 0",pointer)]
			clasp2 = clasp2.replace("v", "")
			clasp2 = clasp2.replace("s", "")
			clasp2 = clasp2.replace("\nc", "")

			atoms = []
			atoms = clasp2.split(" ")
			#print(atoms)
			n = int(math.sqrt(len(atoms)))
			
			board = ""
			for j in range(0,n):
				board+= "----"
			board += "-\n"

			for i in range(0,n):
				for j in range(0,n):
					if int(atoms[i*n+j]) > 0: 
						board += "| Q " 
					else: 
						board += "|   "

				board += "|\n-"
				for j in range(0,n):
					board+= "----"
				board += "\n"

			print("Solution: " + str(ans))
			print(board)
			
			print("")

			ans+=1
			pointer = clasp.find("Answer", pointer+1) 




if __name__ == "__main__":
	main()