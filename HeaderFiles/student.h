#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "exam.h";

class Student
{
    std::string _studentID;
    Exam* _exam;
    int _points;
    int _collectedAnswers;
public:
    Student(std::string studentID, Exam* exam)
    {
        _studentID = studentID;
        _exam = exam;
        _points = 0;
        _collectedAnswers = 0;
    }

    std::string getStudentID() { return _studentID; }
    std::string getExamType() { return _exam->getExamType(); }
    int getPoints() { return _points; }
    void addAnswer(std::string answer)
    {
        if(_collectedAnswers >= 10) return;
        std::string correctAnswer = _exam->getAnswer(_collectedAnswers);
        _collectedAnswers += 1;
        if(correctAnswer != answer) return; // Ignore wrong answers
        _points += 1;
    }
};

#endif
