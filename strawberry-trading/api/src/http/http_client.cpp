#include <http/http_client.hpp>
#include <curl/curl.h>

HTTPClient::HTTPClient(const std::string &public_key, const std::string &private_key, bool paper_trading)
    : public_key(public_key), private_key(private_key)
{
    baseURL = paper_trading ? "https://paper-api.alpaca.markets/v2" : "https://api.alpaca.markets/v2";
};

static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string HTTPClient::makeRequest(const std::string &method, const std::string &endpoint, const std::string &body)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init(); // inits (This is CURL standard procedure)

    if (curl)
    {
        std::string url = baseURL + endpoint;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        struct curl_slist *headers = nullptr; // pointer to the headers strings, curl_slist appends creates LL?
        headers = curl_slist_append(headers, ("APCA-API-KEY-ID: " + public_key).c_str());
        headers = curl_slist_append(headers, ("APCA-API-SECRET-KEY: " + private_key).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // adds headers to CURL OP

        if (method == "POST") // PRELIM CURL prep to send POST
        {
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        }
        else if (method == "DELETE") // PRELIM CURL prep to send DELETE
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        }

        else if (method == "PUT")
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        }
        else if (method == "PATCH")
        {
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback); // gives it function to explain it how to read/write Callbacks
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);       // adds chunks of response to the readBuffer

        res = curl_easy_perform(curl);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
};

std::string HTTPClient::GET(const std::string &end_point)
{
    return makeRequest("GET", end_point);
};

std::string HTTPClient::POST(const std::string &end_point, const std::string &body)
{
    return makeRequest("POST", end_point, body);
};

std::string HTTPClient::DELETE(const std::string &end_point)
{
    return makeRequest("DELETE", end_point);
};

std::string HTTPClient::PATCH(const std::string &end_point, const std::string &body)
{
    return makeRequest("PATCH", end_point, body);
};

std::string HTTPClient::PUT(const std::string &end_point, const std::string &body)
{
    return makeRequest("PUT", end_point, body);
};
