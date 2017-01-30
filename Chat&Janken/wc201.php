<?php

/*じゃんけん画面　画面ID : WC201*/

	/*インクルード*/
	require('define.php');
	require('chatlog.php');

	/*名前が入力されてるか？*/
	if($_REQUEST['u1name'] === NULL_NAME){
		//名前が未記入ならエラー画面へ
		header("Location: er001.php");
		exit(0);
	}
	if($_REQUEST['u2name'] === NULL_NAME){
		//名前が未記入ならエラー画面へ
		header("Location: er001.php");
		exit(0);
	}
	
	//入力された名前を代入
	$userName1 = $_REQUEST['u1name'];
	$userName2 = $_REQUEST['u2name'];
	
	$chatlog = new ChatLog();
	if($chatlog->Initialize() === false){
		exit(0);
	}
	
	$state = STATE_NONE;
	if(!empty($_REQUEST['state'])){
		$state = $_REQUEST['state'];
		
		if($state === STATE_LOGIN){
			$systemMessage = "$userName1 Login.";
			$chatlog->Add(SYSTEM_NAME, $systemMessage);
		}
		if($state === STATE_LOGOUT){
			$systemMessage = "$userName1 Logout.";
			$chatlog->Add(SYSTEM_NAME, $systemMessage);
			header("Location: index.php");
			exit(0);
		}
		
		if($state === STATE_LOGIN){
			$systemMessage = "$userName2 Login.";
			$chatlog->Add(SYSTEM_NAME, $systemMessage);
		}
		if($state === STATE_LOGOUT){
			$systemMessage = "$userName2 Logout.";
			$chatlog->Add(SYSTEM_NAME, $systemMessage);
			header("Location: index.php");
			exit(0);
		}
	}
	
	
	$message1 = '';
	$message2 = '';
	//コメントが書き込まれているか？
	if(!empty($_REQUEST['message1'])){
		$message1 = $_REQUEST['message1'];
		$chatlog->Add($userName1, $message1);
	}
	if(!empty($_REQUEST['message2'])) {
		$message2 = $_REQUEST['message2'];
		$chatlog->Add($userName2, $message2);
	}
	
?>


<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>じゃんけん</title>
		
		<link rel="stylesheet" href="style.css" type="text/css">

	</head>

	<body>
		
		<!--コメントを書き込む-->
		<form action="wc201.php">
			<!--送る引数-->
			<input type="hidden" name="u1name" value="<?php print $userName1 ?>" />
			<input type="hidden" name="u2name" value="<?php print $userName2 ?>" />
			<!--名前-->
			<p><?php print $userName1 ?>
			<form action="" method="post">
    			<button type="submit" name="choice" value="1">グー</button>
    			<button type="submit" name="choice" value="2">チョキ</button>
   				<button type="submit" name="choice" value="3">パー</button>
			</form>
			<p><?php print $userName2 ?>
			<!--コメント入力欄-->
			<input type="text" name="message2" size="30" maxlength="30">			
			<!--コメントを書き込む-->
			<input type="submit" value="Write"></p>

		</form>		
		
		<!--コメント欄-->
		
		<div class="frame">
		<p>結果</p>
		
		<p>
		<?php print $userName1?> <?php echo $myChoice?>		
		</div>
			
		<!--横線-->
		<hr>
		
		<!--ログアウト-->		
		<form action="wc201.php">
			<!--ログアウト-->
			<input type="submit" value="Logout"></p>
			<!--送る引数-->
			<input type="hidden" name="u1name" value="<?php print $userName1 ?>" />
			<input type="hidden" name="u2name" value="<?php print $userName2 ?>" />
			<input type="hidden" name="state" value="<?php print STATE_LOGOUT ?>" />
		</form>
		
	</body>
</html>
