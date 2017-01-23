#ifndef _MESSAGEBUFFER_H_
#define _MESSAGEBUFFER_H_
#include "CriticalSection.h"
#include <deque>
#include <string>
#include <ostream>
// メッセージバッファクラス
class MessageBuffer
{
public:
	// コンストラクタ
	MessageBuffer(unsigned int bufferSize);
	// メッセージを消去
	void clear();
	// メッセージを追加
	void add(const std::string& message);
	// メッセージバッファの出力
	void print(std::ostream& out);
private:
	// メッセージバッファ
	typedef std::deque<std::string> MessageContainer;
	// メッセージバッファ
	MessageContainer mBuffer;
	// メッセージの最大数
	MessageContainer::size_type mBufferSize;
	// バッファ用クリティカルセクション
	CriticalSection mBufferLock;
};
#endif