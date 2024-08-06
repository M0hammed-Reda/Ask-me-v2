# AskMe Project - (Version 2)

## Project Overview

**AskMe v2** is an enhanced version of the original file-based C++ program designed to facilitate a question-and-answer system where users can ask questions and receive answers from others. This version has been refactored to strictly follow object-oriented programming (OOP) principles, ensuring better encapsulation, modularity, and maintainability. The system supports multiple users simultaneously, retains previous states, and ensures real-time visibility of updates.

## Features

### User Authentication
- **Sign Up**: Users can create a new account by providing their name, email, username, and password.
- **Login/Logout**: Users can log in to access their account and log out when done.
- **Anonymous Questions**: Users can opt to allow or disallow anonymous questions.

### User Operations
- **Print Questions**: Users can print questions directed to them, from them, or view feed questions.
- **Ask Questions**: Users can post questions to others.
- **Answer Questions**: Users can respond to questions posed to them.
- **Delete Questions**: Users can delete their own questions or entire threads.
- **Support for Threads**: Users can answer questions within threads, with each original question acting as a parent for its respective thread.

### System Design
- **Unique IDs**: Each user and question is assigned a unique system-generated ID.
- **Thread Management**: Deleting a parent question will remove the entire thread.
- **Access Control**: Users can only view and edit their own questions. Actions such as removing a question asked to someone else are prohibited.

## Object-Oriented Enhancements

### Classes and Design
- **AskMeSystem**: Manages the overall system state, including user and question management.
- **UserManager**: Handles user-related functionalities including login, signup, and user operations.
- **QuestionManager**: Manages question-related functionalities including asking, answering, and deleting questions.
- **Question**: Represents a question with properties and methods for manipulation.
- **User**: Represents a user with properties and methods for interaction.
- **HelperFunction**: Contains utility functions to assist with various operations.
- **View**: Handles the user interface and interaction.

### OOP Principles Applied
- **Encapsulation**: Private and public sections with appropriate use of setters and getters.
- **Const Correctness**: Functions and parameters use `const` where applicable.
- **Low Coupling**: Minimized dependencies between classes.
- **Separation of Concerns**: View is separated from the model.

## Project Structure

### Files and Directories
- **main.cpp**: Contains the main program logic and user interface.
- **AskMeSystem.h/cpp**: Manages the overall system state.
- **UserManager.h/cpp**: Handles user-related functionalities.
- **QuestionManager.h/cpp**: Manages question-related functionalities.
- **Question.h/cpp**: Represents a question.
- **User.h/cpp**: Represents a user.
- **HelperFunction.h/cpp**: Contains utility functions.
- **View.h/cpp**: Handles the user interface.

## Getting Started

### Prerequisites
- C++ Compiler (e.g., GCC, Clang)
- Standard C++ Library

## Usage

1. **Login or Sign Up**: Start by logging into an existing account or signing up for a new one.
2. **Ask Questions**: Use the interface to post new questions.
3. **Answer Questions**: View and respond to questions directed to you.
4. **Manage Questions**: Print, delete, or view questions and threads as needed.

## Future Enhancements

- **Parallel Session Demo**: A demonstration of parallel sessions will be added in the next update.
- **Enhanced Security**: Improvements to user authentication and data protection.
- **UI Enhancements**: Better user interface for easier navigation and use.

### Acknowledgments
- Special thanks to Mostafa S. Ibrahim for his guidance and project inspiration.

---

Feel free to contribute to this project by forking the repository and submitting pull requests. For any issues or suggestions, please open an issue in the GitHub repository.
