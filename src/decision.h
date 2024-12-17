#include "include.h"

class Decision
{
public:
  Decision() = default;
  ~Decision() = default;

  void         setDecision(const std::string &d);
  void         setExplanation(const std::string &e);
  std::string &getDecision(void) const;
  std::string &getExplanation(void) const;

private:
  std::unique_ptr<std::string> m_decision{};
  std::unique_ptr<std::string> m_explanation{};
};
