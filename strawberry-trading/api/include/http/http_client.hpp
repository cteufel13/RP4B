#pragma once

#include <string>
#include <map>

class HTTPClient
{
public:
    HTTPClient(const std::string &public_key, const std::string &private_key, bool paper_trading);

    std::string GET(const std::string &end_point);

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

    std::string makeRequest(const std::string &method, const std::string &endpoint, const std::string &body = "");
};
