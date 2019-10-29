#!/usr/bin/python
# compareTestVectors.py
#
# written by cnorup@jabra.com

#    """ This script will help you compare testvector outputs from matlab,
#    C and target platforms. 
#    
#    Point in to your testvector folder, and it'll compare files with similar
#    in existing subfolders (ie. testvectors/matlab vs testvectors/c).
#
#    Usage:
#        compareTestVectors.py testvectors/
#
#    Pass it more paths, to compare across platforms (it will expect matlab 
#    testvectors as first argument passed):
#        compareTestVectors.py platform_dsp_reference/modules/biquad/test/testvectors/ platform_dsp_hifi3/modules/biquad/test/testvectors/ 
#    
#    Written by cnorup@jabra.com
#    """

import sys
import glob
import numpy as np
np.seterr(divide='ignore', invalid='ignore')    # Nevermind the nans - we now how to handle 'em
from os import walk
from os import path
import os
import itertools
import pickle
import wave

def getFiles(mypath):
    """ Get a list of files in directory (mypath)
    """
    f = []
    for (dirpath, dirnames, filenames) in walk(mypath):
        f.extend(filenames)
        break

    # remove dat/wav/txt files, if present
    f = [ x for x in f if ".dat" not in x ]
    f = [ x for x in f if ".wav" not in x ]
    f = [ x for x in f if ".txt" not in x ]
    return f

def getDirs(mypath):
    """ Get a list of subdirs in directory
    """
    d = []
    for (dirpath, dirnames, filenames) in walk(mypath):
        ret = [dirpath + s for s in dirnames]
        d.extend(ret)
        break
    return d

def parseExt(ext):
    """ Pass an extension and and return the scaling and raw ext
    """
    scale = 1.0
    Q = 0
    q_ext = ''
    if '_q' in ext: # custom format detected - let's parse that, and get a scaling factor
        splitext = ext.split('_')
        ext = splitext[0]
        q_ext = '_' + splitext[1]
        Q = float(splitext[1][1:])
        if 'f' in ext:
            scale = 1.0
        elif 'u' in ext:
            scale = 1.0/pow(2.0, Q)
        elif 's' in ext:
            scale = 1.0/pow(2.0, Q)
    
    return (scale,ext)


# Get values from file
def getFileVals(myfile):
    """ Load binary data from file, based on file extension
    """

    # Define basic extensions
    choices = {'.f32': np.float32, '.f64': np.float64, '.s32': np.int32, '.u32': np.uint32, '.s16': np.int16, '.u16': np.uint16, '.s64': np.int64}
    
    # Parse extension
    (root, ext) =  path.splitext(myfile)

    # Try to match the same extension
    if path.isfile(myfile):
        # Load the data
        ftype = choices.get(ext)
        data = np.fromfile(myfile, dtype=ftype)
        #print "Loading file " + myfile + " with type " + str(ftype)
        return data
    else: 
        # Same extension wasn't found, so load whatever file that it is
        # and apply scaling according to q format
        file = glob.glob(root + '.*')
        if len(file) == 0: # if file is empty, then it doesn't exist - so exit
            return []
        (myFile, myExt) =  path.splitext(file[0])
        out = parseExt(myExt)
        ftype = choices.get(out[1], 'Filetype not recognized')
        data = np.fromfile(file[0], dtype=ftype)
        #print "Loading file " + file[0] + " with type " + str(ftype)
        return data*out[0]

def printTable(myDict, colList=None):
   """ Pretty print a list of dictionnaries (myDict) as a dynamically sized table.
   If column names (colList) aren't specified, they will show in random order.
   Author: Thierry Husson - Use it as you want but don't blame me.
   """
   if not colList: colList = list(myDict[0].keys() if myDict else [])
   myList = [colList] # 1st row = header
   for item in myDict: myList.append([str(item[col] or '') for col in colList])
   colSize = [max(map(len,col)) for col in zip(*myList)]
   formatStr = ' | '.join(["{{:<{}}}".format(i) for i in colSize])
   myList.insert(1, ['-' * i for i in colSize]) # Seperating line
   for item in myList: print(formatStr.format(*item))

def printData(dataDict, id):
    """ Print data dictionary to screen - including nice formatting and
    everything.
    """
    print id[0], "vs", id[1]
    print "-" * 40
    print ""
    headers = ['vectorName', 'maxAbs', 'BitsOA', 'minAbs', 'stdAbs', 'meanAbs', 'maxRelErr', 'corrCoeff', 'comment']
    printTable(dataDict, headers)
    print ""
    print "Testvector validation completed"
    print "-------------------------------"
    print ""

def compare(val1, val2):
    """ Compare values in testvectors and save as dictionary
    """

    # Check if input is valid
    dataDict = {};

    # Matlab file is empty
    if len(val1) == 0:  
        dataDict['comment'] = "Matlab file is empty/Not found??"
        dataDict['maxAbs'] = "";
        dataDict['BitsOA'] = "";
        dataDict['minAbs'] = "";
        dataDict['meanAbs'] = "";
        dataDict['stdAbs'] = "";
        dataDict['maxRelErr'] = "";
        dataDict['corrCoeff'] = "";

    # Target file is empty
    elif len(val2) == 0:
        dataDict['comment'] = "Target file is empty/Not found??"
        dataDict['maxAbs'] = "";
        dataDict['BitsOA'] = "";
        dataDict['minAbs'] = "";
        dataDict['meanAbs'] = "";
        dataDict['stdAbs'] = "";
        dataDict['maxRelErr'] = "";
        dataDict['corrCoeff'] = "";


    # Somethings wrong: lengths doesn't match
    elif (len(val1) != len(val2)):
        dataDict['comment'] = "Vectors doesn't have equal length (%d vs %d)" % (len(val1), len(val2))
        dataDict['maxAbs'] = "";
        dataDict['BitsOA'] = "";
        dataDict['minAbs'] = "";
        dataDict['meanAbs'] = "";
        dataDict['stdAbs'] = "";
        dataDict['maxRelErr'] = "";
        dataDict['corrCoeff'] = "";

    # There's data - we're happy
    elif len(val2):     
        dataDict['comment'] = ""
        # Calculate some stuff
        a = np.array(val1)
        b = np.array(val2)
        absDiff = abs(a-b)
        relErr  = ((b-a)/a)
        corr_coef = np.corrcoef(a,b)
        # Save the stuff
        dataDict['maxAbs']  =   str(np.max(absDiff))
        dataDict['BitsOA']  =   str(-np.round(np.log(np.max(absDiff))/np.log(2)))
        dataDict['minAbs']  =   str(np.min(absDiff))
        dataDict['meanAbs'] =   str(np.mean(absDiff))
        dataDict['stdAbs']  =   str(np.std(absDiff))
        dataDict['maxRelErr'] = str(np.nanmax(relErr))
        dataDict['corrCoeff'] = str(corr_coef[0,1])
        # Print a warning if correlation is low
        if corr_coef[0,1] < 0.9999:
            dataDict['comment'] = "WARNING!! CORRELATION IS LOW!!"
        if (not np.any(a)) and (not np.any(b)):
            dataDict['comment'] = "ZEROS Testvectors!"
        if (not np.any(a-1)) and (not np.any(b-1)):
            dataDict['comment'] = "ONES Testvectors!"
        if np.isnan(corr_coef[0,1]):
            dataDict['comment'] = "NAN WARNING!!"
        if -np.round(np.log(np.max(absDiff))/np.log(2)) < 0:
            dataDict['comment'] = "WARNING!! BitsOA is VERY POOR!!"
   
    # Or else
    else:               
        dataDict['comment'] = ""
        dataDict['maxAbs'] = "";
        dataDict['BitsOA'] = "";
        dataDict['minAbs'] = "";
        dataDict['meanAbs'] = "";
        dataDict['stdAbs'] = "";
        dataDict['maxRelErr'] = "";
        dataDict['corrCoeff'] = "";
    
    # Return dictionary
    return dataDict;

def saveMetrics(data, id):
    """ Save test metrics to a temporary subfolder. This can then 
    be picked up by an external reporting system.
    """
    # Get module name
    fullpath = path.split(os.getcwd())
    modName = path.split(fullpath[0])
    modName = modName[1]
    name = modName
    # Get logging path
    logpath = path.split(path.abspath(__file__))
    logpath = logpath[0]
    # Get target ids
    id1 = path.split(id[0])
    id1 = id1[1]
    id2 = path.split(id[1])
    id2 = id2[1]
    # Build filename and save dictionary
    name = name + '-' + id1 + '-' + id2
    newpath = logpath +'/log_data/'
    if not path.exists(newpath):
        os.makedirs(newpath)
    with open(newpath + name + '.pkl', 'wb') as f:
        pickle.dump(data, f)

#---# Main function #---#
if __name__ == "__main__":
    """ This script will help you compare testvector outputs from matlab,
    C and target platforms. 
    
    Point in to your testvector folder, and it'll compare files with similar
    in existing subfolders (ie. testvectors/matlab vs testvectors/c).

    Usage:
        compareTestVectors.py testvectors/

    Pass it more paths, to compare across platforms (it will expect matlab 
    testvectors as first argument passed):
        compareTestVectors.py platform_dsp_reference/modules/biquad/test/testvectors/ platform_dsp_hifi3/modules/biquad/test/testvectors/ 
    
    Written by cnorup@jabra.com
    """

    # If no path is speficied, then exit..
    if len(sys.argv) == 1:
        print "No path specified!"
        sys.exit(1)

    # Default skip flags
    skip_missing = 0
    skip_matlab = 0
    compare_crossplatform = 0
    skip_saving = 0
    # Check for input flags and parse accordingly
    arg_id = 1
    for k in range(1, len(sys.argv)):
        if sys.argv[k] == '-skip_missing':
            skip_missing = 1
            arg_id = arg_id + 1
        if sys.argv[k] == '-skip_matlab':
            skip_matlab = 1
            arg_id = arg_id + 1
        if sys.argv[k] == '-compare_crossplatform':
            compare_crossplatform = 1
            arg_id = arg_id + 1
        if sys.argv[k] == '-skip_saving':
            skip_saving = 1
            arg_id = arg_id + 1
    
    # Get the basepath and targets
    basePath = str(sys.argv[arg_id])
    targets = []
    for dir in sys.argv[arg_id:]:
        t = getDirs(dir)
        targets = targets + t

    # Get combinations of targets
    target_combs = itertools.combinations(targets, 2)
    
    # If we're comparing wavs across platforms, the approach is a bit different
    if compare_crossplatform:
        # here we don't care about matlab
        skip_matlab = 1
        # Find platforms, AP and stimuli - always base it on the first platform/ap found
        platforms =  getDirs(str(sys.argv[arg_id])+'/')
        if len(platforms) == 1:
            print "Only 1 platform found - exiting..."
            sys.exit(0)
        APs = os.listdir(platforms[0])
        stimuli = os.listdir(platforms[0]+'/'+APs[0])
        # build list of platform/AP
        target_combs = []
        platform_targets = []
        for ap in APs:
            for stim in stimuli:
                platform_targets.append(ap + '/' + stim)
        for target in platform_targets:
            comb = []
            for platform in platforms:
                comb.append(platform + '/' + target)
            target_combs.append(comb)

    # Scroll through files
    for id in target_combs:
        # If one is matlab, then always refer to it
        if 'matlab' in id[1]:
            id = (id[1], id[0])
        
        # if we're comparing platforms, always refer to reference platform
        if compare_crossplatform:
            if 'platform_dsp_reference' in id[1]:
                id = (id[1], id[0])
        
        # If we're skipping matlab, then skip
        if skip_matlab:
            if 'matlab' in id[0]:
                continue

        # Locate testvectors
        testvectors = getFiles(id[0])

        if len(testvectors) == 0:
            print "No testvectors found - exiting..."
            sys.exit(1)
        
        content = []
        skipped = 0
        for f in testvectors:
            (root, ext) =  path.splitext(f)
            # Load files
            val1 = getFileVals(id[0] + "/" + f)
            val2 = getFileVals(id[1] + "/" + f)
            # Compare data
            data = compare(val1, val2)
            data['vectorName'] = root;
            # If we're not skipping missing/empty files
            if not skip_missing:
                content.append(data)
            else:
                if data['comment'] == "Target file is empty/Not found??" or data['comment'] == "Matlab file is empty/Not found??":
                    skipped = skipped + 1
                else:
                    content.append(data)
        printData(content, id)
        if not skipped == 0:
            print 'Skipped ' + str(skipped) + ' empty/not found testvectors..'
        if skip_matlab == 1:
            print 'Skipped matlab testvectors..'
        if skip_saving == 0:
            saveMetrics(content, id)

