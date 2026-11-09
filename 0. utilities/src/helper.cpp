/*! \file	    helper.cpp
	\brief	    Helper utilities
	\author	    Manh Khang Vu
	\date	    2025-01-06
	\copyright	Manh Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2026.05.01
	  Added Julian, Islamic, Hebrew, and Vulcan data types

  Version 2025.04.30
	  Added Gregorian data type

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Manh Khang Vu

  ============================================================= */

#include "../inc/constants.hpp"
#include "../inc/helper.hpp"
#include "../inc/system.hpp"
#include <print>
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
		print(" Expression Evaluator 1.3.1 {}2025-2026, Manh Khang Vu ", copyright);
		set_color(WHITE); print("\n\n");
	}
}	// End of namespace exprevaluator