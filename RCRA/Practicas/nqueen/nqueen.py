#!/usr/bin/env python

# 8 Queens
# RCRA - UDC - 03-02-17
# Miguel Mosuera
# miguel.mosuera.perez@udc.es
# github.com/unrealmitch
#
# Description: 4..8..N Queens Solution for Clasp

import sys

def printboard(n):
	output = ""
	for i in range(0,n):
		for j in range(0,n):
			output += str(i*n+j+1).zfill(2) + " "
		output += "\n"

	return output		

def calcDiag(n):
	rules = []

	#Top-> Left2Right
	for i in range(0,n-1):
		for j in range(0,n-1-i):
			for k in range(j+1,n-i):
				rule = []
				rule.append(-(j*n+j+1+i))
				rule.append(-(k*n+k+1+i))
				rules.append(rule)

	#Bot-> Left2Right
	for i in range(1,n-1):
		for j in range(0,n-1-i):
			for k in range(j+1,n-i):
				rule = []
				rule.append(-(n*i+j*n+j+1))
				rule.append(-(n*i+n*k+k+1))
				rules.append(rule)

	#Top-> R2L
	for i in range(0,n-1):
		for j in range(0,n-1-i):
			for k in range(j+1,n-i):
				rule = []
				rule.append(-(j*n-j+n-i))
				rule.append(-(k*n-k+n-i))
				rules.append(rule)

	#Bot-> R2L
	for i in range(1,n-1):
		for j in range(0,n-1-i):
			for k in range(j+1,n-i):
				rule = []
				rule.append(-(i*n+n+j*n-j))
				rule.append(-(i*n+n+k*n-k))
				rules.append(rule)

	return rules

def calcCols(n):
	rules = []

	for i in range(0,n):
		rule = []

		for j in range(0,n):
			rule.append((i+j*n)+1)
		rules.append(rule);


		for j in range(0,n-1):
			for k in range(j+1,n):
				rule = []
				rule.append(-(j*n+1+i))
				rule.append(-(k*n+1+i))
				rules.append(rule)

	return rules

def calcRows(n):
	rules = []

	for i in range(0,n):
		rule = []
		s = i * n + 1 			#Start of actual row

		for j in range(0,n):
			rule.append(s+j)
		rules.append(rule);


		for j in range(0,n-1):
			for k in range(j+1,n):
				rule = []
				rule.append(-(s+j))
				rule.append(-(s+k))
				rules.append(rule)

	return rules

def list2string(input):
	output = ""

	for rule in input:
		for atom in rule:
			output += str(atom).zfill(2) + " "
			#output += str(atom).rjust(2, '0') + " "
		output += "0 \n"

	return output

def genNqueen(n):

	rows = calcRows(n)
	cols = calcCols(n)
	diag = calcDiag(n)

	n_rules = len(rows) + len(cols) + len(diag)
	n_atoms = n*n

	output = "c NQUEENS: " + str(n)  
	output += "\np cnf " + str(n_atoms) + " " + str(n_rules) + "\n"
	output += "\nc Rows:\n" + list2string(rows)
	output += "\nc Colums:\n" + list2string(cols)
	output += "\nc Diagonals:\n" + list2string(diag)

	print(printboard(n))
	print(list2string(rows))
	print(list2string(cols))
	print(list2string(diag))

	return output

def main():
	if len(sys.argv) < 2:
		print("Error: How many queens? [Missing arg1: command n_queens file_output]")
		sys.exit(0)
	else:
		output = genNqueen(int(sys.argv[1]))
		if len(sys.argv) > 2:
			outfile = open(sys.argv[2], 'w')
			outfile.write(output)
			outfile.close()


if __name__ == "__main__":
	main()
