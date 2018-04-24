all:
	g++ filt.cc `root-config --cflags` `root-config --glibs` -o filt -g -I$(FFTW3ROOT)/include -L$(FFTW3ROOT)/lib -lfftw3 
