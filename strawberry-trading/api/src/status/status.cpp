#include <status/status.hpp>

std::string status_string(Status status)
{
    switch (status)
    {
    case Status::200:
        return "Status:200 OK";
    case Status::201:
        return "Status:201 Order Created";
    case Status::400:
        return "Status:400 Bad Request";
    case Status::403:
        return "Status:403 Forbidden";
    case Status::404:
        return "Status:404 Not Found";
    case Status::429:
        return "Status:429 Too many Requests";
    case Status::500:
        return "Status:500+ Internal Error"
    };
}