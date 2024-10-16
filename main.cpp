#include "colour_logger.hpp"

int main() {
  Logger logger("SomeComponent: ");
  logger.logGreen(Logger::format("Name: %s, Age: %d", "Dave", 30));
  logger.logRed(Logger::format("Name: %s, Age: %d", "Dave", 30));
  logger.logYellow(Logger::format("Name: %s, Age: %d", "Dave", 30));
  logger.logRaw(Logger::format("Name: %s, Age: %d", "Dave", 30));
  return EXIT_SUCCESS;
}