CXX = g++

PROG     = arith_eval
CPPFLAGS = -std=c++11 -g
OBJS 	 = main.o arith_eval.o

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(CPPFLAGS)

clean   :
	rm $(PROG) $(OBJS)

main.o       : main.cpp arith_eval.h
	$(CXX) -c -o main.o main.cpp $(CPPFLAGS)

arith_eval.o : arith_eval.cpp arith_eval.h
	$(CXX) -c -o arith_eval.o arith_eval.cpp $(CPPFLAGS)
