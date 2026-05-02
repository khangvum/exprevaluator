#pragma once
/*! \file	    julian.hpp
	\brief	    Julian class declaration
	\author	    Manh Khang Vu
	\date	    2026-04-26
	\copyright	Manh Khang Vu

  =============================================================
  Declarations of the Julian classes derived from Calendar
  class, including the subclasses:

		class Julian
			class JulianNow

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


#include "operand.hpp"
#include "calendar.hpp"
#include "../../0. utilities/utilities.hpp"

namespace exprevaluator {
	// Operations
	/*	\brief		Convert to Julian day from Julian
		\param		year_t		- The Julian year
					month_t		- The Julian month
					day_t		- The Julian day
					hour_t		- The hour of the day
					minute_t	- The minute of the hour
					second_t	- The second of the minute
		\return		jd_t		- The Julian day
	*/
	jd_t julian_to_jd(year_t year, month_t month, day_t day,hour_t hour = hour_t(0), minute_t minute = minute_t(0), second_t second = second_t(0.0));

	/*	\brief		Convert to Julian from Julian day
		\param		jd_t		- The Julian day
					year_t&		- The Julian year
					month_t&	- The Julian month
					day_t&		- The Julian day
					hour_t&		- The hour of the day
					minute_t&	- The minute of the hour
					second_t&	- The second of the minute
	*/
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	// Julian class
	class Julian : public Calendar {
	public:
		using value_type = jd_t;
		DEF_POINTER_TYPE(Julian)
	private:
		year_t		year_{ -4713 };
		month_t		month_{ November };
		day_t		day_{ 24 };
		hour_t		hour_{ 0 };
		minute_t	minute_{ 0 };
		second_t	second_{ 0.0 };

		// Operations
		/*	\brief		Convert to Julian day from Julian
			\param		year_t		- The Julian year
						month_t		- The Julian month
						day_t		- The Julian day
						hour_t		- The hour of the day
						minute_t	- The minute of the hour
						second_t	- The second of the minute
			\return		value_type	- The Julian day
		*/
		value_type to_jd() const { return julian_to_jd(year_, month_, day_, hour_, minute_, second_); }

		/*	\brief		Convert to Julian from Julian day
			\param		jd_t		- The Julian day
						year_t&		- The Julian year
						month_t&	- The Julian month
						day_t&		- The Julian day
						hour_t&		- The hour of the day
						minute_t&	- The minute of the hour
						second_t&	- The second of the minute
		*/
		void from_jd(value_type jd) { jd_to_julian(jd, year_, month_, day_, hour_, minute_, second_); }
	public:
		Julian();
		Julian(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
			: year_{ year }, month_{ month }, day_{ day }, hour_{ hour }, minute_{ minute }, second_{ second } {}
		Julian(const Jd& jd);

		// Accessors
		constexpr year_t year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t	day() const { return day_; }
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }

		// Implicit cast to Julian day
		operator Jd () const { return Jd(to_jd()); }
		
		// Assign and convert from Julian day to Julian
		Julian& operator = (const Jd& jd) {
			from_jd(jd.jd());
			return *this;
		}

		// Block some operators
		Julian operator + (const detail::packaged_year_real&) = delete;
		Julian operator - (const detail::packaged_year_real&) = delete;
		Julian operator + (const detail::packaged_month_real&) = delete;
		Julian operator - (const detail::packaged_month_real&) = delete;

		[[nodiscard]] value_type	value() const { return to_jd(); }
		[[nodiscard]] string_type	str() const override;

		// 2. Binary operators
		// - Arithmetic
		OVERRIDE_OPERATION(perform_addition)
		OVERRIDE_OPERATION(perform_subtraction)

		// - Relational
		OVERRIDE_OPERATION(perform_equality)
		OVERRIDE_OPERATION(perform_greater)
		OVERRIDE_OPERATION(perform_greater_equal)
		OVERRIDE_OPERATION(perform_inequality)
		OVERRIDE_OPERATION(perform_less)
		OVERRIDE_OPERATION(perform_less_equal)
	};

	// Julian Now class
	class JulianNow : public Julian {
	public:
		JulianNow() : Julian() {}
	};

	// Constants
	// Julian day of the start of the Julian epoch
	constexpr jd_t JULIAN_EPOCH{ 1'721'423.5 };

	// Functions
	/*	\brief		Check if the year is a Julian leap year
		\param		year_t	- The Julian year
		\return		bool	- Whether the year is a leap year
	*/
	constexpr bool is_julian_leapyear(year_t year) {
		return year % 4 == 0;
	}

	/*	\brief		Return the number of days in a Julian month
		\param		month_t	- The Julian month
					bool	- Whether the year is a leap year
		\return		day_t	- The number of days in the Julian month
	*/
	constexpr day_t julian_days_in_month(month_t month, bool isLeapYear) {
		return civil::days_in_month(month, isLeapYear);
	}

	/*	\brief		Return the name of the Julian month
		\param		month_t		- The Julian month
		\return		char const* - The name of the Julian month
	*/
	constexpr char const* julian_month_name(month_t month) {
		return civil::month_name_long(month);
	}

	/*	\brief		Return the short name of the Julian month
		\param		month_t		- The Julian month
		\return		char const* - The short name of the Julian month
	*/
	constexpr char const* julian_short_month_name(month_t month) {
		return civil::month_name_short(month);
	}

	// Month addition/subtraction
	// Julian + (integer month)
	Julian operator + (const Julian& date, const detail::packaged_month_integer& month);

	// Julian - (integer month)
	inline Julian operator - (const Julian& date, const detail::packaged_month_integer& month) { return date + detail::packaged_month_integer(-month.months_); }

	// Year addition/subtraction
	// Julian + (integer year)
	Julian operator + (const Julian& date, const detail::packaged_year_integer& year);

	// Julian - (integer year)
	inline Julian operator - (const Julian& date, const detail::packaged_year_integer& year) { return date + detail::packaged_year_integer(-year.years_); }
}	// End of namespace exprevaluator