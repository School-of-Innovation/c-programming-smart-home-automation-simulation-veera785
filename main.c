#include <stdio.h>

#define MAX_ROOMS 5  // Maximum number of rooms

// Declare arrays to store the status of devices and sensors
int lights[MAX_ROOMS];          // Light System: 1 = ON, 0 = OFF
int temperatures[MAX_ROOMS];    // Temperature Sensors: Stores temperature values
int motionSensors[MAX_ROOMS];   // Motion Sensors: 1 = Detected, 0 = No Movement
int securityLocks[MAX_ROOMS];   // Security Locks: 1 = Locked, 0 = Unlocked
int motionDetectionCounter[MAX_ROOMS]; // Counter for motion detection (for auto-lock)

// Function prototypes
void initializeSystem(int numRooms);
void displayMenu();
void controlLights(int numRooms);
void readTemperature(int numRooms);
void detectMotion(int numRooms);
void securitySystem(int numRooms);
void analyzeHouseStatus(int numRooms);
void autoLock(int numRooms);
void temperatureAlert(int numRooms);

int main() {
    int numRooms;

    // Get number of rooms from user
    printf("Enter number of rooms: ");
    scanf("%d", &numRooms);

    // Initialize the system
    initializeSystem(numRooms);

    int choice;

    // Menu-driven loop
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                controlLights(numRooms);
                break;
            case 2:
                readTemperature(numRooms);
                break;
            case 3:
                detectMotion(numRooms);
                break;
            case 4:
                securitySystem(numRooms);
                break;
            case 5:
                analyzeHouseStatus(numRooms);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

        // Auto lock feature after each action
        autoLock(numRooms);
        // Temperature Alert feature
        temperatureAlert(numRooms);

    } while (choice != 6);

    return 0;
}

// Initialize system: Set default states
void initializeSystem(int numRooms) {
    for (int i = 0; i < numRooms; i++) {
        lights[i] = 0;  // All lights are OFF
        temperatures[i] = 22;  // Default temperature 22°C
        motionSensors[i] = 0;  // No motion detected initially
        securityLocks[i] = 1;  // All doors are locked initially
        motionDetectionCounter[i] = 0;  // Motion detection counter
    }
    printf("Initializing system...\n");
}

// Display menu for user to select actions
void displayMenu() {
    printf("\n===== Smart Home Menu =====\n");
    printf("1. Toggle Light\n");
    printf("2. Read Temperature\n");
    printf("3. Check Motion Sensor\n");
    printf("4. Lock/Unlock Security System\n");
    printf("5. House Status Summary\n");
    printf("6. Exit\n");
}

// Control Lights: Toggle the light for a room
void controlLights(int numRooms) {
    int room;
    printf("Enter room number to toggle light (1-%d): ", numRooms);
    scanf("%d", &room);

    if (room < 1 || room > numRooms) {
        printf("Invalid room number.\n");
        return;
    }

    room--; // Adjust for zero-indexing
    lights[room] = !lights[room];  // Toggle light state
    if (lights[room] == 1)
        printf("Light in Room %d is now ON.\n", room + 1);
    else
        printf("Light in Room %d is now OFF.\n", room + 1);
}

// Read Temperature: Display the temperature for a room
void readTemperature(int numRooms) {
    int room;
    printf("Enter room number to read temperature (1-%d): ", numRooms);
    scanf("%d", &room);

    if (room < 1 || room > numRooms) {
        printf("Invalid room number.\n");
        return;
    }

    room--; // Adjust for zero-indexing
    printf("Temperature in Room %d is %d°C.\n", room + 1, temperatures[room]);
}

// Detect Motion: Check for motion in any room
void detectMotion(int numRooms) {
    int room;
    printf("Enter room number to check motion (1-%d): ", numRooms);
    scanf("%d", &room);

    if (room < 1 || room > numRooms) {
        printf("Invalid room number.\n");
        return;
    }

    room--; // Adjust for zero-indexing
    if (motionSensors[room] == 1)
        printf("Motion detected in Room %d.\n", room + 1);
    else
        printf("No motion detected in Room %d.\n", room + 1);
}

// Lock/Unlock Security System: Lock or unlock doors
void securitySystem(int numRooms) {
    int room, action;
    printf("Enter room number to lock/unlock (1-%d): ", numRooms);
    scanf("%d", &room);

    if (room < 1 || room > numRooms) {
        printf("Invalid room number.\n");
        return;
    }

    room--; // Adjust for zero-indexing
    printf("Enter action (1 to Lock, 0 to Unlock): ");
    scanf("%d", &action);

    if (action == 1) {
        securityLocks[room] = 1;  // Lock the door
        printf("Room %d is now locked.\n", room + 1);
    } else if (action == 0) {
        securityLocks[room] = 0;  // Unlock the door
        printf("Room %d is now unlocked.\n", room + 1);
    } else {
        printf("Invalid action.\n");
    }
}

// Analyze House Status: Display status of all rooms
void analyzeHouseStatus(int numRooms) {
    printf("\nHouse Status:\n");
    for (int i = 0; i < numRooms; i++) {
        printf("Room %d: Light %s, Temp %d°C, Motion %s, %s\n", 
            i + 1, 
            lights[i] ? "ON" : "OFF", 
            temperatures[i], 
            motionSensors[i] ? "Detected" : "No Motion", 
            securityLocks[i] ? "Locked" : "Unlocked");
    }
}

// Auto-Lock Feature: Lock door if no motion detected for a while
void autoLock(int numRooms) {
    for (int i = 0; i < numRooms; i++) {
        if (motionSensors[i] == 0) {
            motionDetectionCounter[i]++;
            if (motionDetectionCounter[i] >= 5) {
                if (securityLocks[i] == 0) {
                    securityLocks[i] = 1;  // Lock the door automatically
                    printf("Room %d is automatically locked due to no motion.\n", i + 1);
                }
            }
        } else {
            motionDetectionCounter[i] = 0;  // Reset the counter when motion is detected
        }
    }
}

// Temperature Alert: Warn if temperature exceeds 30°C
void temperatureAlert(int numRooms) {
    for (int i = 0; i < numRooms; i++) {
        if (temperatures[i] > 30) {
            printf("Warning: Temperature in Room %d is above 30°C! (%d°C)\n", i + 1, temperatures[i]);
        }
    }
}
