/**
* Guillermo G. Trabes
* ARSLab - Carleton University
*
* Daily Return Generator:
* Cadmium implementation
*/

#ifndef __PREDICTION_GENERATOR_HPP__
#define __PREDICTION_GENERATOR_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <limits>
#include <assert.h>
#include <string>
#include <random>
#include "boost/date_time/gregorian/gregorian.hpp"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random.hpp>


#include <Python.h>
#include <stdio.h>
#include <string.h>

#include "../data_structures/time_series.hpp"

using namespace cadmium;
using namespace std;
using namespace boost::gregorian;

//Port definition
struct prediction_generator_defs{
    struct in : public in_port<time_series_element> { };
    struct out : public out_port<time_series_element> { };
};


template<typename TIME> class prediction_generator{
	public:
	// ports definition
        using input_ports=std::tuple<typename prediction_generator_defs::in>;
        using output_ports=std::tuple<typename prediction_generator_defs::out>;

	// state definition
	struct state_type{
		time_series_element prediction, real_value, last_value;
		bool output_needed = 0;
    	};

	state_type state;

	/* random generation auxiliar function*/
        boost::random::mt19937 gen;

	PyObject *pName, *pModule, *pDict, *pFunc;


        // default constructor
        prediction_generator() {

		//set seed
		gen.seed(std::time(0));

		//initialize python caller
		Py_Initialize();

		if( !Py_IsInitialized() ){
			printf("Initialize failed\n");
			exit(0);
		}

		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append('../scripts/')");
	
		pName = PyUnicode_DecodeFSDefault("predictor");
	
		pModule = PyImport_Import(pName);

		if ( !pModule ){
			printf("No pModule\n");
			return;
		}

		pDict = PyModule_GetDict(pModule);

		if ( !pDict ){
			printf("No pDict\n");
			return;
		}

		pFunc = PyDict_GetItemString(pDict, "predict");

		if ( !pFunc || !PyCallable_Check(pFunc) ){
			printf("No pFunc\n");	
			return;
		}
        }

        // internal transition
        void internal_transition() {
		state.output_needed=0;
        }

        // external transition
        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {

		time_series_element prediction, real_value, last_value;
		date d;
		double normal_value;

		/* get messages from port*/
		vector<time_series_element> bag_port_in;

		bag_port_in = get_messages<typename prediction_generator_defs::in>(mbs);

		/* get random value */
		//random_value= bag_port_in[0];

		/* get last date and price */
		real_value = bag_port_in[60];
		last_value = bag_port_in[59];

		/* convert string to boost date datatype */
		d = from_simple_string(real_value.date);

		/* advenace date on day for prediction */
//	 	d += days(1);

		state.last_value = last_value;

		state.real_value = real_value;	

		/* convert back to string and store in state*/
		state.prediction.date = to_iso_extended_string(d);

		PyObject *pArgs, *pRet;

		pArgs = PyTuple_New(1);  // create a tuple which has two elements

		PyObject* inputs = Py_BuildValue("[[f,f,f,f,f,f,f,f,f,f,\
						    f,f,f,f,f,f,f,f,f,f,\
						    f,f,f,f,f,f,f,f,f,f,\
						    f,f,f,f,f,f,f,f,f,f,\
						    f,f,f,f,f,f,f,f,f,f,\
						    f,f,f,f,f,f,f,f,f,f]]",\
						    bag_port_in[0].price, bag_port_in[1].price, bag_port_in[2].price, bag_port_in[3].price, bag_port_in[4].price, bag_port_in[5].price, bag_port_in[6].price, bag_port_in[7].price, bag_port_in[8].price, bag_port_in[9].price,\
						    bag_port_in[10].price, bag_port_in[11].price, bag_port_in[12].price, bag_port_in[13].price, bag_port_in[14].price, bag_port_in[15].price, bag_port_in[16].price, bag_port_in[17].price, bag_port_in[18].price, bag_port_in[19].price,\
						    bag_port_in[20].price, bag_port_in[21].price, bag_port_in[22].price, bag_port_in[23].price, bag_port_in[24].price, bag_port_in[25].price, bag_port_in[26].price, bag_port_in[27].price, bag_port_in[28].price, bag_port_in[29].price,\
						    bag_port_in[30].price, bag_port_in[31].price, bag_port_in[32].price, bag_port_in[33].price, bag_port_in[34].price, bag_port_in[35].price, bag_port_in[36].price, bag_port_in[37].price, bag_port_in[38].price, bag_port_in[39].price,\
						    bag_port_in[40].price, bag_port_in[41].price, bag_port_in[42].price, bag_port_in[43].price, bag_port_in[44].price, bag_port_in[45].price, bag_port_in[46].price, bag_port_in[47].price, bag_port_in[48].price, bag_port_in[49].price,\
						    bag_port_in[50].price, bag_port_in[51].price, bag_port_in[52].price, bag_port_in[53].price, bag_port_in[54].price, bag_port_in[55].price, bag_port_in[56].price, bag_port_in[57].price, bag_port_in[58].price, bag_port_in[59].price);


		PyTuple_SetItem(pArgs, 0, inputs);   

		if ( !pFunc || !PyCallable_Check(pFunc) ){
			printf("No pFunc\n");   
			return;
		}

		//printf(" ===========> START CALL PYTHON SCRIPT <===========\n");
		pRet = PyObject_CallObject(pFunc, pArgs);     // call the function
		//printf(" ===========> CALLING FINISHED <===========\n");

		double result = PyFloat_AsDouble(pRet);            // get the return value by pRet
		//printf(" ===========> result = %f <===========\n", result);

		state.prediction.price = result;

                state.output_needed=1;


        }

        // confluence transition
        void confluence_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {
            internal_transition();
            external_transition(TIME(), std::move(mbs));
        }

        // output function
        typename make_message_bags<output_ports>::type output() const {
            typename make_message_bags<output_ports>::type bags;

	    get_messages<typename prediction_generator_defs::out>(bags).push_back(state.last_value);
	    get_messages<typename prediction_generator_defs::out>(bags).push_back(state.real_value);
	    get_messages<typename prediction_generator_defs::out>(bags).push_back(state.prediction);

            return bags;
        }

        // time_advance function
        TIME time_advance() const {

		TIME next_internal;
		if (state.output_needed==1) {
			next_internal = TIME("00:00:00:000");
		}else {
			next_internal = numeric_limits<TIME>::infinity();
		}

		return next_internal;
        }

        friend std::ostringstream& operator<<(std::ostringstream& os, const typename prediction_generator<TIME>::state_type& i) {
        return os;
        }
};
#endif // __PREDICTION_GENERATOR_HPP__
