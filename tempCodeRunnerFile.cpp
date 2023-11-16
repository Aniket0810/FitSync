#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class TrainingNode {
public:
    string exercise;
    TrainingNode* next;

    TrainingNode(const string& ex) : exercise(ex), next(nullptr) {}
};

class TrainingAdvice {
private:
    TrainingNode* upperBodyExercises;
    TrainingNode* lowerBodyExercises;

public:
    TrainingAdvice() : upperBodyExercises(nullptr), lowerBodyExercises(nullptr) {
        LoadTrainingAdvice();
    }

    ~TrainingAdvice() {
        ClearLinkedList(upperBodyExercises);
        ClearLinkedList(lowerBodyExercises);
    }

    void displayTrainingAdvice() {
        cout << "Here's some training advice: \n\n";
        cout << "Upper Body Workout: \n";
        DisplayLinkedList(upperBodyExercises);

        cout << "\nLower Body Workout: \n";
        DisplayLinkedList(lowerBodyExercises);
    }

    void addUpperBodyExercise(const string& exercise) {
        upperBodyExercises = AddExercise(upperBodyExercises, exercise);
        SaveTrainingAdvice();
    }

    void addLowerBodyExercise(const string& exercise) {
        lowerBodyExercises = AddExercise(lowerBodyExercises, exercise);
        SaveTrainingAdvice();
    }

    void removeUpperBodyExercise(int index) {
        upperBodyExercises = RemoveExercise(upperBodyExercises, index);
        SaveTrainingAdvice();
    }

    void removeLowerBodyExercise(int index) {
        lowerBodyExercises = RemoveExercise(lowerBodyExercises, index);
        SaveTrainingAdvice();
    }

private:
    void ClearLinkedList(TrainingNode*& head) {
        while (head) {
            TrainingNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void DisplayLinkedList(TrainingNode* head) {
        int index = 1;
        TrainingNode* current = head;
        while (current) {
            cout << index << ". " << current->exercise << "\n";
            current = current->next;
            index++;
        }
    }

    TrainingNode* AddExercise(TrainingNode* head, const string& exercise) {
        TrainingNode* newNode = new TrainingNode(exercise);
        newNode->next = head;
        return newNode;
    }

    TrainingNode* RemoveExercise(TrainingNode* head, int index) {
        if (index <= 0) {
            return head;
        }

        if (index == 1) {
            TrainingNode* temp = head;
            head = head->next;
            delete temp;
        } else {
            TrainingNode* current = head;
            TrainingNode* prev = nullptr;
            int count = 1;
            while (count < index && current) {
                prev = current;
                current = current->next;
                count++;
            }
            if (current) {
                prev->next = current->next;
                delete current;
            }
        }

        return head;
    }

    void SaveTrainingAdvice() {
        ofstream file("training_advice.txt");
        if (file.is_open()) {
            SaveLinkedListToFile(file, "Upper: ", upperBodyExercises);
            SaveLinkedListToFile(file, "Lower: ", lowerBodyExercises);
            file.close();
        }
    }

    void LoadTrainingAdvice() {
        ifstream file("training_advice.txt");
        if (file.is_open()) {
            LoadLinkedListFromFile(file, "Upper: ", upperBodyExercises);
            LoadLinkedListFromFile(file, "Lower: ", lowerBodyExercises);
            file.close();
        }
    }

    void SaveLinkedListToFile(ofstream& file, const string& prefix, TrainingNode* head) {
        TrainingNode* current = head;
        while (current) {
            file << prefix << current->exercise << "\n";
            current = current->next;
        }
    }

    void LoadLinkedListFromFile(ifstream& file, const string& prefix, TrainingNode*& head) {
        string line;
        while (getline(file, line)) {
            if (!line.empty() && line.find(prefix) == 0) {
                string exercise = line.substr(prefix.length());
                head = AddExercise(head, exercise);
            }
        }
    }
};

int main() {
    TrainingAdvice trainingAdvice;
    trainingAdvice.addUpperBodyExercise("chest");
    trainingAdvice.addUpperBodyExercise("Curls");
    trainingAdvice.addLowerBodyExercise("Legs");
    trainingAdvice.displayTrainingAdvice();

    // cout << "Removing exercise...\n";
    // trainingAdvice.removeUpperBodyExercise(1); // Remove the first upper body exercise
    // trainingAdvice.displayTrainingAdvice();

    return 0;
}
