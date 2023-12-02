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
	std::string name = user.getNickname();
	std::string reply =
		":" + serverName + " 001 " + name + " :Welcome to the Localnet IRC Network\n";

		":" + serverName + " 375 " + name + " :- <server> Message of the day - \n"
		":" + serverName + " 372 " + name + " :                                            /\n"
		":" + serverName + " 372 " + name + " :                         _,.------....___,.' ',.-.\n"
		":" + serverName + " 372 " + name + " :                      ,-'          _,.--\"        |\n"
		":" + serverName + " 372 " + name + " :                    ,'         _.-'              .\n"
		":" + serverName + " 372 " + name + " :                   /   ,     ,'                   `\n"
		":" + serverName + " 372 " + name + " :                  .   /     /                     ``.\n"
		":" + serverName + " 372 " + name + " :                  |  |     .                       \\.\\\n"
		":" + serverName + " 372 " + name + " :        ____      |___._.  |       __               \\ `.\n"
		":" + serverName + " 372 " + name + " :      .'    `---\"\"       ``\"-.--\"'`  \\               .  \\\n"
		":" + serverName + " 372 " + name + " :     .  ,            __               `              |   .\n"
		":" + serverName + " 372 " + name + " :     `,'         ,-\"'  .               \\             |    L\n"
		":" + serverName + " 372 " + name + " :    ,'          '    _.'                -._          /    |\n"
		":" + serverName + " 372 " + name + " :   ,`-.    ,\".   `--'                      >.      ,'     |\n"
		":" + serverName + " 372 " + name + " :  . .'\\'   `-'       __    ,  ,-.         /  `.__.-      ,'\n"
		":" + serverName + " 372 " + name + " :  ||:, .           ,'  ;  /  / \\ `        `.    .      .'/\n"
		":" + serverName + " 372 " + name + " :  j|:D  \\          `--'  ' ,'_  . .         `.__, \\   , /\n"
		":" + serverName + " 372 " + name + " : / L:_  |                 .  \"' :_;                `.'.'\n"
		":" + serverName + " 372 " + name + " : .    \"\"'                  \"\"\"\"\"'                    V\n"
		":" + serverName + " 372 " + name + " :  `.                                 .    `.   _,..  `\n"
		":" + serverName + " 372 " + name + " :    `,_   .    .                _,-'/    .. `,'   __  `\n"
		":" + serverName + " 372 " + name + " :     ) \\`._        ___....----\"'  ,'   .'  \\ |   '  \\  .\n"
		":" + serverName + " 372 " + name + " :    /   `. \"`-.--\"'         _,' ,'     `---' |    `./  |\n"
		":" + serverName + " 372 " + name + " :   .   _  `\"\"'--.._____..--\"   ,             '         |\n"
		":" + serverName + " 372 " + name + " :   | .\" `. `-.                /-.           /          ,\n"
		":" + serverName + " 372 " + name + " :   | `._.'    `,_            ;  /         ,'          .\n"
		":" + serverName + " 372 " + name + " :  .'          /| `-.        . ,'         ,           ,\n"
		":" + serverName + " 372 " + name + " :  '-.__ __ _,','    '`-..___;-...__   ,.'\\ ____.___.'\n"
		":" + serverName + " 372 " + name + " :  `\"^--'..'   '-`-^-'\"--    `-^-'`.''\"\"\"\"\"`.,^.`.--' mh\n\n"

		":" + serverName + " 376 " + name + " :End of message of the day.";

	ft_send(user.getFd(), reply);
}

Auth::Auth(UserInfo &user, std::string serverName) : user(user), serverName(serverName)
{
	if (!isNamesEmpty() && isAllPass())
	{
		user.checkActive();
		sendReplies();
	}
}
