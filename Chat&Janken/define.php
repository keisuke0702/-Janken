<?php

/*定数定義ファイル*/

//名前が未記入の判定に使う定数
const NULL_NAME = '';

//チャットログを保管するファイルの名前
const LOG_FILE_NAME = 'chatlog.txt';

//ファイルがないときに表示するコメント
const ERROR_MESSAGE_NO_FILE = 'ファイルがない --- 解決策：chatlog.txtを作って';
//ファイルが正常に読み込めないときに表示するコメント
const ERROR_MESSAGE_NO_READABLE = 'ファイルが正常に読み込めない --- 解決策：プロパティのアクセス権を確認';
//ファイルに正常に書き込めないときに表示するコメント
const ERROR_MESSAGE_NO_WRITEABLE = 'ファイルに正常に書き込めない --- 解決策：プロパティのアクセス権を確認';

//ファイル操作中にエラーが起きた時のコメント
const ERROR_MESSAGE_FAILURE_READ_WRITE = 'ファイル操作中にエラーが起きた';

//ログの配列用の添え字 [日にち]
const LOG_DATE = 'date';
//ログの配列用の添え字 [名前]
const LOG_NAME = 'name';
//ログの配列用の添え字 [コメント]
const LOG_MESSAGE = 'message';

//ログイン状態か？
const STATE_LOGIN = 'login';
//ログアウト状態か？
const STATE_LOGOUT = 'logout';
//リフレッシュ状態か？
const STATE_REFRESH = 'refresh';
//書き込み状態か？
const STATE_WRITE = 'write';
//デフォルト状態か？
const STATE_NONE = 'none';

//システムの名前
const SYSTEM_NAME = 'SysOP';

//コメントの最大表示数
const MAX_PRINT_MESSAGE = 15;

?>
