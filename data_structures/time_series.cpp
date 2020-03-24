#include <math.h> 
#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>

#include "time_series.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"



/***************************************************/
/************* Output stream for time_series ************************/
/***************************************************/


ostream& operator<<(ostream& os, const time_series_t& ts) {
//  os << to_iso_extended_string(ts.d) << " " << ts.price;
	int i;
	for(i=0; i<ts.ts.size(); i++){
		os << " "<< ts.ts[i].date << " " << ts.ts[i].price << ",";
	}

	os << " " <<ts.last_date << " " << ts.last_price << " ";
  return os;
}

/***************************************************/
/************* Input stream for time_series ************************/
/***************************************************/

istream& operator>> (istream& is, time_series_t& ts) {
	int i=0;
	for(i=0; i<ts.ts.size(); i++){
		is >> ts.ts[i].date;
	}
	return is;
}



/***************************************************/
/************* Output stream for time_series_element ************************/
/***************************************************/


ostream& operator<<(ostream& os, const time_series_element& ts) {
//  os << to_iso_extended_string(ts.d) << " " << ts.price;
  os << ts.date << " " << ts.price;
  return os;
}

/***************************************************/
/************* Input stream for time_series_element************************/
/***************************************************/

istream& operator>> (istream& is, time_series_element& ts) {
  is >> ts.date;
  is >> ts.price;
  return is;
}


/***************************************************/
/************* Output stream for random_choice ************************/
/***************************************************/


ostream& operator<<(ostream& os, const random_choice& ts) {
//  os << to_iso_extended_string(ts.d) << " " << ts.price;
  os << ts.rand_choice  << " " << ts.last_date << " " << ts.last_price;
  return os;
}

/***************************************************/
/************* Input stream for random_choice************************/
/***************************************************/

istream& operator>> (istream& is, random_choice& ts) {
  is >> ts.last_date;
  is >> ts.last_price;
  is >> ts.rand_choice;
  return is;
}


