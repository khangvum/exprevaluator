#pragma once
/*! \file	    hebrew.hpp
	\brief	    Hebrew class declaration
	\author	    Manh Khang Vu
	\date	    2026-04-30
	\copyright	Manh Khang Vu

  =============================================================
  Declarations of the Hebrew classes derived from Calendar
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
	enum hebrew_month_codes { Nisan = 1, Iyyar, Sivan, Tammuz, Av, Elul, Tishri, Heshvan, Kislev, Teveth, Shevat, Adar, Veadar };

	// Operations
	/*	\brief		Convert to Julian day from Hebrew
		\param		year_t		- The Hebrew year
					month_t		- The Hebrew month
					day_t		- The Hebrew day
					hour_t		- The hour of the day
					minute_t	- The minute of the hour
					second_t	- The second of the minute
		\return		jd_t		- The Julian day
	*/
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day,hour_t hour = hour_t(0), minute_t minute = minute_t(0), second_t second = second_t(0.0));

	/*	\brief		Convert to Hebrew from Julian day
		\param		jd_t		- The Julian day
					year_t&		- The Hebrew year
					month_t&	- The Hebrew month
					day_t&		- The Hebrew day
					hour_t&		- The hour of the day
					minute_t&	- The minute of the hour
					second_t&	- The second of the minute
	*/
	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	// Hebrew class
	class Hebrew : public Calendar {
	public:
		using value_type = jd_t;
		DEF_POINTER_TYPE(Hebrew)
	private:
		year_t		year_{ -3759 };
		month_t		month_{ Tishri };
		day_t		day_{ 25 };
		hour_t		hour_{ 0 };
		minute_t	minute_{ 0 };
		second_t	second_{ 0.0 };

		// Operations
		/*	\brief		Convert to Julian day from Hebrew
			\param		year_t		- The Hebrew year
						month_t		- The Hebrew month
						day_t		- The Hebrew day
						hour_t		- The hour of the day
						minute_t	- The minute of the hour
						second_t	- The second of the minute
			\return		value_type	- The Julian day
		*/
		value_type to_jd() const { return hebrew_to_jd(year_, month_, day_, hour_, minute_, second_); }

		/*	\brief		Convert to Hebrew from Julian day
			\param		jd_t		- The Julian day
						year_t&		- The Hebrew year
						month_t&	- The Hebrew month
						day_t&		- The Hebrew day
						hour_t&		- The hour of the day
						minute_t&	- The minute of the hour
						second_t&	- The second of the minute
		*/
		void from_jd(value_type jd) { jd_to_hebrew(jd, year_, month_, day_, hour_, minute_, second_); }
	public:
		Hebrew();
		Hebrew(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
			: year_{ year }, month_{ month }, day_{ day }, hour_{ hour }, minute_{ minute }, second_{ second } {}
		Hebrew(const Jd& jd);

		// Accessors
		constexpr year_t year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t	day() const { return day_; }
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }

		// Implicit cast to Julian day
		operator Jd () const { return Jd(to_jd()); }
		
		// Assign and convert from Julian day to Hebrew
		Hebrew& operator = (const Jd& jd) {
			from_jd(jd.jd());
			return *this;
		}

		// Block some operators
		Hebrew operator + (const detail::packaged_year_real&) = delete;
		Hebrew operator - (const detail::packaged_year_real&) = delete;
		Hebrew operator + (const detail::packaged_month_real&) = delete;
		Hebrew operator - (const detail::packaged_month_real&) = delete;

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

	class HebrewNow : public Hebrew {
	public:
		HebrewNow() : Hebrew() {}
	};

	// Constants
	// Julian day of the start of the Hebrew epoch
	constexpr jd_t HEBREW_EPOCH{ 347'995.5 };

	// Functions
	/*	\brief		Check if the year is a Hebrew leap year
		\param		year_t	- The Hebrew year
		\return		bool	- Whether the year is a leap year
	*/
	inline bool is_hebrew_leapyear(year_t year) {
		return utility::mod(7 * year + 1, 19) < 7;
	}

	/*	\brief		Return the number of months in a Hebrew year
		\param		year_t	- The Hebrew year
		\return		month_t	- The number of months in the Hebrew year
	*/
	inline month_t hebrew_months_in_year(year_t year) {
		return is_hebrew_leapyear(year) ? 13 : 12;
	}

	/*	\brief		Return the delay of the start of a Hebrew year
		\param		year_t	- The Hebrew year
		\return		day_t	- The number of days to delay the start of the year
	*/
	inline day_t hebrew_delay_of_week(year_t year) {
		double months{ floor((235 * year - 234) / 19.0) };
		double parts{ 12'084 + 13'753 * months };
		double days{ 29 * months + floor(parts / 25'920) };

		if (utility::mod(3 * (days + 1), 7) < 3)
			++days;

		return static_cast<day_t>(days);
	}

	/*	\brief		Return the additional delay of adjacent Hebrew years
		\param		year_t	- The Hebrew year
		\return		day_t	- The number of days to adjust the year start (0, 1, or 2)
	*/
	inline day_t hebrew_delay_adjacent_year(year_t year) {
		day_t last{ hebrew_delay_of_week(year - 1) };
		day_t present{ hebrew_delay_of_week(year) };
		day_t next{ hebrew_delay_of_week(year + 1) };

		if (next - present == 356)
			return 2;
		else if (present - last == 382)
			return 1;

		return 0;
	}

	/*	\brief		Return the number of days in a Hebrew year
		\param		year_t	- The Hebrew year
		\return		day_t	- The number of days in the Hebrew year
	*/
	inline day_t hebrew_days_in_year(year_t year) {
		return hebrew_to_jd(year + 1, Tishri, 1) - hebrew_to_jd(year, Tishri, 1);
	}

	/*	\brief		Return the number of days in a Hebrew month
		\param		year_t	- The Hebrew year
					month_t	- The Hebrew month
		\return		day_t	- The number of days in the Hebrew month
	*/
	inline day_t hebrew_days_in_month(year_t year, month_t month) {
		switch (month) {
		case 2: case 4: case 6: case 10: case 13:
			return 29;
		case 12:
			return is_hebrew_leapyear(year) ? 30 : 29;
		case 8:
			return utility::mod(hebrew_days_in_year(year), 10) != 5 ? 29 : 30;
		case 9:
			return utility::mod(hebrew_days_in_year(year), 10) == 3 ? 29 : 30;
		default:
			return 30;
		}
	}

	/*	\brief		Return the name of the Hebrew month
		\param		month_t		- The Hebrew month
		\return		char const* - The name of the Hebrew month
	*/
	constexpr char const* hebrew_month_name(month_t month) {
		constexpr char const* const names[]{ "", "Nisan", "Iyyar", "Sivan", "Tammuz", "Av", "Elul", "Tishri", "Heshvan", "Kislev", "Teveth", "Shevat", "Adar", "Veadar" };

		assert(month > 0);
		assert(month < 14);
		return names[month];
	}

	// Month addition/subtraction
	// Hebrew + (integer month)
	Hebrew operator + (const Hebrew& date, const detail::packaged_month_integer& month);

	// Hebrew - (integer month)
	inline Hebrew operator - (const Hebrew& date, const detail::packaged_month_integer& month) { return date + detail::packaged_month_integer(-month.months_); }

	// Year addition/subtraction
	// Hebrew + (integer year)
	Hebrew operator + (const Hebrew& date, const detail::packaged_year_integer& year);

	// Julian - (integer year)
	inline Hebrew operator - (const Hebrew& date, const detail::packaged_year_integer& year) { return date + detail::packaged_year_integer(-year.years_); }
}	// End of namespace exprevaluator