#include <iostream>
#include <string>
#include <vector>

class Alarm;

class AlarmClock {
public:
  // Your constructors and destructor.

  void AddAlarm(Alarm* alarm);
  void Input();
  void TimeElapse();
  // ...

private:
  std::vector<Alarm*> m_alarms;
  // ...
};

class Alarm {
public:
  // Your constructors and destructor.

  virtual void Trigger() = 0;
  // ...

protected:
  // Declare protected members so that child classes have access to them.
  // ...
};

class RepeatableAlarm;

class SnoozeableAlarm;


/**************** Implementations ******************/
void AlarmClock::AddAlarm(Alarm* alarm) {

}

void AlarmClock::Input() {

}

void AlarmClock::TimeElapse() {

}

// ...

int main() {
  AlarmClock clock;
  for (int days = 0; days < 3; days++) {
    std::cout << "Do you want to add any alarms?" << std::endl;
    clock.Input();
    for (int minute = 0; minute < 24 * 60; minute++) {
      clock.TimeElapse();
    }
    std::cout << "A day has elapsed." << std::endl;
  }
}