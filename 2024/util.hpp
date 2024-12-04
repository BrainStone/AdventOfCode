#pragma once

#include <functional>
#include <istream>
#include <memory>
#include <string>

using wrapped_istream = std::unique_ptr<std::istream, std::function<void(std::istream*)>>;

wrapped_istream open_input(const std::string& problem);
