#include "include.h"

class HashTable
{
public:
  HashTable() = default;
  ~HashTable() = default;

  bool        insert(const int &key, const std::string &value);
  bool        remove(const int &key);
  std::string get(const int &key);

private:
  static const int                       m_groups = 128;
  std::list<std::pair<int, std::string>> m_table[m_groups];
  int                                    hashFunction(const int &key) const;
};
