/*! \file	    system.cpp
	\brief	    System utilities
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

#include "../inc/system.hpp"
using namespace std;

namespace exprevaluator {
    CONSOLE_SCREEN_BUFFER_INFO csbi{ 0 };
    UINT codepage{ GetConsoleOutputCP() };
    size_t horizontal_width{};

    // === 1. Color functions ======================================
    void save_color() { GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); }

    void set_color(WORD attribute) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attribute); }

    void restore_color() { set_color(csbi.wAttributes); }

    // === 2. Codepage functions ===================================
    void restore_codepage() { SetConsoleOutputCP(codepage); }
}   // End of namespace exprevaluator