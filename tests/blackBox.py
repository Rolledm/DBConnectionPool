#!/usr/bin/python3

import subprocess
import sys
 
process = subprocess.Popen(["../src/main", "-x", "../../test.xml"], )
process.communicate(input="exit")