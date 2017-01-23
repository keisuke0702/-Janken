#include "SocketImpl.h"

class ChatMain1
{
public:
	//コンストラクタ
	ChatMain1();

	//サーバー関数
	void ChatServer();

	//クライアント関数
	void ChatClient();

	//実行
	void Run();
private:
	SocketImpl mImpl;
};
