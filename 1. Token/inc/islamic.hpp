#pragma once
/*! \file	    islamic.hpp
	\brief	    Islamic class declaration
	\author	    Manh Khang Vu
	\date	    2026-04-28
	\copyright	Manh Khang Vu

  =============================================================
  Declarations of the Islamic classes derived from Calendar
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
	enum islamic_month_codes { Muharram = 1, Safar, RabialAwwal, RabiathThani, JumadalAwwal, JumadatTania, Rajab, Shaban, Ramadan, Shawwal, DhulQadah, DhulHijja };

	// Operations
	/*	\brief		Convert to Julian day from Islamic
		\param		year_t		- The Islamic year
					month_t		- The Islamic month
					day_t		- The Islamic day
					hour_t		- The hour of the day
					minute_t	- The minute of the hour
					second_t	- The second of the minute
		\return		jd_t		- The Julian day
	*/
	jd_t islamic_to_jd(year_t year, month_t month, day_t day,hour_t hour = hour_t(0), minute_t minute = minute_t(0), second_t second = second_t(0.0));

	/*	\brief		Convert to Islamic from Julian day
		\param		jd_t		- The Julian day
					year_t&		- The Islamic year
					month_t&	- The Islamic month
					day_t&		- The Islamic day
					hour_t&		- The hour of the day
					minute_t&	- The minute of the hour
					second_t&	- The second of the minute
	*/
	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);

	// Julian class
	class Islamic : public Calendar {
	public:
		using value_type = jd_t;
		DEF_POINTER_TYPE(Islamic)
	private:
		// Julian values
		year_t		year_{ -949 };
		month_t		month_{ Ramadan };
		day_t		day_{ 24 };
		hour_t		hour_{ 0 };
		minute_t	minute_{ 0 };
		second_t	second_{ 0.0 };

		// Operations
		/*	\brief		Convert to Julian day from Islamic
			\param		year_t		- The Islamic year
						month_t		- The Islamic month
						day_t		- The Islamic day
						hour_t		- The hour of the day
						minute_t	- The minute of the hour
						second_t	- The second of the minute
			\return		value_type	- The Julian day
		*/
		value_type to_jd() const { return islamic_to_jd(year_, month_, day_, hour_, minute_, second_); }

		/*	\brief		Convert to Islamic from Julian day
			\param		jd_t		- The Julian day
						year_t&		- The Islamic year
						month_t&	- The Islamic month
						day_t&		- The Islamic day
						hour_t&		- The hour of the day
						minute_t&	- The minute of the hour
						second_t&	- The second of the minute
		*/
		void from_jd(value_type jd) { jd_to_islamic(jd, year_, month_, day_, hour_, minute_, second_); }
	public:
		Islamic();
		Islamic(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second)
			: year_{ year }, month_{ month }, day_{ day }, hour_{ hour }, minute_{ minute }, second_{ second } {}
		Islamic(const Jd& jd);

		// Accessors
		constexpr year_t year() const { return year_; }
		constexpr month_t month() const { return month_; }
		constexpr day_t	day() const { return day_; }
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }

		// Implicit cast to Julian day
		operator Jd () const { return Jd(to_jd()); }
		
		// Assign and convert from Julian day to Islamic
		Islamic& operator = (const Jd& jd) {
			from_jd(jd.jd());
			return *this;
		}

		// Block some operators
		Islamic operator + (const detail::packaged_year_real&) = delete;
		Islamic operator - (const detail::packaged_year_real&) = delete;
		Islamic operator + (const detail::packaged_month_real&) = delete;
		Islamic operator - (const detail::packaged_month_real&) = delete;

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
	// Julian day of the start of the Islamic epoch
	constexpr jd_t ISLAMIC_EPOCH{ 1'948'439.5 };

	// Functions
	/*	\brief		Check if the year is a Islamic leap year
		\param		year_t	- The Islamic year
		\return		bool	- Whether the year is a leap year
	*/
	constexpr bool is_islamic_leapyear(year_t year) {
		return (11 * year + 14) % 30 < 11;
	}

	/*	\brief		Return the number of days in a Islamic month
		\param		month_t	- The Islamic month
					bool	- Whether the year is a leap year
		\return		day_t	- The number of days in the Islamic month
	*/
	constexpr day_t islamic_days_in_month(month_t month, bool isLeapYear) {
		if ((month % 2 == 1) || (month == 12 && isLeapYear))
			return 30;

		return 29;
	}

	/*	\brief		Return the name of the Islamic month
		\param		month_t		- The Islamic month
		\return		char const* - The name of the Islamic month
	*/
	constexpr char const* islamic_month_name(month_t month) {
		constexpr char const* const names[]{ "", "Muharram", "Safar", "Rabi'al-Awwal", "Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal", "Dhu I-Qa'da", "Dhu I-Hijja" };

		assert(month > 0);
		assert(month < 13);
		return names[month];
	}

	/*	\brief		Return the name of the Islamic day of the week
		\param		day_t		- The day of the week
		\return		char const*	- The Islamic name of the day
	*/
	constexpr char const* islamic_day_name(day_t day) {
		constexpr char const* names[7] = {
			"al-'ithnayn", "alth-thalatha", "al-'arb`a'", "al-khamis", "al-jum`a", "as-sabt", "al-'ahad"
		};
		assert(day >= 0);
		assert(day < 7);
		return names[day];
	}

	// Month addition/subtraction
	// Islamic + (integer month)
	Islamic operator + (const Islamic& date, const detail::packaged_month_integer& month);

	// Islamic - (integer month)
	inline Islamic operator - (const Islamic& date, const detail::packaged_month_integer& month) { return date + detail::packaged_month_integer(-month.months_); }

	// Year addition/subtraction
	// Islamic + (integer year)
	Islamic operator + (const Islamic& date, const detail::packaged_year_integer& year);

	// Julian - (integer year)
	inline Islamic operator - (const Islamic& date, const detail::packaged_year_integer& year) { return date + detail::packaged_year_integer(-year.years_); }
}	// End of namespace exprevaluator