#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

class Logger {
private:
  enum class Colour { Red, Green, Yellow, None };

  const std::string preface_;
  const std::string RED_COLOUR = "\033[31m";
  const std::string GREEN_COLOUR = "\033[32m";
  const std::string YELLOW_COLOUR = "\033[33m";
  const std::string RESET = "\033[0m";

  std::string colour(Colour colour) {
    switch (colour) {
    case Colour::Green:
      return GREEN_COLOUR;
    case Colour::Yellow:
      return YELLOW_COLOUR;
    case Colour::Red:
      return RED_COLOUR;
    default:
      return RESET;
    }
  }

  auto log(std::string &&msg, Colour colour) -> void {
    std::cout << this->colour(colour) + this->preface_ + msg + RESET << '\n';
  }

  template <typename T> static constexpr auto decayToCString(T &&arg) {
    if constexpr (std::is_same_v<std::decay_t<T>, std::string>) {
      return arg.c_str();
    } else {
      return std::forward<T>(arg);
    }
  }

public:
  Logger(std::string_view preface) : preface_(preface) {}

  void logRaw(std::string &&msg) { this->log(std::move(msg), Colour::None); }
  void logGreen(std::string &&msg) { this->log(std::move(msg), Colour::Green); }
  void logRed(std::string &&msg) { this->log(std::move(msg), Colour::Red); }
  void logYellow(std::string &&msg) {
    this->log(std::move(msg), Colour::Yellow);
  }

  template <typename... Args>
  static std::string format(const char *format, Args... args) {
    // Calculate the number of character that would be written, plus one for
    // null termination
    int size_s = snprintf(nullptr, 0, format, decayToCString(args)...) + 1;
    auto size = static_cast<size_t>(size_s);
    // Create a unique pointer to a character array of that size
    auto buf = std::make_unique<char[]>(size);
    // Write the formatted string to the allocated buffer
    snprintf(buf.get(), size, format, decayToCString(args)...);
    // Create a string using the a pointer to the bufer
    return {buf.get()};
  }
};