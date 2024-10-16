#pragma once

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>

class ColourLogger {
private:
  const std::string preface_;

  enum class Colour { Red, Green, Yellow, None };
  const std::map<Colour, std::string> colours_{ std::pair(Colour::None, "\033[0m"),
                                                std::pair(Colour::Green, "\033[32m"),
                                                std::pair(Colour::Red, "\033[31m"),
                                                std::pair(Colour::Yellow, "\033[33m") };

  auto log(std::string&& msg, Colour colour) -> void {
    auto full_msg =
        this->colours_.at(colour) + this->preface_ + msg + this->colours_.at(Colour::None);
    std::cout << full_msg << '\n';
  }

  template <typename T>
  static constexpr auto decayToCString(T&& arg) {
    if constexpr (std::is_same_v<std::decay_t<T>, std::string>) {
      return arg.c_str();
    } else {
      return std::forward<T>(arg);
    }
  }

public:
  explicit ColourLogger(std::string_view preface) : preface_(preface) {
  }

  void logRaw(std::string&& msg) {
    this->log(std::move(msg), Colour::None);
  }
  void logGreen(std::string&& msg) {
    this->log(std::move(msg), Colour::Green);
  }
  void logRed(std::string&& msg) {
    this->log(std::move(msg), Colour::Red);
  }
  void logYellow(std::string&& msg) {
    this->log(std::move(msg), Colour::Yellow);
  }

  template <typename... Args>
  static auto format(const char* format, Args... args) -> std::string {
    // Calculate the number of character that would be written, plus one for
    // null termination
    int size_s = snprintf(nullptr, 0, format, decayToCString(args)...) + 1;
    auto size = static_cast<size_t>(size_s);
    // Create a unique pointer to a character array of that size
    auto buf = std::make_unique<char[]>(size);
    // Write the formatted string to the allocated buffer
    snprintf(buf.get(), size, format, decayToCString(args)...);
    // Create a string using the a pointer to the bufer
    return { buf.get() };
  }
};
