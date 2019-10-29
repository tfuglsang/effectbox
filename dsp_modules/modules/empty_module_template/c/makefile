# This is a template makefile for a DSP module.
# Usage:
#   make        (builds default target: all)
#   make clean  (cleans all output files that result from a build)
#
# There should be no need modify this file if normal operation is
# required. However it is possible to replace this makefile with
# a specialized version if desired.
#
# In addition there is an option to add extra defines for the compiler.
# To do this create a file alongside this makefile, i.e.:
#   <module name>/c/<module name>.mak
# in this file add a variable:
#   EXTRA_DEFINES = MY_SPECIAL_DEFINE
# the extra defines will be passed to the compiler with the -D option.
# If you want to make the defines selectable from using a make switch
# it can be done like this (example from acoustic_shock_protection):
#   ifeq ($(subsample_accuracy),true)
# 	  EXTRA_DEFINES += SUBSAMPLE_ACCURACY
#   endif
# Run "make subsample_accuracy=true" to turn on subsample accuracy in pitch_finder(). 
#
# Author: Bo Vincentz Bonnichsen, 2018-05-24

#######################
# include build system
#######################
module_path := $(realpath ./..)
module_name := $(notdir $(module_path))

include ../../make_c.inc
