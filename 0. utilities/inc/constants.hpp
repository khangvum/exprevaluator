#pragma once
/*! \file	    constants.hpp
	\brief	    Useful constants
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include <Windows.h>

namespace exprevaluator {
	// === 1. Color constants ======================================
	//constexpr WORD GREY{ FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED };
	constexpr WORD WHITE{ FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY }; // FOREGROUND_INTENSITY | GREY
	constexpr WORD YELLOW{ FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY };
	constexpr WORD CYAN{ FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY };
	constexpr WORD GREEN{ FOREGROUND_GREEN | FOREGROUND_INTENSITY };
	constexpr WORD RED{ FOREGROUND_RED | FOREGROUND_INTENSITY };
	constexpr WORD INVERSE_WHITE{ BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY };
	constexpr WORD INVERSE_GREY{ BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED };
	constexpr WORD INVERSE_RED{ BACKGROUND_RED | BACKGROUND_INTENSITY };

	// === 2. Character constants in the codepage 850 ==============
	constexpr char copyright{ '\xB8' };
}	// End of namespace exprevaluator
