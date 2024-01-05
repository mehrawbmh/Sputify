#include <iostream>
#include "../headers/command_manager.hpp"
#include "../headers/client_exception.hpp"
 
using namespace std;

int main(int argc, char* argv[]) {
    Database *db = new Database();
    CommandManager* manager = new CommandManager(db); 
    
    manager->handle();    
    return 0;
}
