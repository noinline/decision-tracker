/* C++11 standard application that helps Me with logging My daily decisions.
 * Since I don't have opinion on some of them, it doesn't bothers Me much...
 * Yet I'm still curious on what's I've been deciding. */

#include <fstream>
#include <iostream>
#include <pwd.h>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

class Decision
{
public:
  std::string
  getDecision() const
  {
    return this->m_decision;
  }
  void
  setDecision(const std::string &d)
  {
    return [&]() { this->m_decision = d; }();
  }

  std::string
  getExplanation() const
  {
    return this->m_explanation;
  }
  void
  setExplanation(const std::string &e)
  {
    return [&]() { this->m_explanation = e; }();
  }

private:
  std::string m_decision{};
  std::string m_explanation{};
};

class FileManager
{
public:
  std::string
  getHomeDirectory()
  {
    struct passwd *pwd = getpwuid(static_cast<uid_t>(geteuid()));
    return (pwd != nullptr)
               ? std::string(pwd->pw_dir)
               : throw std::runtime_error("failed to get home directory.\n");
  }

  bool
  setDirectory(const std::string &dir)
  {
    /* this-> looks ugly but it's ok */
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
};

class Logger : public Decision
{
public:
  void
  logDecision(FileManager *fileManager)
  {
    if (!fileManager)
      return;
    return [&]() {
      std::ofstream file(fileManager->getHomeDirectory() +
                             "/.decision_tracker/decisions.txt",
                         std::ios_base::app);
      file << this->getDecision() << ":" << this->getExplanation() << '\n';
    }();
  }
};

int
main(int argc, char *argv[])
{
  if (isatty(STDOUT_FILENO) != 1)
    return 1;

  try {
    FileManager      *fileManager = new FileManager();
    Decision         *decision = new Decision();
    Logger           *logger = new Logger();
    const std::string dir =
        fileManager->getHomeDirectory() + "/.decision_tracker/";
    fileManager->setDirectory(dir);
    /*clang-format off*/
    std::cout << R"(
██████╗ ███████╗ ██████╗██╗███████╗██╗ ██████╗ ███╗   ██╗
██╔══██╗██╔════╝██╔════╝██║██╔════╝██║██╔═══██╗████╗  ██║
██║  ██║█████╗  ██║     ██║███████╗██║██║   ██║██╔██╗ ██║
██║  ██║██╔══╝  ██║     ██║╚════██║██║██║   ██║██║╚██╗██║
██████╔╝███████╗╚██████╗██║███████║██║╚██████╔╝██║ ╚████║
╚═════╝ ╚══════╝ ╚═════╝╚═╝╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝
                                                         
████████╗██████╗  █████╗  ██████╗██╗  ██╗███████╗██████╗ 
╚══██╔══╝██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝██╔══██╗
   ██║   ██████╔╝███████║██║     █████╔╝ █████╗  ██████╔╝
   ██║   ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝  ██╔══██╗
   ██║   ██║  ██║██║  ██║╚██████╗██║  ██╗███████╗██║  ██║
   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝
                                                         )"
              << '\n';
    /*clang-format on*/
    std::string decisionBuffer{};
    std::string explanationBuffer{};

    for (;;) {
      std::cout << "\n'log' to log a decision, "
                   "'list' to view "
                   "decisions, 'q' to quit: ";
      std::string command{};
      std::getline(std::cin, command);
      std::cout << '\n'; /* new line my beloved :w: */

      /* cancer method of doing things */
      if (command == "log") {
        std::cout << "enter decision: ";
        std::getline(std::cin, decisionBuffer);
        std::cout << "enter explanation: ";
        std::getline(std::cin, explanationBuffer);

        decision->setDecision(decisionBuffer);
        decision->setExplanation(explanationBuffer);

        logger->logDecision(fileManager);
        std::cout << "decision logged successfully.\n";
      } else if (command == "list") {
        std::ifstream file(fileManager->getHomeDirectory() +
                           "/.decision_tracker/decisions.txt");
        std::string   line{};
        int           count = 0;

        while (std::getline(file, line)) {
          ++count;
          std::cout << count << ". " << line << '\n';
        }

        std::cout << "total decisions: " << count << '\n';
      } else if (command == "q")
        break;
      else if (command != "q")
        std::cerr << "invalid command." << '\n';
    }
    /* delete */
    delete fileManager;
    delete logger;
    delete decision;
  } catch (const std::exception &e) {
    throw std::runtime_error(e.what());
    return 1;
  }

  return 0;
}
