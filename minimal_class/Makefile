#intentionally kept verbose to clearly show what's going on

libMyClass.so: MyClass.o MyClassDict.o

MyClassDict.cxx: MyClass.h LinkDef.h
	rootcint -f MyClassDict.cxx -rmf .rootmap -rml libMyClass.so -c $(root-config --cflags) MyClass.h LinkDef.h
	
MyClassDict.o: MyClassDict.cxx
	g++ -fPIC $(shell root-config --cflags) -c MyClassDict.cxx
	
MyClass.o:
	g++ -fPIC $(shell root-config --cflags) -c MyClass.cxx

libMyClass.so: MyClass.o MyClassDict.o
	g++ --shared -o libMyClass.so $(shell root-config --cflags --ldflags --libs) MyClass.o MyClassDict.o
	
.PHONY: clean

clean:
	rm -rf *.o *.so *Dict* .rootmap