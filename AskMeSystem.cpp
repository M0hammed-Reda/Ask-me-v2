#include "AskMeSystem.h"
#include "View.h"

void AskMeSystem::reset_currentUser_questions() {
	const User& user = userManager.get_current_user();

	const auto& to_questions = questionManager.get_user_to_questions(user);
	userManager.reset_to_questions(to_questions);

	const auto& from_questions = questionManager.get_user_from_questions(user);
	userManager.reset_from_questions(from_questions);
}

void AskMeSystem::load_data_base(bool fill_user_questions) {
	userManager.load_data_base();
	questionManager.load_data_base();

	if (fill_user_questions) { // first time, waiting for login
		reset_currentUser_questions();
	}
}

void AskMeSystem::run() {
	load_data_base(false);
	View view;
	view.access_system(userManager);
	reset_currentUser_questions();

	while (true) {
		int choice = view.show_read_menu(view.menu());
		load_data_base(true);

		if (choice == 1)
			questionManager.print_user_to_question(userManager.get_current_user());
		else if (choice == 2)
			questionManager.print_user_from_question(userManager.get_current_user());
		else if (choice == 3) {
			questionManager.answer_question(userManager.get_current_user(), questionManager);
			questionManager.update_data_base();
		}
		else if (choice == 4) {
			questionManager.delete_question(userManager.get_current_user(), questionManager);
			reset_currentUser_questions();
			questionManager.update_data_base();
		}
		else if (choice == 5) {
			std::pair<int, int>& to_user_pair = userManager.read_user_id();
			if (to_user_pair.first != -1) {
				questionManager.ask_question(userManager.get_current_user(), to_user_pair);
				questionManager.update_data_base();
			}
		}
		else if (choice == 6)
			userManager.list_user_names_ids();
		else if (choice == 7)
			questionManager.list_feed();
		else
			break;
	}
}