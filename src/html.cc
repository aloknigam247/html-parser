#include "html.h"

#include <cstdio>

Html *Html::current_ = nullptr;
CURL *Html::handle_ = NULL;

Html::Html(const char *p_url) : url_(p_url) {
  if(!handle_)
    handle_ = curl_easy_init();
  
  curl_easy_setopt(handle_, CURLOPT_WRITEFUNCTION, curlCallback);
}

size_t Html::curlCallback(char *p_ptr, size_t p_size, size_t p_nemb, void *p_userdata) {
  if(!current_)
    return p_nemb;
  
  static int state = kOpenTag;
  static bool isTagName = false;
  static std::string temp_name,
                     ref_name,
                     ref_link;

  for(int i=0; i<p_nemb; ++i) {
    switch(state) {
      case kOpenTag:
          for( ; i<p_nemb && p_ptr[i] != '<'; ++i) ;
          state = kTagName;
          break;

      case kTagName:
          for( ; i<p_nemb; ++i) {
            
            if(p_ptr[i] == '!' || p_ptr[i] == '/') {
              state = kCloseTag;
              break;
            }

            else if(p_ptr[i] == '>') {
              state = kOpenTag;
              temp_name.clear();
              break;
            }
            
            else if(p_ptr[i] == ' ') {
              state = (temp_name == "a") ? kAttr : kCloseTag;
              temp_name.clear();
              break;
            }

            temp_name += p_ptr[i];
          }

          break;

      case kAttr:
          for( ; i<p_nemb; ++i) {
            
            if(p_ptr[i] == '>') {
              if(!temp_name.compare(0,5,"href=")) {
                state = kTagValue;
                ref_link = temp_name.substr(6, temp_name.length()-7);
              }
              else
                state = kOpenTag;

              temp_name.clear();
              break;
            }
            
            else if(p_ptr[i] == ' ') {
              if(!temp_name.compare(0,5,"href=")) {
                state = kGetValue;
                ref_link = temp_name.substr(6, temp_name.length()-7);
                temp_name.clear();
                break;
              }
              
              temp_name.clear();
              continue;
            }
            
            temp_name += p_ptr[i];
          }
          break;
          
      case kTagValue:
          for( ; i<p_nemb; ++i) {

            if(p_ptr[i] == '<') {
              if(temp_name.length() == 0) {
                state = kCheckEndTag;
                break;
              }
              else {
                state = kCloseTag;
                ref_name = std::move(temp_name);
                temp_name.clear();
                current_->refs_.push(std::make_pair(ref_name,ref_link));
                ref_name.clear();
                ref_link.clear();
                break;
              }
            }

            temp_name += p_ptr[i];
          }
          break;

      case kCloseTag:
          for( ; i<p_nemb && p_ptr[i] != '>'; ++i) ;
          state = kOpenTag;
          break;

      case kGetValue:
          for( ; i<p_nemb && p_ptr[i] != '>'; ++i) ;
          state = kTagValue;
          break;

      case kCheckEndTag:
          for( ; i<p_nemb && p_ptr[i] != '>'; ++i)
            temp_name += p_ptr[i];

          state = (temp_name == "/a") ? kOpenTag : kTagValue;
          temp_name.clear();
    }
 
  }
  return p_nemb;
}

void Html::retrieve() {
  current_ = this;
  CURLcode result;
  curl_easy_setopt(handle_, CURLOPT_URL, url_.c_str());
  result = curl_easy_perform(handle_);
}

const std::queue<std::pair<std::string, std::string>>& 
Html::get_all_refs() {
  return refs_;
}
