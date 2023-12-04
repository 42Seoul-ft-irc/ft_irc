#include "Bot.hpp"

Bot::Bot(Message *msg, UserInfo &user): Command(msg), user(user){
	
}

void Bot::execute() {
	// 오늘의 저녁 메뉴를 추천하고 출력
	std::string dinnerMenu = recommendDinnerMenu();
	std::string response = "PRIVMSG " + user.getNickname() + " :" + dinnerMenu;
	ft_send(user.getFd(), response);
}

// 오늘의 저녁 메뉴 추천 함수
std::string Bot::recommendDinnerMenu() {
	// 간단한 메뉴 리스트
	std::vector<std::string> menuList;
	menuList.push_back("마라탕");
	menuList.push_back("떡볶이");
	menuList.push_back("등촌칼국수");
	menuList.push_back("쌀국수");
	menuList.push_back("치킨");
	menuList.push_back("피자");
	menuList.push_back("찜닭");

	// 현재 시간을 이용하여 랜덤하게 메뉴를 선택
	std::srand(static_cast<unsigned int>(std::time(0)));
	int randomIndex = std::rand() % menuList.size();

	return "오늘의 저녁 메뉴는 '" + menuList[randomIndex] + "' 어떠세요?";
}