#!/usr/bin/env python3
# Copyright (c) 2021 Emmanuel Arias

import os
import os.path
from shutil import copyfile
import subprocess

def create_exercise(): 
	exercise_name = input("Enter test name: ")
	if not exercise_name:
		print("Invalid test name")
		return

	exercises_path = os.path.join(os.getcwd(), "exercises")
	exercise_project_path = os.path.join(exercises_path, exercise_name)
	exercise_exists = os.path.exists(exercise_project_path)

	if exercise_exists:
		print("File already exists")
		return
	
	try:
		# Create project directories
		os.mkdir(exercise_project_path)

		exercise_source_path = os.path.join(exercise_project_path, exercise_name)
		os.mkdir(exercise_source_path)

		# Copy main file
		template_main_file = os.path.join(os.getcwd(), "templates", "main.cpp.template")
		main_file = os.path.join(exercise_source_path, "main.cpp")

		copyfile(template_main_file, main_file)

		# Read the Sharpmake template file and replace project name
		template_sharpmake_file = open(os.path.join(os.getcwd(), "templates", "test.application.sharpmake.cs.template"), "r")
		template_sharpmake_file_content = template_sharpmake_file.read()
		template_sharpmake_file.close()

		template_sharpmake_file_content = template_sharpmake_file_content.replace("%NAME%", exercise_name)

		sharpmake_file = open(os.path.join(exercise_project_path, exercise_name+".application.sharpmake.cs"), "w")
		sharpmake_file.write(template_sharpmake_file_content)
		sharpmake_file.close()

		# Now read all exercise project folders and redo main sharpmake file
		dirlist = [ item for item in os.listdir(exercises_path) if item != "common_lib" and os.path.isdir(os.path.join(exercises_path, item)) ]
		include_modules = ""
		add_projects = ""
		for d in dirlist:
			include_modules += "[module: Sharpmake.Include(\"../exercises/%s/%s.application.sharpmake.cs\")]\n" % (d, d)
			add_projects += "            conf.AddProject<%s_Exercise>(target);\n" % d
		
		template_sharpmake_main_file = open(os.path.join(os.getcwd(), "templates", "main.sharpmake.cs.template"), "r")
		template_sharpmake_main_file_content = template_sharpmake_main_file.read()
		template_sharpmake_main_file.close()

		template_sharpmake_main_file_content = template_sharpmake_main_file_content.replace("%INCLUDE_MODULES%", include_modules)
		template_sharpmake_main_file_content = template_sharpmake_main_file_content.replace("%ADD_PROJECTS%", add_projects)

		sharpmake_main_file = open(os.path.join(os.getcwd(), "sharpmake", "main.sharpmake.cs"), "w")
		sharpmake_main_file.write(template_sharpmake_main_file_content)
		sharpmake_main_file.close()

	except OSError:
		print ("Creation of directories failed")
		return

	input("Exercise [%s] created sucessfully, press Enter to rebuild Sharpmake" % exercise_name)

	subprocess.call(["Sharpmake.Application.exe", "/sources('sharpmake/main.sharpmake.cs')"])

	input("Sharpmake compilation completed")

create_exercise();
