#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

struct Student {
    std::string name;
    std::string stream; // "Bio" or "Math"
    int classNumber;
    int marks[3]; // Stores marks for the three subjects
    int totalMarks;
    int schoolRank;
    int classRank;

    Student(std::string name, std::string stream, int classNumber) 
        : name(name), stream(stream), classNumber(classNumber), totalMarks(0), schoolRank(0), classRank(0) {
            for (int &mark : marks) mark = 0;
    }

    void calculateTotalMarks() {
        totalMarks = marks[0] + marks[1] + marks[2];
    }
};
void readStudentData(std::vector<Student>& students) {
    // Implement file reading logic
    // This function should populate the 'students' vector with data from a file
}

void writeStudentData(const std::vector<Student>& students) {
    std::ofstream file("student_ranks.txt");
    for (const auto& student : students) {
        file << student.name << ", " << student.stream << ", Class " << student.classNumber 
             << ", Total Marks: " << student.totalMarks << ", School Rank: " << student.schoolRank 
             << ", Class Rank: " << student.classRank << std::endl;
    }
    file.close();
}
void enterStudentMarks(Student& student) {
    std::cout << "Enter marks for " << student.name << " (" << student.stream << " stream): ";
    for (int& mark : student.marks) {
        std::cin >> mark;
    }
    student.calculateTotalMarks();
}
void calculateRanks(std::vector<Student>& students) {
    // Sort students by total marks for school rank
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.totalMarks > b.totalMarks;
    });

    int rank = 1;
    for (auto& student : students) {
        student.schoolRank = rank++;
    }

    // Calculate class rank
    for (int i = 1; i <= 8; ++i) { // Assuming 8 classes in total
        std::vector<Student*> classStudents;
        for (auto& student : students) {
            if (student.classNumber == i) {
                classStudents.push_back(&student);
            }
        }

        std::sort(classStudents.begin(), classStudents.end(), [](const Student* a, const Student* b) {
            return a->totalMarks > b->totalMarks;
        });

        int classRank = 1;
        for (auto* student : classStudents) {
            student->classRank = classRank++;
        }
    }
}
int main() {
    std::vector<Student> students;

    // Example of adding students
    students.emplace_back("Alice", "Bio", 1);
    students.emplace_back("Bob", "Math", 4);
    // ... Add other students

    // Enter marks for each student
    for (auto& student : students) {
        enterStudentMarks(student);
    }

    // Calculate ranks
    calculateRanks(students);

    // Write to file
    writeStudentData(students);

    // Display on console
    for (const auto& student : students) {
        std::cout << student.name << " - School Rank: " << student.schoolRank 
                  << ", Class Rank: " << student.classRank << std::endl;
    }

    return 0;
}
