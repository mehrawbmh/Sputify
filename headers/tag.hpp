#ifndef SPUTIFY_TAG_HPP
#define SPUTIFY_TAG_HPP

#include <string>

using namespace std;

class Tag {
private:
    string title = "";

public:
    Tag(string name);
        
    string getTitle();
};

#endif //end SPUTIFY_TAG_HPP