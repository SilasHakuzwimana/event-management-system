#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QString>
#include <QMessageBox>
#include <vector>
using namespace std;

struct Event {
    QString name;
    QString date;
    QString venue;
    int priority;
};

class EventManagerGUI : public QWidget {
    Q_OBJECT
private:
    vector<Event> events;
    QLineEdit *nameInput, *dateInput, *venueInput, *priorityInput;
    QTextEdit *eventDisplay;
public:
    EventManagerGUI(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        layout->addWidget(new QLabel("Event Name:"));
        nameInput = new QLineEdit();
        layout->addWidget(nameInput);

        layout->addWidget(new QLabel("Date:"));
        dateInput = new QLineEdit();
        layout->addWidget(dateInput);

        layout->addWidget(new QLabel("Venue:"));
        venueInput = new QLineEdit();
        layout->addWidget(venueInput);

        layout->addWidget(new QLabel("Priority:"));
        priorityInput = new QLineEdit();
        layout->addWidget(priorityInput);

        QPushButton *addEventButton = new QPushButton("Add Event");
        layout->addWidget(addEventButton);
        connect(addEventButton, &QPushButton::clicked, this, &EventManagerGUI::addEvent);

        QPushButton *showEventsButton = new QPushButton("Show Events");
        layout->addWidget(showEventsButton);
        connect(showEventsButton, &QPushButton::clicked, this, &EventManagerGUI::displayEvents);

        eventDisplay = new QTextEdit();
        eventDisplay->setReadOnly(true);
        layout->addWidget(eventDisplay);
    }

public slots:
    void addEvent() {
        QString name = nameInput->text();
        QString date = dateInput->text();
        QString venue = venueInput->text();
        int priority = priorityInput->text().toInt();
        
        if (name.isEmpty() || date.isEmpty() || venue.isEmpty() || priorityInput->text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill all fields.");
            return;
        }
        
        events.push_back({name, date, venue, priority});
        QMessageBox::information(this, "Success", "Event added successfully!");
        nameInput->clear(); dateInput->clear(); venueInput->clear(); priorityInput->clear();
    }

    void displayEvents() {
        eventDisplay->clear();
        for (const auto &e : events) {
            eventDisplay->append("Event: " + e.name + " | Date: " + e.date + " | Venue: " + e.venue + " | Priority: " + QString::number(e.priority));
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    EventManagerGUI window;
    window.setWindowTitle("Event Management System");
    window.resize(300, 400);
    window.show();
    return app.exec();
}
