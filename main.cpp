#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "./functions.h"

using namespace std;

string getDate(){
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    tm timeInfo = *localtime(&time);

    string date = to_string(timeInfo.tm_mday) + "/" + to_string(timeInfo.tm_mon + 1) + "/" + to_string(1900 + timeInfo.tm_year);
    return date;
}

string removeTrailingSpaces(const string &str) {
    size_t start = str.find_first_not_of(' ');
    size_t end = str.find_last_not_of(' ');

    if (start == std::string::npos) {
        // If the string is all spaces
        return "";
    }

    return str.substr(start, end - start + 1);
}

struct TasksWithProject
{
    string projectName;
    vector<string> tasks;
};

int main()
{
    const vector<string> GUIDELINES = {"Start with 'P ' to indicate In progress", "E to terminate",  "C to change the project name"};
    string heading = "Summary of " + getDate() + ":";
    heading = "*" + heading + "*";
    const string ending = "*CHECKOUT*";
    string punchWord = "*COMPLETED*";
    bool terminate = false;

    vector<TasksWithProject> tasksWithProject;

    cout << endl;
    cout << "Guidelines: " << endl;
    for(int i = 0; i < GUIDELINES.size(); i++){
        const string guideline = GUIDELINES[i];
        cout << "- " << guideline << endl;
    }
    cout << endl;

    while (!terminate)
    {
        TasksWithProject project;
        string projectName;
        vector<string> tasks;

        cout << "Enter the Project Name: ";
        getline(cin, projectName);
        cout << endl;

        if (projectName == "E")
        {
            break;
        }
        project.projectName = projectName;
        while (true)
        {
            string task;

            cout << "Enter Task: ";
            getline(cin, task);

            if (task == "E")
            {
                terminate = true;
                break;
            }
            else if (task == "C")
            {
                break;
            }
            project.tasks.push_back(task);
        }
        tasksWithProject.push_back(project);
    }

    if (!tasksWithProject.empty())
    {
        cout << "Generating..." << endl
             << endl;

        cout << heading;
        cout << endl
             << endl;
        string finalText = heading + "\n\n";
        for (int i = 0; i < tasksWithProject.size(); i++)
        {
            const TasksWithProject taskWithProject = tasksWithProject[i];
            string project = "";
            if(taskWithProject.projectName != ""){
                project = '*' + removeTrailingSpaces(taskWithProject.projectName) + ":*";
            }
            const vector<string> tasks = taskWithProject.tasks;

            finalText += project + '\n';

            cout << project << endl;
            for (int i = 0; i < tasks.size(); i++)
            {
                string task = tasks[i];
                if (task == "")
                {
                    continue;
                }
                if (task[0] == 'P' & task[1] == ' ')
                {
                    punchWord = "IN PROGRESS";
                    task = task.substr(2); // removes the portion that indicates that this task is in progress
                }

                cout << punchWord << " " << task << endl;
                finalText += punchWord + " " + task + "\n";
            }
            if (i < tasksWithProject.size())
            {
                cout << endl;
            }
        }

        cout << endl;
        cout << ending;
        finalText += "\n" + ending;
        copyToClipboard(finalText);
    }

    return 0;
}
