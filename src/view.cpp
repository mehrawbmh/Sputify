#include "view.hpp"

string View::showResponse(int statusCode)
{
    switch (statusCode) {
    case 200:
        return RESOPNSE_200_SUCCESS;
    case 201:
        return RESOPNSE_201_NO_RESOPNSE;
    case 400:
        return RESOPNSE_400_BAD_REQUEST;
    case 403:
        return RESPONSE_403_FORBIDDEN;
    case 404:
        return RESOPNSE_404_NOT_FOUND;
    default:
        cout << "bad status code provided";
    }
}
