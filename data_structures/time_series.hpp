#ifndef BOOST_SIMULATION_TIME_SERIES_HPP
#define BOOST_SIMULATION_TIME_SERIES_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/gregorian/gregorian_types.hpp"

using namespace std;

/*******************************************/
/**************** time_series_t ****************/
/*******************************************/

struct time_series_element{
        time_series_element(){}

        time_series_element(string d_date, double d_price): date(d_date), price(d_price){}

        string date;
        double price;
};


struct time_series_t{
	time_series_t(){}

	time_series_t(string d_date, double d_price): last_date(d_date), last_price(d_price){}

	string last_date;
	double last_price;
	vector<time_series_element> ts;
};



struct random_choice{
        random_choice(){}

        random_choice(string d_date, double d_price, double d_rand_choice): last_date(d_date), last_price(d_price), rand_choice(d_rand_choice){}

        string last_date;
        double last_price;
	double rand_choice;
};





istream& operator>> (istream& is, time_series_t& ts);

ostream& operator<<(ostream& os, const time_series_t& ts);

istream& operator>> (istream& is, time_series_element& ts);

ostream& operator<<(ostream& os, const time_series_element& ts);

istream& operator>> (istream& is, random_choice& ts);

ostream& operator<<(ostream& os, const random_choice& ts);




#endif // BOOST_SIMULATION_TIME_SERIES_HPP
