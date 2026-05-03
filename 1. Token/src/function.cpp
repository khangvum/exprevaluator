/*! \file	    function.cpp
	\brief	    Function class definitions
	\author	    Manh Khang Vu
	\date	    2025-01-06
	\copyright	Manh Khang Vu

  =============================================================
  Definitions of the Function classes derived from Operation
  class

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

#include "../inc/function.hpp"
#include "../inc/boolean.hpp"
#include "../inc/integer.hpp"
#include "../inc/real.hpp"
#include "../inc/variable.hpp"

#include "../inc/gregorian.hpp"
#include "../inc/julian.hpp"
#include "../inc/islamic.hpp"
#include "../inc/hebrew.hpp"
#include "../inc/vulcan.hpp"
#include "../inc/ymd.hpp"
using namespace std;

namespace exprevaluator {
	// Normalize the operands for functions
	void OneArgFunction::normalize(OperandStack& operand_stack) const {
		auto operand{ operand_stack.top() }; operand_stack.pop();
		if (!is<Variable>(operand)) {
			operand_stack.push(operand);
			return;
		}

		auto variable{ convert<Variable>(operand)->value() };
		if (!variable)
			throw runtime_error("Error: variable not initialized");
		operand_stack.push(variable);
	}

	void TwoArgFunction::normalize(OperandStack& operand_stack) const {
		array<Operand::pointer_type, 2> operands;
		bool is_real{ false };
		unsigned num_of_bools{ 0 };
		for (size_t i{ 0 }; i < operands.size(); ++i) {
			const size_t index{ operands.size() - 1 - i };
			operands[index] = operand_stack.top(); operand_stack.pop();

			// Get the values if the operand is Variable
			if (is<Variable>(operands[index])) {
				auto variable{ convert<Variable>(operands[index])->value() };
				if (!variable)
					throw runtime_error("Error: variable not initialized");

				operands[index] = variable;
			}

			if (is<Real>(operands[index]))
				is_real = true;
			else if (is<Boolean>(operands[index]))
				++num_of_bools;
		}

		if (num_of_bools == 1)
			throw runtime_error("Cannot convert");
		else if (is_real) {
			for (size_t i{ 0 }; i < operands.size(); ++i) {
				if (is<Integer>(operands[i]))
					operands[i] = convert<Operand>(make<Real>(value_of<Integer>(operands[i]).convert_to<Real::value_type>()));
			}
		}

		for (size_t i{ 0 }; i < operands.size(); ++i) {
			operand_stack.push(move(operands[i]));
		}
	}

	void ThreeArgFunction::normalize(OperandStack& operand_stack) const {
		array<Operand::pointer_type, 3> operands;
		array<string, 3> operand_names{ "Year", "Month", "Day" };
		for (size_t i{ 0 }; i < operands.size(); ++i) {
			const size_t index{ operands.size() - 1 - i };
			operands[index] = operand_stack.top(); operand_stack.pop();

			// Get the values if the operand is Variable
			if (is<Variable>(operands[index])) {
				auto variable{ convert<Variable>(operands[index])->value() };
				if (!variable)
					throw runtime_error("Error: variable not initialized");
				operands[index] = variable;
			}
		}
		for (size_t i{ 0 }; i < operands.size(); ++i) {
			if (!is<Integer>(operands[i]))
				throw runtime_error(operand_names[i] + " parameter is not an integer");

			operand_stack.push(move(operands[i]));
		}
	}

	// Calendar functions
	DEFINE_OPERATION(GregorianFunc, perform_calendar) {
		auto day{ static_cast<day_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();
		auto month{ static_cast<month_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();
		auto year{ static_cast<year_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();

		if (month < January || month > December)
			throw std::runtime_error("Month must be an integer in the range [1,12]");

		day_t days_in_month{ civil::days_in_month(month, is_gregorian_leapyear(year)) };
		if (day < 1 || day > days_in_month)
			throw std::runtime_error("Month of " + std::string(civil::month_name_long(month)) + " must be an integer in the range [1," + std::to_string(days_in_month) + "]");

		return convert<Operand>(make<Gregorian>(gregorian_to_jd(year, month, day)));
	}

	DEFINE_OPERATION(JulianFunc, perform_calendar) {
		auto day{ static_cast<day_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();
		auto month{ static_cast<month_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();
		auto year{ static_cast<year_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();

		if (month < January || month > December)
			throw std::runtime_error("Month must be an integer in the range [1,12]");

		day_t days_in_month{ civil::days_in_month(month, is_julian_leapyear(year)) };
		if (day < 1 || day > days_in_month)
			throw std::runtime_error("Month of " + std::string(civil::month_name_long(month)) + " must be an integer in the range [1," + std::to_string(days_in_month) + "]");

		return convert<Operand>(make<Julian>(julian_to_jd(year, month, day)));
	}

	DEFINE_OPERATION(IslamicFunc, perform_calendar) {
		auto day{ static_cast<day_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();
		auto month{ static_cast<month_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();
		auto year{ static_cast<year_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();

		if (month < 1 || month > DhulHijja)
			throw std::runtime_error("Month must be an integer in the range [1,12]");

		day_t days_in_month{ islamic_days_in_month(month, is_islamic_leapyear(year)) };
		if (day < 1 || day > days_in_month)
			throw std::runtime_error("Month of " + std::string(islamic_month_name(month)) + " must be an integer in the range [1," + std::to_string(days_in_month) + "]");

		return convert<Operand>(make<Islamic>(islamic_to_jd(year, month, day)));
	}

	DEFINE_OPERATION(HebrewFunc, perform_calendar) {
		auto day{ static_cast<day_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();
		auto month{ static_cast<month_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();
		auto year{ static_cast<year_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();

		month_t months_in_year{ hebrew_months_in_year(year) };
		if (month < Nisan || month > months_in_year)
			throw std::runtime_error("Month must be an integer in the range [1," + std::to_string(months_in_year) + "]");

		day_t days_in_month{ hebrew_days_in_month(year, month) };
		if (day < 1 || day > days_in_month)
			throw std::runtime_error("Month of " + std::string(hebrew_month_name(month)) + " must be an integer in the range [1," + std::to_string(days_in_month) + "]");

		return convert<Operand>(make<Hebrew>(hebrew_to_jd(year, month, day)));
	}

	DEFINE_OPERATION(VulcanFunc, perform_calendar) {
		auto day{ static_cast<day_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();
		auto month{ static_cast<month_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();
		auto year{ static_cast<year_t>(value_of<Integer>(operand_stack.top())) }; operand_stack.pop();

		if (month < Zat || month > Tasmeen)
			throw std::runtime_error("Month must be an integer in the range [1,12]");

		if (day < 1 || day > vulcan_days_in_month())
			throw std::runtime_error("Month of " + std::string(vulcan_month_name(month)) + " must be an integer in the range [1," + std::to_string(vulcan_days_in_month()) + "]");

		return convert<Operand>(make<Vulcan>(vulcan_to_jd(year, month, day)));
	}
}	// End of namespace exprevaluator