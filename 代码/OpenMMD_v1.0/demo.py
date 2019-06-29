# -*- coding: utf-8 -*-
import os
import tensorflow as tf

tf.app.flags.DEFINE_string('inputpath',None,'the path of your video')
FLAGS=tf.app.flags.FLAGS
INPUT_VIDEO_PATH=FLAGS.inputpath
temp=INPUT_VIDEO_PATH.rfind('\\')
INPUT_VIDEO_DIR=INPUT_VIDEO_PATH[:temp]
OUTPUT_JSON_DIR=INPUT_VIDEO_DIR+'\\'+'OpenPose_result'
OUTPUT_3D=INPUT_VIDEO_DIR+'\\'+'OpenPose_result_3d'
OUTPUT_VIDEO_PATH=INPUT_VIDEO_DIR+'\\'+'openpose.mp4'
NUMBER_PEOPLE_MAX=1

def main(_):
	os.system('bin\\OpenPoseDemo.exe --video %s --write_json %s --write_video %s --number_people_max %d ' %(INPUT_VIDEO_PATH,OUTPUT_JSON_DIR,OUTPUT_VIDEO_PATH,NUMBER_PEOPLE_MAX))
	os.system('python src\\openpose_3dpose_sandbox_vmd.py --camera_frame --residual --batch_norm --dropout 0.5 --max_norm --evaluateActionWise --use_sh --epochs 200 --load 4874200 --gif_fps 30 --verbose 2 --openpose %s --person_idx 1' %(OUTPUT_JSON_DIR))
	os.system('python txt2json.py --inputpath %s' %(OUTPUT_3D))

if __name__ == '__main__': 
	tf.app.run()