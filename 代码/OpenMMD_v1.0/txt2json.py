# -*- coding: utf-8 -*-
import os
import json
import tensorflow as tf

tf.app.flags.DEFINE_string('inputpath',None,'the path of txt')
tf.app.flags.DEFINE_string('outputpath',None,'the path of json')
FLAGS=tf.app.flags.FLAGS
OUTPUT_3D_JSON=FLAGS.outputpath
data=[[]]
joints=[[]]


filename=FLAGS.inputpath+'\\'+'pos.txt'
f=open(filename)
lines=f.readlines()
if not lines:
	pass
frame_number=len(lines)
joints_array=[[] for i in range(frame_number)]
for i in range(frame_number):
	data=lines[i].split(',')
	for j in range(17):
		joints=data[j].split()
		joints_array[i].append(float(joints[1]))
		joints_array[i].append(float(joints[2]))
		joints_array[i].append(float(joints[3]))
output_format={'bodies' : []}
output=[]
for i in range(frame_number):
	output.append({'frame' : i, 
	               'position' : joints_array[i],}, )
	  
output_format['bodies']=output

with open(OUTPUT_3D_JSON,'w',encoding='utf-8') as f2 :
	json.dump(output_format,f2)
	
	    
		
	    