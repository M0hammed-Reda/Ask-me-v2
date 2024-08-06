#pragma once
#include <bits/stdc++.h>
class User
{
private:
	int user_id;
	std::string user_name;
	std::string password;
	std::string name;
	std::string email;
	int allow_anonymous_questions;

	std::vector<int> question_id_from_me;
	std::map<int, std::vector<int>> question_id_to_question_ids_thread;

public:
	User();
	User(std::string line);
	std::string to_string() const;
	void print() const;
	void reset_to_questions(const std::vector<int>& to_questions);
	void reset_from_questions(const std::vector<std::pair<int, int>>& to_questions);

	int get_user_id() const;
	void set_user_id(int& id);

	std::string get_user_name() const;
	void set_user_name(std::string& _user_name);

	std::string get_password() const;
	void set_password(std::string& _password);

	std::string get_name() const;
	void set_name(std::string& _name);

	std::string get_email() const;
	void set_email(std::string& _email);

	int get_allow_anonymous_questions() const;
	void set_allow_anonymous_questions(int& allow_aq);

	std::vector<int>& get_question_id_from_me() ;
	void set_question_id_from_me(std::vector<int>& vec);

	std::map<int, std::vector<int>>& get_question_id_to_question_ids_thread();
	void set_question_id_to_question_ids_thread(std::map<int, std::vector<int>>& mp);
};
