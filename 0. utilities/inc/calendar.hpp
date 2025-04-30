#pragma once
/*! \file	    calendar.hpp
	\brief	    Calendar utilities and type aliases
	\author	    Khang Vu
	\date	    2025-04-02
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

#include "helper.hpp"
#include <array>

namespace exprevaluator {
	// Define type aliases for calendar
	// - Hours, minutes, seconds
	using second_t = double;
	using minute_t = int;
	using hour_t = int;

	// - Time of day
	using tod_t = double;

	// - Day, month, year
	using day_t = int;
	using month_t = int;
	using year_t = long long;

	// - Julian date
	using jd_t = double;

	// Constants
	constexpr double EARTH_ORBITAL_PERIOD_DAYS = 365.256'363'004;

	namespace civil {
		namespace detail {
			constexpr std::array<std::array<day_t, 13>, 2> days_in_month = {
				0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
				0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
			};
		}	// End of namespace detail

		// Day functions
		/*	\brief		Return the name of the day
			\param		day_t		- The day of the week
			\return		char const*	- The name of the day
		*/
		constexpr char const* day_name(day_t day) {
			constexpr char const* days[7]{ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
			return days[day];
		}

		/*	\brief		Return the day of the week based on the Julian date
			\param		jd_t	- The Julian date
			\return		day_t	- The day of the week
		*/
		inline day_t day_of_week(jd_t jd) { return static_cast<day_t>(utility::mod(jd + 0.5, 7)); }

		/*	\brief		Return the number of days in a month
			\param		day_t		- The day of the week
			\return		char const*	- The name of the day
		*/
		constexpr day_t days_in_month(month_t month, bool is_leap_year) {
			return detail::days_in_month[is_leap_year][month];
		}

		// Month functions
		/*	\brief		Return the name of the month
			\param		month_t		- The month
			\return		char const*	- The name of the month
		*/
		constexpr char const* month_name_long(month_t month) {
			constexpr char const* const months[13] = {
				"",
				"January", "February", "March", "April", "May", "June",
				"July", "August", "September", "October", "November", "December"
			};
			return months[month];
		}

		/*	\brief		Return the short name of the month
			\param		month_t		- The month
			\return		char const*	- The short name of the month
		*/
		constexpr char const* month_name_short(month_t month) {
			constexpr char const* const months[13] = {
				"",
				"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
				"JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
			};
			return months[month];
		}
	}	// End of namespace civil

	// Constants
	enum civil_month_codes_long { January = 1, February, March, April, May, June, July, August, September, October, November, December };
	enum civil_month_codes_short { JAN = January, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
	enum civil_weekday_codes_long { Monday = 0, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
	enum civil_weekday_codes_short { MON = Monday, TUE, WED, THU, FRI, SAT, SUN };

	// Alternative queries
	template <class Calendar> inline year_t year(const Calendar& date) { return date.year(); }
	template <class Calendar> inline month_t month(const Calendar& date) { return date.month(); }
	template <class Calendar> inline day_t day(const Calendar& date) { return date.day(); }
	template <class Calendar> inline hour_t hour(const Calendar& date) { return date.hour(); }
	template <class Calendar> inline minute_t minute(const Calendar& date) { return date.minute(); }
	template <class Calendar> inline second_t second(const Calendar& date) { return date.second(); }
}	// End of namespace exprevaluator