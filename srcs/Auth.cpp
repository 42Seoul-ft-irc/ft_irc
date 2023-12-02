#include "Auth.hpp"

bool Auth::isNamesEmpty()
{
	if (user.getNickname().empty() || user.getRealname().empty() || user.getUsername().empty())
		return true;

	return false;
}

bool Auth::isAllPass()
{
	if (user.getPass() && user.getNick() && user.getUser())
		return true;

	return false;
}

void Auth::sendReplies()
{
	std::ostringstream oss;
    oss << users.size();
    std::string num = oss.str();

	std::string name = user.getNickname();
	std::string reply =
		":" + user.getHostname() + " 001 " + name + " :Welcome to the Localnet IRC Network\n"
		":" + user.getHostname() + " 002 " + name + " :running version ft_irc-42\n"
		":" + user.getHostname() + " 002 " + name + " :Current local users: " + num + "\n"
		":" + user.getHostname() + " 375 " + name + " :- <server> Message of the day - \n"
		":" + user.getHostname() + " 372 " + name + " :                                            /\n"
		":" + user.getHostname() + " 372 " + name + " :                         _,.------....___,.' ',.-.\n"
		":" + user.getHostname() + " 372 " + name + " :                      ,-'          _,.--\"        |\n"
		":" + user.getHostname() + " 372 " + name + " :                    ,'         _.-'              .\n"
		":" + user.getHostname() + " 372 " + name + " :                   /   ,     ,'                   `\n"
		":" + user.getHostname() + " 372 " + name + " :                  .   /     /                     ``.\n"
		":" + user.getHostname() + " 372 " + name + " :                  |  |     .                       \\.\\\n"
		":" + user.getHostname() + " 372 " + name + " :        ____      |___._.  |       __               \\ `.\n"
		":" + user.getHostname() + " 372 " + name + " :      .'    `---\"\"       ``\"-.--\"'`  \\               .  \\\n"
		":" + user.getHostname() + " 372 " + name + " :     .  ,            __               `              |   .\n"
		":" + user.getHostname() + " 372 " + name + " :     `,'         ,-\"'  .               \\             |    L\n"
		":" + user.getHostname() + " 372 " + name + " :    ,'          '    _.'                -._          /    |\n"
		":" + user.getHostname() + " 372 " + name + " :   ,`-.    ,\".   `--'                      >.      ,'     |\n"
		":" + user.getHostname() + " 372 " + name + " :  . .'\\'   `-'       __    ,  ,-.         /  `.__.-      ,'\n"
		":" + user.getHostname() + " 372 " + name + " :  ||:, .           ,'  ;  /  / \\ `        `.    .      .'/\n"
		":" + user.getHostname() + " 372 " + name + " :  j|:D  \\          `--'  ' ,'_  . .         `.__, \\   , /\n"
		":" + user.getHostname() + " 372 " + name + " : / L:_  |                 .  \"' :_;                `.'.'\n"
		":" + user.getHostname() + " 372 " + name + " : .    \"\"'                  \"\"\"\"\"'                    V\n"
		":" + user.getHostname() + " 372 " + name + " :  `.                                 .    `.   _,..  `\n"
		":" + user.getHostname() + " 372 " + name + " :    `,_   .    .                _,-'/    .. `,'   __  `\n"
		":" + user.getHostname() + " 372 " + name + " :     ) \\`._        ___....----\"'  ,'   .'  \\ |   '  \\  .\n"
		":" + user.getHostname() + " 372 " + name + " :    /   `. \"`-.--\"'         _,' ,'     `---' |    `./  |\n"
		":" + user.getHostname() + " 372 " + name + " :   .   _  `\"\"'--.._____..--\"   ,             '         |\n"
		":" + user.getHostname() + " 372 " + name + " :   | .\" `. `-.                /-.           /          ,\n"
		":" + user.getHostname() + " 372 " + name + " :   | `._.'    `,_            ;  /         ,'          .\n"
		":" + user.getHostname() + " 372 " + name + " :  .'          /| `-.        . ,'         ,           ,\n"
		":" + user.getHostname() + " 372 " + name + " :  '-.__ __ _,','    '`-..___;-...__   ,.'\\ ____.___.'\n"
		":" + user.getHostname() + " 372 " + name + " :  `\"^--'..'   '-`-^-'\"--    `-^-'`.''\"\"\"\"\"`.,^.`.--' mh\n\n"
		":" + user.getHostname() + " 376 " + name + " :End of message of the day.";

	ft_send(user.getFd(), reply);
}

Auth::Auth(UserInfo &user, std::map<int, UserInfo> &users) : user(user), users(users)
{
	if (!isNamesEmpty() && isAllPass())
	{
		user.checkActive();
		sendReplies();
	}
}
