/*! \file	    julian_day.cpp
	\brief	    Julian Day class definition
	\author	    Khang Vu
	\date	    2025-04-05
	\copyright	Khang Vu

  =============================================================
  Declarations of the Julian Day class

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

#include "../inc/julian_day.hpp"
#include "../inc/time_of_day.hpp"
#include "../../1. Token/inc/gregorian.hpp"
#include <time.h>
using namespace std;

namespace exprevaluator {
	// Jd default constructor
	Jd::Jd() {
		time_t now{ time(nullptr) };
		struct tm tm_now;
		localtime_s(&tm_now, &now);

		jd_ = gregorian_to_jd(
			tm_now.tm_year + 1900,
			tm_now.tm_mon + 1,
			tm_now.tm_mday,
			tm_now.tm_hour,
			tm_now.tm_min,
			tm_now.tm_sec
		);
	}

	// Julian day from Gregorian
	namespace detail {
		jd_t gregorian_to_jd(year_t year, month_t month, day_t day) {
			long long a{ (14 - month) / 12 };
			long long y{ year + 4'800 - a };
			long long m{ month + 12 * a - 3 };
			return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32'045 - 0.5;
		}
	}
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds) {
		return detail::gregorian_to_jd(year, month, day) + tod(hour, minute, seconds);
	}

	// Gregorian from Julian day
	namespace detail {
		void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day) {
			jd = floor(jd - 0.5) + 0.5;
			long long a{ static_cast<long long>(jd + 0.5) + 32'044 };
			long long b{ (4 * a + 3) / 146'097 };
			long long c{ a - b * 146'097 / 4 };
			long long d{ (4 * c + 3) / 1'461 };
			long long e{ c - 1'461 * d / 4 };
			long long m{ (5 * e + 2) / 153 };
			day = static_cast<day_t>(e - (153 * m + 2) / 5 + 1);
			month = static_cast<month_t>(m + 3 - 12 * (m / 10));
			year = b * 100 + d - 4800 + m / 10;
		}
	}
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		detail::jd_to_gregorian(jd, year, month, day);
		hms(tod(jd), hour, minute, second);
	}
}	// End of namespace exprevaluator