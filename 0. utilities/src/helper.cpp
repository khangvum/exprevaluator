/*! \file	    helper.cpp
	\brief	    Helper utilities
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  Version 2025.04.30
	  Added Gregorian data type

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "../inc/constants.hpp"
#include "../inc/helper.hpp"
#include "../inc/system.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

namespace exprevaluator {
	void print_title() {
		// Save the current color
		save_color();
		atexit(restore_color);

		// Set the codepage to 850
		SetConsoleOutputCP(850);
		atexit(restore_codepage);

		set_color(INVERSE_GREY);
		cout << " Expression Evaluator 1.0.0 "s << copyright << "2025, Khang Vu "s;
		set_color(WHITE); cout << "\n\n";
	}
}	// End of namespace exprevaluator