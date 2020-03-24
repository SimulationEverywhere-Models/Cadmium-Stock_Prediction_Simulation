CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ../../cadmium/include
INCLUDEDESTIMES=-I ../../DESTimes/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

#TARGET TO COMPILE ALL THE TESTS TOGETHER (NOT SIMULATOR)
time_series.o: data_structures/time_series.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) data_structures/time_series.cpp -o build/time_series.o -lboost_date_time

main_top.o: top_model/main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) top_model/main.cpp -o build/main_top.o -lboost_date_time -lpython3.6m -L/usr/include/python3.6m/ -I/usr/include/python3.6m/

main_accuracy_evaluator_test.o: test/main_accuracy_evaluator_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_accuracy_evaluator_test.cpp -o build/main_accuracy_evaluator_test.o

main_prediction_generator_test.o: test/main_prediction_generator_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/main_prediction_generator_test.cpp -lboost_date_time -lpython3.6m -L/usr/include/python3.6m/ -I/usr/include/python3.6m/ -o build/main_prediction_generator_test.o


tests: main_accuracy_evaluator_test.o main_prediction_generator_test.o time_series.o
		$(CC) -g -o bin/ACCURACY_EVALUATOR_TEST build/main_accuracy_evaluator_test.o build/time_series.o
		$(CC) -g -o bin/PREDICTION_GENERATOR_TEST build/main_prediction_generator_test.o build/time_series.o -lboost_date_time -lpython3.6m -L/usr/include/python3.6m/ -I/usr/include/python3.6m/

#TARGET TO COMPILE ONLY APS SIMULATOR
simulator: main_top.o time_series.o
	$(CC) -g -o bin/stock_prediction_simulator build/main_top.o build/time_series.o -lboost_date_time -lpython3.6m -L/usr/include/python3.6m/ -I/usr/include/python3.6m/
	
#TARGET TO COMPILE EVERYTHING (ABP SIMULATOR + TESTS TOGETHER)
all: simulator tests

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*
