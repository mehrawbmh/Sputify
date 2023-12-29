#include "../headers/users_controller.hpp"

UsersController::UsersController()
{
    this->model = UsersModel();
}
void UsersController::signUp(string userName, string passWord)
{
    cout << view.showResponse(model.addNewUser(userName, passWord)) << endl;
}
