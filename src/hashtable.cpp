#include "hashtable.h"

bool
HashTable::insert(const int &key, const std::string &value)
{
  int  index = hashFunction(key);
  auto begin = std::begin(m_table[index]);
  bool keyFound = false;
  for (/* no */; begin != std::end(m_table[index]); ++begin)
    if (begin->first == key) {
      /* replace old value once 'keyFound' */
      keyFound = true;
      begin->second = value;
      break;
    }
  if (!keyFound) /* set the value in that case */
    m_table[index].emplace_back(key, value);

  return true;
}

bool
HashTable::remove(const int &key)
{
  int  index = hashFunction(key);
  auto begin = std::begin(m_table[index]);
  for (/* no again */; begin != std::end(m_table[index]); ++begin)
    if (begin->first == key) {
      /* erase the value once key found */
      begin = m_table[index].erase(begin);
      return true;
    }

  return false;
}

std::string
HashTable::get(const int &key)
{
  int  index = hashFunction(key);
  auto begin = std::begin(m_table[index]);
  for (/* no AGAIN */; begin != std::end(m_table[index]); ++begin)
    if (begin->first == key)
      return begin->second; /* output the value once key found */

  return "";
}

int
HashTable::hashFunction(const int &key) const
{
  return key % m_groups;
}
