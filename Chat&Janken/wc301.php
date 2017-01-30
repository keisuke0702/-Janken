
<!--過去ログ　画面ID : WC301-->

<?php

	/*インクルード*/
	require('define.php');
	require('chatlog.php');
	
	$chatlog = new ChatLog();
	if($chatlog->Initialize() === false){
		exit(0);
	}

?>

<html>
	<head>
		<title> Chat - History </title>
		<link rel="stylesheet" href="style.css" type="text/css">
	</head>
	
	<body>
	
		<!--Title Name-->
		<p><h1>Chat History</h1></p>	
		
		<!--更新-->
		<form action="wc301.php">
			<!--更新-->
			<input type="submit" value="Refresh">
		</form>
		
		<!--コメント欄-->
		
		<div class="frame">
		
		<?php
			$log = $chatlog->GetLog();
			$length = count($log);
			
			if($length >= 1){
    			for($i=0; $i < $length; $i++){
    				if($log[$i][LOG_NAME] === SYSTEM_NAME){ 
    				    	?>
    				   <a class="systemName"><?php print $log[$i][LOG_NAME] ?></a>
     				   <a class="systemMessage"><?php print $log[$i][LOG_MESSAGE] ?></a>
     				   <a class="date">  (<?php print $log[$i][LOG_DATE] ?>)</a>			  
    						<?php
    				}else{
    						?>
    				   <a class="userName"><?php print $log[$i][LOG_NAME] ?></a>
     				   <a class="userMessage"><?php print $log[$i][LOG_MESSAGE] ?></a>
     				   <a class="date">  (<?php print $log[$i][LOG_DATE] ?>)</a>	
    						<?php
    				}

					
					   				 			
					//<!--横線-->
					print "<hr>";		
   				 }			

			}			
		?>
		
		</div>
		
		
		<!--更新-->
		<form action="wc301.php">
			<!--更新-->
			<input type="submit" value="Refresh">
		</form>		

		<!--ログアウト-->		
		<form action="wc201.php">
			<!--ログアウト-->
			<input type="submit" value="Close" onclick="window.close();">
		</form>		
		

	</body>
	
</html>
