#!/usr/bin/env python

import sys

f = sys.stdin.readlines()[0].replace('\n', '')
with open(f, 'r') as file:
  arr = file.readlines()

  output = "".join(arr).replace('\n', '\\n')

print(output)