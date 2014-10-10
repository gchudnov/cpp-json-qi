#pragma once

#include "json_types.h"
#include <string>
#include <utility>
#include <stdexcept>

namespace jsonqi {

  class json_error
    : public std::runtime_error {
  public:
    typedef std::pair<size_t, size_t> position_type;

  private:
    size_t line_;
    size_t column_;

  public:
    json_error(const std::string& message)
      : runtime_error(message),
      line_(0),
      column_(0) {
    }

    json_error(const std::string& message, size_t line, size_t column)
      : runtime_error(message),
      line_(line),
      column_(column) {
    }

  public:
    size_t line() const {
      return line_;
    }

    size_t column() const {
      return column_;
    }

    position_type position() const {
      return std::make_pair(line_, column_);
    }
  };


} // namespace jsonqi
