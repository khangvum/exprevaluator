/*! \file	    exprevaluator.cpp
	\brief	    Expression Evaluator application
    \author	    Khang Vu
    \date	    2025-01-06
    \copyright	Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
      Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "exprevaluator.hpp"
using namespace std;
<<<<<<< HEAD
using namespace exprevaluator;
=======
>>>>>>> origin/master

int main()
{
    // Print the title
    print_title();

    ExpressionEvaluator expression_evaluator;
    for (size_t count{ 0 }; ; ) {
        set_color(WHITE);       cout << " > ";
        set_color(RED);
        string command;
        if (!getline(cin, command) || command.empty())
            break;

        try {
            ExpressionEvaluator::result_type result{ expression_evaluator.evaluate(command) };
            set_color(WHITE);   cout << " [";
            set_color(GREEN);   cout << ++count; 
            set_color(WHITE);   cout << "] = ";
            set_color(CYAN);    cout << result << "\n\n";
            set_color(WHITE);
        }
        catch (const exception& e) {
            set_color(YELLOW);  cout << e.what() << "\n\n";
        }
    }
}