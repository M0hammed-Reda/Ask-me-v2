#pragma once
#include <bits/stdc++.h>
#include "User.h"
#include "QuestionManager.h"

class UserManager;
class View
{
public:
	int show_read_menu(std::vector<std::string> choices);
	int read_int(int low, int high);
	int read_question_id(User& user, QuestionManager& question_mange);
	int read_question_id_thread(User& user);
	void access_system(UserManager& user_manage);
	std::vector<std::string> menu() const;
};
