#!/usr/bin/python3

import subprocess
import difflib

def rmSymb(string, symbol):
    i = 0
    while string[i] != symbol:
        i += 1
    return string[i+1::]

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
        
        if (i == 1):  #LOG
            if (rmSymb(line1, ']') != rmSymb(line2,']')):
                print("FAILED: %r != %r" %(line1, line2))
                return False

        elif (i == 0): #OUTPUT
            if (line1 != line2):
                print("FAILED: %r != %r" %(line1, line2))
                return False
        
    
    print("PASSED.")
    return True

def ASSERT_EQ_LOG_FILES(file1, file2, name):
    return ASSERT_EQ_FILES(file1, file2, 1, name) # we aren't need in timestamp in log file

def ASSERT_EQ_OUT_FILES(file1, file2, name):
    return ASSERT_EQ_FILES(file1, file2, 0, name)

def summary(lst):
    print("\nTotal: %d." %len(lst))
    print("Passed: %d." %lst.count(True))
    print("Failed: %d." %lst.count(False))


l = list()    

process = subprocess.call(["../build/quickSQLClient", "-x"])   # only -x key w/out path to file
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "test_files/logerror1_-x", "only -x"))

process = subprocess.call(["../build/quickSQLClient", "-l", "fatal"])  # correct initialising severity level but w/out initialisation of .xml file
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "test_files/logerror5_fatal", "fatal sev_lvl"))

process = subprocess.call(["../build/quickSQLClient", "-x", "qqqqqq"]) # incorrect path to .xml file
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "test_files/logerror6_incorrect", "incorrect_file"))

process = subprocess.call(["../build/quickSQLClient", "-x", "test_files/clear.xml"])  # trying to launch w/ clear .xml file
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "test_files/logerror7_clear_xml", "clear xml"))

process = subprocess.call(["../build/quickSQLClient", "-x", "test_files/clear.xml", "-l", "fatal"])  # like previous but w/ fatal severity
l.append(ASSERT_EQ_LOG_FILES("sample_0.log", "test_files/logerror8_clear_fatal", "clear xml w/ fatal sev_lvl"))

#for example of wrong test
l.append(ASSERT_EQ_OUT_FILES("test_files/wr1", "test_files/wr2", "EXAMPLE"))


summary(l)
