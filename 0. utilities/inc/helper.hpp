#pragma once
/*! \file	    helper.hpp
	\brief	    Helper utilities
    \author	    Khang Vu
    \date	    2025-01-06
    \copyright	Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.04.30
	  Added Gregorian data type

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include <cmath>
#include <string>

namespace exprevaluator {
	/*	\brief		Print the title of the program
	*/
	void print_title();

	namespace utility {
		/*	\brief		Calculate the modulus of two real numbers
			\param		double	- The dividend
						double	- The divisor
			\return		double	- The result of the modulus
		*/
		inline double mod(double a, double b) { return a - b * floor(a / b); }

		/*	\brief		Determine the day of the week based on the Julian day
			\param		double	- The Julian day
			\return		double	- The day of the week
		*/
		inline double jwday(double j) { return mod(floor(j + 1.5), 7.0); }
	}	// End of namespace utility
}	// End of namespace exprevaluator