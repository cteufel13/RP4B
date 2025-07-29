#pragma once
#include <string>

enum class Status
{
    OK = 200,
    Created = 201,
    BadRequest = 400,
    Forbidden = 403,
    NotFound = 404,
    TooManyRequests = 429,
    InternalServerError = 500,
};

std::string status_string(Status error);
