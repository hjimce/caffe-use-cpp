CC=g++

INCLUDE = -I../caffeoldversion_cpu/include/ 

LIBRARY =-L/usr/local/lib/ -lopencv_core -lopencv_imgproc -lopencv_highgui	-lopencv_imgcodecs \
		-L../caffeoldversion_cpu/build/lib/ -lcaffe

all:	
	$(CC) $(INCLUDE) $(OBJS) directory.cpp	testcpp.cpp -o exercise $(LIBRARY)


