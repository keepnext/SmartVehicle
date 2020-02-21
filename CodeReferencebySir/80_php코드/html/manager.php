<?php 

$order = $_POST['cmd']; 
if($order != NULL)
{
	$conn = mysqli_connect(
	  'localhost',
	  'root',
	  '1234',
	  'test');

	$strID = $_GET['Id'];

	$sql = "INSERT INTO CAR_COMMAND SELECT COUNT(*) + 1, '" . $_POST['id'] . "','" .  $order . "'," . "now() FROM CAR_COMMAND";

	//echo $sql;
	$result = mysqli_query($conn, $sql);

	if ($order == "0"){
		$result = "sended 'engine on'"; 
	}
	else if ($order == "0"){
		$result = "sended 'sended unlock'"; 
	}

}
?> 

<!DOCTYPE html> 
<html lang="ko"> 
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" /> 
	<head>
		<title>V2I Service</title> 
	</head> 
	<body> 
		<h1>HI ONLINE-CAR-MANAGER</h1> 
	<form method="post" action="./manager.php">
		id : <input type="id" name="id">
		command : <input type="radio" name="cmd" value="0" checked="checked"> engine on
			  <input type="radio" name="cmd" value="1"> unlock
		<input type="submit"> 
	</form> 

	<div>
		<?php echo $result; ?>
	</div> 

	</body> 
</html>
