#include <iostream>
#include <string>
#include <cstring>
#include "html.h"

int main(int argc, char *argv[]) {
  std::cout << "HTML PARSER\n";
  
  if(argc < 2) {
    std::cerr << "URL Missing\n";
    return 1;
  }

  Html top_link(argv[1]);
  top_link.retrieve();
  auto refs = top_link.get_all_refs();
  while(!refs.empty()) {
    auto x = refs.front();
    std::cout << x.first << " --> " << x.second << '\n';
    refs.pop();
  }
  return 0;
}

