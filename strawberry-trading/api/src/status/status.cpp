#include <status/status.hpp>

std::string status_string(Status status)
{
    switch (status)
    {
    case Status::OK:
        return "Status:200 OK";
    case Status::Created:
        return "Status:201 Order Created";
    case Status::BadRequest:
        return "Status:400 Bad Request";
    case Status::Forbidden:
        return "Status:403 Forbidden";
    case Status::NotFound:
        return "Status:404 Not Found";
    case Status::TooManyRequests:
        return "Status:429 Too Many Requests";
    case Status::InternalServerError:
        return "Status:500+ Internal Error";
    default:
        return "Unknown Status";
    }
}
