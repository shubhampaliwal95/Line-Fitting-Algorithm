from matplotlib import pyplot as plt
import numpy as np
from itertools import islice
import subprocess
#Method for visualisation of data
subprocess.call(["g++", "LineFitting.cpp"])
def display():

	tmp=subprocess.call("./a.out")										
	total = open('Output.txt')						
	points = []									
	total_points=int(total.readline())				#Reading total number of points from file
	print(total_points)
	for line in islice(total,0,total_points):		#Reading points line by line
		line=line.replace("\n","")
		points.append(line.split(" "))
		#print(line)
	
	#print(points)
	points=np.asarray(points)
	lines=[]
	for line in total:								#Reading slope and intercept on lines formed
		line=line.replace("\n","")
		lines.append(line.split(" "))


	plt.title('Segmented least square fitting')
	lines=np.asarray(lines)
	plt.plot(points[:,0].astype(np.float32),points[:,1].astype(np.float32),'o')		#Printing points on graph
	#print(points[:,0])
	#print(points[:,1])
	
	
	

	x=np.linspace(0,9,10)
	#print(x)
	# print(lines.shape)
	for i in range(0,lines.shape[0]):
		#print(i)
		a=float(lines[i][0])
		b=float(lines[i][1])
		y=a*x+b 			#Equation of line
		#print(y)
		#print(a)
		#print(b)
		plt.plot(x,y)		#plotting line on graph
	# plt.grid()
	#print(lines)		
	plt.show()
for i in range(0,100):
	print("Press 1 if you want to check another value of cost")
	c = int(input())
	if(i>0):
		plt.close()
	if(c==1): 
		display()
	else:
		exit(0)
