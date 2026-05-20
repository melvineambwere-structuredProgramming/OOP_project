#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Keypad.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


SoftwareSerial mySerial(10, 11);
Adafruit_Fingerprint finger(&mySerial);


const byte ROWS = 4, COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0,A1,A2,A3};
byte colPins[COLS] = {5,4,3,2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


// INHERITANCE

class User {

  protected:
    int id;

  public:
    User(int i) {
      id = i;
    }

    int getID() {
      return id;
    }

  
  //POLYMORPHISM
    
    virtual void role() {
      lcd.print("User");
    }
};

class Admin : public User {

  public:
    Admin(int i) : User(i) {}

    void role() override {
      lcd.print("Admin");
    }
};


// ENCAPSULATION AND  ABSTRACTION

class AttendanceSystem {

  private:

    bool attendance[11];
    bool loggedIn = false;

    unsigned long lastActivity = 0;

    int nextID = 2;

    Admin admin = Admin(1);

  public:

    void message(String a, String b = "") {

      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print(a);

      lcd.setCursor(0,1);
      lcd.print(b);
    }

    int scanFinger() {

      if (finger.getImage() != FINGERPRINT_OK) return -1;
      if (finger.image2Tz() != FINGERPRINT_OK) return -1;
      if (finger.fingerFastSearch() != FINGERPRINT_OK) return -1;

      return finger.fingerID;
    }

    void begin() {

      lcd.init();
      lcd.backlight();

      Serial.begin(9600);

      finger.begin(57600);

      message("BAVS System", "Initializing");

      delay(2000);

      if (!finger.verifyPassword()) {

        message("Sensor Error");

        while (1);
      }

      message("Scan Admin");
    }

    void menu() {

      message("1E 2A", "3R 4X");
    }

    void login() {

      int id = scanFinger();

      if (id == admin.getID()) {

        loggedIn = true;

        lastActivity = millis();

        message("Welcome", "ADM001");

        delay(2000);

        menu();
      }
    }

    void enroll() {

      if (nextID > 10) {

        message("Memory Full");

        delay(2000);

        return;
      }

      int id = nextID;

      message("Enroll STD00" + String(id - 1));

      delay(2000);

      int p = -1;

      message("Place Finger");

      while (p != FINGERPRINT_OK)
        p = finger.getImage();

      finger.image2Tz(1);

      message("Remove Finger");

      delay(2000);

      while (finger.getImage() != FINGERPRINT_NOFINGER);

      message("Place Again");

      p = -1;

      while (p != FINGERPRINT_OK)
        p = finger.getImage();

      finger.image2Tz(2);

      if (finger.createModel() == FINGERPRINT_OK &&
          finger.storeModel(id) == FINGERPRINT_OK) {

        message("Enroll Success");

        nextID++;

      } else {

        message("Enroll Failed");
      }

      delay(2000);
    }

    void attendanceMode() {

      message("Attendance", "Open");

      delay(2000);

      unsigned long start = millis();

      while (millis() - start < 30000) {

        message("Scan Finger");

        int id = scanFinger();

        if (id > 1) {

          if (!attendance[id]) {

            attendance[id] = true;

            message("Attendance", "Recorded");

          } else {

            message("Already", "Marked");
          }

          delay(2000);
        }
      }

      message("Attendance End");

      delay(2000);
    }

    void records() {

      int count = 0;

      for (int i = 2; i <= 10; i++)
        if (attendance[i]) count++;

      message("Total Present", String(count));

      delay(3000);
    }

    void resetRecords() {

      for (int i = 0; i <= 10; i++)
        attendance[i] = false;

      message("Records", "Cleared");

      delay(2000);
    }

    void autoLogout() {

      if (millis() - lastActivity > 60000) {

        loggedIn = false;

        message("Admin Logged", "Out");

        delay(2000);

        message("Scan Admin");
      }
    }

    void run() {

      if (!loggedIn) {

        login();

      } else {

        char key = keypad.getKey();

        if (key) {

          lastActivity = millis();

          switch(key) {

            case '1': enroll(); break;
            case '2': attendanceMode(); break;
            case '3': records(); break;
            case '4': resetRecords(); break;
          }

          menu();
        }

        autoLogout();
      }
    }
};

AttendanceSystem bavs;

void setup() {

  bavs.begin();
}


void loop() {

  bavs.run();
}