#include "colour_logger.hpp"

int main() {
  ColourLogger logger("SomeComponentName: ");
  logger.logRaw(ColourLogger::format("Name: %s, Age: %d", "Dave", 30));
  logger.logGreen(ColourLogger::format("Name: %s, Age: %d", "Dave", 30));
  logger.logRed(ColourLogger::format("Name: %s, Age: %d", "Dave", 30));
  logger.logYellow(ColourLogger::format("Name: %s, Age: %d", "Dave", 30));
  return EXIT_SUCCESS;
}