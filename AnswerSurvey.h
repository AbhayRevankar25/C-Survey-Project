#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class AnswerSurveyBase
{
protected:
    string title;
    string topic;
    int noOfQuestions;

public:
    AnswerSurveyBase(string title)
        : title(title), topic(""), noOfQuestions(0) {}

    AnswerSurveyBase(string title, string topic)
        : title(title), topic(topic), noOfQuestions(0) {}

    virtual ~AnswerSurveyBase() {}

    virtual void answerSurvey() = 0;
    virtual void storeAnswer(ofstream &fout) const = 0;
};

class AnswerSurvey : public AnswerSurveyBase
{
private:
    string question;
    string answer;
    string response;

public:
    AnswerSurvey(string title)
        : AnswerSurveyBase(title), question(""), answer(""), response("") {}

    AnswerSurvey(string title, string topic)
        : AnswerSurveyBase(title, topic), question(""), answer(""), response("") {}

    void answerSurvey() override
    {
        ifstream fin("Surveys/" + title + ".txt");
        getline(fin, title);
        fin >> noOfQuestions;
        fin.ignore();
        cout << "Enter the response for the following questions (ratings between 1 and 5): " << endl;

        for (int i = 0; i < noOfQuestions; i++)
        {
            getline(fin, question);
            cout << question << endl;

            while (true)
            {
                getline(cin, response);

                try
                {
                    int rating = stoi(response);
                    if (rating >= 1 && rating <= 5)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid rating. Please enter a number between 1 and 5." << endl;
                    }
                }
                catch (const invalid_argument &)
                {
                    cout << "Invalid input. Please enter a valid number between 1 and 5." << endl;
                }
            }

            answer += response + "\n";
        }

        fin.close();
    }

    void storeAnswer(ofstream &fout) const override
    {
        fout << title << endl;
        fout << answer << endl;
    }
};
