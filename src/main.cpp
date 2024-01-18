#include <iostream>

#include "../headers/command_manager.hpp"
#include "../headers/sputify.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Database *db = new Database();
    Sputify app(db);
    
    app.run(argc, argv);
    return 0;
}
