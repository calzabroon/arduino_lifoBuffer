#include <ee108.h>

const int SUPERLOOP_DELAY_MS = 20;
const int BUFFER_LEN = 9;

void printSlotsAndElements(int *slice, int counter);
/**
 * prints the array in array style and amount of slots used
 * in the for { x, y, z }, 3 used
 */
int UsedSlots(int counter);
/**
 * returns the amount of used slots according to counter
 */
int FreeSlots(int counter, int len);
/**
 * returns the amount of free slots according to counter
 */
void addElement(int *slice, int *counter, int number);
/**
 * adds number to the end of the array inputted
 * also updates counter (optional)
 */
int removeElement(int *slice, int *counter);
/**
 * removes number at end of array
 * also updates counter (optional)
 */


void setup() {
  Serial.begin(9600);
}


void loop() {
  static int lifoBuffer[BUFFER_LEN] = { };
  static int lifoCounter = 0;
  static int loopCounter = 1;
  int sw1Event;
  int sw2Event;
  int pPrevStateDurationMs1;
  int pPrevStateDurationMs2;
  int number;

  //these read if either SW1 or SW2 have been clicked
  sw1Event = readSwitchEventTimes(sw1Object, &pPrevStateDurationMs1);
  sw2Event = readSwitchEventTimes(sw2Object, &pPrevStateDurationMs2);

  if (sw1Event == SW_CLICK) {   //checks if SW1 has been clicked for less than 1 second
    if (pPrevStateDurationMs1 < 1000){ 
      if (lifoCounter < BUFFER_LEN){    // if the amount of numbs in the array are less than max it will add number and print
        Serial.print("Loop ");
        Serial.print(loopCounter);
        Serial.print(": [SW1 CLICK] added to buffer, ");
        addElement(lifoBuffer, &lifoCounter, random(100));  //adds a random numb to the array
        Serial.print(", buffer is now ");
        printSlotsAndElements(lifoBuffer, lifoCounter);
      } else {    //if buffer is full it will print so
        Serial.print("Loop ");
        Serial.print(loopCounter);
        Serial.println(": [SW1 Click] Cannot add to buffer -- buffer full");
      }
    }
  }

  if (sw2Event == SW_CLICK) {   //checks if SW2 has been clicked for less than 1 second
    if (pPrevStateDurationMs2 < 1000){ 
      if (lifoCounter > 0){   //if there are more than one number in array it will remove element and print
        Serial.print("Loop ");
        Serial.print(loopCounter);
        Serial.print(": [SW2 CLICK] removed from buffer, ");
        number = removeElement(lifoBuffer, &lifoCounter); //removes most recent numb
        Serial.print(number);
        Serial.print(", buffer is now ");
        printSlotsAndElements(lifoBuffer, lifoCounter);
      } else {    //if buffer is empty it will print some
        Serial.print("Loop ");
        Serial.print(loopCounter);
        Serial.println(": [SW2 click] Cannot remove from buffer -- buffer empty");
      }
    }
  }

  delay(SUPERLOOP_DELAY_MS);
  loopCounter++;
}





void printSlotsAndElements(int *slice, int counter) {
  int *pValue;
 
  Serial.print(" { ");
  
  // print first value without comma before  
  if (counter == 0) {
    Serial.print(" }");
  } else {
  // now print remaining values
    for (pValue = slice; pValue < slice + counter; pValue++) {
      Serial.print(*pValue);
      if (pValue < slice + counter - 1) {
        Serial.print(", ");
      }
    }
    Serial.print(" }, ");
  }
  
  Serial.print(counter);
  Serial.println(" used");
}



int FreeSlots(int counter, int len) {
  return( len - counter );
}


int UsedSlots(int counter) {
  return( counter );
}


void addElement(int *slice, int *counter, int number) {
    slice += *counter;
  
    *slice = number;
    *counter += 1;
}


int removeElement(int *slice, int *counter) {
    int temp; 
    slice += *counter - 1;
  
    temp = *slice;
  
    *slice = 0;
    *counter = *counter - 1;
    return temp;
}
