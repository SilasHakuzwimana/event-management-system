#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// Structure to store event details
struct Event
{
    string name;
    string date;
    string venue;
    int priority; // Higher priority events are scheduled first
    Event *next;
};

// Class for Event Management
class EventManager
{
private:
    Event *head; // Linked List head (sorted by priority)

public:
    EventManager()
    {
        head = nullptr;
        loadFromFile();
    }

    // Function to add an event
    void addEvent(string name, string date, string venue, int priority)
    {
        Event *newEvent = new Event{name, date, venue, priority, nullptr};

        // Insert into linked list based on priority
        if (!head || priority > head->priority)
        {
            newEvent->next = head;
            head = newEvent;
        }
        else
        {
            Event *temp = head;
            while (temp->next && temp->next->priority >= priority)
            {
                temp = temp->next;
            }
            newEvent->next = temp->next;
            temp->next = newEvent;
        }

        cout << "Event added successfully!\n";
        saveToFile();
    }

    // Function to display all events
    void displayEvents()
    {
        if (!head)
        {
            cout << "No events scheduled.\n";
            return;
        }

        Event *temp = head;
        cout<<"\n";
        cout << "\nUpcoming Events:\n";
        while (temp)
        {
            cout<<"\n";
            cout << "Event: " << temp->name
                 << " | Date: " << temp->date
                 << " | Venue: " << temp->venue
                 << " | Priority: " << temp->priority << endl;
            temp = temp->next;
        }
    }

    // Function to remove an event
    void removeEvent(string name)
    {
        if (!head)
        {
            cout << "No events to remove.\n";
            return;
        }

        // If the event to remove is the head
        if (head->name == name)
        {
            Event *temp = head;
            head = head->next;
            delete temp;
            cout << "Event removed successfully.\n";
            saveToFile();
            return;
        }

        Event *temp = head;
        while (temp->next && temp->next->name != name)
        {
            temp = temp->next;
        }

        if (temp->next)
        {
            Event *toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Event removed successfully.\n";
            saveToFile();
        }
        else
        {
            cout << "Event not found.\n";
        }
    }

    // Save events to a file
    void saveToFile()
    {
        ofstream file("events.txt");
        Event *temp = head;
        while (temp)
        {
            file << temp->name << "\n"
                 << temp->date << "\n"
                 << temp->venue << "\n"
                 << temp->priority << "\n";
            temp = temp->next;
        }
        file.close();
    }

    // Load events from a file
    void loadFromFile()
    {
        ifstream file("events.txt");
        if (!file)
            return;

        string name, date, venue;
        int priority;
        while (getline(file, name) && getline(file, date) && getline(file, venue) && file >> priority)
        {
            file.ignore(); // Ignore the newline character
            addEvent(name, date, venue, priority);
        }
        file.close();
    }

    // Destructor to free memory
    ~EventManager()
    {
        while (head)
        {
            Event *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main function
int main()
{
    EventManager manager;
    int choice;
    string name, date, venue;
    int priority;

    do
    {
        cout << "\n";
        cout << "=============================";
        cout << "\n|| Event Management System ||\n";
        cout << "=============================";
        cout << "\n";
        cout << "1. Add Event\n";
        cout << "2. Display Events\n";
        cout << "3. Remove Event\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number: ";
        }
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "\n";
            cout << "Enter event name: ";
            getline(cin, name);
            cout << "Enter event date: ";
            getline(cin, date);
            cout << "Enter event venue: ";
            getline(cin, venue);
            cout << "Enter event priority (higher number = higher priority): ";

            while (!(cin >> priority))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: ";
            }
            cin.ignore();

            manager.addEvent(name, date, venue, priority);
            break;

        case 2:
            cout << "\n";
            manager.displayEvents();
            break;

        case 3:
            cout << "\n";
            cout << "Enter event name to remove: ";
            getline(cin, name);
            manager.removeEvent(name);
            break;

        case 4:
            cout << "\n";
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}