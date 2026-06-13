# online-election-system-c
A command-line online election system in C featuring voter authentication, vote tracking, file handling, result generation, progress saving, and election analytics.

## Overview

The Online Election System is a command-line voting application developed in C that simulates a secure digital voting process.

The system allows registered voters to log in using their credentials, cast a vote for their preferred candidate, and ensures that each voter can vote only once. The application also maintains voting records, logs system activities, saves progress automatically, and generates election results.

This project was developed to strengthen programming skills in file handling, authentication systems, data persistence, and real-world application design.

## Features

* Voter authentication using ID and password
* One-person-one-vote enforcement
* Candidate selection and vote casting
* Automatic vote counting
* Election result generation
* Vote percentage calculation
* Activity logging with timestamps
* Progress saving and recovery
* Duplicate vote prevention
* Invalid login tracking
* Leaderboard generation
* Voter status tracking

## Technologies Used

* C Programming Language
* Standard C Libraries

  * stdio.h
  * string.h
  * time.h
  * stdlib.h

## Concepts Practiced

* File Handling
* Authentication Systems
* Arrays and Strings
* Functions
* Data Persistence
* Logging Systems
* Voting Algorithms
* Input Validation
* Menu-Based Logic
* Election Data Management

## System Workflow

1. Voter enters their ID and password.
2. System verifies credentials.
3. Authenticated voter selects a candidate.
4. Vote is recorded securely.
5. System prevents duplicate voting.
6. Results and voter status are updated.
7. Logs and progress files are saved automatically.
8. Final leaderboard is generated after voting ends.

## Generated Files

The application automatically creates and updates:

| File             | Purpose                        |
| ---------------- | ------------------------------ |
| progress.txt     | Stores voting progress         |
| voter_status.txt | Tracks voting status of voters |
| results.txt      | Stores election results        |
| leaderboard.txt  | Displays final rankings        |
| log.txt          | Records system activities      |

## How to Run

### Compile

```bash
gcc main.c -o election
```

### Run

```bash
./election
```

## Sample Candidates

```text
1. Imran
2. Nawaz
3. Altaf
```

## Security Features

* Login authentication
* Duplicate vote prevention
* Invalid credential tracking
* Vote activity logging
* Progress recovery after restart

## Future Improvements

* Dynamic voter registration
* Admin dashboard
* Password encryption
* Graphical User Interface (GUI)
* Database integration
* Online networking support
* Candidate management system

## Learning Outcomes

This project helped strengthen understanding of:

* File handling in C
* Authentication mechanisms
* Logging and auditing systems
* Data persistence techniques
* Election system design
* Real-world problem solving

## Author

Developed as an academic project to explore voting system implementation and file handling concepts using C.
