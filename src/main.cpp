#include <iostream>
#include "../headers/command_manager.hpp"
#include "../headers/client_exception.hpp"
 

using namespace std;

int main(int argc, char* argv[]) {
    cout << "running" << endl;
    Database *db = new Database();

    try {
        CommandManager::handle(argc, argv, db);    
    } catch(ClientException &exc) {
        View view;
        cout << exc.what();
        cout << view.showResponse(exc.getCode()) << endl;
    }

    cout << db->getAllUsers()[0]->getId();
    cout << "END\n";    
    return 0;
}
