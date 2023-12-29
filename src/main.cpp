#include <iostream>
#include "../headers/command_manager.hpp"
#include "../headers/client_exception.hpp"
 

using namespace std;

int main(int argc, char* argv[]) {
    cout << "running" << endl;
    try {
        CommandManager::handle(argc, argv);    
    } catch(ClientException &exc) {
        View view;
        cout << exc.what();
        cout << view.showResponse(exc.getCode()) << endl;
    }

    cout << "END\n";    
    return 0;
}
