#ifndef __LOADERPOINT_HPP__
#define __LOADERPOINT_HPP__

#include <string>

class LoaderPoint{
protected:
public:
  
  LoaderPoint(){}
  ~LoaderPoint(){}
  
  int loadFile(std::string filename);
  
};

#endif // __LOADERPOINT_HPP__
