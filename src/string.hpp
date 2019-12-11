#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <regex>
#include <vector>
using namespace std;

bool numberp (string& s)
{
  return regex_match (s, regex("[-+]?(0|[1-9][0-9]*)\\.([eEdD][-+]?(0|[1-9][0-9]*))?"))
    or regex_match (s, regex("[-+]?\\.[0-9]+([eEdD][-+]?(0|[1-9][0-9]*))?"))
    or regex_match (s, regex("[-+]?(0|[1-9][0-9]*)\\.[0-9]+([eEdD][-+]?(0|[1-9][0-9]*))?"))
    or regex_match (s, regex("[-+]?([1-9]+[0-9]*|0)([eEdD][-+]?(0|[1-9][0-9]*))?"));
}		    

bool integerp (string& s)
{
  return regex_match (s, regex("[-+]?([1-9]+[0-9]*|0)"));
}

bool boolp (string& s)
{
  if (s == "true" or s == "True" or s == "1" or
      s == "false" or s == "False" or s == "0")
    return true;
  return false;
}

bool truep (string& s)
{
  if (s == "true" or s == "True" or s == "1")
    return true;
  else
    return false;
}

bool blankp (string& s)
{
  return regex_match (s, regex("^\\s*$"));
}

string& trim (string& s)
{
  if (s.empty())
    return s;

  // remove comments
  regex_replace (s, regex("[!#].*$"), "");
  
  // trim
  regex_replace (s, regex("^\\s*"), "");
  regex_replace (s, regex("\\s*$"), "");

  return s;
}

vector<string> split (string& s, string delim="\\s+")
{
}
#endif	// STRING_HPP
