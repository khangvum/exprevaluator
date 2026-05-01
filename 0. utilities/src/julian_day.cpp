/*! \file	    julian_day.cpp
	\brief	    Julian Day class definition
	\author	    Manh Khang Vu
	\date	    2025-04-05
	\copyright	Manh Khang Vu

  =============================================================
  Declarations of the Julian Day class

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.04.30
	  Added Gregorian data type

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Manh Khang Vu

  ============================================================= */

#include "../inc/julian_day.hpp"
#include "../inc/time_of_day.hpp"
#include "../../1. Token/inc/gregorian.hpp"
#include "../../1. Token/inc/julian.hpp"
#include "../../1. Token/inc/islamic.hpp"
#include "../../1. Token/inc/hebrew.hpp"
#include "../../1. Token/inc/vulcan.hpp"
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

#pragma region Gregorian
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
#pragma endregion

#pragma region Julian
	// Julian day from Julian
	namespace detail {
		jd_t julian_to_jd(year_t year, month_t month, day_t day) {
			long long a{ (14 - month) / 12 };
			long long y{ year + 4'800 - a };
			long long m{ month + 12 * a - 3 };
			return day + (153 * m + 2) / 5 + 365 * y + y / 4 - 32'083 - 0.5;
		}
	}
	jd_t julian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds) {
		return detail::julian_to_jd(year, month, day) + tod(hour, minute, seconds);
	}

	// Julian from Julian day
	namespace detail {
		void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day) {
			long long a{ static_cast<long long>(floor(jd + 0.5)) };
			long long b{ a + 1'524 };
			long long c{ static_cast<long long>(floor((b - 122.1) / 365.25)) };
			long long d{ static_cast<long long>(floor(365.25 * c)) };
			long long e{ static_cast<long long>(floor((b - d) / 30.6001)) };

			month = static_cast<month_t>((e < 14) ? e - 1 : e - 13);
			year = static_cast<year_t>((month > 2) ? c - 4'716 : c - 4'715);
			day = static_cast<day_t>(b - d - static_cast<long long>(30.6001 * e));
		}
	}
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		detail::jd_to_julian(jd, year, month, day);
		hms(tod(jd), hour, minute, second);
	}
#pragma endregion

#pragma region Islamic
	// Julian day from Islamic
	namespace detail {
		jd_t islamic_to_jd(year_t year, month_t month, day_t day) {
			long long a{ static_cast<long long>(ceil(29.5 * (month - 1))) };
			long long b{ 354 * (year - 1) };
			long long c{ static_cast<long long>(floor((3 + 11 * year) / 30.0)) };

			return day + a + b + c + ISLAMIC_EPOCH - 1;
		}
	}
	jd_t islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds) {
		tod_t time_of_day{ tod(hour, minute, seconds) };
		if (time_of_day >= 0.5)
			time_of_day -= 1;
		return detail::islamic_to_jd(year, month, day) + time_of_day;
	}

	// Islamic from Julian day
	namespace detail {
		void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day) {
			jd = floor(jd) + 0.5;

			year = floor((30 * (jd - ISLAMIC_EPOCH) + 10'646) / 10'631);
			month = std::min(static_cast<month_t>(ceil(((jd - (29 + islamic_to_jd(year, 1, 1))) / 29.5)) + 1), 12);
			day = jd - islamic_to_jd(year, month, 1) + 1;
		}
	}
	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		detail::jd_to_islamic(jd, year, month, day);
		hms(tod(jd), hour, minute, second);
	}
#pragma endregion

#pragma region Hebrew
	// Julian day from Hebrew
	namespace detail {
		jd_t hebrew_to_jd(year_t year, month_t month, day_t day) {
			assert(month >= 1 && "Minimum month is Nisan = 1");
			assert(month <= 13 && "Maximum month is Veadar = 13");
			assert(day >= 1 && "Minimum day of the month is 1");
			assert(day <= 30 && "Maximum day of the month is 30");

			jd_t jdn{ HEBREW_EPOCH + hebrew_delay_of_week(year) + hebrew_delay_adjacent_year(year) + day + 1 };

			if (month < 7) {
				for (month_t m{ 7 }; m <= hebrew_months_in_year(year); ++m)
					jdn += hebrew_days_in_month(year, m);
				for (month_t m{ 1 }; m < month; ++m)
					jdn += hebrew_days_in_month(year, m);
			}
			else {
				for (month_t m{ 7 }; m < month; ++m)
					jdn += hebrew_days_in_month(year, m);
			}

			return jdn;
		}
	}
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds) {
		tod_t time_of_day{ tod(hour, minute, seconds) };
		if (time_of_day >= 0.5)
			time_of_day -= 1;
		return detail::hebrew_to_jd(year, month, day) + time_of_day;
	}

	// Hebrew from Julian day
	namespace detail {
		void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day) {
			jd = floor(jd) + 0.5;

			// Year
			double count{ floor((jd - HEBREW_EPOCH) * 98'496 / 35'975'351) };
			year = static_cast<year_t>(count - 1);
			while (jd >= hebrew_to_jd(year + 1, 7, 1))
				++year;

			// Month
			month_t first{ jd < hebrew_to_jd(year, 1, 1) ? 7 : 1 };
			month = first;
			while (jd > hebrew_to_jd(year, month, hebrew_days_in_month(year, month)))
				++month;

			// Day
			day = static_cast<day_t>(floor(jd - hebrew_to_jd(year, month, 1) + 1));
		}
	}
	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		detail::jd_to_hebrew(jd, year, month, day);
		hms(tod(jd), hour, minute, second);
	}
#pragma endregion

#pragma region Vulcan
	// Julian day from Vulcan
	namespace detail {
		jd_t vulcan_to_jd(year_t year, month_t month, day_t day) {
			return VULCAN_EPOCH + (year - 1 + (month - 1) / 12.0 + (day - 1) / 252.0) * 266.4;
		}
	}
	jd_t vulcan_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t seconds) {
		const double h{ hour / 18.0 * EARTH_DAY_PER_VULCAN_DAY };
		const double m{ minute / (54.0 * 18.0) * EARTH_DAY_PER_VULCAN_DAY };
		const double s{ seconds / (54.0 * 54.0 * 18.0) * EARTH_DAY_PER_VULCAN_DAY };
		return detail::vulcan_to_jd(year, month, day) + h + m + s;
	}

	// Vulcan from Julian day
	namespace detail {
		void jd_to_vulcan(jd_t& jd, year_t& year, month_t& month, day_t& day) {
			jd = (jd - VULCAN_EPOCH) / 266.4;

			year = static_cast<year_t>(floor(jd) + 1);
			jd -= (year - 1);

			month = static_cast<month_t>(floor(jd * 12) + 1);
			jd -= (month - 1) / 12.0;

			day = static_cast<day_t>(floor(jd * 252) + 1);
			jd -= (day - 1) / 252.0;
		}
	}
	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		detail::jd_to_vulcan(jd, year, month, day);
		
		// Calculate the time of day
		tod_t tod{ jd * 252 };

		double total_hours{ tod * 18.0 };
		hour = static_cast<hour_t>(tod * 18.0);

		double remaining{ (total_hours - hour) * 54.0 }; // Vulcan hour has 54 minutes
		minute = static_cast<minute_t>(remaining);

		remaining = (remaining - minute) * 54.0; // Vulcan minute has 54 seconds
		second = static_cast<second_t>(remaining);
	}
#pragma endregion
}	// End of namespace exprevaluator