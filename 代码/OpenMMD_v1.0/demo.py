# -*- coding: utf-8 -*-
import os
import tensorflow as tf
import subprocess



CREATE_NO_WINDOW = 0x08000000
tf.app.flags.DEFINE_string('inputpath',None,'the path of your video')

tf.app.flags.DEFINE_string('outputpath',None,'the path of the output')

tf.app.flags.DEFINE_string('jsonpath',None,'the path of the output json')
FLAGS=tf.app.flags.FLAGS
INPUT_VIDEO_PATH=FLAGS.inputpath
OUTPUT_JSON_DIR=FLAGS.outputpath+'\\'+'OpenPose_result'
OUTPUT_baseline=FLAGS.outputpath+'\\'+'OpenPose_result_3d'
OUTPUT_3D=FLAGS.jsonpath
OUTPUT_VIDEO_PATH=FLAGS.outputpath+'\\'+'openpose.avi'
NUMBER_PEOPLE_MAX=1

def main(_):
	#os.system('OpenPose\\OpenPoseDemo.exe --video %s --write_json %s --write_video %s --number_people_max %d ' %(INPUT_VIDEO_PATH,OUTPUT_JSON_DIR,OUTPUT_VIDEO_PATH,NUMBER_PEOPLE_MAX))
	subprocess.call('OpenPose\\OpenPoseDemo.exe --video %s --write_json %s --write_video %s --number_people_max %d ' %(INPUT_VIDEO_PATH,OUTPUT_JSON_DIR,OUTPUT_VIDEO_PATH,NUMBER_PEOPLE_MAX),creationflags=CREATE_NO_WINDOW)
	#os.system('python src\\openpose_3dpose_sandbox_vmd.py --camera_frame --residual --batch_norm --dropout 0.5 --max_norm --evaluateActionWise --use_sh --epochs 200 --load 4874200 --gif_fps 30 --verbose 2 --openpose %s --person_idx 1' %(OUTPUT_JSON_DIR))
	#os.system('python txt2json.py --inputpath %s --outputpath %s' %(OUTPUT_baseline,OUTPUT_3D))
	subprocess.call('python src\\openpose_3dpose_sandbox_vmd.py --camera_frame --residual --batch_norm --dropout 0.5 --max_norm --evaluateActionWise --use_sh --epochs 200 --load 4874200 --gif_fps 30 --verbose 2 --openpose %s --person_idx 1' 
		%(OUTPUT_JSON_DIR),creationflags=CREATE_NO_WINDOW)
	subprocess.call('python txt2json.py --inputpath %s --outputpath %s --videopath %s' %(OUTPUT_baseline,OUTPUT_3D,INPUT_VIDEO_PATH),creationflags=CREATE_NO_WINDOW)

if __name__ == '__main__': 
	tf.app.run()