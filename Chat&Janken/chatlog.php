<?php



/*チャットログ管理クラス*/
class ChatLog{
	
	//コンストラクタ
	function __construct(){
	
	}
	
	//チャットログの初期化
	//＠戻り値あり　[bool]
	function Initialize(){
		$file = LOG_FILE_NAME;
		
		//ファイルがあるか？
		if(!is_file($file)){
			print ERROR_MESSAGE_NO_FILE;
			return(false);
		}
		
		//ファイルが正常に読み込めるか？
		if(!is_readable($file)){
			print ERROR_MESSAGE_NO_READABLE;
			return(false);
		}
		//ファイルに正常に書き込めるか？
		if(!is_writeable($file)){
			print ERROR_MESSAGE_NO_WRITEABLE;
			return(false);
		}
		
		return(true);
	
	}
	//チャットログを取得
	//＠戻り値あり [連想配列]
	//＠[LOG_DATE] = 日にち
	//＠[LOG_NAME] = ユーザーの名前
	//＠[LOG_MESSAGE] = ユーザーの書き込んだコメント 
	function GetLog(){
		// ファイルを開く
    	$fp = fopen(LOG_FILE_NAME, 'r');
    	if( $fp === false )
      		return(false);

    	// ファイルを読み込む
    	$log = [];
    	while( ($line = fgets($fp)) !== false ){
      		$line = rtrim($line);
      		$buff = explode(',', $line);

      		$log[] = [
          		LOG_DATE => date('Y-m-d H:i:s', $buff[0])
        		, LOG_NAME      => $buff[1]
        		, LOG_MESSAGE   => $buff[2]
      		];
    	}
    	fclose($fp);
    	return($log);
	}
	
	//ログに書き込む
	//＠戻り値なし　[void]
	//＠引数1 : $userName = ユーザーの名前
	//＠引数2 : $message  = ユーザーが書き込んだコメント
	function Add($userName1, $message1){
		$userName1 = $this->Replace($userName1);
		$message1 = $this->Replace($message1);
		
		$str = implode(',', [time(), $userName1, $message1]);
		$str .= PHP_EOL; // PHP_EOL === \n
		
		if($this->Write($str) === false){
			print ERROR_MESSAGE_FAILURE_READ_WRITE;
		}		
	}
	
	function Add2($userName2, $message2){
		$userName2 = $this->Replace($userName2);
		$message2 = $this->Replace($message2);
		
		$str = implode(',', [time(), $userName2, $message2]);
		$str .= PHP_EOL; // PHP_EOL === \n
		
		if($this->Write($str) === false){
			print ERROR_MESSAGE_FAILURE_READ_WRITE;
		}		
	}
	
	//文字列中にカンマや改行があると誤作動を起こしてしまうため
	//	別の文字に置換、または削除をする。
	//＠戻り値あり　[string]
	//＠引数1 : $string = ファイルに書き込む文字列
	private function Replace($string){
		$string = str_replace(',',  '&#44', $string);    // 区切り文字 -> 文字参照
    	$string = str_replace("\n", '<br>', $string);    // ¥n -> <br>
    	$string = str_replace("\r", '',     $string);    // ¥r -> ""
    	return($string);
	}
	
	//ファイルに書き込む
	//＠戻り値あり　[bool]
	//＠引数1 : $string = ファイルに書き込む文字列
	private function Write($string){
		//ファイルを開く
		$fp = fopen(LOG_FILE_NAME, 'a');		
		if($fp === false){
			return(false);
		}
		
		//ロックする
		flock($fp, LOCK_EX);
		
		//書き込み
		$ret = fwrite($fp, $string);
		if($ret === false){
			return(false);
		}
		
		//ロックを解除
		flock($fp, LOCK_UN);
		
		//ファイルを閉じる
		fclose($fp);
		return(true);
		
	}


}

?>
