#include <bits/stdc++.h>
#include "Welcome.h"
#include "createSurvey.h"
#include "AnswerSurvey.h"
#include "map"
using namespace std;

void clearScreen()
{
#ifdef _WIN32
    // For Windows
    system("cls");
#else
    // For Unix/Linux
    system("clear");
#endif
}

map<int, string> loadSurveyTitles();
string getUserChoiceForAnswering();
string getSurveyTitleByLineNumber();

int main()
{
    int userChoice;
    do
    {
        try
        {
            Welcome::greetUser();
            userChoice = Welcome::getUserChoice();
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << endl;
            return 1;
        }

        switch (userChoice)
        {
        case 1:
        {
            string title, topic;
            cin.ignore();
            cout << "Enter the title of the survey: ";
            getline(cin, title);
            cout << "Enter the topic of the survey: ";
            getline(cin, topic);
            cout << "The response for a question can be only of the following type : " << endl;
            cout << "Any rating between 1 to 5" << endl;
            Survey survey(title, topic);
            survey.createSurvey();
            ofstream fout("Surveys/" + title + ".txt");
            survey.storeSurvey(fout);
            fout.close();
            survey.appendSurveyTitle();
            cout << "Survey created successfully!" << endl;
            clearScreen();
            break;
        }
        case 2:
        {
            string title = getUserChoiceForAnswering();
            clearScreen();
            if (!title.empty())
            {
                AnswerSurvey answerSurvey(title);
                answerSurvey.answerSurvey();
                ofstream fout("Completed Surveys/" + title + ".txt");
                answerSurvey.storeAnswer(fout);
                fout.close();
                clearScreen();
            }
            else
            {
                cout << "Invalid choice. Survey not found." << endl;
            }
            break;
        }
        case 3:
            cout << "Exiting program" << endl;
            cout << "Thank you for using the Survey Management System!" << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (true);

    return 0;
}

map<int, string> loadSurveyTitles()
{
    ifstream fin("survey_titles.txt");
    string title;
    int lineNumber = 1;
    map<int, string> surveyMap;
    while (getline(fin, title))
    {
        surveyMap[lineNumber] = title;
        lineNumber++;
    }
    fin.close();
    return surveyMap;
}

string getSurveyTitleByLineNumber()
{
    map<int, string> surveyMap = loadSurveyTitles();
    int lineNumber;
    cout << "Enter the line number of the survey you want to answer: ";
    cin >> lineNumber;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (surveyMap.find(lineNumber) != surveyMap.end())
    {
        return surveyMap[lineNumber];
    }
    else
    {
        return "";
    }
}

string getUserChoiceForAnswering()
{
    ifstream fin("survey_titles.txt");
    string title;
    int serialNo = 1;

    cout << "List of available surveys: " << endl;

    while (getline(fin, title))
    {
        cout << serialNo << ". " << title << endl;
        serialNo++;
    }

    fin.close();

    cout << "Enter the title or serial number of the survey you want to answer: ";

    string userInput;
    getline(cin, userInput);

    // Check if the user entered a number
    if (all_of(userInput.begin(), userInput.end(), ::isdigit))
    {
        int selectedSerialNo = stoi(userInput);
        fin.open("survey_titles.txt");

        for (int i = 1; i <= selectedSerialNo; ++i)
        {
            getline(fin, title);
        }

        fin.close();
    }
    else
    {
        title = userInput;
    }

    return title;
}