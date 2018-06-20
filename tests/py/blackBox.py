#!/usr/bin/python3

import subprocess
import difflib

def ASSERT_EQ_FILES(file1, file2, i, name):
    print("TEST %r:"%name)
    file1_lines = open(file1).readlines()
    file2_lines = open(file2).readlines()
    if (len(file1_lines) != len(file2_lines)):
        print("FAILED: Different size of files!")
        return False

    for line1, line2 in zip(file1_lines, file2_lines):
        line1 = line1.replace("\n", "")
        line2 = line2.replace("\n", "")
        
        if (line1[i:] != line2[i:]):
            print("FAILED: %r != %r" %(line1, line2))
            return False
    
    print("PASSED.")
    return True

def ASSERT_EQ_LOG_FILES(file1, file2, name):
    return ASSERT_EQ_FILES(file1, file2, 29, name) # we aren't need in timestamp in log file

def ASSERT_EQ_OUT_FILES(file1, file2, name):
    return ASSERT_EQ_FILES(file1, file2, 0, name)

def summary(lst):
    print("\nTotal: %d." %len(lst))
    print("Passed: %d." %lst.count(True))
    print("Failed: %d." %lst.count(False))


l = list()    

process = subprocess.call(["../../src/main", "-x"])
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "logerror1_-x", "only -x"))

process = subprocess.call(["../../src/main", "-o"])
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "logerror2_-o", "only -o"))

process = subprocess.call(["../../src/main", "-x", "-o"])
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "logerror3_-x-o", "-x -o"))

process = subprocess.call(["../../src/main", "-o", "~/file1"])
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "logerror4_no_init", "valid file but no initialiser"))

process = subprocess.call(["../../src/main", "-l", "fatal"])
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "logerror5_fatal", "fatal sev_lvl"))

process = subprocess.call(["../../src/main", "-x", "qqqqqq"])
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "logerror6_incorrect", "incorrect_file"))

process = subprocess.call(["../../src/main", "-x", "../../../clear.xml"])
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "logerror7_clear_xml", "clear xml"))

process = subprocess.call(["../../src/main", "-x", "../../../clear.xml", "-l", "fatal"])
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "logerror8_clear_fatal", "clear xml w/ fatal sev_lvl"))

#for example of wrong test
l.append(ASSERT_EQ_OUT_FILES("wr1", "wr2", "EXAMPLE"))


summary(l)
