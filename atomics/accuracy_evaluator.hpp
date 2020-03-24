/**
* Guillermo G. Trabes
* ARSLab - Carleton University
*
* Daily Return Generator:
* Cadmium implementation
*/

#ifndef __ACCURACY_EVALUATOR_HPP__
#define __ACCURACY_EVALUATOR_HPP__

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <limits>
#include <assert.h>
#include <string>
#include <random>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>


#include "../data_structures/time_series.hpp"

using namespace cadmium;
using namespace std;


//Port definition
struct accuracy_evaluator_defs{
    struct in : public in_port<time_series_element> { };
    struct out : public out_port<double> { };
};


template<typename TIME> class accuracy_evaluator{
	public:
	// ports definition
        using input_ports=std::tuple<typename accuracy_evaluator_defs::in>;
        using output_ports=std::tuple<typename accuracy_evaluator_defs::out>;

	// state definition
	struct state_type{
		time_series_element prediction, real_value, last_value;
		double accurate_decision_percentage, average_estimation_error;
		double values_predicted,right_decisions;
		int output_needed;
    	};

	/* state declaration */
	state_type state;

	/* random generation auxiliar function*/
	boost::random::mt19937 gen;


        // default constructor
        accuracy_evaluator() {
	  state.output_needed = 0;
	  gen.seed(std::time(0));
	  state.right_decisions = 0.0;
	  state.values_predicted = 0.0;
	  state.average_estimation_error = 0.0;
        }

        // internal transition
        void internal_transition() {
		state.output_needed=0;
        }

        // external transition
        void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs) {

		double real_value, prediction, accuracy, estimation_error;

		/* get messages from port*/
		vector<time_series_element> bag_port_in;

		bag_port_in = get_messages<typename accuracy_evaluator_defs::in>(mbs);

		/* get real value and estimation */
		state.last_value=bag_port_in[0];
		state.real_value=bag_port_in[1];
		state.prediction=bag_port_in[2];

		/* estimate accuracy of the prediction */
		estimation_error=abs(state.prediction.price-state.real_value.price)/state.real_value.price;

		/*calculate new accuracy average */
                state.average_estimation_error=((state.average_estimation_error*state.values_predicted)+estimation_error)/(state.values_predicted+1);

		/*calculate right or wrong decision: is the predicted value grows or dimishes as the real value the
		  decision is correct
		 */
		if(state.last_value.price==state.real_value.price && state.last_value.price==state.prediction.price){
			state.right_decisions++;
		}
		else{
			if(state.last_value.price<state.real_value.price && state.last_value.price<state.prediction.price){
				state.right_decisions++;
			}
			else{
				if(state.last_value.price>state.real_value.price && state.last_value.price>state.prediction.price){
                                	state.right_decisions++;
				}

			}
		}

		/*store number of values predicted and right decisions made */
		state.values_predicted++;
		state.accurate_decision_percentage=state.right_decisions/state.values_predicted;

                /* store random value and last price on state */
		state.real_value.price = real_value;
		state.prediction.price = prediction;

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

	    get_messages<typename accuracy_evaluator_defs::out>(bags).push_back(state.accurate_decision_percentage);
	    get_messages<typename accuracy_evaluator_defs::out>(bags).push_back(state.average_estimation_error);

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

        friend std::ostringstream& operator<<(std::ostringstream& os, const typename accuracy_evaluator<TIME>::state_type& i) {
//            os << "Prediction: " << i.accuracy << " " << i.real_value.price << " " << "Real Value: " << i.real_value.date << " " << i.real_value.price;
        return os;
        }
};
#endif // __ACCURACY_EVALUATOR_HPP__
