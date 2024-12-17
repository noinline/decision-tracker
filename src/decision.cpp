#include "decision.h"

void
Decision::setDecision(const std::string &d)
{
  return [this, d]() mutable { /* std::make_unique<>() is c++14 sadly :3 */
                               this->m_decision = std::unique_ptr<std::string>(
                                   new std::string(d));
  }();
}

void
Decision::setExplanation(const std::string &e)
{
  return [this,
          e]() mutable { /* not gonna lie this looks awful */
                         this->m_explanation =
                             std::unique_ptr<std::string>(new std::string(e));
  }();
}

std::string &
Decision::getDecision(void) const
{
  return *this->m_decision;
}

std::string &
Decision::getExplanation(void) const
{
  return *this->m_explanation;
}
