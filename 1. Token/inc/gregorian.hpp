#pragma once
/*! \file	    gregorian.hpp
	\brief	    Gregorian class declaration
	\author	    Khang Vu
	\date	    2025-04-02
	\copyright	Khang Vu

  =============================================================
  Declarations of the Gregorian classes derived from Operand 
  class

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


#include "operand.hpp"
#include "../../0. utilities/utilities.hpp"

namespace exprevaluator {
	// Operations
	/*	\brief		Convert to Julian date from Gregorian
		\param		year_t		- The Gregorian year
					month_t		- The Gregorian month
					day_t		- The Gregorian day
					hour_t		- The hour of the day
					minute_t	- The minute of the hour
					second_t	- The second of the minute
		\return		jd_t		- The Julian date
	*/
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day,hour_t hour = hour_t(0), minute_t minute = minute_t(0), second_t second = second_t(0.0));

	/*	\brief		Convert to Gregorian from Julian date
		\param		jd_t		- The Julian date
					year_t&		- The Gregorian year
					month_t&	- The Gregorian month
					day_t&		- The Gregorian day
					hour_t&		- The hour of the day
					minute_t&	- The minute of the hour
					second_t&	- The second of the minute
	*/
	void jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	// Gregorian class
	class Gregorian : public Operand {
	public:
		using value_type = jd_t;
		DEF_POINTER_TYPE(Gregorian)
	private:
		// Gregorian values
		year_t		year_{ -4713 };
		month_t		month_{ November };
		day_t		day_{ 24 };
		hour_t		hour_{ 0 };
		minute_t	minute_{ 0 };
		second_t	second_{ 0.0 };

		// Operations
		/*	\brief		Convert to Julian date from Gregorian
			\param		year_t		- The Gregorian year
						month_t		- The Gregorian month
						day_t		- The Gregorian day
						hour_t		- The hour of the day
						minute_t	- The minute of the hour
						second_t	- The second of the minute
			\return		value_type	- The Julian date
		*/
		value_type to_jd() const { return gregorian_to_jd(year_, month_, day_, hour_, minute_, second_); }

		/*	\brief		Convert to Gregorian from Julian date
			\param		jd_t		- The Julian date
						year_t&		- The Gregorian year
						month_t&	- The Gregorian month
						day_t&		- The Gregorian day
						hour_t&		- The hour of the day
						minute_t&	- The minute of the hour
						second_t&	- The second of the minute
		*/
		void from_jd(value_type jd) { jd_to_gregorian(jd, year_, month_, day_, hour_, minute_, second_); }
	public:
		Gregorian();
		Gregorian(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
			: year_{ year }, month_{ month }, day_{ day }, hour_{ hour }, minute_{ minute }, second_{ second } {}
		Gregorian(const Jd& jd);

		// Accessors
		constexpr year_t year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t	day() const { return day_; }
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }

		// Implicit cast to Julian day
		operator Jd () const { return Jd(to_jd()); }
		
		// Assign and convert from Julian day to Gregorian
		Gregorian& operator = (const Jd& jd) {
			from_jd(jd.jd());
			return *this;
		}

		// Block some operators
		Gregorian operator + (const detail::packaged_year_real&) = delete;
		Gregorian operator - (const detail::packaged_year_real&) = delete;
		Gregorian operator + (const detail::packaged_month_real&) = delete;
		Gregorian operator - (const detail::packaged_month_real&) = delete;

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

	// Gregorian Now class
	class Now : public Gregorian {
	public:
		Now() : Gregorian() {}
	};

	// User-defined literals
	// - Convert a Gregorian year AD to an astronomical Gregorian year
	constexpr year_t operator ""_AD(unsigned long long gregorian_year_AD) {
		return static_cast<year_t>(gregorian_year_AD);
	}
	constexpr year_t operator ""_ad(unsigned long long gregorian_year_AD) {
		return static_cast<year_t>(gregorian_year_AD);
	}

	// - Convert a Gregorian year BC to an astronomical Gregorian year
	constexpr year_t operator ""_BC(unsigned long long gregorian_year_BC) {
		return -static_cast<year_t>(gregorian_year_BC) + 1;
	}
	constexpr year_t operator ""_bc(unsigned long long gregorian_year_BC) {
		return -static_cast<year_t>(gregorian_year_BC) + 1;
	}

	// Constants
	// Julian date of the start of the Gregorian epoch
	constexpr jd_t GREGORIAN_EPOCH{ 1'721'425.5 };

	// Functions
	/*	\brief		Check if the year is a Gregorian leap year
		\param		year_t	- The Gregorian year
		\return		bool	- Whether the year is a leap year
	*/
	constexpr bool is_gregorian_leapyear(year_t year) {
		return (year % 400 == 0) || (year % 4 == 0) && (year % 100 != 0);
	}

	/*	\brief		Return the number of days in a Gregorian month
		\param		month_t	- The Gregorian month
					bool	- Whether the year is a leap year
		\return		day_t	- The number of days in the Gregorian month
	*/
	constexpr day_t gregorian_days_in_month(month_t month, bool isLeapYear) {
		return civil::days_in_month(month, isLeapYear);
	}

	/*	\brief		Return the name of the Gregorian month
		\param		month_t		- The Gregorian month
		\return		char const* - The name of the Gregorian month
	*/
	constexpr char const* gregorian_month_name(month_t month) {
		return civil::month_name_long(month);
	}

	/*	\brief		Return the short name of the Gregorian month
		\param		month_t		- The Gregorian month
		\return		char const* - The short name of the Gregorian month
	*/
	constexpr char const* gregorian_short_month_name(month_t month) {
		return civil::month_name_short(month);
	}

	// Month addition/subtraction
	// Gregorian + (integer month)
	Gregorian operator + (const Gregorian& date, const detail::packaged_month_integer& month);

	// Gregorian - (integer month)
	inline Gregorian operator - (const Gregorian& date, const detail::packaged_month_integer& month) { return date + detail::packaged_month_integer(-month.months_); }

	// Year addition/subtraction
	// Gregorian + (integer year)
	Gregorian operator + (const Gregorian& date, const detail::packaged_year_integer& year);

	// Gregorian - (integer year)
	inline Gregorian operator - (const Gregorian& date, const detail::packaged_year_integer& year) { return date + detail::packaged_year_integer(-year.years_); }
}	// End of namespace exprevaluator