#include "QuestionManager.h"
#include "HelperFunction.h"
#include "User.h"
#include "View.h"
#include <bits/stdc++.h>

// Constructor
QuestionManager::QuestionManager() : last_id(0) {}

// Load data from the database (file)
void QuestionManager::load_data_base() {
    HelperFunction helper_function;

    last_id = 0;
    question_id_to_question_ids_thread.clear();
    question_id_to_QuestionObject.clear();

    std::vector<std::string> lines = helper_function.read_line_from_file("questions.txt");

    for (const auto& line : lines) {
        Question question(line);

        question_id_to_QuestionObject[question.get_qusetion_id()] = question;

        if (question.get_parent_question_id() != -1)
            question_id_to_question_ids_thread[question.get_parent_question_id()].push_back(question.get_qusetion_id());
        else
            question_id_to_question_ids_thread[question.get_qusetion_id()].push_back(question.get_qusetion_id());

        last_id = std::max(last_id, question.get_qusetion_id());
    }
}

std::vector<std::pair<int, int>> QuestionManager::get_user_from_questions(const User& user) const {
    std::vector<std::pair<int, int>> question_ids;

    for (const auto& pair : question_id_to_question_ids_thread) {	// pair<int, vector<Question>>
        for (const auto& question_id : pair.second) {		//  vector<Question>
            // Get the question from the map. & means same in memory, DON'T COPY
            const Question& question = question_id_to_QuestionObject.find(question_id)->second;

            if (question.get_to_user_id() == user.get_user_id()) {
                if (question.get_parent_question_id() == -1)
                    question_ids.push_back(std::make_pair(question.get_qusetion_id(), question.get_qusetion_id()));
                else                       
                    question_ids.push_back(std::make_pair(question.get_parent_question_id(), question.get_qusetion_id()));
            }
        }
    }
    return question_ids;
}


std::vector<int> QuestionManager::get_user_to_questions(const User& user) const {
    std::vector<int> question_ids;

    for (const auto& pair : question_id_to_question_ids_thread) {	// pair<int, vector<Question>>
        for (const auto& question_id : pair.second) {		//  vector<Question>

            // Get the question from the map. & means same in memory, DON'T COPY
            const Question& question = question_id_to_QuestionObject.find(question_id)->second;

            if (question.get_from_user_id() == user.get_user_id())
                question_ids.push_back(question.get_qusetion_id());
        }
    }
    return question_ids;
}


// Print questions to user
void QuestionManager::print_user_to_question(User& user) {
    std::cout << "\n\n";

    if (user.get_question_id_to_question_ids_thread().size() == 0)
        std::cout << "\tNo Questions for this user.\n\n";

    for (const auto& pair : user.get_question_id_to_question_ids_thread()) {
        // Get the question from the map. & means same in memory, DON'T COPY
        // Accessing questionid_questionobject_map[] change the map by adding if not exist. You can't use in const function
        // Here we just find, which return iterator (second is like a pointer to object)
        for (const auto& question_id : pair.second) {
            const Question& question = question_id_to_QuestionObject.find(question_id)->second;
            question.print_to_question();
        }
    }

    std::cout << "\n\n";
}

// Print questions from user
void QuestionManager::print_user_from_question(User& user) {
    std::cout << "\n\n";

    if (user.get_question_id_from_me().size() == 0)
        std::cout << "\tNo Questions for this user.\n\n";

    for (const auto& question_id : user.get_question_id_from_me()) {
        const Question& question = question_id_to_QuestionObject.find(question_id)->second;
        question.print_from_question();
    }

    std::cout << "\n\n";
}

// Ask a question
void QuestionManager::ask_question(User& user, std::pair<int, int>& to_user_pair) {
    View view;
    Question question;
    
    if (!to_user_pair.second) {
        std::cout << "Note: Anonymous questions are not allowed for this user.\n";
        question.set_is_anonymous_questions(to_user_pair.second);
    }
    else {
        std::cout << "Is anonymous questions? (0 or 1): ";
        int is_aq;
        std::cin >> is_aq;
        question.set_is_anonymous_questions(is_aq);
    }

    int thread_id = view.read_question_id_thread(user);
    question.set_parent_question_id(thread_id);

    std::cout << "Enter question text: ";
    std::cin.ignore();
    std::string text;
    getline(std::cin, text);
    question.set_question_text(text);

    int from_id = user.get_user_id();
    question.set_from_user_id(from_id);

    int to_id = to_user_pair.first;
    question.set_to_user_id(to_id);

    question.set_question_id(++last_id);

    question_id_to_QuestionObject[question.get_qusetion_id()] = question;

    if (question.get_parent_question_id() != -1)
        question_id_to_question_ids_thread[question.get_parent_question_id()].push_back(question.get_qusetion_id());
    else
        question_id_to_question_ids_thread[question.get_qusetion_id()].push_back(question.get_qusetion_id());
}

// Answer a question
void QuestionManager::answer_question(User& user, QuestionManager& question_mange) {
    View view;
    int question_id = view.read_question_id(user, question_mange);

    if (question_id == -1)
        return;

    Question& question = question_id_to_QuestionObject[question_id];

    question.print_to_question();

    if (!question.get_answer_text().empty())
        std::cout << "\nWarning: This question is already answered. The answer will be updated...\n";

    std::string answer;
    std::cout << "Enter your answer: ";
    std::cin.ignore();
    getline(std::cin, answer);
    question.set_answer_text(answer);
}

// Delete a question
void QuestionManager::delete_question(User& user, QuestionManager& question_mange) {
    View view;
    int question_id = view.read_question_id(user, question_mange);

    if (question_id == -1)
        return;

    std::vector<int> remove_ids;

    if (question_id_to_question_ids_thread.count(question_id)) {
        remove_ids = question_id_to_question_ids_thread[question_id];
        question_id_to_question_ids_thread.erase(question_id);
    }
    else {
        remove_ids.push_back(question_id);
        for (auto& pair : question_id_to_question_ids_thread) {
            std::vector<int>& vec = pair.second;
            vec.erase(std::remove(vec.begin(), vec.end(), question_id), vec.end());
        }
    }

    for (const auto& id : remove_ids)
        question_id_to_QuestionObject.erase(id);
}

// List feed of answered questions
void QuestionManager::list_feed() const {
    for (const auto& pair : question_id_to_QuestionObject) {
        const Question& question = pair.second;

        if (question.get_answer_text().empty())
            continue;

        question.print_feed_question();
    }
}

// Update database with all questions
void QuestionManager::update_data_base() {
    HelperFunction helper_function;
    std::vector<std::string> lines;

    for (const auto& pair : question_id_to_QuestionObject)
        lines.push_back(pair.second.to_string());

    helper_function.write_line_on_file("questions.txt", lines, false);
}

// Getters and setters
std::map<int, std::vector<int>> QuestionManager::get_question_id_to_question_ids_thread() const {
    return question_id_to_question_ids_thread;
}

void QuestionManager::set_question_id_to_question_ids_thread(std::map<int, std::vector<int>>& mp) {
    question_id_to_question_ids_thread = mp;
}

std::map<int, Question> QuestionManager::get_question_id_to_QuestionObject() const {
    return question_id_to_QuestionObject;
}

void QuestionManager::set_question_id_to_QuestionObject(std::map<int, Question>& mp) {
    question_id_to_QuestionObject = mp;
}

int QuestionManager::get_last_id() const {
    return last_id;
}

void QuestionManager::set_last_id(int& id) {
    last_id = id;
}