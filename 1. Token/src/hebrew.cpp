/*! \file	    hebrew.cpp
	\brief	    Hebrew class definition
	\author	    Manh Khang Vu
	\date	    2026-04-26
	\copyright	Manh Khang Vu

  =============================================================
  Definition of the Hebrew classes derived from Calendar class

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

#include "../inc/hebrew.hpp"
#include "../inc/gregorian.hpp"
#include "../inc/boolean.hpp"
#include "../inc/integer.hpp"
#include "../inc/ymd.hpp"
#include <sstream>
#include <iomanip>
using namespace std;

namespace exprevaluator {
	// Hebrew default constructor
	Hebrew::Hebrew() {
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

		// Convert Julian day to Hebrew
		from_jd(jd);
	}

	// Hebrew constructor from Julian day
	Hebrew::Hebrew(const Jd& jd) {
		from_jd(jd.jd());
	}

	// Hebrew value
	[[nodiscard]] Hebrew::string_type Hebrew::str() const {
		ostringstream oss;
		oss << hebrew_month_name(month_) << " "
			<< day_ << " "
			<< year_ << ", "
			<< (hour_ % 12 == 0 ? 12 : hour_ % 12) << ":"
			<< setfill('0') << setw(2) << minute_ << ":"
			<< setfill('0') << setw(2) << second_ << " "
			<< (hour_ < 12 ? "AM" : "PM");
		return oss.str();
	}

	// Month addition/subtraction
	// Hebrew + (integer month)
	Hebrew operator + (const Hebrew& date, const detail::packaged_month_integer& month) {
		year_t years{ date.year() };
		month_t months{ date.month() };

		month_t months_to_add{ month.months_ };
		// Add months one by one to handle month length variations and leap years
		while (months_to_add > 0) {
			month_t months_in_year{ hebrew_months_in_year(years) };

			if (months == Elul) {
				months = Tishri;
				++years;
			}
			else if (months == months_in_year) {
				months = Nisan;
			}
			else {
				++months;
			}
			--months_to_add;
		}

		while (months_to_add < 0) {
			if (months == Tishri) {
				months = Elul;
				--years;

			}
			else if (months == Nisan) {
				months = hebrew_months_in_year(years);
			}
			else {
				--months;
			}
			++months_to_add;
		}

		day_t days{ min(date.day(), hebrew_days_in_month(years, months)) };

		return Hebrew(years, months, days, date.hour(), date.minute(), date.second());
	}

	// Year addition/subtraction
	// Hebrew + (integer year)
	Hebrew operator + (const Hebrew& date, const detail::packaged_year_integer& year) {
		year_t years{ date.year() + year.years_ };
		month_t months{ date.month() };

		// If the original month was Veadar (13) but the new year is not a leap year, adjust to Adar (12)
		if (months == Veadar && !is_hebrew_leapyear(years)) {
			months = Adar;
		}

		day_t days{ min(date.day(), hebrew_days_in_month(years, months)) };

		return Hebrew(years, months, days, date.hour(), date.minute(), date.second());
	}

	// 2. Binary operators
	// - Arithmetic
	DEFINE_OPERATION(Hebrew, perform_addition) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();

		auto hebrew_date{ Hebrew(value_of<Hebrew>(rhs)) };

		if (is<Calendar>(lhs))
			throw runtime_error("Operation cannot be performed on a Hebrew operand");
		else if (is<Year>(lhs))
			return convert<Operand>(make<Hebrew>((hebrew_date + value_of<Year>(lhs)).value()));
		else if (is<Month>(lhs))
			return convert<Operand>(make<Hebrew>((hebrew_date + value_of<Month>(lhs)).value()));
		else if (is<Day>(lhs))
			return convert<Operand>(make<Hebrew>((hebrew_date + value_of<Day>(lhs))));
		else
			return convert<Operand>(make<Hebrew>((hebrew_date + detail::packaged_day(static_cast<day_t>(value_of<Integer>(lhs))))));
	}
	DEFINE_OPERATION(Hebrew, perform_subtraction) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();

		auto hebrew_date{ Hebrew(value_of<Hebrew>(rhs)) };

		if (is<Calendar>(lhs))
			return convert<Operand>(make<Day>(static_cast<day_t>(value_of<Calendar>(lhs) - hebrew_date)));
		if (is<Year>(lhs))
			return convert<Operand>(make<Hebrew>((hebrew_date - value_of<Year>(lhs)).value()));
		else if (is<Month>(lhs))
			return convert<Operand>(make<Hebrew>((hebrew_date - value_of<Month>(lhs)).value()));
		else if (is<Day>(lhs))
			return convert<Operand>(make<Hebrew>((hebrew_date - value_of<Day>(lhs))));
		else
			return convert<Operand>(make<Hebrew>((hebrew_date - detail::packaged_day(static_cast<day_t>(value_of<Integer>(lhs))))));
	}

	// - Relational
	DEFINE_OPERATION(Hebrew, perform_equality) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) == value_of<Calendar>(rhs)));
	}
	DEFINE_OPERATION(Hebrew, perform_greater) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) > value_of<Calendar>(rhs)));
	}
	DEFINE_OPERATION(Hebrew, perform_greater_equal) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) >= value_of<Calendar>(rhs)));
	}
	DEFINE_OPERATION(Hebrew, perform_inequality) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) != value_of<Calendar>(rhs)));
	}
	DEFINE_OPERATION(Hebrew, perform_less) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) < value_of<Calendar>(rhs)));
	}
	DEFINE_OPERATION(Hebrew, perform_less_equal) {
		auto rhs{ operand_stack.top() }; operand_stack.pop();
		auto lhs{ operand_stack.top() }; operand_stack.pop();
		return convert<Operand>(make<Boolean>(value_of<Calendar>(lhs) <= value_of<Calendar>(rhs)));
	}
}	// End of namespace exprevaluator