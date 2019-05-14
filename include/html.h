#ifndef HTML_H
#define HTML_H

#include <queue>
#include <string>

#include "curl/curl.h"

/* HTML class that represents a HTML document. */
class Html {
private:
  static Html *current_;
  std::string url_;
  std::queue<std::pair<std::string, std::string>> refs_;

  static CURL *handle_;

  void findKey(int &p_i, int p_size, std::string p_key);

public:
  Html(const char *p_url);
  static size_t curlCallback(char *p_ptr, size_t p_size, size_t p_nmemb, void *p_userdata);
  void retrieve();
  const std::queue<std::pair<std::string, std::string>>& get_all_refs();
};

enum state {
  kOpenTag,
  kTagName,
  kAttr,
  kTagValue,
  kGetValue,
  kCloseTag,
  kCheckEndTag
};

#endif
