#pragma once
/*! \file	    pseudo_operation.hpp
	\brief	    PseudoOperation class declarations
	\author	    Khang Vu
	\date	    2025-01-06
	\copyright	Khang Vu

  =============================================================
  Declarations of the PseudoOperation classes derived from 
  Token class, including the subclasses:

		class PseduoOperation
			class Parenthesis
				class LeftParenthesis
				class RightParenthesis
			class ArgumentSeparator

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2025.01.06
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include "token.hpp"

// PseudoOperation base class
class PseudoOperation : public Token {};

		// Parenthesis base class
		class Parenthesis : public PseudoOperation {};

				// LeftParenthesis class
				class LeftParenthesis : public Parenthesis {};

				// RightParenthesis class
				class RightParenthesis : public Parenthesis {};

		// ArgumentSeparator class
		class ArgumentSeparator : public PseudoOperation {};