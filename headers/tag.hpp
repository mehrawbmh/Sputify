#ifndef SPUTIFY_TAG_HPP
#define SPUTIFY_TAG_HPP

#include <string>

using namespace std;

class Tag {
private:
    string title = "";
public:
    Tag(string name);
    Tag() = default;
    
    const string getTitle() const;
};

#endif //end SPUTIFY_TAG_HPP