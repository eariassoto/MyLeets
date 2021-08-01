# My Leets

This is a C++ solution to make it easier and faster to code/debug typical (input/expected output) programming exercises, like Leet codes. The most boring part of doing them is to set up a build system, so I have created a set of scripts to make this easier.

I chose [Sharpmake](https://github.com/ubisoft/Sharpmake) as build system, it supports Windows, Linux, Mac and it is a open source project made by Ubisoft.

## Requirements

* Have Python installed
* Install/compile Sharpmake and have it in your path.
* Have VS2019 installed, though the Sharpmake files can be modified to support older versions
* Clone this repo and its submodules (spdlog and fmt)

## How to compile

Run the `build_solution.py` script, this will invoke sharpmake to create your VS solution and projects. The .sln can be found in `sharpmake/generated/solutions`. After conpilation, the executable files will be in `sharpmake/generate/target`

## How to create a new exercise project

Run the `create_exercise.py` . It will ask you for the name of the exercise and will create a folder in `exercises/`. The script will re-run Sharpmake and you will have the project available in VS immediately.

## TODO:

* Have a helper script to compile the solution, read the executables and provide a way to select the test to run
* Add time measurements
* Support batch input execution



