#include "FractionCPP.hpp"

arithmetica::Fraction::Fraction () {};
arithmetica::Fraction::Fraction (const std::string &numerator,
                                 const std::string &denominator)
{
  this->numerator = numerator;
  this->denominator = denominator;
}
arithmetica::Fraction::Fraction (const std::string &frac)
{
  std::string frac_str = frac;
  frac_str.erase (
      std::remove_if (frac_str.begin (), frac_str.end (), [] (char c) {
        return c == ' ' || c == '\t' || c == '\n';
      }));
  struct fraction cfrac = parse_fraction (frac_str.c_str ());
  this->numerator = cfrac.numerator;
  this->denominator = cfrac.denominator;
  delete_fraction (cfrac);
}
arithmetica::Fraction::Fraction (const char *frac)
{
  struct fraction cfrac = parse_fraction (frac);
  this->numerator = cfrac.numerator;
  this->denominator = cfrac.denominator;
  delete_fraction (cfrac);
}
arithmetica::Fraction::Fraction (const struct fraction &frac)
{
  numerator = frac.numerator;
  denominator = frac.denominator;
}

std::string
arithmetica::Fraction::to_string ()
{
  std::string answer = numerator;
  if (denominator != "1")
    answer += "/" + denominator;
  return answer;
}

/// @brief Adds two fractions.
/// @param n The right argument to be added to the left argument.
/// @return Where the addition will be stored.
arithmetica::Fraction
arithmetica::Fraction::operator+ (const Fraction &n)
{
  struct fraction i_1;
  struct fraction i_2;

  i_1.numerator = (char *)calloc (numerator.length () + 1, 1);
  i_1.denominator = (char *)calloc (denominator.length () + 1, 1);
  i_2.numerator = (char *)calloc (n.numerator.length () + 1, 1);
  i_2.denominator = (char *)calloc (n.denominator.length () + 1, 1);

  strcpy (i_1.numerator, numerator.c_str ());
  strcpy (i_1.denominator, denominator.c_str ());
  strcpy (i_2.numerator, n.numerator.c_str ());
  strcpy (i_2.denominator, n.denominator.c_str ());

  struct fraction result = add_fraction (i_1, i_2);
  delete_fraction (i_1);
  delete_fraction (i_2);

  Fraction answer (result.numerator, result.denominator);
  delete_fraction (result);

  return answer;
}

/// @brief Subtracts two fractions.
/// @param n The right argument to be subtracted from the left argument.
/// @return Where the subtraction will be stored.
arithmetica::Fraction
arithmetica::Fraction::operator- (const arithmetica::Fraction &n)
{
  struct fraction i_1;
  struct fraction i_2;

  i_1.numerator = (char *)calloc (numerator.length () + 1, 1);
  i_1.denominator = (char *)calloc (denominator.length () + 1, 1);
  i_2.numerator = (char *)calloc (n.numerator.length () + 1, 1);
  i_2.denominator = (char *)calloc (n.denominator.length () + 1, 1);

  strcpy (i_1.numerator, numerator.c_str ());
  strcpy (i_1.denominator, denominator.c_str ());
  strcpy (i_2.numerator, n.numerator.c_str ());
  strcpy (i_2.denominator, n.denominator.c_str ());

  struct fraction result = subtract_fraction (i_1, i_2);
  delete_fraction (i_1);
  delete_fraction (i_2);

  Fraction answer (result.numerator, result.denominator);
  delete_fraction (result);

  return answer;
}

/// @brief Multiplies two fractions.
/// @param n The right argument to be multiplied by the left argument.
/// @return Where the multiplication will be stored.
arithmetica::Fraction
arithmetica::Fraction::operator* (const Fraction &n)
{
  struct fraction i_1;
  struct fraction i_2;

  i_1.numerator = (char *)calloc (numerator.length () + 1, 1);
  i_1.denominator = (char *)calloc (denominator.length () + 1, 1);
  i_2.numerator = (char *)calloc (n.numerator.length () + 1, 1);
  i_2.denominator = (char *)calloc (n.denominator.length () + 1, 1);

  strcpy (i_1.numerator, numerator.c_str ());
  strcpy (i_1.denominator, denominator.c_str ());
  strcpy (i_2.numerator, n.numerator.c_str ());
  strcpy (i_2.denominator, n.denominator.c_str ());

  struct fraction result = multiply_fraction (i_1, i_2);
  delete_fraction (i_1);
  delete_fraction (i_2);

  Fraction answer (result.numerator, result.denominator);
  delete_fraction (result);

  return answer;
}

/// @brief Divides two fractions.
/// @param n The denominator of the division.
/// @return Where the division will be stored.
arithmetica::Fraction
arithmetica::Fraction::operator/ (const Fraction &n)
{
  struct fraction i_1;
  struct fraction i_2;

  i_1.numerator = (char *)calloc (numerator.length () + 1, 1);
  i_1.denominator = (char *)calloc (denominator.length () + 1, 1);
  i_2.numerator = (char *)calloc (n.denominator.length () + 1, 1);
  i_2.denominator = (char *)calloc (n.numerator.length () + 1, 1);

  strcpy (i_1.numerator, numerator.c_str ());
  strcpy (i_1.denominator, denominator.c_str ());
  strcpy (i_2.numerator, n.denominator.c_str ());
  strcpy (i_2.denominator, n.numerator.c_str ());

  struct fraction result = multiply_fraction (i_1, i_2);
  delete_fraction (i_1);
  delete_fraction (i_2);

  Fraction answer (result.numerator, result.denominator);
  delete_fraction (result);

  return answer;
}

bool
arithmetica::Fraction::operator== (const arithmetica::Fraction &n)
{
  if ((this->numerator == "-0" && n.numerator == "0")
      || (this->numerator == "0" && n.numerator == "-0"))
    return true;
  return this->numerator == n.numerator && this->denominator == n.denominator;
}

bool
arithmetica::operator== (const arithmetica::Fraction &LHS,
                         const arithmetica::Fraction &RHS)
{
  if ((LHS.numerator == "-0" && RHS.numerator == "0")
      || (LHS.numerator == "0" && RHS.numerator == "-0"))
    return true;
  return LHS.numerator == RHS.numerator && LHS.denominator == RHS.denominator;
}
bool
arithmetica::operator< (const arithmetica::Fraction &LHS,
                        const arithmetica::Fraction &RHS)
{
  // a < b if a - b < 0
  arithmetica::Fraction _LHS = LHS;
  arithmetica::Fraction subtraction = _LHS - RHS;
  return subtraction.numerator[0] == '-';
}
