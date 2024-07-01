#ifndef EXAM_H
#define EXAM_H

#include <string>

class Exam
{
    std::string _correctAnswers[10];
    std::string _examType;
    int _collectedAnswers;
public:
    Exam(std::string examType)
    {
        for(auto &answer : _correctAnswers) answer = "";
        _examType = examType;
        _collectedAnswers = 0;
    }
    std::string getExamType() { return _examType; }
    std::string getAnswer(int index)
    {
        if(index < 0 || index > 9) return "";
        return _correctAnswers[index];
    }
    void addAnswer(std::string answer)
    {
        if(_collectedAnswers >= 10) return;
        _correctAnswers[_collectedAnswers] = answer;
        _collectedAnswers += 1;
    }

};

#endif
