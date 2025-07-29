
enum class Status
{
    200,
    201,
    400,
    403,
    404,
    429,
    500,
};

std::string status_string(Status error);
