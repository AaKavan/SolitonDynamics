# PHYS305 - Term Project
# Makefile for KdV RK4 Solver

CXX = g++
# For suppresing some warning that happen
CXXFLAGS = -c -Wall -Wno-vla-cxx-extension
OBJS = functions.o
TARGETS = rk4 phi C_convergence f_self_convergence richardson_extrapolation

# Standard rule: build all targets
all: $(TARGETS)


rk4: rk4.o $(OBJS)
	$(CXX) -o rk4 rk4.o $(OBJS) -lm

rk4.o: rk4.C header.h
	$(CXX) $(CXXFLAGS) rk4.C


phi: phi.o $(OBJS)
	$(CXX) -o phi phi.o $(OBJS) -lm

phi.o: phi.C header.h
	$(CXX) $(CXXFLAGS) phi.C


C_convergence: C_convergence.o $(OBJS)
	$(CXX) -o C_convergence C_convergence.o $(OBJS) -lm

C_convergence.o: C_convergence.C header.h
	$(CXX) $(CXXFLAGS) C_convergence.C


f_self_convergence: f_self_convergence.o $(OBJS)
	$(CXX) -o f_self_convergence f_self_convergence.o $(OBJS) -lm

f_self_convergence.o: f_self_convergence.C header.h
	$(CXX) $(CXXFLAGS) f_self_convergence.C


richardson_extrapolation: richardson_extrapolation.o $(OBJS)
	$(CXX) -o richardson_extrapolation richardson_extrapolation.o $(OBJS) -lm

richardson_extrapolation.o: richardson_extrapolation.C header.h
	$(CXX) $(CXXFLAGS) richardson_extrapolation.C


functions.o: functions.C header.h
	$(CXX) $(CXXFLAGS) functions.C

# Clean rule
clean:
	rm -f $(TARGETS) *.o *~
