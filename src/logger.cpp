#include "logger.h"

void
Logger::logDecision(std::shared_ptr<Decision> d, std::shared_ptr<HashTable> t)
{
  if (!this->m_fileManager)
    return;
  return [t, d, this]() {
    std::string decision = d->getDecision();
    std::string explanation = d->getExplanation();
    int         decisionKey = decision.size();
    int         explanationKey = explanation.size();
    t->insert(decisionKey, decision);
    t->insert(explanationKey, explanation);
    if (decision.empty() || explanation.empty()) {
      throw std::runtime_error("empty decision/explanation. exitting...");
    }
    std::ofstream file(this->m_fileManager->getHomeDirectory() +
                           "/.decision_tracker/decisions.txt",
                       std::ios_base::app);

    std::time_t time = std::time(0);
    std::tm    *now = std::localtime(&time);

    if (file.is_open()) {
      file << "[" << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-'
           << now->tm_mday << " at " << now->tm_hour << ":" << now->tm_min
           << ":" << now->tm_sec << "]" << " " << t->get(decisionKey) << ":"
           << t->get(explanationKey) << '\n';
      file.close();
      std::cout << "decision logged successfully.\n";
    }
    t->remove(decisionKey);
    t->remove(explanationKey);
  }();
}

void
Logger::listDecisions(void)
{
  return [this]() mutable {
    std::ifstream file(this->m_fileManager->getHomeDirectory() +
                       "/.decision_tracker/decisions.txt");
    std::string   line{};
    int           count = 0;

    while (std::getline(file, line)) {
      ++count;
      std::cout << count << ". " << line << '\n';
    }

    std::cout << "total decisions: " << count << '\n';
  }();
}
