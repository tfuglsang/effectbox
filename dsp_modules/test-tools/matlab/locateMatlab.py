#!/usr/bin/python
# locateMatlab.py
#
# Will look for matlab executable and choose the latest one - with a preference for 64 bit.
#
# written by cnorup@jabra.com
import os
import sys

# Main function
if __name__ == "__main__":
    # Set base matlab path
    mat64 = '/cygdrive/c/Program Files/MATLAB/'
    mat32 = '/cygdrive/c/Program Files (x86)/MATLAB/'
    theRest = '/bin/matlab.exe'

    # Look for a 64 bit version
    matlablist = []
    flag32bit = 0
    if os.path.isdir(mat64):
        matlablist = os.listdir(mat64)

    # Only look for a 32 bit version if we couldn't find a 64 bit
    if len(matlablist) < 1:
        if os.path.isdir(mat32):
            matlablist = os.listdir(mat32)
            flag32bit = 1

    # If we can't find a matlab:
    if len(matlablist) < 1:
        # print echo to bypass matlab related commands in make-system
        print "echo"
        sys.exit(1)

    # If theres more than one select the newest one
    matlablist = sorted(matlablist, reverse=True)
    thisIsTheOne = matlablist[0]

    # Construct a path based on architecture (and escape spaces)
    if flag32bit:
        outString = mat32.replace(" ", "\ ") + thisIsTheOne + theRest
    else:
        outString = mat64.replace(" ", "\ ") + thisIsTheOne + theRest
    # Finally print it to screen for make to grab
    print outString
