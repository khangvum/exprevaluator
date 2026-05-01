#pragma once
/*! \file	    vulcan.hpp
	\brief	    Vulcan class declaration
	\author	    Manh Khang Vu
	\date	    2026-04-30
	\copyright	Manh Khang Vu

  =============================================================
  Declarations of the Vulcan classes derived from Calendar
  class

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


#include "operand.hpp"
#include "calendar.hpp"
#include "../../0. utilities/utilities.hpp"

namespace exprevaluator {
	enum vulcan_month_codes { Zat = 1, Druh, KriBrax, reTKhutai, TkeKhuti, Khuti, TaKrat, Krilior, etkhior, Tlakht, TkeTas, Tasmeen };

	// Operations
	/*	\brief		Convert to Julian day from Vulcan
		\param		year_t		- The Vulcan year
					month_t		- The Vulcan month
					day_t		- The Vulcan day
					hour_t		- The hour of the day
					minute_t	- The minute of the hour
					second_t	- The second of the minute
		\return		jd_t		- The Julian day
	*/
	jd_t vulcan_to_jd(year_t year, month_t month, day_t day,hour_t hour = hour_t(0), minute_t minute = minute_t(0), second_t second = second_t(0.0));

	/*	\brief		Convert to Vulcan from Julian day
		\param		jd_t		- The Julian day
					year_t&		- The Vulcan year
					month_t&	- The Vulcan month
					day_t&		- The Vulcan day
					hour_t&		- The hour of the day
					minute_t&	- The minute of the hour
					second_t&	- The second of the minute
	*/
	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	// Vulcan class
	class Vulcan : public Calendar {
	public:
		using value_type = jd_t;
		DEF_POINTER_TYPE(Vulcan)
	private:
		year_t		year_{ 9051 };
		month_t		month_{ Zat };
		day_t		day_{ 1 };
		hour_t		hour_{ 0 };
		minute_t	minute_{ 0 };
		second_t	second_{ 0.0 };

		// Operations
		/*	\brief		Convert to Julian day from Vulcan
			\param		year_t		- The Vulcan year
						month_t		- The Vulcan month
						day_t		- The Vulcan day
						hour_t		- The hour of the day
						minute_t	- The minute of the hour
						second_t	- The second of the minute
			\return		value_type	- The Julian day
		*/
		value_type to_jd() const { return vulcan_to_jd(year_, month_, day_, hour_, minute_, second_); }

		/*	\brief		Convert to Vulcan from Julian day
			\param		jd_t		- The Julian day
						year_t&		- The Vulcan year
						month_t&	- The Vulcan month
						day_t&		- The Vulcan day
						hour_t&		- The hour of the day
						minute_t&	- The minute of the hour
						second_t&	- The second of the minute
		*/
		void from_jd(value_type jd) { jd_to_vulcan(jd, year_, month_, day_, hour_, minute_, second_); }
	public:
		Vulcan();
		Vulcan(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
			: year_{ year }, month_{ month }, day_{ day }, hour_{ hour }, minute_{ minute }, second_{ second } {}
		Vulcan(const Jd& jd);

		// Accessors
		constexpr year_t year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t	day() const { return day_; }
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }

		// Implicit cast to Julian day
		operator Jd () const { return Jd(to_jd()); }
		
		// Assign and convert from Julian day to Vulcan
		Vulcan& operator = (const Jd& jd) {
			from_jd(jd.jd());
			return *this;
		}

		// Block some operators
		Vulcan operator + (const detail::packaged_year_real&) = delete;
		Vulcan operator - (const detail::packaged_year_real&) = delete;
		Vulcan operator + (const detail::packaged_month_real&) = delete;
		Vulcan operator - (const detail::packaged_month_real&) = delete;

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

	// Constants
	// Julian day of the start of the Vulcan epoch
	constexpr jd_t VULCAN_EPOCH{ 173'651.6 };
	constexpr double EARTH_DAY_PER_VULCAN_DAY{ 266.4 / 252.0 };

	// Functions
	/*	\brief		Return the number of days in a Vulcan month
		\param		year_t	- The Vulcan year
					month_t	- The Vulcan month
		\return		day_t	- The number of days in the Vulcan month
	*/
	constexpr day_t vulcan_days_in_month() {
		return 21;
	}

	/*	\brief		Return the name of the Vulcan month
		\param		month_t		- The Vulcan month
		\return		char const* - The name of the Vulcan month
	*/
	constexpr char const* vulcan_month_name(month_t month) {
		constexpr char const* const names[]{ "", "Z'at", "D'ruh", "K'riBrax", "re'T'Khutai", "T'keKhuti", "Khuti", "Ta'Krat", "K'ri'lior", "et'khior", "T'lakht", "T'ke'Tas", "Tasmeen" };;

		assert(month > 0);
		assert(month < 13);
		return names[month];
	}

	// Day addition/subtraction
	// Vulcan + (integer day)
	Vulcan operator + (const Vulcan& date, detail::packaged_day days);
	
	// Vulcan - (integer day)
	inline Vulcan operator - (const Vulcan& date, detail::packaged_day days) { return date + detail::packaged_day(-days.days_); }

	// Month addition/subtraction
	// Vulcan + (integer month)
	Vulcan operator + (const Vulcan& date, const detail::packaged_month_integer& month);

	// Vulcan - (integer month)
	inline Vulcan operator - (const Vulcan& date, const detail::packaged_month_integer& month) { return date + detail::packaged_month_integer(-month.months_); }

	// Year addition/subtraction
	// Vulcan + (integer year)
	Vulcan operator + (const Vulcan& date, const detail::packaged_year_integer& year);

	// Vulcan - (integer year)
	inline Vulcan operator - (const Vulcan& date, const detail::packaged_year_integer& year) { return date + detail::packaged_year_integer(-year.years_); }
}	// End of namespace exprevaluator