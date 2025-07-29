#pragma once

#include <string>
#include <map>
#include <optional>

class HTTPClient
{
public:
    HTTPClient(const std::string &public_key, const std::string &private_key, const std::string &baseurl);

    std::string GET(const std::string &end_point,
                    const std::optional<std::string> &body = "");

    std::string POST(const std::string &end_point,
                     const std::string &body);

    std::string PUT(const std::string &end_point,
                    const std::string &body);

    std::string PATCH(const std::string &end_point,
                      const std::string &body);

    std::string DELETE(const std::string &end_point);

private:
    std::string baseURL;
    std::string public_key;
    std::string private_key;

    std::string makeRequest(const std::string &method, const std::string &endpoint, const std::optional<std::string> &body = "", const std::optional<std::string> &parameters = "");
};
