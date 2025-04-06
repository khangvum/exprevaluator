#pragma once
/*! \file	    time_of_day.hpp
	\brief	    Time of day utilities
	\author	    Khang Vu
	\date	    2025-04-05
	\copyright	Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "calendar.hpp"

namespace exprevaluator {
	// User-defined literals
	// - Convert an AM hour to military hour
	constexpr hour_t operator ""_AM(unsigned long long hours) {
		return static_cast<hour_t>(hours % 12);
	}
	constexpr hour_t operator ""_am(unsigned long long hours) {
		return static_cast<hour_t>(hours % 12);
	}

	// - Convert a PM hour to military hour
	constexpr hour_t operator ""_PM(unsigned long long hours) {
		return static_cast<hour_t>((hours % 12 + 12) % 24);
	}
	constexpr hour_t operator ""_pm(unsigned long long hours) {
		return static_cast<hour_t>((hours % 12 + 12) % 24);
	}

	// Constants
	// Seconds per day
	constexpr long long SECONDS_PER_DAY{ 86'400 };

	/*	\brief		Calculate the time of day from hours, minutes, and seconds
		\param		hour_t		- The hour of the day
					minute_t	- The minute of the hour
					second_t	- The second of the minute
		\return		tot_t		- The time of day
		*/
	constexpr tod_t tod(hour_t hours, minute_t minutes, second_t seconds) {
		return static_cast<tod_t>((hours * 3'600 + minutes * 60 + seconds) / SECONDS_PER_DAY);
	}
	/*	\brief		Calculate the time of day from Julian day
		\param		jd_t		- The Julian day
		\return		tod_t		- The time of day
	*/
	inline tod_t tod(jd_t jd) {
		return static_cast<tod_t>(jd + 0.5 - floor(jd + 0.5));
	}

	/*	\brief		Calculate the hours, minutes, and seconds from time of day
		\param		tod_t		- The time of day
					hour_t&		- The hour of the day
					minute_t&	- The minute of the hour
					second_t&	- The second of the minute
	*/
	inline void hms(tod_t tod, hour_t& hours, minute_t& minutes, second_t& seconds) {
		int seconds_in_day{ static_cast<int>(floor(tod * SECONDS_PER_DAY + 0.5)) };
		hours = static_cast<hour_t>(seconds_in_day / 3'600);
		minutes = static_cast<minute_t>((seconds_in_day / 60) % 60);
		seconds = static_cast<second_t>(seconds_in_day % 60);
	}
}	// End of namespace exprevaluator