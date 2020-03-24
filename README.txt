This folder contains the STOCK PRICE SIMULATOR DEVS model implemented in Cadmium and Keras/TensorFlow

/**************************/
/****FILES ORGANIZATION****/
/**************************/

README.txt	
SPS.docx
makefile

machine_learning [this folder contains the files to train a deep learning model]
	GOOG.svc [last 5 years data from google stock price]
	train.py []
	scaler.scale [scale file]
	trained_model.h5 [exported trained model] 
atomics [This folder contains atomic models implemented in Cadmium]
	prediction_generator.hpp
	accuracy_evaluator.hpp
bin [This folder will be created automatically the first time you compile the project.
     It will contain all the executables]
build [This folder will be created automatically the first time you compile the project.
       It will contain all the build files (.o) generated during compilation]
data_structures [This folder contains message data structure used in the model]
	time_series.hpp
	time_series.cpp
input_data [This folder contains all the input data to run the model and the tests]
	prediction_generator_input_test1.txt
	prediction_generator_input_test2.txt
	prediction_generator_input_test2.txt
	accuracy_evaluator_input_test1.txt
	accuracy_evaluator_input_test2.txt
	accuracy_evaluator_input_test2.txt
	stock_prediction_simulation_input_test.txt
simulation_results [This folder will be created automatically the first time you compile the project.
                    It will store the outputs from your simulations and tests]
test [This folder the unit test of the atomic models]
	main_prediction_generator_test.cpp
	main_accuracy_evaluator_test.cpp
top_model [This folder contains the Asset Price Simulator top model]	
	main_.cpp
scripts
	[This folder contains the scripts to execute the bin files with the different input_data files]
	stock_prediction_simulation.sh [executes STOCK_PREDICTION_SIMULATION file (compiled in the bin folder) with the stock_prediction_simulation_input_test.txt input data file]
	prediction_generator_test1.sh [executes PREDICTION_GENERATOR_TEST file (compiled in the bin folder) with the prediction_generator_input_test1.txt input data file]
	prediction_generator_test2.sh [executes PREDICTION_GENERATOR_TEST file (compiled in the bin folder) with the prediction_generator_input_test2.txt input data file]
	prediction_generator_test3.sh [executes PREDICTION_GENERATOR_TEST file (compiled in the bin folder) with the prediction_generator_input_test3.txt input data file]
	accuracy_evaluator_test1.sh [executes ACCURACY_EVALUATOR_TEST file (compiled in the bin folder) with the accuracy_evaluator_input_test1.txt input data file]
	accuracy_evaluator_test2.sh [executes ACCURACY_EVALUATOR_TEST file (compiled in the bin folder) with the accuracy_evaluator_input_test2.txt input data file]
	accuracy_evaluator_test3.sh [executes ACCURACY_EVALUATOR_TEST file (compiled in the bin folder) with the accuracy_evaluator_input_test3.txt input data file]
	scaler.scale [scale file required by tensorFlow]
	predictor.py [contains the function that calls the trained model]	
	trained_model.h5 [deep learning trained model]

/*************/
/****STEPS****/
/*************/

0 - SPS.docx contains the explanation of this model

1 - Install Cadmium and dependencies.

2. Update include path in the makefile in this folder and subfolders. You need to update the following lines:
	INCLUDECADMIUM=-I ../../cadmium/include
	INCLUDEDESTIMES=-I ../../DESTimes/include
    Update the relative path to cadmium/include from the folder where the makefile is. You need to take into account where you copied the folder during the installation process
	Example: INCLUDECADMIUM=-I ../../cadmium/include
	Do the same for the DESTimes library
    NOTE: if you follow the step by step installation guide you will not need to update these paths.

3. Install TensorFlow and Keras
	1. open a terminal in the main folder.
	2. Install the machine learning dependencies, type in the terminal "sudo ./install_dependencies.sh" 

2 - Compile the project and the tests
	1 - Open the terminal (Ubuntu terminal for Linux and Cygwin for Windows) in the APS folder
	2 - To compile the project and the tests, type in the terminal:
			make clean; make all
3 - Run tests
	1 - Open the terminal in the scripts folder.
	2 - To run the test, type in the terminal "./NAME_OF_THE_SCRIPT.sh" (For windows, inside the script the executable should be changed to the extension .exe).
	3 - To check the output of the test, go to the folder simulation_results.
			
4 - Run the top model
	1 - Open the terminal (Ubuntu terminal for Linux and Cygwin for Windows) in the scripts folder.
	2 - To run the model, type in the terminal "./stock_prediction_simulator.sh" (For windows, inside the script the executable should be changed to the extension .exe).
	3 - To check the output of the model, go to the folder simulation_results and open "stock_prediction_simulator_output_messages.txt".
	





