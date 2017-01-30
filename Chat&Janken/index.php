<!--ログイン画面　画面ID : WC101-->

<?php

	/*インクルード*/
	require('define.php');

?>

<html>
	<head>
		<title> Chat - Login </title>
	</head>
	
	<body>
	
		<form action="wc201.php">
	
			<!--Title Name-->
			<p><h1>限定じゃんけん！</h1></p>		
		
			<p>	User1: 	
				<!--名前入力欄-->
				<input type="text" name="u1name">
			</p>
			<p>	User2: 	
				<!--名前入力欄-->
				<input type="text" name="u2name">
			</p>
		
			<!--ログインボタン-->
			<p><input type="submit" value="Login"></p>		
			
			<!--送る引数-->
			<input type="hidden" name="state" value="<?php print STATE_LOGIN ?>" />	

		
		</form>
		
		

	</body>
	
</html>
