#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct User {
    std::string username;
    std::string password;
};

class UserManager {
private:
    std::vector<User> users;

public:
    UserManager() {
        loadUsersFromFile(); // Load existing users from file
    }


//signup 
    void signUp() {
        User newUser;
        std::cout << "Enter a new username: ";
        std::cin >> newUser.username;

        // Check if the username already exists
        if (userExists(newUser.username)) {
            std::cout << "Username already exists. Please choose a different one.\n";
            return;
        }

        std::cout << "Enter a password: ";
        std::cin >> newUser.password;

        users.push_back(newUser);
        saveUsersToFile(); // Save the new user to file

        std::cout << "Sign-up successful. You can now sign in.\n";
    }
//signin
    void signIn() {
        std::string username, password;
        std::cout << "Enter your username: ";
        std::cin >> username;

        // Check if the username exists
        auto it = std::find_if(users.begin(), users.end(), [&username](const User& user) {
            return user.username == username;
        });

        if (it != users.end()) {
            std::cout << "Enter your password: ";
            std::cin >> password;

            // Check the password
            if (it->password == password) {
                std::cout << "Sign-in successful. Welcome, " << username << "!\n";
            } else {
                std::cout << "Incorrect password. Sign-in failed.\n";
            }
        } else {
            std::cout << "Username not found. Sign-in failed.\n";
        }
    }

private:
    void loadUsersFromFile() {
        std::ifstream file("users.txt");

        if (file.is_open()) {
            User user;
            while (file >> user.username >> user.password) {
                users.push_back(user);
            }

            file.close();
        }
    }

    void saveUsersToFile() {
        std::ofstream file("users.txt");

        if (file.is_open()) {
            for (const auto& user : users) {
                file << user.username << " " << user.password << "\n";
            }

            file.close();
        }
    }

    bool userExists(const std::string& username) const {
        return std::any_of(users.begin(), users.end(), [&username](const User& user) {
            return user.username == username;
        });
    }
};

int main() {
    UserManager userManager;

    int choice;
    do {
        std::cout << "\nUser Authentication System\n";
        std::cout << "1. Sign Up\n";
        std::cout << "2. Sign In\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                userManager.signUp();
                break;
            case 2:
                userManager.signIn();
                break;
            case 3:
                std::cout << "Exiting User Authentication System. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }

    } while (choice != 3);

    return 0;
}
