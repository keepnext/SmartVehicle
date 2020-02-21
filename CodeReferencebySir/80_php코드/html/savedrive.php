<?php
	$conn = mysqli_connect(
	  'localhost',
	  'root',
	  '1234',
	  'test');

	$strID = $_GET['Id'];
	$iMileage = $_GET['Mil'];
	$fBattery = $_GET['Bat'];
	$strLastLOC = $_GET['Loc'];
	$iOilGauge = $_GET['Oil'];

	$sql = "INSERT INTO CAR_LOG SELECT COUNT(*) + 1, '" . $strID . "','" .  $iMileage . "','" . $fBattery . "','" . $strLastLOC . "','" . $iOilGauge . "'," . "now() FROM CAR_LOG";

	//echo $sql;
	$result = mysqli_query($conn, $sql);

	$result_Query = "SELECT (SELECT COUNT(*) FROM CAR_LOG WHERE strID = '". $strID."'), iMileage FROM CAR_LOG WHERE strID = '" . $strID . "'  ORDER BY idx DESC Limit 1";
	$result = mysqli_query($conn, $result_Query);
	$row = mysqli_fetch_array($result);

	// 그룹에 대한 정보를 저장
	header('Content-Type: application/json');
	header("Content-Type:text/html;charset=utf-8");
	////01. 데이터 만들기
	$groupData = array();
	$groupData["rtn"] = "finish_comment";
	$groupData["enginestopcount"] = $row[0];

	////02. 데이터 안에 데이터 만들기
	$comment = array("avr" => $row["iMileage"] / $row[0], "comment" => "safety!! Good");
	$commentData = array($comment);
	////02-01. 데이터 안에 데이터 넣기
	$groupData["enginestop"] = $commentData;

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
	echo $data_array['enginestopcount']."<br/>";

	foreach ($data_array['enginestop'] as $key => $value){
	    echo $value['avr']."<br/>";
	    echo $value['comment']."<br/>";
	    echo "<br/>";

	};

	// 03. Json 에러내역 보여주기
	if (json_last_error() > 0) {
	    echo json_last_error_msg() . PHP_EOL;
	}
*/
?>
