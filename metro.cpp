#include <iostream>
#include "card_operations.h"
#include "graph_operations.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
vector<string> travelHistory; // stores past trips this session


void userLogin(string username) {
    int choice;
    vector<string> travelHistory; // stores past trips this session

    while (true) {
        cout << "\nWelcome to the Metro Path Finder, " << username << "!\n";
        cout << "***** Metro Rail Route Finder *****\n";
        cout << "1. Find Shortest Path (Dijkstra)\n";
        cout << "2. Find Most Economical Path\n";
        cout << "3. Find Fewest Stops Path (BFS)\n";
        cout << "4. Recharge Metro Card\n";
        cout << "5. View Travel History\n";
        cout << "0. Logout\nEnter choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Logging out. Goodbye!" << endl;
            break;
        }

        switch (choice) {
            case 1: {
                loadGraph1();
                travelHistory.push_back("Shortest Path trip");
                deductFare(username, 30.0); // flat fare for shortest path
                break;
            }
            case 2: {
                loadGraph2();
                travelHistory.push_back("Most Economical Path trip");
                deductFare(username, 20.0); // cheaper economical route
                break;
            }
            case 3: {
                loadGraph3();
                travelHistory.push_back("Fewest Stops (BFS) trip");
                deductFare(username, 25.0);
                break;
            }
            case 4:
                recharge(username);
                break;
            case 5:
                cout << "\n--- Travel History ---\n";
                if (travelHistory.empty()) {
                    cout << "No trips taken yet.\n";
                } else {
                    for (size_t i = 0; i < travelHistory.size(); i++)
                        cout << i + 1 << ". " << travelHistory[i] << "\n";
                }
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

int main() {
    int choice;
//beginning of menu driven options
    while (true) {
        cout << "1. Login " << endl;
        cout << "2. Sign up" << endl;
        cout<< "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }

        switch (choice) {
            case 1: {
                string username, password, info;
                cout << "Enter your username: ";
                cin >> username;
                cout << "Enter your password: ";
                cin >> password;
                //concatinating all the user info for easy comparison
                info= username + " " + password;

                //extraction of vectors inside the file
                ifstream inputFile("./usernames.txt");
                if (!inputFile.is_open()) {
                    std::cerr << "Error opening the file." << std::endl;
                    return 1;
                }
                vector<std::string> usernames;
                string line;
                while (std::getline(inputFile, line)) {
                    usernames.push_back(line);
                }
                inputFile.close();


                //implementig binary search to find info of the user in the vector
                int left = 0;
                int right = usernames.size() - 1;
                bool found = false;

                while (left <= right) {
                    int mid = (left + right) / 2;
                    if (usernames[mid] == info) {
                        found = true;
                        break;
                    } else if (usernames[mid] < info) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
                // POV: found yaaaayyyy
                if (found) {
                    std::cout << "Login successful!" << std::endl;
                    cout<<"Welcome "<<username<<"!"<<endl;
                    cout<<"Press 0 to logout at any point" << endl;
                    userLogin(username);
                } else {
                    std::cout << "Invalid username or password." << std::endl;
                }
                //closing file after use
                inputFile.close();
                break;
            }

            case 2: {
                string newUsername, newPassword;
                cout << "Enter new username: ";
                cin >> newUsername;
                cout << "Enter new password: ";
                cin >> newPassword;
                //concatinating all the user info for easy insertion and comparison
                string info= newUsername + " " + newPassword;
                ifstream inputFile("./usernames.txt");
                if (!inputFile.is_open()) {
                    std::cerr << "Error opening the file." << std::endl;
                    return 1;
                }
                //extracting all the users info from the file
                vector<std::string> usernames;
                string line;
                while (std::getline(inputFile, line)) {
                    usernames.push_back(line);
                }
                inputFile.close();

                // Find the insertion point for the new user info using binary search
                int left = 0;
                int right = usernames.size() - 1;
                int insertionPoint = -1;

                while (left <= right) {
                    int mid = (left + right) / 2;
                    if (usernames[mid] == info) {
                        std::cout << "Username already exists." << std::endl;
                        return 0;
                    } else if (usernames[mid] < info) {
                        left = mid + 1;
                        insertionPoint = mid + 1;
                    } else {
                        right = mid - 1;
                        insertionPoint = mid;
                    }
                }

                // Insert the new user info at the correct position in the vector
                if (insertionPoint == -1) {
                    usernames.insert(usernames.begin(), info);
                } else {
                    usernames.insert(usernames.begin() + insertionPoint, info);
                }

                // Write the sorted list of usernames into the file
                ofstream outputFile("./usernames.txt");
                if (!outputFile.is_open()) {
                    std::cerr << "Error opening the file for writing." << std::endl;
                    return 1;
                }
                for (const auto& username : usernames) {
                    outputFile << username << std::endl;
                }
                outputFile.close();

                std::cout << "New user added: " << newUsername << std::endl;
                break;
            }
            default:
                cout << "Invalid choice. Please enter a valid option (1-3)." << endl;
                continue;
        }
    }
    return 0;
}
