https://github.com/user-attachments/assets/daa4f134-dcc8-468e-8ff7-185b17a04c80

https://github.com/user-attachments/assets/d1b1bd8d-7e14-45b7-956c-db5517992cbe

https://github.com/user-attachments/assets/5b39a649-afa1-49eb-bafe-5072adc91c03


communication protocol:


myTeams Communication Protocol Documentation

* Overview:

The myTeams communication protocol streamlines data exchange between system components. It utilizes op codes and fixed-length structures for clear and efficient communication.

* Op Code:

The protocol employs OP_CODE to denote specific operations. Each OP_CODE corresponds to a distinct action within the system, ensuring standardized communication.

* Structures:

- message_t:
Represents a message with sender UUID, timestamp, and body.
Limited to MAX_BODY_LENGTH characters.
- thread_t:
Organizes messages into threads.
** Command-Specific Structures:
Defined for each supported operation, e.g., quit_t, login_t, logout_t, etc.
Each structure contains fields pertinent to its operation.
* Binary File Format:

Data is stored in a binary file format for efficiency. Serialized structures optimize storage and retrieval.

* Data Integrity:

Each binary file includes a 2-byte hash at the end to detect and prevent data corruption.

