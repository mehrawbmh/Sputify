#include <iostream>
#include "../headers/command_manager.hpp"
#include "../headers/client_exception.hpp"
 
using namespace std;

int main(int argc, char* argv[]) {
    cout << "running" << endl;
    Database *db = new Database();

    CommandManager::handle(db);    

    cout << "END\n";    
    cout << db->getAllUsers()[db->getAllUsers().size() - 1]->getId();
    cout << db->getAllUsers()[db->getAllUsers().size() - 1]->getUsername();
    return 0;
}
