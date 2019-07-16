# -*- coding: utf-8 -*-
import os
import json

openpose_output_dir="E:\\MMtesting\\test\\test\\OpenPose_result"
json_files = os.listdir(openpose_output_dir)

for file_name in json_files:
	_file = os.path.join(openpose_output_dir,file_name)
	data = json.load(open(_file))
	json_output={'version':1.3,'people':[]}
	json_output["people"]=[{'person_id':[-1],'pose_keypoints_2d':[],"face_keypoints_2d":[],"hand_left_keypoints_2d":[],"hand_right_keypoints_2d":[],"pose_keypoints_3d":[],"face_keypoints_3d":[],"hand_left_keypoints_3d":[],"hand_right_keypoints_3d":[]}]
	for i in range(19):
		if(i!=8):
			json_output['people'][0]['pose_keypoints_2d'].append(data['people'][0]['pose_keypoints_2d'][i])
			json_output['people'][0]['pose_keypoints_2d'].append(data['people'][0]['pose_keypoints_2d'][i+1])
			json_output['people'][0]['pose_keypoints_2d'].append(data['people'][0]['pose_keypoints_2d'][i+2])
    
    

	with open(_file,'w',encoding='utf-8') as f:
		json.dump(json_output,f)

	



