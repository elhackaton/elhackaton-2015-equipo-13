<?php

	require_once("config/db.php");
	require_once("classes/Edit.php");
	$select = new Edit();
	$getData = $select->showSomething("value");
	echo count($getData);	

	for($i = 0; $i <= count($getData); $i++){
		echo "<br>" . $getData[$i];
	}

?>
