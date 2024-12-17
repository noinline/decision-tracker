#include "decision.h"
#include "filemanager.h"
#include "hashtable.h"
#include "include.h"

class Logger
{
public:
  Logger(std::shared_ptr<FileManager> fileManager)
      : m_fileManager(std::move(fileManager))
  {}
  ~Logger() = default;

  void logDecision(std::shared_ptr<Decision> d, std::shared_ptr<HashTable> t);
  void listDecisions(void);

private:
  std::shared_ptr<FileManager> m_fileManager{};
};
