#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string title;
    bool completed;
    int difficulty; // 1 = easy, 2 = medium, 3 = hard
};

void showMenu() {
    cout << "\n--- TO DO LIST (Murat.01)---\n";
    cout << "1. Add task\n";
    cout << "2. Show tasks\n";
    cout << "3. Mark task as completed\n";
    cout << "4. Delete task\n";
    cout << "5. Energy mode (recommend tasks)\n";
    cout << "6. Exit\n";
    cout << "Choose option: ";
}

string diffToText(int d) {
    if (d == 1) return "Easy";
    if (d == 2) return "Medium";
    return "Hard";
}

void showTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "Task list is empty.\n";
        return;
    }

    for (int i = 0; i < (int)tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].title
             << " (" << diffToText(tasks[i].difficulty) << ")";

        if (tasks[i].completed) cout << " [DONE]";
        cout << endl;
    }
}

void energyMode(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to recommend.\n";
        return;
    }

    int energy;
    cout << "Enter your energy level (1-10): ";
    cin >> energy;

    int targetDiff;
    if (energy <= 3) targetDiff = 1;
    else if (energy <= 7) targetDiff = 2;
    else targetDiff = 3;

    cout << "\nRecommended tasks for energy " << energy
         << " (" << diffToText(targetDiff) << "):\n";

    bool found = false;
    for (int i = 0; i < (int)tasks.size(); i++) {
        if (!tasks[i].completed && tasks[i].difficulty == targetDiff) {
            cout << "- " << tasks[i].title << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No tasks of this difficulty. Maybe do something else or add tasks.\n";
    }
}

int main() {
    vector<Task> tasks;
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            Task newTask;
            cout << "Enter task name: ";
            cin.ignore();
            getline(cin, newTask.title);

            cout << "Choose difficulty (1=Easy, 2=Medium, 3=Hard): ";
            cin >> newTask.difficulty;

            if (newTask.difficulty < 1 || newTask.difficulty > 3) {
                newTask.difficulty = 2; // default
                cout << "Wrong input, set to Medium.\n";
            }

            newTask.completed = false;
            tasks.push_back(newTask);
            cout << "Task added.\n";
        }

        else if (choice == 2) {
            showTasks(tasks);
        }

        else if (choice == 3) {
            int num;
            showTasks(tasks);
            cout << "Enter task number: ";
            cin >> num;

            if (num > 0 && num <= (int)tasks.size()) {
                tasks[num - 1].completed = true;
                cout << "Task marked as completed.\n";
            } else {
                cout << "Invalid number.\n";
            }
        }

        else if (choice == 4) {
            int num;
            showTasks(tasks);
            cout << "Enter task number to delete: ";
            cin >> num;

            if (num > 0 && num <= (int)tasks.size()) {
                tasks.erase(tasks.begin() + (num - 1));
                cout << "Task deleted.\n";
            } else {
                cout << "Invalid number.\n";
            }
        }

        else if (choice == 5) {
            energyMode(tasks);
        }

        else if (choice == 6) {
            cout << "Goodbye.\n";
            break;
        }

        else {
            cout << "Wrong option.\n";
        }
    }

    return 0;
}

