#ifndef SPUTIFY_VIEW_HPP
#define SPUTIFY_ARTIST_HPP
#define SPUTIFY_VIEW_HPP

#include <string>
#include <iostream>

using namespace std;

const string RESOPNSE_200_SUCCESS = "OK";
const string RESOPNSE_201_NO_RESOPNSE = "Empty";
const string RESOPNSE_400_BAD_REQUEST = "Bad request";
const string RESPONSE_403_FORBIDDEN = "Permission Denied";
const string RESOPNSE_404_NOT_FOUND = "Not Found";

class View {
public:
    View() = default;
    string showResponse(int statusCode);
};

#endif
