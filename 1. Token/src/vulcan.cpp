/*! \file	    vulcan.cpp
	\brief	    Vulcan class definition
	\author	    Manh Khang Vu
	\date	    2026-04-26
	\copyright	Manh Khang Vu

  =============================================================
  Definition of the Vulcan classes derived from Calendar class

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

#include "../inc/vulcan.hpp"
#include "../inc/gregorian.hpp"
#include "../inc/boolean.hpp"
#include "../inc/integer.hpp"
#include "../inc/ymd.hpp"
#include <sstream>
#include <iomanip>
using namespace std;

namespace exprevaluator {
	// Vulcan default constructor
	Vulcan::Vulcan() {
		time_t now{ time(NULL) };
		struct tm tm_now;
		localtime_s(&tm_now, &now);

		year_ = year_t(tm_now.tm_year) + 1900;
		month_ = month_t(tm_now.tm_mon) + 1;
		day_ = day_t(tm_now.tm_mday);
		hour_ = hour_t(tm_now.tm_hour);
		minute_ = minute_t(tm_now.tm_min);
		second_ = second_t(tm_now.tm_sec);

		// Convert Gregorian to Julian day
		jd_t jd{ gregorian_to_jd(year_, month_, day_, hour_, minute_, second_) };

		// Convert Julian day to Vulcan
		from_jd(jd);
	}

	// Vulcan constructor from Julian day
	Vulcan::Vulcan(const Jd& jd) {
		from_jd(jd.jd());
	}

	// Vulcan value
	[[nodiscard]] Vulcan::string_type Vulcan::str() const {
		ostringstream oss;
		oss << vulcan_month_name(month_) << " "
			<< day_ << ", "
			<< year_ << " "
			<< hour_ << ":"
			<< setfill('0') << setw(2) << minute_ << ":"
			<< setfill('0') << setw(2) << second_;
		return oss.str();
	}

	// Day addition/subtraction
	// Vulcan + (integer day)
	Vulcan operator + (const Vulcan& date, detail::packaged_day days) {
		return Vulcan{ vulcan_to_jd(date.year(), date.month(), date.day(), date.hour(), date.minute(), date.second()) + days.days_ * EARTH_DAY_PER_VULCAN_DAY };
	}

	// Month addition/subtraction
	// Vulcan + (integer month)
	Vulcan operator + (const Vulcan& date, const detail::packaged_month_integer& month) {
		year_t years{ date.year() + month.months_ / 12 };
		month_t months{ date.month() + month.months_ % 12 };
		day_t days{ date.day() };

		return Vulcan(years, months, days, date.hour(), date.minute(), date.second());
	}

	// Year addition/subtraction
	// Vulcan + (integer year)
	Vulcan operator + (const Vulcan& date, const detail::packaged_year_integer& year) {
		year_t years{ date.year() + year.years_ };
		month_t months{ date.month() };
		day_t days{ date.day() };

		return Vulcan(years, months, days, date.hour(), date.minute(), date.second());
	}

	// 2. Binary operators
	// - Arithmetic
	DEFINE_OPERATION(Vulcan, perform_addition) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();

		auto vulcan_date{ Vulcan(value_of<Vulcan>(rhs)) };

		if (is<Calendar>(lhs))
			throw runtime_error("Operation cannot be performed on a Vulcan operand");
		else if (is<Year>(lhs))
			return convert<Operand>(make<Vulcan>((vulcan_date + value_of<Year>(lhs)).value()));
		else if (is<Month>(lhs))
			return convert<Operand>(make<Vulcan>((vulcan_date + value_of<Month>(lhs)).value()));
		else if (is<Day>(lhs))
			return convert<Operand>(make<Vulcan>((vulcan_date + value_of<Day>(lhs)).value()));
		else
			return convert<Operand>(make<Vulcan>((vulcan_date + detail::packaged_day(static_cast<day_t>(value_of<Integer>(lhs)))).value()));
	}
	DEFINE_OPERATION(Vulcan, perform_subtraction) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();

		auto vulcan_date{ Vulcan(value_of<Vulcan>(rhs)) };

		if (is<Calendar>(lhs))
			return convert<Operand>(make<Day>(static_cast<day_t>(value_of<Calendar>(lhs) - vulcan_date)));
		if (is<Year>(lhs))
			return convert<Operand>(make<Vulcan>((vulcan_date - value_of<Year>(lhs)).value()));
		else if (is<Month>(lhs))
			return convert<Operand>(make<Vulcan>((vulcan_date - value_of<Month>(lhs)).value()));
		else if (is<Day>(lhs))
			return convert<Operand>(make<Vulcan>((vulcan_date - value_of<Day>(lhs)).value()));
		else
			return convert<Operand>(make<Vulcan>((vulcan_date - detail::packaged_day(static_cast<day_t>(value_of<Integer>(lhs)))).value()));
	}

	// - Relational
	DEFINE_OPERATION(Vulcan, perform_equality) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) == value_of<Calendar>(rhs)));
	}
	DEFINE_OPERATION(Vulcan, perform_greater) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) > value_of<Calendar>(rhs)));
	}
	DEFINE_OPERATION(Vulcan, perform_greater_equal) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) >= value_of<Calendar>(rhs)));
	}
	DEFINE_OPERATION(Vulcan, perform_inequality) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) != value_of<Calendar>(rhs)));
	}
	DEFINE_OPERATION(Vulcan, perform_less) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) < value_of<Calendar>(rhs)));
	}
	DEFINE_OPERATION(Vulcan, perform_less_equal) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) <= value_of<Calendar>(rhs)));
	}
}	// End of namespace exprevaluator