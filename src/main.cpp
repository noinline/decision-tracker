/* C++11 standard application that helps Me with logging My daily decisions.
 * Since I don't have opinion on some of them, it doesn't bothers Me much...
 * Yet I'm still curious on what's I've been deciding. */

/* toiletline :3 */
#define TOILETLINE_IMPLEMENTATION
#include "../lib/toiletline/toiletline.h"
#include "logger.h"

int
main(void)
{
  if (isatty(STDOUT_FILENO) != 1)
    return 1;

  if (tl_init() != TL_SUCCESS)
    throw std::runtime_error("toiletline: i frew up D:.\n");

  tl_set_title("decision tracker");
  tl_exit_raw_mode();

  try {
    std::shared_ptr<Decision>    decision = std::make_shared<Decision>();
    std::shared_ptr<HashTable>   table = std::make_shared<HashTable>();
    std::shared_ptr<FileManager> fileManager = std::make_shared<FileManager>();
    std::unique_ptr<Logger>      logger =
        std::unique_ptr<Logger>(new Logger(std::move(fileManager)));
    fileManager = std::shared_ptr<FileManager>(new FileManager());
    if (fileManager) {
      const std::string dir =
          fileManager->getHomeDirectory() + "/.decision_tracker/";
      fileManager->setDirectory(dir);
    } else
      throw std::runtime_error("fileManager explode \\|/.");
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
    std::string command{};
    std::string decisionBuffer{};
    std::string explanationBuffer{};
AGAIN:
    for (;;) {
      std::cout << "\n'log' to log a decision, "
                   "'list' to view "
                   "decisions, 'q' to quit: ";
      std::getline(std::cin, command);
      std::cout << '\n'; /* new line my beloved :w: */

      /* cancer method of doing things */
      if (command == "log") {
        std::cout << "enter decision: ";
        std::getline(std::cin, decisionBuffer);
        std::cout << "enter explanation: ";
        std::getline(std::cin, explanationBuffer);

        if (!decisionBuffer.empty() || !explanationBuffer.empty()) {
          decision->setDecision(std::move(decisionBuffer));
          decision->setExplanation(std::move(explanationBuffer));
        } else {
          std::cerr << "buffer is empty! try again." << '\n';
          goto AGAIN;
        }
        logger->logDecision(std::move(decision), std::move(table));
        decision = std::make_shared<Decision>();
        table = std::make_shared<HashTable>();
      } else if (command == "list")
        logger->listDecisions();
      else if (command == "q" || command == "q!")
        break;
      else if (command != "q")
        std::cerr << "invalid command " << "\"" << command << "\". "
                  << "try again!" << '\n';
      else if (command.empty())
        std::cerr << "command was empty. try again!" << '\n';
    }
  } catch (const std::exception &e) {
    throw std::runtime_error(e.what());
  }

  return 0;
}
