export PATH := $(MINGW_PATH):$(PATH)
export CC=mingw32-gcc -std=c99 -I../../modules/ -I../../libraries/ -I../../libraries/arm_math/Include 
