#pragma once
/*! \file	    julian_day.hpp
	\brief	    Julian Day class declaration
	\author	    Khang Vu
	\date	    2025-04-02
	\copyright	Khang Vu

  =============================================================
  Declarations of the Julian Day class

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
	class Jd {
		jd_t	jd_;
	public:
		Jd();
		constexpr Jd(jd_t jd) : jd_{ jd } {}

		[[nodiscard]] constexpr jd_t jd() const { return jd_; }
	};

	// Relational operators
	constexpr auto operator <=> (const Jd& lhs, const Jd& rhs) { return lhs.jd() <=> rhs.jd(); }
	constexpr bool operator == (const Jd& lhs, const Jd& rhs) { return lhs.jd() == rhs.jd(); }

	// Difference
	constexpr auto operator - (const Jd& lhs, const Jd& rhs) { return lhs.jd() - rhs.jd(); }

	// Day of week
	/*	\brief		Return the day of the week based on the Julian day
		\param		Jd&		- The Julian day
		\return		day_t	- The day of the week
	*/
	inline day_t day_of_week(const Jd& jd) { return civil::day_of_week(jd.jd()); }

	// Day addition/subtraction
	namespace detail {
		struct packaged_day {
			day_t days_;
			constexpr packaged_day(day_t days) : days_{ days } {}
		};
	}
	constexpr detail::packaged_day days(day_t days) { return detail::packaged_day{ days }; }
	constexpr Jd operator + (const Jd& jd, detail::packaged_day days) { return Jd{ jd.jd() + days.days_ }; }
	constexpr Jd operator - (const Jd& jd, detail::packaged_day days) { return Jd{ jd.jd() - days.days_ }; }

	// Week addition/subtraction
	namespace detail {
		struct packaged_week {
			day_t days_;
			constexpr packaged_week(day_t days) : days_{ days } {}
		};
	}
	constexpr detail::packaged_week weeks(day_t days) { return detail::packaged_week{ days }; }
	constexpr Jd operator + (const Jd& jd, detail::packaged_week days) { return Jd{ jd.jd() + 7 * days.days_ }; }
	constexpr Jd operator - (const Jd& jd, detail::packaged_week days) { return Jd{ jd.jd() - 7 * days.days_ }; }

	// Month addition/subtraction
	namespace detail {
		struct packaged_month_integer {
			month_t months_;
			constexpr packaged_month_integer(month_t months) : months_(months) {}
		};
		struct packaged_month_real {
			double months_;
			constexpr packaged_month_real(double months) : months_(months) {}
		};
	};
	constexpr detail::packaged_month_real months(double months) { return detail::packaged_month_real(months); }
	constexpr detail::packaged_month_real months(float months) { return detail::packaged_month_real(months); }
	template <typename T> constexpr detail::packaged_month_integer months(T months) { return detail::packaged_month_integer(month_t(months)); }

	// Jd + (real months)
	constexpr Jd operator + (Jd const& date, detail::packaged_month_real const& month) {
		return Jd(date.jd() + month.months_ * EARTH_ORBITAL_PERIOD_DAYS);
	}
	// Jd - (real months)
	constexpr Jd operator - (Jd const& date, detail::packaged_month_real const& month) {
		return Jd(date.jd() - month.months_ * EARTH_ORBITAL_PERIOD_DAYS);
	}
	// Jd + (integer months)
	constexpr Jd operator + (Jd const& date, detail::packaged_month_integer const& month) {
		return Jd(date.jd() + month.months_ * EARTH_ORBITAL_PERIOD_DAYS);
	}
	// Jd - (integer months)
	constexpr Jd operator - (Jd const& date, detail::packaged_month_integer const& month) {
		return Jd(date.jd() - month.months_ * EARTH_ORBITAL_PERIOD_DAYS);
	}

	// Year addition/subtraction
	namespace detail {
		struct packaged_year_integer {
			year_t years_;
			constexpr packaged_year_integer(year_t years) : years_(years) {}
		};
		struct packaged_year_real {
			double years_;
			constexpr packaged_year_real(double years) : years_(years) {}
		};
	};
	// Wrap a double literal into a real year package.
	constexpr detail::packaged_year_real years(double years) { return detail::packaged_year_real(years); }
	// Wrap a float literal into a real year package.
	constexpr detail::packaged_year_real years(float years) { return detail::packaged_year_real(years); }
	// Wrap all other literals into an integer year package
	template<typename T> constexpr detail::packaged_year_integer years(T years) { return detail::packaged_year_integer(static_cast<year_t>(years)); }

	// Jd + (real years)
	constexpr Jd operator + (Jd const& date, detail::packaged_year_real const& year) {
		return Jd(date.jd() + year.years_ * EARTH_ORBITAL_PERIOD_DAYS);
	}
	// Jd - (real years)
	constexpr Jd operator - (Jd const& date, detail::packaged_year_real const& year) {
		return Jd(date.jd() - year.years_ * EARTH_ORBITAL_PERIOD_DAYS);
	}
	// Jd + (integer years)
	constexpr Jd operator + (Jd const& date, detail::packaged_year_integer const& year) {
		return Jd(date.jd() + year.years_ * EARTH_ORBITAL_PERIOD_DAYS);
	}
	// Jd - (integer years)
	constexpr Jd operator - (Jd const& date, detail::packaged_year_integer const& year) {
		return Jd(date.jd() - year.years_ * EARTH_ORBITAL_PERIOD_DAYS);
	}
}	// End of namespace exprevaluator