<?php
	$szPID= $_REQUEST["PID"];
	$nCommandCode= $_REQUEST["apiKey"];
	$result = "RESULT_".$szPID;
?>
----- RESULT ------
<RESULT><?=$result?></RESULT>
<COMMAND><?=$nCommandCode?></COMMAND>
