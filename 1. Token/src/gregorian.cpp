/*! \file	    gregorian.cpp
	\brief	    Gregorian class definition
	\author	    Khang Vu
	\date	    2025-04-05
	\copyright	Khang Vu

  =============================================================
	Definition of the Gregorian classes derived from Operand class

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "../inc/gregorian.hpp"
#include <sstream>
#include <iomanip>
using namespace std;

namespace exprevaluator {
	// Gregorian default constructor
	Gregorian::Gregorian() {
		time_t now{ time(NULL) };
		struct tm tm_now;
		localtime_s(&tm_now, &now);

		year_ = year_t(tm_now.tm_year) + 1900;
		month_ = month_t(tm_now.tm_mon) + 1;
		day_ = day_t(tm_now.tm_mday);
		hour_ = hour_t(tm_now.tm_hour);
		minute_ = minute_t(tm_now.tm_min);
		second_ = second_t(tm_now.tm_sec);
	}

	// Gregorian constructor from Julian day
	Gregorian::Gregorian(const Jd& jd) {
		from_jd(jd.jd());
	}

	// Gregorian value
	[[nodiscard]] Gregorian::string_type Gregorian::str() const {
		ostringstream oss;
		oss << civil::day_name(day_of_week(to_jd())) << ", "
			<< gregorian_month_name(month_) << " "
			<< day_ << " "
			<< (year_ > 0 ? year_ : -year_ + 1) << " " << (year_ > 0 ? "AD" : "BC") << ", "
			<< (hour_ % 12 == 0 ? 12 : hour_ % 12) << ":"
			<< setfill('0') << setw(2) << minute_ << ":"
			<< setfill('0') << setw(2) << second_ << " "
			<< (hour_ < 12 ? "AM" : "PM");
		return oss.str();
	}

	// Month addition/subtraction
	// Gregorian + (integer month)
	Gregorian operator + (const Gregorian& date, const detail::packaged_month_integer& month) {
		year_t years{ date.year() + month.months_ / 12 };
		month_t months{ date.month() + month.months_ % 12 };

		int adjustment{ (months - 1) / 12 + (months - 12) / 12 };
		years += adjustment;
		months -= month_t(adjustment * 12);

		day_t days{ min(date.day(), civil::days_in_month(months, is_gregorian_leapyear(years))) };

		return Gregorian(years, months, days, date.hour(), date.minute(), date.second());
	}

	// Year addition/subtraction
	// Gregorian + (integer year)
	Gregorian operator + (const Gregorian& date, const detail::packaged_year_integer& year) {
		year_t years{ date.year() + year.years_ };
		month_t months{ date.month() };
		day_t days{ date.day() };

		if (months == 2 && days == 29 && !is_gregorian_leapyear(years)) {
			days = 28;
		}

		return Gregorian(years, months, days, date.hour(), date.minute(), date.second());
	}
}	// End of namespace exprevaluator