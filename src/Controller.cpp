#include <codecvt>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "./Controller.h"

using namespace std;
using namespace web::http;
using namespace web::http::experimental::listener;

string convertWString(wstring objective)
{
    wstring_convert<codecvt_utf8_utf16<wchar_t>> convert;
    return convert.to_bytes(objective);
}

wstring convertString(string objective)
{
    wstring_convert<codecvt_utf8_utf16<wchar_t>> convert;
    return convert.from_bytes(objective);
}

void Controller::HandleGet(http_request request)
{
    ucout << request.to_string() << endl;
    try
    {
        auto leafs = ProcessLCABody(convertWString(request.extract_string().get())); //seems to be a wstring;
        if (tree == nullptr)
            throw logic_error("Empty tree");
        auto internalResponse = tree->FindCommonAncestor(leafs.first, leafs.second);
        auto response = web::json::value::object();
        response[U("ancestor")] = web::json::value::number(internalResponse);
        request.reply(status_codes::OK, response);
    }
    catch (const logic_error &e) // This includes the invalid_parameter exception
    {
        auto response = web::json::value::object();
        response[U("message")] = web::json::value::string(convertString(e.what()));
        request.reply(status_codes::BadRequest, response);
    }
    catch (const exception &e)
    {
        auto response = web::json::value::object();
        response[U("message")] = web::json::value::string(convertString(e.what()));
        request.reply(status_codes::InternalError, response);
    }
}

void Controller::HandlePost(http_request request)
{
    ucout << request.to_string() << endl;
    try
    {
        auto treeNodes = ProcessTreeBody(convertWString(request.extract_string().get())); //seems to be a wstring;
        PopulateTree(move(treeNodes));
        auto response = web::json::value::object();
        response[U("tree")] = web::json::value::string(convertString(tree->Traverse()));
        request.reply(status_codes::OK, response);
    }
    catch (const exception &e)
    {
        auto response = web::json::value::object();
        response[U("message")] = web::json::value::string(convertString(e.what()));
        request.reply(status_codes::InternalError, response);
    }
}

void Controller::Start()
{
    cout << " ================= OPENING HTTP SERVER =================" << endl;
    web::uri_builder uriBuilder(L"http://127.0.0.1:2777");
    listener = http_listener(uriBuilder.to_uri());
    listener.support(methods::GET, std::bind(&Controller::HandleGet, this, std::placeholders::_1));
    listener.support(methods::POST, std::bind(&Controller::HandlePost, this, std::placeholders::_1));

    listener.open().wait();
    cout << " ================ OPENING HTTP SERVER OK ================" << endl;
}

void Controller::Stop()
{
    listener.close();
}

vector<int> Controller::ProcessTreeBody(const string &requestBody)
{
    stringstream input(requestBody);
    string segment;
    vector<int> segmentList;

    while (getline(input, segment, ','))
    {
        segmentList.push_back(atoi(segment.c_str()));
    }

    return segmentList;
}

void Controller::PopulateTree(vector<int> &&nodes)
{
    // each time we create a new tree
    tree = make_unique<BinaryTree>();

    for (auto node : nodes)
    {
        tree->InsertNode(node);
    }
}

pair<int, int> Controller::ProcessLCABody(const string &requestBody)
{
    pair<int, int> inputValues;
    auto firstProcess = ProcessTreeBody(requestBody);
    inputValues.first = firstProcess.at(0);
    inputValues.second = firstProcess.at(1);
    return inputValues;
}