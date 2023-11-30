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
	// todo custom
	std::string str =
		// ":irc.local 251 nickwonlim2222 :There are 0 users and 1 invisible on 1 servers\n"
		// ":irc.local 253 nickwonlim2222 1 :unknown connections"
		// ":irc.local 254 nickwonlim2222 1 :channels formed"
		// ":irc.local 255 nickwonlim2222 :I have 1 clients and 0 servers"
		// ":irc.local 265 nickwonlim2222 :Current local users: 1  Max: 1"
		// ":irc.local 266 nickwonlim2222 :Current global users: 1  Max: 1"
		"375 :- <server> Message of the day - \n"
		"372 :                                            /\n"
		"372 :                         _,.------....___,.' ',.-.\n"
		"372 :                      ,-'          _,.--\"        |\n"
		"372 :                    ,'         _.-'              .\n"
		"372 :                   /   ,     ,'                   `\n"
		"372 :                  .   /     /                     ``.\n"
		"372 :                  |  |     .                       \\.\\\n"
		"372 :        ____      |___._.  |       __               \\ `.\n"
		"372 :      .'    `---\"\"       ``\"-.--\"'`  \\               .  \\\n"
		"372 :     .  ,            __               `              |   .\n"
		"372 :     `,'         ,-\"'  .               \\             |    L\n"
		"372 :    ,'          '    _.'                -._          /    |\n"
		"372 :   ,`-.    ,\".   `--'                      >.      ,'     |\n"
		"372 :  . .'\\'   `-'       __    ,  ,-.         /  `.__.-      ,'\n"
		"372 :  ||:, .           ,'  ;  /  / \\ `        `.    .      .'/\n"
		"372 :  j|:D  \\          `--'  ' ,'_  . .         `.__, \\   , /\n"
		"372 : / L:_  |                 .  \"' :_;                `.'.'\n"
		"372 : .    \"\"'                  \"\"\"\"\"'                    V\n"
		"372 :  `.                                 .    `.   _,..  `\n"
		"372 :    `,_   .    .                _,-'/    .. `,'   __  `\n"
		"372 :     ) \\`._        ___....----\"'  ,'   .'  \\ |   '  \\  .\n"
		"372 :    /   `. \"`-.--\"'         _,' ,'     `---' |    `./  |\n"
		"372 :   .   _  `\"\"'--.._____..--\"   ,             '         |\n"
		"372 :   | .\" `. `-.                /-.           /          ,\n"
		"372 :   | `._.'    `,_            ;  /         ,'          .\n"
		"372 :  .'          /| `-.        . ,'         ,           ,\n"
		"372 :  '-.__ __ _,','    '`-..___;-...__   ,.'\\ ____.___.'\n"
		"372 :  `\"^--'..'   '-`-^-'\"--    `-^-'`.''\"\"\"\"\"`.,^.`.--' mh\n\n"

		"376 :End of message of the day.\r\n";

	const char *msg = str.c_str();

	ft_send(user.getFd(), const_cast<char *>(msg));
}

Auth::Auth(UserInfo &user) : user(user)
{
	if (!isNamesEmpty() && isAllPass())
	{
		user.checkActive();
		sendReplies();
	}
}
