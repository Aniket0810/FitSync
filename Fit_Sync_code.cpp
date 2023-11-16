#include <iostream>   // Standard input and output streams (e.g., cin, cout)
#include <string>     // String manipulation and handling
#include <thread>     // Threading support for concurrent execution
#include <chrono>     // Time-related functions and durations
#include <windows.h>  // Windows-specific functions and types (typically not portable)
#include <cstdlib>    // General utilities and conversions (e.g., exit function)
#include <vector>     // Dynamic array (vector) container
#include <ctime>      // Date and time functions
#include <fstream>    // File input/output operations
//#include <SDL2/SDL.h>

using namespace std;  // Add this line

// void playAudio(const char* filename) {
//     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
//         cerr << "SDL initialization failed: " << SDL_GetError() << endl;w
//         return;
//     }

//     SDL_AudioSpec wavSpec;
//     Uint32 wavLength;
//     Uint8* wavBuffer;

//     if (SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength) == nullptr) {
//         cerr << "Failed to load WAV file: " << SDL_GetError() << endl;
//         SDL_Quit();
//         return;
//     }

//     if (SDL_OpenAudio(&wavSpec, nullptr) < 0) {
//         cerr << "Failed to open audio: " << SDL_GetError() << endl;
//         SDL_FreeWAV(wavBuffer);
//         SDL_Quit();
//         return;
//     }

//     SDL_PauseAudio(0);
//     while (SDL_GetAudioStatus() == SDL_AUDIO_PLAYING) {
//         SDL_Delay(100); // Delay to allow audio to finish playing
//     }

//     SDL_CloseAudio();
//     SDL_FreeWAV(wavBuffer);
//     SDL_Quit();
// }

class Info {
private:
    string name;
    string email;
    int age;
    string gender;
    double height;
    double weight;
    string goal;

public:
    Info() {
        cout << "------**DETAILS**------" << endl;
        cout << "Name: ";
        getline(cin, name);
        cout << "E-mail: ";
        cin >> email;
        cout << "Age: ";
        cin >> age;
        cout << "Gender (Male/Female): ";
        cin >> gender;
        cout << "Height (in cm): ";
        cin >> height;
        cout << "Weight (in kg): ";
        cin >> weight;

        if (gender != "Male" && gender != "Female") {
            gender = "Others";
        }

        displayData();
        calculateBMI();
    }

    void displayData() {
        cout << "---------SUBMITTED DETAILS---------" << endl;
        cout << "Name: " << name << endl;
        cout << "E-mail: " << email << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Height: " << height << " cm" << endl;
        cout << "Weight: " << weight << " kg" << endl;
    }

    void calculateBMI() {
        double height_meter = height / 100; 
        double BMI = weight / (height_meter * height_meter);
        
        cout << "Your BMI: " << BMI << endl;

        if (BMI < 18.5) {
            cout << "\nSuggested goal: Gain weight" << endl;
        } else if (BMI >= 18.5 && BMI < 24.9) {
            cout << "\nSuggested goal: Maintain weight" << endl;
        } else {
            cout << "\nSuggested goal: Lose weight" << endl;
        }
    }

};

class LowerBody {
public:
    LowerBody() {}

    void startWorkout() {
        cout << "Lower Body Workout:" << endl;
        cout << "Starting workout..." << endl;

        //playAudio("lunges.wav");
        cout << "Do 5 Lunges." << endl;
        this_thread::sleep_for(chrono::seconds(5));

        // playAudio("Brake.wav");
        cout << "Take a 30-second break." << endl;

        // playAudio("squats.wav");
        cout << "Do squats for 30 seconds." << endl;
        this_thread::sleep_for(chrono::seconds(5));

        // playAudio("Brake.wav");
        cout << "Take a 30-second break." << endl;

        // playAudio("hip_bridges.wav");
        cout << "Do 10 Hip-Bridges." << endl;
        this_thread::sleep_for(chrono::seconds(5));

        cout << "Congratulations! You have completed your workout." << endl;
        // playAudio("congrats.wav");
    }

    
};

class UpperBody {
public:
    UpperBody() {}

    void startWorkout() {
        cout << "Upper Body Workout:" << endl;
        cout << "Starting workout..." << endl;

        // playAudio("pushups.wav");
        cout << "-----Do 10 Push-ups-----" << endl;
        this_thread::sleep_for(chrono::seconds(5));

        // playAudio("break.wav");
        cout << "***Take a 30-second break***" << endl;

        // playAudio("squats.wav");
        cout << "-----Do Bench Press of 10 repetition -----" << endl;
        this_thread::sleep_for(chrono::seconds(5));
        
        // playAudio("break.wav");
        cout << "***Take a 30-second break***" << endl;

        // playAudio("pullups.wav");
        cout << "-----Do 10 Pull-ups-----" << endl;
        this_thread::sleep_for(chrono::seconds(5));

        cout << "Congratulations! You have completed your workout." << endl;
    }

    void playAudio(const string& filename) {
        Beep(1000, 500); 
    }
};

class SelectExercise {
public:
    void selectUpperBodyExercise() {
        cout << "Your Upper Body Training will start now." << endl;
        UpperBody ub;
        ub.startWorkout();
    }

    void selectLowerBodyExercise() {
        cout << "Your Lower Body Training will start now." << endl;
        LowerBody lb;
        lb.startWorkout();
    }

    void showMenu() {
        cout << "Select One:" << endl;
        cout << "1. Upper Body" << endl;
        cout << "2. Lower Body" << endl;
    }

    void run() {
        int choice;

        while (true) {
            showMenu();
            cout << "Enter your choice (1 for Upper Body, 2 for Lower Body, 0 to exit): ";
            cin >> choice;

            switch (choice) {
                case 1:
                    selectUpperBodyExercise();
                    break;
                case 2:
                    selectLowerBodyExercise();
                    break;
                case 0:
                    cout << "Exiting program." << endl;
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

class TrainingNode {
public:
    string exercise;
    TrainingNode* next;

    TrainingNode(const string& ex) : exercise(ex), next(NULL) {}
};

class TrainingAdvice {
public:
    TrainingNode* upperBodyExercises;
    TrainingNode* lowerBodyExercises;

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
        }
        else {
            TrainingNode* current = head;
            TrainingNode* prev = NULL;
            int count = 1;
            while (count < index && current) {
                prev = current;
                current = current->next;
                count++;
            }
            if (current!=NULL) {
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

class UpdateSchedule {
public:
    UpdateSchedule() {
        daysOfWeek = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
        workoutPlan = {
            { "Lower Body" },
            { "Upper Body" },
            { "Lower Body" },
            { "Upper Body" },
            { "Lower Body" },
            { "Upper Body" },
            { "Rest" }
        };
    }

    void Run() {
        int choice;
        do {
            PrintMenu();
            cin >> choice;
            cin.ignore(); // Clearing new line char

            switch (choice) {
                case 1:
                    UpdateScheduleForDay();
                    break;
                case 2:
                    cout << "Exiting the program." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 2);
    }

public:
    vector<string> daysOfWeek;
    vector<vector<string>> workoutPlan;

    void PrintMenu() {
        cout << "-------Schedule Manager--------" << endl;
        cout << "1. Update Schedule" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
    }

    void UpdateScheduleForDay() {
        cout << "Select a day of the week:" << endl;
        for (int i = 0; i < daysOfWeek.size(); i++) {
            cout << i + 1 << ". " << daysOfWeek[i] << endl;
        }

        cout << "Enter the day number (1-7): ";
        int day;
        cin >> day;

        if (day >= 1 && day <= 7) {
            cout << "Select a workout type:" << endl;
            cout << "1. Upper Body" << endl;
            cout << "2. Lower Body" << endl;
            cout << "3. Rest" << endl;
            cout << "Enter the workout type (1-3): ";
            int workoutType;
            cin >> workoutType;

            if (workoutType >= 1 && workoutType <= 3) {
                workoutPlan[day - 1].clear();  // Clearing the previous workout plan
                if (workoutType == 1) {
                    workoutPlan[day - 1].push_back("Upper Body");
                    cout << "Your upper body workout plan for " << daysOfWeek[day - 1] << " has been updated." << endl;
                } else if (workoutType == 2) {
                    workoutPlan[day - 1].push_back("Lower Body");
                    cout << "Your lower body workout plan for " << daysOfWeek[day - 1] << " has been updated." << endl;
                } else if (workoutType == 3) {
                    workoutPlan[day - 1].push_back("Rest");
                    cout << "Your rest day workout plan for " << daysOfWeek[day - 1] << " has been updated." << endl;
                }
            } else {
                cout << "Invalid workout type. Please try again." << endl;
            }
        } else {
            cout << "Invalid day selection. Please try again." << endl;
        }
    }
};

class ViewSchedule {
public:
    ViewSchedule() {
        dayLabel = "Select a day of the week: ";
        daysOfWeek = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
        workoutPlan = {
            { "Lower Body" },
            { "Upper Body" },
            { "Lower Body" },
            { "Upper Body" },
            { "Lower Body" },
            { "Upper Body" },
            { "Rest" }
        };
        motivation = {
            "Push yourself because no one else is going to do it for you.",
            "Don't stop when you're tired. Stop when you're done.",
            "Your only limit is the one you set for yourself.",
            "Whenever you think about giving up just remember why you have started it.",
            "It's going to be hard but hard is not impossible.",
            "DON'T GIVE UP, There is no shame in falling down! True shame is not standing up again.",
            "A goal with no plan is called a delusion. You need a plan to achieve your GOAL!!!"
        };

        srand(static_cast<unsigned int>(time(NULL)));

        dayComboBox = 0; // Default selection
        scheduleLabel = "";
        motivationLabel = "";
    }

    void Run() {
        int choice;
        do {
            PrintMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    ViewScheduleForDay();
                    break;
                case 2:
                    GetMotivated();
                    break;
                case 3:
                    cout << "Exiting the program." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 3);
    }

    string dayLabel;
    vector<string> daysOfWeek;
    vector<vector<string>> workoutPlan;
    vector<string> motivation;
    int dayComboBox;
    string scheduleLabel;
    string motivationLabel;

    void PrintMenu() {
        cout << "----------------------------"<<endl;
        cout << "****Training Schedule****" << endl;
        cout << "1. View Schedule" << endl;
        cout << "2. Get Motivated" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
    }

    void ViewScheduleForDay() {
        cout << dayLabel << endl;
        for (int i = 0; i < daysOfWeek.size(); i++) {
            cout << i + 1 << ". " << daysOfWeek[i] << endl;
        }

        cout << "Enter the day number (1-7): ";
        cin >> dayComboBox;

        if (dayComboBox >= 1 && dayComboBox <= 7) {
            string schedule = "";
            for (const string& exercise : workoutPlan[dayComboBox - 1]) {
                schedule += exercise + " ";
            }
            cout << "Your gym schedule for " << daysOfWeek[dayComboBox - 1] << " is: " << schedule << endl;
            motivationLabel = "";
        }
        else {
            cout << "Invalid day selection. Please try again." << endl;
        }
    }

    void GetMotivated() {
            int index = rand() % motivation.size();
        cout << "Motivation: " << motivation[index] << endl;
    }
};

class Menu {
public:
    void startWorkout() {
        cout << "Starting workout..." << endl;
        SelectExercise exercise;
        exercise.run();
    }

    void trainingAdvice() {
        TrainingAdvice training;


        cout << "Training Advice Program" << endl;
        training.displayTrainingAdvice();

        string userInput;
        int option;

        do {
            cout << "--------------------------------------"<<endl;
            cout << "\nOptions:\n";
            cout << "1 - Add an upper body exercise\n";
            cout << "2 - Add a lower body exercise\n";
            cout << "3 - Remove an upper body exercise\n";
            cout << "4 - Remove a lower body exercise\n";
            cout << "0 - Quit\n";
            cout << "Choose an option: ";
            cin >> option;

            switch (option) {
                case 1:
                    cout << "Enter new upper body exercise: ";
                    cin>>userInput;
                    cout<<endl;
                    training.addUpperBodyExercise(userInput);
                    break;
                case 2:
                    cout << "Enter new lower body exercise: ";
                    cin>>userInput;
                    cout<<endl;
                    training.addLowerBodyExercise(userInput);
                    break;
                case 3:
                    int remove_upper_Index;
                    cout << "Enter the index of the upper body exercise to remove: ";
                    cin >> remove_upper_Index;
                    training.upperBodyExercises = training.RemoveExercise(training.upperBodyExercises,remove_upper_Index);
                    break;
                case 4:
                    int remove_lower_Index;
                     cout << "Enter the index of the lower body exercise to remove: ";
                     cin >> remove_lower_Index;
                     training.lowerBodyExercises = training.RemoveExercise(training.lowerBodyExercises, remove_lower_Index);
                     break;

                case 0:
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
        } while (option != 0);

        return;
    }

    void updateSchedule() {
        cout << "Updating schedule..." << endl;
        UpdateSchedule program;
        program.Run();
    }

    void viewSchedule() {
        cout << "Viewing schedule..." << endl;
        ViewSchedule program;
        program.Run();
    }

    void showMenu() {
        cout << "---------------------"<<endl;
        cout << "Choose an option:" << endl;
        cout << "1. Start workout" << endl;
        cout << "2. Training advice" << endl;
        cout << "3. Update schedule" << endl;
        cout << "4. View schedule" << endl;
        cout << "5. Exit" << endl;
    }

    void run() {
        int choice;
        bool exit = false;

        while (!exit) {
            showMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    startWorkout();
                    break;
                case 2:
                    trainingAdvice();
                    break;
                case 3:
                    updateSchedule();
                    break;
                case 4:
                    viewSchedule();
                    break;
                case 5:
                    exit = true;
                    cout << "Exiting program." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

int main() {
    Info myInfo;

    Menu menu;
    menu.run();

    return 0;
}