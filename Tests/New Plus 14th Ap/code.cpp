#include "bits/stdc++.h"
using namespace std;

struct student {
    int index;
    string roll;
    int rank;
    vector<int> preferences;
    int allotedCourse;
};

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ifstream inFile1, inFile2;
    ofstream outFile;

    inFile1.open("courses", ios::in);
    int numOfCourses = 20;
    map<int, int> seatsForCourse;
    for (int i = 0; i < numOfCourses; i++) {
        int course, seats;
        inFile1 >> course >> seats;
        seatsForCourse[course] = seats;
    }

    inFile2.open("students", ios::in);
    int numOfStudents = 10000;
    vector<student> students;
    for (int i = 0; i < numOfStudents; i++) {
        student currStudent;
        currStudent.index = i + 1;
        inFile2 >> currStudent.roll;
        inFile2 >> currStudent.rank;
        currStudent.preferences.resize(numOfCourses);
        for (int j = 0; j < numOfCourses; j++) {
            inFile2 >> currStudent.preferences[j];
        }
        students.push_back(currStudent);
    }

    sort(students.begin(), students.end(), [&] (const student &a, const student &b) {
        return a.rank < b.rank;
    });

    for (student &currStudent : students) {
        for (int &preference : currStudent.preferences) {
            if (seatsForCourse[preference] > 0) {
                seatsForCourse[preference] -= 1;
                currStudent.allotedCourse = preference;
                break;
            }
        }
    }

    sort(students.begin(), students.end(), [&] (const student &a, const student &b) {
        return a.index < b.index;
    });

    outFile.open("allotments");
    for (student &currStudent : students) {
        outFile << currStudent.roll << ' ' << currStudent.allotedCourse << '\n';
    }

    return 0;
}