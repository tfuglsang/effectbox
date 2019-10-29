# This mak file is included by the make system automatically.
#
# In this file you can add extra defines for the compiler, e.g.:
#   EXTRA_DEFINES = MY_SPECIAL_DEFINE
# the extra defines will be passed to the compiler with the -D option.
#
# If you want to make the defines selectable from using a make switch
# it can be done like this (example from acoustic_shock_protection):
#   ifeq ($(subsample_accuracy),true)
# 	  EXTRA_DEFINES += SUBSAMPLE_ACCURACY
#   endif
# Run "make subsample_accuracy=true" to turn on subsample accuracy in pitch_finder(). 
