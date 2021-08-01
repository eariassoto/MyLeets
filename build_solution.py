#!/usr/bin/env python3
# Copyright (c) 2021 Emmanuel Arias

import subprocess

subprocess.call(["Sharpmake.Application.exe", "/sources('sharpmake/main.sharpmake.cs')"])

input("Sharpmake compilation completed")
