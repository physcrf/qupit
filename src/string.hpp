#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <regex>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
using namespace std;

bool integerp (string& s)
{
  return regex_match (s, regex("[-+]?([1-9]+[0-9]*|0)"));
}

bool numberp (string& s)
{
  return regex_match (s, regex("[-+]?(0|[1-9][0-9]*)\\.([eEdD][-+]?(0|[1-9][0-9]*))?"))
    or regex_match (s, regex("[-+]?\\.[0-9]+([eEdD][-+]?(0|[1-9][0-9]*))?"))
    or regex_match (s, regex("[-+]?(0|[1-9][0-9]*)\\.[0-9]+([eEdD][-+]?(0|[1-9][0-9]*))?"))
    or regex_match (s, regex("[-+]?([1-9]+[0-9]*|0)([eEdD][-+]?(0|[1-9][0-9]*))?"));
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
  s = regex_replace (s, regex("[!#].*$"), "");
  
  // trim
  s = regex_replace (s, regex("^\\s*"), "");
  s = regex_replace (s, regex("\\s*$"), "");

  return s;
}

vector<string> split (string& s, string delim="\\s+")
{
  vector<string> v;
  const sregex_token_iterator end;
  regex re(delim.c_str());
  for (sregex_token_iterator iter(s.begin(), s.end(), re, -1);
       iter != end; ++iter)
    v.push_back(*iter);
  return v;
}

string abspath (string& s)
{
  string path;
  if (s[0] == '/')
    path = s;
  else
    {
      char buff[200];
      getcwd (buff, sizeof(buff));
      path = string(buff) + "/" + s;
    }
  path = regex_replace (path, regex("/+"), "/");
  path = regex_replace (path, regex("/(\\./)+"), "/");

  while (regex_search(path, regex("/\\w+/\\.{2}")))
    path = regex_replace (path, regex("/\\w+/\\.{2}"), "");
      
  return path;
}

int32_t stoi (string& s)
{
  return atoi (s.c_str());
}

double stof (string& s)
{
  return atof (s.c_str());
}
  
#endif	// STRING_HPP
