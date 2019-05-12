all: osproj2a osproj2b osproj2c

osproj2a: 
	g++ osproj2a.cpp -o osproj2a -lpthread
osproj2b: 
	g++ osproj2b.cpp -o osproj2b -lpthread

osproj2c: 
	g++ osproj2c.cpp -o osproj2c -lpthread 

