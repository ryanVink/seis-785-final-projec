// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_TLC59711.h"

#define NUM_TLC59711 1

// uint8_t data = D0; // Instead of writing D0 over and over again, we'll write led1
// // You'll need to wire an LED to this one to see it blink.

// uint8_t clock = D2; // Instead of writing D7 over and over again, we'll write led2


Adafruit_TLC59711 gtlc = Adafruit_TLC59711(NUM_TLC59711, D2, D0);

class Subscriber {
  public:
    Subscriber() {
        Particle.subscribe("event_update_led", &Subscriber::handler, this);
    }
    void setColor(uint8_t lednum, char* tok) {
        if (strcmp(tok, "GREEN") == 0) {
            gtlc.setLED(lednum, 0, 65535, 0);
        }
        if(strcmp(tok, "YELLOW") == 0) {
            gtlc.setLED(lednum, 65535 * .65, 65535 * .65, 0);
        }
        if(strcmp(tok, "RED") == 0) {
            gtlc.setLED(lednum, 65535, 0, 0);
        }
        gtlc.write();
    }
    void handler(const char *eventName, const char *data) {
        char* copy = strdup(data);
        
        copy = strtok(copy, "~");
        char* tokens[4];
        int counter = 0;
        while (copy != NULL) {
            tokens[counter] = copy;
            copy = strtok(NULL, "~");
            counter++;
        }
        
        for (int i = 0; i < 4; i++) {
            char* led = strtok(tokens[i], ":");
            char* tok = strtok(NULL, ":");
            Particle.publish("debug", led);
            if (strcmp(led,"0") == 0) {
                setColor(0, tok);
            }
            if (strcmp(led,"1") == 0) {
                setColor(1, tok);
            }
            if (strcmp(led,"2") == 0) {
                setColor(2, tok);
            }
            if (strcmp(led,"3") == 0) {
                setColor(3, tok);
            }
            // if (strcmp(led,"1") == 0) {
            //     if (strcmp(strtok(NULL, ":"), "HIGH") == 0) {
            //         digitalWrite(led1, HIGH);
            //     } else {
            //         digitalWrite(led1, LOW);
            //     }
            // }
            // if (strcmp(led,"1") == 0) {
            //     if (strcmp(strtok(NULL, ":"), "HIGH") == 0) {
            //         digitalWrite(led1, HIGH);
            //     } else {
            //         digitalWrite(led1, LOW);
            //     }
            // }
            // if (strcmp(led,"1") == 0) {
            //     if (strcmp(strtok(NULL, ":"), "HIGH") == 0) {
            //         digitalWrite(led1, HIGH);
            //     } else {
            //         digitalWrite(led1, LOW);
            //     }
            // }
            // if (strcmp(led,"1") == 0) {
            //     if (strcmp(strtok(NULL, ":"), "HIGH") == 0) {
            //         digitalWrite(led1, HIGH);
            //     } else {
            //         digitalWrite(led1, LOW);
            //     }
            // }
        }
    }
};

// void myHandler(const char *event, const char *data) {
//     Particle.publish("new_event", "here");
// }

void setup() {
    gtlc.begin();
    gtlc.write();
    Subscriber mySubscribe;
    gtlc.setLED(0, 65535, 65535, 65535);
    gtlc.write();
    gtlc.setLED(1, 65535, 65535, 65535);
    gtlc.write();
    gtlc.setLED(2, 65535, 65535, 65535);
    gtlc.write();
    gtlc.setLED(3, 65535, 65535, 65535);
    gtlc.write();
}

void loop() {

}

