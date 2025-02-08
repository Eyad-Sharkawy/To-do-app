#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string description;
    bool completed;
};

void saveTasksToFile(const vector<Task>& tasks, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task.description << "\n" << task.completed << "\n";
        }
        file.close();
        cout << "Tasks saved to file!\n";
    } else {
        cerr << "Error: Unable to save tasks to file.\n";
    }
}

void loadTasksFromFile(vector<Task>& tasks, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        tasks.clear();
        Task task;
        while (getline(file, task.description)) {
            file >> task.completed;
            file.ignore();
            tasks.push_back(task);
        }
        file.close();
        cout << "Tasks loaded from file!\n";
    } else {
        cerr << "No existing tasks file found. Starting with an empty list.\n";
    }
}


void printMenu() {
    cout << "\nTo-Do List Menu:\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Delete Task\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

void addTask (vector<Task>& tasks) {
    string description;
    cout << "What is your task?\n";
    cin.ignore();
    getline(cin, description);
    tasks.push_back({description, false});
    cout << "Task added\n";
}

void viewTasks (const vector<Task> &tasks) {
    if (tasks.empty()) {
        cout << "No tasks has been added yet\n";
    }
    else {
        for (int i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << tasks.at(i).description
                 << " [" << (tasks.at(i).completed? "Completed" : "Pending") << "] \n";
        }
    }
}

void markTask(vector<Task>& tasks) {

   if (!tasks.empty()) {
        int choice = 0;
        viewTasks(tasks);
        cout << "Enter the task number to mark as completed: ";
        cin >> choice;

        if (choice > 0 && choice <= tasks.size()) {
            tasks.at(choice - 1).completed = true;
            cout << "Task is marked as complete\n";
        }
        else {
           cout << "Invalid task number\n";
        }
    }
}

void deleteTask (vector<Task>& tasks) {
    if (!tasks.empty()) {
        int choice;
        viewTasks(tasks);
        cout << "Enter the task number to be deleted: ";
        cin >> choice;
        if (choice > 0 && choice <= tasks.size()) {
            tasks.erase(tasks.begin() + choice - 1);
            cout << "Task deleted\n";
        }
        else {
            cout << "Invalid task number\n";
        }
    }
}

int main() {
    vector<Task> tasks = {};
    const string filename = "tasks.txt";
    loadTasksFromFile(tasks, filename);

    int choice = 0;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
            break;

            case 2:
                viewTasks(tasks);
            break;

            case 3:
                markTask(tasks);
            break;
            case 4:
                deleteTask(tasks);
            break;
            case 5:
                cout << "Exiting...";
            break;
            default:
                cout << "Invalid input";
            break;
        }
    } while (choice != 5);

    saveTasksToFile(tasks, filename);

    return 0;
}