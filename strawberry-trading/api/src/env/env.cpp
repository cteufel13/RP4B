#include <cstdlib>
#include <string>
#include <tuple>
#include <cassert>
#include <stdexcept>

#include <env/env.hpp>

std::string get_env_var(const std::string &env_var)
{
    const char *env_val = std::getenv(env_var.c_str());
    assert(env_val != nullptr);

    if (!env_val)
    {
        throw std::runtime_error(
            "Environment variable '" + env_var + "' is not set");
    }

    return std::string(env_val);
}

std::tuple<std::string, std::string> get_env_keys()
{

    // std::getenv is a C not CPP lib thats why string are const char*
    std::string public_key = get_env_var("ALPACA_PUBLIC");
    std::string private_key = get_env_var("ALPACA_PRIVATE");

    return {public_key, private_key};
}
