#include "common.h"
#include <iostream>
int call_cpp(const std::string& patha, const std::string &pathb) {
  std::cout << __FILE__ << ":" << __LINE__ << ":" 
            << "called from c++, path " << patha 
            << "," << pathb;
  return 0;
}