#include "filemanager.h"

std::string
FileManager::getHomeDirectory(void)
{
  struct passwd *pwd = getpwuid(static_cast<uid_t>(geteuid()));
  return (pwd != nullptr)
             ? std::string(pwd->pw_dir)
             : throw std::runtime_error("failed to get home directory.\n");
}

bool
FileManager::setDirectory(const std::string &dir)
{
  /* this-> looks ugly too but it's ok */
  try {
    struct stat st
    {};
    if (stat(dir.c_str(), &st) == -1)
      return false;
    if (mkdir(dir.c_str(), 0700) == -1)
      return false;
    return true;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return false;
  }
}
