#include "include.h"

class FileManager
{
public:
  FileManager() = default;
  ~FileManager() = default;

  std::string getHomeDirectory(void);
  bool setDirectory(const std::string &dir);
};
