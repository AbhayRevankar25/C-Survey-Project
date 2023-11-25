#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class SurveyBase
{
protected:
    string title;
    string topic;
    int noOfQuestions;

public:
    SurveyBase(string title)
        : title(title), topic(""), noOfQuestions(0) {}

    SurveyBase(string title, string topic)
        : title(title), topic(topic), noOfQuestions(0) {}

    virtual ~SurveyBase() {}

    virtual void createSurvey()
    {
        while (true)
        {
            cout << "Enter the number of questions (max 5): ";
            cin >> noOfQuestions;

            if (cin.fail() || noOfQuestions < 1 || noOfQuestions > 5)
            {
                cerr << "Invalid input. Please enter a number between 1 and 5." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
    }

    virtual void storeSurvey(ofstream &fout) const
    {
        fout << title << endl;
        fout << noOfQuestions << endl;
    }
};

class Question
{
protected:
    string question;

public:
    Question(string question)
        : question(question) {}

    virtual ~Question() {}

    string getQuestion() const
    {
        return question;
    }
    virtual void createQuestion()
    {
        cout << "Enter the question: ";
        getline(cin, question);
    }
};

class Survey : public SurveyBase
{
    vector<Question *> questions;

public:
    Survey(string title)
        : SurveyBase(title), questions() {}

    Survey(string title, string topic)
        : SurveyBase(title, topic), questions() {}

    ~Survey()
    {
        for (Question *q : questions)
        {
            delete q;
        }
    }

    void createSurvey() override
    {
        SurveyBase::createSurvey();

        for (int i = 0; i < noOfQuestions; ++i)
        {
            Question *q = new Question("Question " + to_string(i + 1));
            q->createQuestion();
            questions.push_back(q);
        }
    }

    void appendSurveyTitle() const
    {
        ofstream titleFile("survey_titles.txt", ios::app);

        if (!titleFile.is_open())
        {
            cerr << "Error opening survey_titles.txt for appending" << endl;
            return;
        }

        titleFile << title << endl;

        titleFile.close();
    }

    void storeSurvey(ofstream &fout) const override
    {
        SurveyBase::storeSurvey(fout);

        for (const Question *q : questions)
        {
            fout << q->getQuestion() << endl;
        }
    }
};
