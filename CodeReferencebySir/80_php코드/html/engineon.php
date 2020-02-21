<?php
	$conn = mysqli_connect(
	  'localhost',
	  'root',
	  '1234',
	  'test');

	$strID = $_GET['Id'];
	$result_Query = "SELECT (SELECT COUNT(*) FROM CAR_COMMAND WHERE strID = '" . $strID . "'), strCOMMAND FROM CAR_COMMAND WHERE strID = '" . $strID . "' AND dtCreateTime >= DATE_ADD(NOW(), INTERVAL -1 MINUTE) ORDER BY idx DESC";

//echo $result_Query;

	$result = mysqli_query($conn, $result_Query);
	$row = mysqli_fetch_array($result);

	// 그룹에 대한 정보를 저장
	header('Content-Type: application/json');
	header("Content-Type:text/html;charset=utf-8");
	////01. 데이터 만들기
	$groupData = array();
	$groupData["rtn"] = "command";
	$groupData["commandcount"] = $row[0];

	////02. 데이터 안에 데이터 만들기
	$return_data = array();
	$return_data[] = array("cnt" => $row[0], "CMD" => $row[1]);
	while($row = mysqli_fetch_array($result))
	{
		$return_data[] = array("cnt" => $row[0], "CMD" => $row[1]);
	}
	$commandData = array($return_data);
	////02-01. 데이터 안에 데이터 넣기
	$groupData["commandList"] = $commandData;

	////03.  Json으로 만들기     // JSON Array가 포함된 Object를 문자열로 변환
	$output =  json_encode($groupData);

	echo $output;
/* 
test
	//   01. Json 데이터 배열로 담기
	$json_string = $output;
	$data_array = json_decode($json_string, true);

	//   02. JSon 데이터 뿌리기
	echo $data_array['rtn']."<br/>";
	echo $data_array['commandcount']."<br/>";

	foreach ($data_array['commandList'] as $key => $value){
	    echo $value['cnt']."<br/>";
	    echo $value['CMD']."<br/>";
	    echo "<br/>";

	};

	// 03. Json 에러내역 보여주기
	if (json_last_error() > 0) {
	    echo json_last_error_msg() . PHP_EOL;
	}
*/
?>
