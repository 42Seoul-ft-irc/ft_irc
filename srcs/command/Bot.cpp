#include "Bot.hpp"

Bot::Bot(Message *msg, UserInfo &user): Command(msg), user(user){
	std::srand(static_cast<unsigned int>(std::time(0)));
 }

void Bot::execute() {
	std::string dinnerMenu = recommendDinnerMenu();
	//:sooyang!root@127.0.0.1
	std::string response = ":" + user.getNickname() + "!" + user.getUsername() + "@" + user.getServername() + " DINNER :"+ dinnerMenu;
	ft_send(user.getFd(), response);
}

std::string Bot::recommendDinnerMenu() {
	std::vector<std::string> menuList;
	menuList.push_back("마라탕");
	menuList.push_back("떡볶이");
	menuList.push_back("등촌칼국수");
	menuList.push_back("쌀국수");
	menuList.push_back("치킨");
	menuList.push_back("피자");
	menuList.push_back("찜닭");

	std::rand();
	int randomIndex = std::rand() % menuList.size();

	return "오늘의 저녁 메뉴는 '" + menuList[randomIndex] + "' 어떠세요?";
}