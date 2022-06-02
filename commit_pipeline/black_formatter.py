#!/usr/bin/env python

import subprocess

output = subprocess.run(
    "find src -name '*.py' -type f -exec black {} 2>&1 \;", 
    shell=True, 
    stdout=subprocess.PIPE, 
    stderr=subprocess.PIPE, 
    check=True).stdout.decode('utf-8')

with open('black_logs.txt', 'w') as f:
    f.writelines(output)