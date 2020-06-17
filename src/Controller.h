#pragma once
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "BinaryTree.h"

class Controller
{
private:
    std::unique_ptr<BinaryTree> tree{nullptr};
    web::http::experimental::listener::http_listener listener;

public:
    Controller(/* args */) = default;
    ~Controller() = default;

    /**
     * @brief Methods which supports API request by the moment the only
     * two supported operations are GET (In order to get a common ancestor) 
     * and POST (used to populate a tree).
     * 
     * @param request http request.
     */
    void HandleGet(web::http::http_request request);
    void HandlePost(web::http::http_request request);

    void Start();
    void Stop();

private:
    std::vector<int> ProcessTreeBody(const std::string &requestBody);
    void PopulateTree(std::vector<int> &&nodes);
    std::pair<int, int> ProcessLCABody(const std::string &requestBody);
};