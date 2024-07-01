#include <iostream>
#include <filesystem>
#include <fstream>

#include "HeaderFiles/student.h";
#include "HeaderFiles/exam.h";

constexpr int NUMBER_OF_STUDENTS = 999;
constexpr int NUMBER_OF_EXAMS = 999;

std::string STUDENTS_FILE_PATH = "Files/Students";
std::string EXAMS_FILE_PATH = "Files/ExamAnswerKeys";

Student* listOfStudents[NUMBER_OF_STUDENTS] = {};
Exam* listOfExams[NUMBER_OF_EXAMS] = {};

int studentCount = 0;
int examCount = 0;

struct StudentStruct
{
    bool hasStudent;
    Student* student;
};

Exam* getStudentsExam(std::string examType)
{
    for(const auto& exam : listOfExams)
    {
        if(exam->getExamType() == examType) return exam;
    }
    std::cerr<<"Found a student who took a non-existing exam!!!";
    return nullptr;
}

void getStudents()
{
    std::string fileName, fileText, examType;
    std::ifstream file;
    for(const auto &entry : std::filesystem::directory_iterator(STUDENTS_FILE_PATH))
    {
        fileName = entry.path().filename().generic_string();
        file.open(entry.path());
        for(int i = 0; i < 4; i++) fileName.pop_back();
        getline(file, examType);
        auto* student = new Student(fileName, getStudentsExam(examType));
        while(getline(file, fileText)) student->addAnswer(fileText);
        file.close();
        listOfStudents[studentCount] = student;
        studentCount += 1;
    }
}

void getExams()
{
    std::string fileName, fileText;
    std::ifstream file;
    for(const auto &entry : std::filesystem::directory_iterator(EXAMS_FILE_PATH))
    {
        fileName = entry.path().filename().generic_string();
        file.open(entry.path());
        for(int i = 0; i < 4; i++) fileName.pop_back();
        auto* exam = new Exam(fileName);
        while(getline(file, fileText)) exam->addAnswer(fileText);
        file.close();
        listOfExams[examCount] = exam;
        examCount += 1;
    }
}

StudentStruct getStudentWithExamType(std::string examType)
{
    StudentStruct studentStruct{false, nullptr};
    for(int i = 0; i < studentCount; i++)
    {
        if(listOfStudents[i]->getExamType() != examType) continue;
        studentStruct.hasStudent = true;
        studentStruct.student = listOfStudents[i];
        listOfStudents[i] = listOfStudents[studentCount - 1];
        studentCount -= 1;
        return studentStruct;
    }
    return studentStruct;
}

int main()
{
    getExams();
    getStudents();

    std::string answerArray[examCount][NUMBER_OF_STUDENTS + 1][3];
    StudentStruct studentStruct{};
    for(int i = 0; i < examCount; i++)
    {
        studentStruct = getStudentWithExamType(listOfExams[i]->getExamType());
        int currStudent = 0;
        while(studentStruct.hasStudent)
        {
            answerArray[i][currStudent][0] = studentStruct.student->getExamType();
            answerArray[i][currStudent][1] = studentStruct.student->getStudentID();
            answerArray[i][currStudent][2] = std::to_string(studentStruct.student->getPoints());
            studentStruct = getStudentWithExamType(listOfExams[i]->getExamType());
            currStudent += 1;
        }
        answerArray[i][currStudent][0] = "-There-Are-No-More-Students-";
    }

    for(int i = 0; i < examCount; i++)
    {
        for(int j = 0; j < NUMBER_OF_STUDENTS; j++)
        {
            if(answerArray[i][j][0] == "-There-Are-No-More-Students-") break;
            std::cout<<"Student ID: "<<answerArray[i][j][1]
                     <<" | Student took "<<answerArray[i][j][0]
                     <<" exam and scored "<<answerArray[i][j][2]<<"/10 points!"<<std::endl;
        }
    }

    return 0;
}
